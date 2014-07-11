/**
 * \file main.c
 * \brief Programme de Rendu Officieux de Fichiers
 * \author Carette Antonin
 * \version 0.1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <dirent.h>


#include <curl/curl.h>
#include <zip.h>

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

	FILE *fichier;
    long size;
 
    fichier=fopen(cheminFichier,"rb");
 
    if(fichier)
    {
            fseek (fichier, 0, SEEK_END);
            size=ftell (fichier);
            fclose (fichier);          
    }
    return size;

}

/**
 * \fn static void lireFichier(char* cheminFichier, char* data)
 * \brief Fonction permettant de lire et copier le contenu du fichier cheminFichier, dans data
 *
 * \param cheminFichier Le chemin du fichier que l'on veut lire
 * \param data La structure de données représentant les données contenues dans cheminFichier
 */
static void lireFichier(char* cheminFichier, char* data) {

	char caractere;
	int i = 0;
	FILE *fichier = fopen(cheminFichier, "r");
	while ((caractere = fgetc(fichier)) != EOF) {
		data[i] = caractere;
		i++;
	};
	fclose(fichier);

}

/**
 * \fn static int creerZip(char* cheminFichier, struct zip *fichierZip)
 * \brief Fonction permettant de créer un zip selon le chemin donné en paramètre
 *
 * \param cheminFichier Le chemin du fichier/répertoire à zipper
 * \param fichierZip Le fichier zip dans lequel on ajoutera tous les fichiers et sous-dossiers de celui pointé par cheminFichier
 * \return Retourne un entier: EXIT_SUCCESS si le zip à bien fonctionner, EXIT_FAILURE si le répertoire/fichier n'a pu etre zippé
 */
static int creerZip(const char* cheminFichier, struct zip *fichierZip) {

	char* cheminAAjouter = malloc(sizeof(char) * PATH_MAX);
	struct zip_source *source = NULL;
	DIR* repertoire = NULL;
	struct dirent *structRepert = NULL;
	char* data = "";

	repertoire = opendir(cheminFichier);

	do {
		if ((structRepert = readdir(repertoire)) != NULL)
			/*
			Chemin vers fichier/répertoire
			*/
			cheminAAjouter = strcpy(cheminAAjouter, cheminFichier);
			/*
			TODO: Vérifier si le "/" n'est pas déjà mis...
			*/
			cheminAAjouter = strcat(cheminAAjouter, "/");
			cheminAAjouter = strcat(cheminAAjouter, structRepert->d_name);
			/*
			Si fichier -> On prend tout le contenu de celui-ci dans un buffer, compression, on ajoute, on libère la mémoire du buffer
			*/
			if (structRepert->d_type == DT_REG) {
				long taille = tailleFichier(cheminAAjouter);
				data = malloc(sizeof(char) * taille);
				lireFichier(cheminAAjouter, data);
				source = zip_source_buffer(fichierZip, data, taille, 0);
				/*
				Ajout du fichier cheminAAjouter dans zipAAjouter, qui lui meme sera ajouté dans fichierZip - on garde l'encodag UTF-8
				*/
				zip_file_add(fichierZip, structRepert->d_name, source, ZIP_FL_ENC_UTF_8);
				free(data);
			}
			else
				/*
				Ajout du répertoire en entier
				*/
				zip_dir_add(fichierZip, structRepert->d_name, ZIP_FL_ENC_UTF_8);
	}
	while (structRepert != NULL);

	closedir(repertoire);	

	exit(EXIT_SUCCESS);

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
	
	/*
	Si problème sur l'ouverture du répertoire, on averti l'utilisateur
	*/
	if (repertoire == NULL) {
		printf("ERREUR: Répertoire non trouvé pour %s",cheminFichier);
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}

/**
 * \fn static int verificationZip(char* cheminFichier)
 * \brief Fonction permettant de vérifier si le fichier/dossier passé en paramètre est déjà zippé ou non - s'il ne l'est pas, on le fait
 *
 * \param cheminFichier Le chemin du fichier/répertoire à vérifier
 * \return Retourne un entier: EXIT_SUCCESS si le fichier a bien été zippé / est déjà zippé, EXIT_FAILURE s'il ne l'est pas
 */
static int verificationZip(char* cheminFichier) {

	int err = 0;
	struct zip *fichierZip = NULL;
	const char* constCheminFichier = strcpy(constCheminFichier, cheminFichier);

	fichierZip = zip_open(cheminFichier, ZIP_EXCL, &err);

	/*
	Le fichier existe déjà en version zippé - on s'arrete là pour la vérification
	*/
	if (&err == ZIP_ER_EXISTS) {
		printf("Fichier déjà zippé\n");
		exit(EXIT_SUCCESS);
	}
	/*
	Le fichier/répertoire n'est pas zippé - on le zippe
	*/
	if (&err == ZIP_ER_NOZIP)
		if (creerZip(constCheminFichier, fichierZip) == EXIT_FAILURE)
			exit(EXIT_FAILURE);
	else
		exit(EXIT_FAILURE);

	exit(EXIT_SUCCESS);

}

/**
 * \fn static int demandeChemin(char *cheminFichier)
 * \brief Fonction permettant de demander le chemin du dossier/fichier
 *
 * \param cheminFichier Une chaine de caractères (PATH_MAX max), destinée à recevoir le chemin donné au dossier/fichier
 * \return Retourne un entier: EXIT_SUCCESS si la fonction a bien été exécuté, EXIT_FAILURE si erreur
 */
static int demandeChemin(char *cheminFichier) {

	char* cheminEntre = "";

	printf("Entrez le chemin du fichier/dossier à transférer sur PROF:\n");
	printf("~/");
	fgets(cheminEntre, PATH_MAX, stdin);
	strcat(cheminFichier, cheminEntre);
	supprimeCaractere(cheminFichier, '\n');
	if (verificationChemin(cheminFichier)) {
		if(verificationZip(cheminFichier))
			exit(EXIT_SUCCESS);
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