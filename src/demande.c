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

	char* home = getcwd(cheminFichier, PATH_MAX);
        char* resolved_path = malloc(sizeof(char) * PATH_MAX);

	home = strcat(home, "/");

	printf("Entrez le chemin du fichier/dossier à transférer sur PROF:\n");
        cheminFichier = readline(home);
	cheminFichier = strcat(home, cheminFichier);
        realpath(cheminFichier, resolved_path);
	printf("cheminFichier: %s\n",cheminFichier);
        printf("cheminFichier : %s\n",cheminFichier);
        printf("resolved_path : %s\n",resolved_path);
        printf("realpath(cheminFichier, resolved_path);\n");
        if ( realpath(cheminFichier, resolved_path) == NULL ){
          printf("real path failed, errno %d \n", errno);
          if (errno == EACCES)
            printf("EACCES");
          if ( errno == EINVAL)
            printf("EINVAL");
          if (errno == EIO)
            printf("EIO");
          if (errno == ELOOP)
            printf("ELOOP");
          if (errno == ENOTDIR)
            printf("ENOTDIR");
          if (errno == ENOENT)
            {
              printf("ENOENT");
              if (access(resolved_path, F_OK) == 0)
                printf(" ... access ok\n");
            }

          if (errno == ENAMETOOLONG)
            printf("ENAMETOOLONG");
          printf("\n");
        }
        printf("cheminFichier : %s\n",cheminFichier);
        printf("resolved_path : %s\n",resolved_path);
        printf("cheminFichier = resolved_path;\n");
        cheminFichier = resolved_path;

	return cheminFichier;
}
