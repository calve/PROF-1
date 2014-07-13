/**
 * \file main.c
 * \brief Programme de Rendu Officieux de Fichiers
 * \author Carette Antonin
 * \version 0.1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zip.h>
#include <curl/curl.h>
#include <assert.h>
#include <errno.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <dirent.h>

/**
 * \def FALSE
 * \brief Macro permettant d'associer le bit 0 à FALSE
 */
#define FALSE 0

/**
 * \def TRUE
 * \brief Macro permettant d'associer le bit 1 à TRUE
 */
#define TRUE 1

/** 
  * \def LONGUEUR_ID
  * \brief Macro concernant la longueur maximale d'un identifiant étudiant - ici: 20 caractères
  */
#define LONGUEUR_ID 20

/**
 * \def LONGUEUR_MDP
 * \brief Macro concernant la longueur maximale d'un mot-de-passe étudiant - ici: 15 caractères
 */
#define LONGUEUR_MDP 15

/**
 * \def URL
 * \brief Macro contenant l'URL de la plateforme PROF
 */
#define URL_PROF "https://prof.fil.univ-lille1.fr"

/**
 * \def DEBUG
 * \brief Macro permettant d'initialiser d'autres macros, selon le bit attribué au debuggage du programme
 */
#ifdef NDEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif

 struct zip;

/**
 * \fn static void supprimerSuite(char caractereRecherche)
 * \brief Fonction permettant de contourner le problème du buffer vide / trop plein
 *
 * \param caractereRecherche Le caractère recherché (le même que la fonction supprimeCaractere si utilisation)
 */
static void supprimerSuite(char caractereRecherche) {

	int caractere;

	while ((caractere = getchar()) != caractereRecherche && caractere != EOF) 
		{}

}

/**
 * \fn static void supprimeCaractere(char* ligne, char caractere)
 * \brief Fonction permettant de rechercher un caractère dans une chaîne de caractères, et de supprimer ce qui suit celui-ci
 *
 * \param ligne La chaîne de caractères dans laquelle on voudra rechercher le caractère
 * \param caractere Le caractère que l'on voudra rechercher dans la chaîne de caractères
 */
static void supprimeCaractere(char* ligne, char caractere) {

	/*
	On recherche après le caractère donné en paramètre, dans la chaîne de caractères
	*/
	char *saut = strchr(ligne, caractere);

	if (saut)
		*saut = 0;
	else
		supprimerSuite(caractere);

}

/**
 * \fn static void demandeLogin(char* idFIL)
 * \brief Fonction permettant de demander le login de l'utilisateur
 *
 * \param idFIL Une chaîne de caractères (20 caractères), destinée à recevoir le login de l'utilisateur
 */
static void demandeLogin(char* idFIL) {
	
	printf("Entrez votre identifiant FIL:");
	fgets(idFIL, LONGUEUR_ID, stdin);
	supprimeCaractere(idFIL, '\n');

}

/**
 * \fn static void demandeMDP(char* mdpFIL)
 * \brief Fonction permettant de demander le mot-de-passe associé au login de l'utilisateur
 *
 * \param mdpFIL Une chaîne de caractères (15 caractères), destinée à recevoir le mot-de-passe de l'utilisateur
 */
static void demandeMDP(char* mdpFIL) {

	printf("Entrez votre mot de passe FIL:");
	fgets(mdpFIL, LONGUEUR_MDP, stdin);
	supprimeCaractere(mdpFIL, '\n');

}

/**
 * \fn static long tailleFichier(char* cheminFichier)
 * \brief Fonction permettant d'obtenir la taille d'un fichier
 *
 * \param cheminFichier Le chemin du fichier pour lequel on veut connaitre la taille
 * \return La taille du fichier - format long
 */ 
static long tailleFichier(char* cheminFichier) {

    long size = 0;
 
    FILE *fichier=fopen(cheminFichier,"rb");
 
    if(fichier != NULL)
    {
            fseek (fichier, 0, SEEK_END);
            size=ftell (fichier);
            fclose (fichier);          
    }
    return size;

}

/**
 * \fn static int ajouterDansZip(const char* cheminFichier, struct zip *fichierZip)
 * \brief Fonction permettant d'ajouter un fichier/répertoire, dans un zip
 *
 * \param cheminFichier Le chemin du fichier/répertoire à ajouter
 * \param fichierZip Le fichier zip dans lequel on ajoutera tous les fichiers et sous-dossiers de celui pointé par cheminFichier
 * \return Retourne un entier: 0 si l'action zip à bien fonctionner, EXIT_FAILURE si le répertoire/fichier n'a pu etre zippé
 */
static int ajouterDansZip(const char* cheminFichier, struct zip *fichierZip) {

	struct zip_source *source = NULL;
	DIR* repertoire = NULL;
	struct dirent *structRepert = NULL;

	printf("cheminActuel: %s\n",cheminFichier);

	repertoire = opendir(cheminFichier);

	if (repertoire == NULL) {
		printf("ERREUR: Répertoire NULL, dans ajouterDansZip()\n");
		exit(EXIT_FAILURE);
	}

	if (fichierZip == NULL) {
		printf("ERREUR: fichierZip NULL\n");
		exit(EXIT_FAILURE);
	}

	do {
		if ((structRepert = readdir(repertoire)) != NULL) {

			char* cheminAAjouter = malloc(sizeof(char) * PATH_MAX);

			/*
			Chemin vers fichier/répertoire
			*/
			cheminAAjouter = strcpy(cheminAAjouter, cheminFichier);
			/*
			TODO: Vérifier si le "/" n'est pas déjà mis...
			*/
			cheminAAjouter = strcat(cheminAAjouter, "/");
			cheminAAjouter = strcat(cheminAAjouter, structRepert->d_name);

			char* dname = structRepert->d_name;

			printf("cheminAAjouter: %s\n",cheminAAjouter);

			if (strcmp(dname, ".")  == 0 || strcmp(dname, "..") == 0)
				continue;

			/*
			Si fichier -> On prend tout le contenu de celui-ci dans un buffer, compression, on ajoute, on libère la mémoire du buffer
			*/
			if (structRepert->d_type == DT_REG) {
				if ((source = zip_source_file(fichierZip, cheminAAjouter, (off_t)0, (off_t)0)) == 0) {
					printf("ERREUR: Ajout de source impossible dans le fichier zip");
					exit(EXIT_FAILURE);
				};
				/*
				Ajout du fichier cheminAAjouter dans zipAAjouter, qui lui meme sera ajouté dans fichierZip - on garde l'encodag UTF-8
				*/
				zip_file_add(fichierZip, dname, source, ZIP_FL_ENC_UTF_8);
			}
			else {
				/*
				Ajout du répertoire dans le zip, et tout ce qui l'accompagne
				*/
				zip_dir_add(fichierZip, dname, ZIP_FL_ENC_UTF_8);
				ajouterDansZip(cheminAAjouter, fichierZip);
			}
		}
	}
	while (structRepert != NULL);

	closedir(repertoire);	

	return 0;
}

/**
 * \fn static int verificationChemin(char* cheminFichier)
 * \brief Fonction permettant de vérifier le chemin passé en paramètre - c'est-à-dire de vérifier si le chemin existe réellement
 *
 * \param cheminFichier Le chemin du fichier/répertoire à vérifier
 * \return Retourne un entier: EXIT_SUCCESS si le chemin est correct, EXIT_FAILURE s'il ne l'est pas
 */
static int verificationChemin(char* cheminFichier) {

	DIR* repertoire = NULL;
	repertoire = opendir(cheminFichier);
	
	printf("Vérification de l'existence du répertoire/fichier %s\n",cheminFichier);

	/*
	Si problème sur l'ouverture du répertoire, on averti l'utilisateur
	*/
	if (repertoire == NULL) {
		if (errno == ENOTDIR) {
			printf("Fichier trouvé\n");
			closedir(repertoire);
			return 0;
		}
		else {
			printf("ERREUR: Répertoire non trouvé pour %s\n",cheminFichier);
			closedir(repertoire);
			exit(EXIT_FAILURE);
		}
		
	}
	else {
		printf("Répertoire %s trouvé\n", cheminFichier);
		closedir(repertoire);
		return 0;
	}
}

/**
 * \fn static int estArchiveZip(char* cheminFichierDonne)
 * \brief Fonction permettant de vérifier si le fichier/répertoire donné en paramètre est déjà zippé ou non
 *
 * \param cheminFichierDonne Le chemin du fichier/répertoire à vérifier
 * \return Retourne un entier: 0 s'il s'agit d'un fichier/répertoire non-zippé, 1 sinon
 */
static int estArchiveZip(char* cheminFichierDonne) {

	char* ext = "";

	/*
	Vérification de l'extension du fichier
	*/
	ext = strrchr(cheminFichierDonne, '.');

	if (ext != NULL)
		if (strcmp(ext, ".zip") == 0) {
			printf("Le fichier donné en entré est une archive Zip... Pas de compression prévue!\n");
			return 1;
		}

	return 0;

}

/**
 * \fn static int verificationZip(char* cheminFichier)
 * \brief Fonction permettant de vérifier si le fichier/répertoire passé en paramètre est déjà zippé ou non - s'il ne l'est pas, on le fait
 *
 * \param cheminFichier Le chemin du fichier/répertoire à vérifier
 * \return Retourne un entier: 0 si le fichier a bien été zippé / est déjà zippé, EXIT_FAILURE s'il ne l'est pas
 */
static int verificationZip(char* cheminFichier) {

	int err = 0;
	struct zip *fichierZip = NULL;
	char* constCheminFichier = malloc(sizeof(char) * tailleFichier(cheminFichier));
	
	/*
	 *Si le fichier est donné sous format .zip, celà ne nécessite pas de continuer,
	 *sinon on va créer l'archive en apposant le .zip à la fin du chemin donné
	 */
	strcpy(constCheminFichier, cheminFichier);
	if (estArchiveZip(constCheminFichier) == 0)
		constCheminFichier = strcat(constCheminFichier, ".zip");
	else
		return 0;

	/*
	On ne crée pas l'archive si et seulement si elle existe
	*/
	fichierZip = zip_open(constCheminFichier, ZIP_EXCL|ZIP_CREATE, &err);

	printf("Vérification concernant la compression Zip...\n");

	if (fichierZip == NULL) {
		/*
		Le pathname est nul
		*/
		if (err == ZIP_ER_INVAL) {
			printf("ERREUR: Chemin non-trouvé - verificationZip()\n");
			exit(EXIT_FAILURE);
		};

		if (err == ZIP_ER_NOENT) {
			printf("ERREUR: Chemin non-existant - verificationZip()\n");
			exit(EXIT_FAILURE);
		};
		if (err == ZIP_ER_EXISTS) {
			printf("WARNING: Le fichier zip existe déjà...\n");
			return 0;	
		}

		printf("ERREUR: Ouverture du fichier impossible...\n");
		exit(EXIT_FAILURE);
	}
	
	printf("CréerZip()\n");
	if (ajouterDansZip(cheminFichier, fichierZip) == 0)
		zip_close(fichierZip);
	else {
		exit(EXIT_FAILURE);
	}
	
	return 0;

}

/**
 * \fn static int demandeChemin(char *cheminFichier)
 * \brief Fonction permettant de demander le chemin du dossier/fichier
 *
 * \param cheminFichier Une chaine de caractères (PATH_MAX max), destinée à recevoir le chemin donné au dossier/fichier
 * \return Retourne un entier: EXIT_SUCCESS si la fonction a bien été exécuté, EXIT_FAILURE si erreur
 */
static int demandeChemin(char *cheminFichier) {

	char* cheminEntre = malloc(sizeof(char) * PATH_MAX);
	struct passwd* passwdEnt = getpwuid(getuid());
	char* home = passwdEnt->pw_dir;

	home = strcat(home, "/");

	printf("Entrez le chemin du fichier/dossier à transférer sur PROF (sans .zip):\n");
	printf("%s",home);
	fgets(cheminEntre, PATH_MAX, stdin);
	supprimeCaractere(cheminEntre, '\n');
	cheminFichier = strcat(home, cheminEntre);

	/*
	Vérification chemin + zip
	*/
	if (verificationChemin(cheminFichier) == 0) {
		if (verificationZip(cheminFichier) == 0)
			return 0;
		else 
			exit(EXIT_FAILURE);
	}
	else
		exit(EXIT_FAILURE);
}

/** 
 * \fn int main()
 * \brief Main du programme PROF
 *
 * \return Retour système: EXIT_SUCCESS si le programme se termine correctement, EXIT_FAILURE sinon...
 */
int main() {

	char identifiantFIL[LONGUEUR_ID];
	char motDePasseFIL[LONGUEUR_MDP];
	char cheminFichier[PATH_MAX] = "~/";
	CURL *curl;
	
	printf("Bienvenue sur Prof!\n");
	
	demandeLogin(identifiantFIL);

	demandeMDP(motDePasseFIL);

	demandeChemin(cheminFichier);

	/*
	Connection sur PROF (prof.fil.univ-lille1.fr) avec ID + MDP
	*/

	printf("Demande de login...\n");

	curl = curl_easy_init();
	
	/*
	Début de connexion
	*/

	assert(curl);

	/*
	Connexion OK
	*/

	curl_easy_setopt(curl, CURLOPT_URL, URL_PROF);
	curl_easy_setopt(curl, CURLOPT_VERBOSE, DEBUG);

	/*
	Connexion perdue -> On redemande la combinaison ID + MDP
	*/
	
	/*
	Demande de la matière
	*/
	
	/*
	Si chemin vers dossier, on zip le tout, on renomme et on envoie; sinon, on envoie
	*/

	/*
	Envoi!
	*/
	
	curl_easy_cleanup(curl);

	exit(EXIT_SUCCESS);

}