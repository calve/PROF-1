/**
 * \file main.c
 * \brief Programme de Rendu Officieux de Fichiers
 * \author Carette Antonin
 * \version 0.1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

	//On recherche après le caractère donné en paramètre, dans la chaîne de caractères
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
 * \fn int main()
 * \brief Main du programme PROF
 *
 * \return Entier valant le retour de l'exécution de la fonction: 0 si le programme se termine correctement, autre sinon...
 */
int main() {

	char identifiantFIL[LONGUEUR_ID];
	char motDePasseFIL[LONGUEUR_MDP];
	
	printf("Bienvenue sur Prof!\n");
	
	demandeLogin(identifiantFIL);

	demandeMDP(motDePasseFIL);

	//Connection sur PROF (prof.fil.univ-lille1.fr) avec ID + MDP

	printf("Attente de login...\n");
	printf("Login: %s\n",identifiantFIL);
	printf("Mdp: %s\n",motDePasseFIL);

	//Connection ok -> On continue
	//Connection perdue -> On redemande la combinaison ID + MDP

	//Demande de matière

	//Demande de chemin du TP

	//Envoi!

	return 0;

}