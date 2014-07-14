/**
 * \file parse.c
 * \brief Module de parçage de page HTML/PHP
 * \author Carette Antonin
 * \version 0.1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * \def OOPTION
 * \brief Macro contenant la balise HTML de début d'option - on considère ici le début de déclaration d'une matière
 */
#define OOPTION "<option>"


/**
 * \def EOPTION
 * \brief Macro contenant la balise HTML de fin d'option - on considère ici la fin de déclaration d'une matière
 */
#define EOPTION "</option>"

/**
 * \fn char** parseFichierHTML(char* str)
 * \brief Fonction permettant de parser une longue chaîne de caractères (page PHP sauvée), afin de trouver les options de matières de TD/TP
 *
 * \param str Une chaîne valant la page PHP de sélection de projets
 * \return Un tableau contenant les titres des options de projets
 */
char** parseFichierHTML(char* str) {

	int positionEOption = 0;
	int i = 0;

	/*
	Tableau de 20 options max, chaque option faisant 100 caractères max
	*/
	char tabOptions[20][100];

	/*Tableau de caractères valant l'option*/
	char* option = malloc(sizeof(char) * 100);

	strcpy(option, str);

	printf("OK\n");

	/*
	Tant qu'il y a des options...
	*/
	while ((str = strstr(str, OOPTION)) != NULL) {

		/*
		Décalage de la longueur de OPTION
		*/
		str = str + strlen(OOPTION);

		char* finOption = malloc(sizeof(char) * strlen(str));

		/*
		On recherche après la fin de la balise
		*/
		if ((finOption = strstr(str, EOPTION)) != NULL) {

			/*
			Longueur de l'option
			*/
			positionEOption = str - finOption + 1;

			char* aCopier = str+positionEOption;

			strcpy(option, aCopier);

			/*
			Enregistrement
			*/
			strcpy(tabOptions[i],option);

			free(finOption);

			i++;
		}
		/*
		Si pas de balise de fin, on s'arrête (car le WebDev' a fait une bêtise!!)
		*/
		else {
			free(finOption);
			break;
		}

	}

	free(option);

	printf("SORTIE\n");

	/*
	Retour du tableau d'options
	*/
	return tabOptions;

}