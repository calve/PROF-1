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
#include <curl/curl.h>

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
 * \fn void demandeMDP(char* mdpFIL)
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
 * \fn int verificationChemin(char* cheminFichier)
 * \brief Fonction permettant de vérifier le chemin passé en paramètre - c'est-à-dire de vérifier si le chemin existe réellement
 *
 * \param cheminFichier Le chemin du fichier/répertoire à vérifier
 * \return Retourne un entier: 0 si le chemin est correct, 1 s'il ne l'est pas
 */
static int verificationChemin(char* cheminFichier) {

}

/**
 * \fn int verificationZip(char* cheminFichier)
 * \brief Fonction permettant de vérifier si le fichier/dossier passé en paramètre est déjà zippé ou non - s'il ne l'est pas, on le fait
 *
 * \param cheminFichier Le chemin du fichier/répertoire à vérifier
 * \return Retourne un entier: 0 si le fichier a bien été zippé / est déjà zippé, 1 s'il ne l'est pas
 */
static int verificationChemin(char* cheminFichier) {

}

/**
 * \fn int demandeChemin(char *cheminFichier)
 * \brief Fonction permettant de demander le chemin du dossier/fichier
 *
 * \param cheminFichier Une chaine de caractères (PATH_NAME max), destinée à recevoir le chemin donné au dossier/fichier
 * \return Retourne un entier: 0 si la fonction a bien été exécuté, 1 si erreur
 */
static int demandeChemin(char *cheminFichier) {

	char* cheminEntre = "";

	printf("Entrez le chemin du fichier/dossier à transférer sur PROF:\n");
	printf("~/");
	fgets(cheminEntre, PATH_NAME, stdin);
	strcat(cheminFichier, cheminEntre);
	supprimeCaractere(cheminFichier, '\n');
	if (verificationChemin(cheminFichier)) {
		if(verificationZip(cheminFichier))
			return 0;
		else 
			return 1;
	}
	else
		return 1;

}

/** 
 * \fn int main()
 * \brief Main du programme PROF
 *
 * \return Entier valant le retour de l'exécution de la fonction: 0 si le programme se termine correctement, autre sinon...
 */
int main() {

	char identifiantFIL[LONGUEUR_ID];
	char motDePasseFIL[LONGUEUR_MDP];
	char cheminFichier[PATH_NAME] = "~/";
	CURL *curl;
	CURLcode ccode;
	
	printf("Bienvenue sur Prof!\n");
	
	demandeLogin(identifiantFIL);

	demandeMDP(motDePasseFIL);

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

	/*
	Demande du chemin où se trouve le TP
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

	return 0;

}