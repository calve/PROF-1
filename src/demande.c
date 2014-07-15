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
#include <readline/readline.h>
#include <errno.h>
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

	char* home = malloc(sizeof(char) * PATH_MAX);
        char* resolved_path = malloc(sizeof(char) * PATH_MAX);
        char* tmp;
        int i;

        home = getcwd(home, PATH_MAX);
        home = strcat(home,"/");

	printf("Entrez le chemin du fichier/dossier à transférer sur PROF:\n");
        cheminFichier = readline(home);

        // Remove trailing space if one
        for (i = 0; i < PATH_MAX ; i++){
          if (cheminFichier[i] =='\0') { // End of user input
            if (cheminFichier[i-1] ==' '){ // Trailing space
              tmp = readline("Remove one suspicious trailing space ? [Y/n] : ");
              if (tmp[0] != 'n'){ // Delete it
                cheminFichier[i-1] = '\0';
              }
            }
            break;
          }
        }

	cheminFichier = strcat(home, cheminFichier);
        resolved_path = realpath(cheminFichier, resolved_path);

        if ( resolved_path == NULL ){
          {
            printf("Error reading file");
            return NULL;
          }
        }

        strcpy(cheminFichier, resolved_path);
        free(resolved_path);

	return cheminFichier;
}
