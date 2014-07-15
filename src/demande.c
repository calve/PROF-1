/**
 * \file demande.c
 * \brief Module de demande de login/mot-de-passe
 * \author Carette Antonin
 * \version 0.1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <limits.h>
#include "suppr.h"

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
 * \fn void demandeLogin(char* idFIL)
 * \brief Fonction permettant de demander le login de l'utilisateur
 *
 * \param idFIL Une chaîne de caractères (20 caractères), destinée à recevoir le login de l'utilisateur
 */
void demandeLogin(char* idFIL) {
	
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
void demandeMDP(char* mdpFIL) {

	printf("Entrez votre mot de passe FIL:");
	fgets(mdpFIL, LONGUEUR_MDP, stdin);
	supprimeCaractere(mdpFIL, '\n');

}

/**
 * \fn char* demandeChemin(char *cheminFichier)
 * \brief Fonction permettant de demander le chemin du dossier/fichier, et de retourner le chemin absolu vers celui-ci
 *
 * \param cheminFichier Une chaine de caractères (PATH_MAX max), destinée à recevoir le chemin donné au dossier/fichier
 * \return Retourne le chemin absolu vers le dossier/fichier voulu
 */
char* demandeChemin(char* cheminFichier) {

	char* cheminEntre = malloc(sizeof(char) * PATH_MAX);
	struct passwd* passwdEnt = getpwuid(getuid());
	char* home = passwdEnt->pw_dir;

	home = strcat(home, "/");

	printf("Entrez le chemin du fichier/dossier à transférer sur PROF:\n");
	printf("%s",home);
	fgets(cheminEntre, PATH_MAX, stdin);
	supprimeCaractere(cheminEntre, '\n');
	cheminFichier = strcat(home, cheminEntre);
	printf("cheminFichier: %s\n",cheminFichier);

	free(cheminEntre);

	return cheminFichier;
}