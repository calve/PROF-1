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
#define OOPTION "<OPTION\nVALUE="

/**
 * \def OAHREF
 * \brief Macro contenant le début de déclaration d'un rendu - s'ensuit X')">
 */
#define OAHREF "<a\n	  \nhref=\"javascript:popup('popup.php?id_echeance="

/**
 * \def ORENDU
 * \brief Macro contenant le début de déclaration d'une information pour un rendu
 */
#define ORENDU "<td align=center>"

/**
 * \def EOPTION
 * \brief Macro contenant la balise HTML de fin d'option - on considère ici la fin de déclaration d'une matière
 */
#define EOPTION "</OPTION>"

/**
 * \def EAHREF
 * \brief Macro contenant la fin de déclaration d'un rendu
 */
#define EAHREF "</a>"

/**
 * \def ERENDU
 * \brief Macro contenant la fin de déclaration d'une information pour un rendu
 */
#define ERENDU "</td>"

/**
 * \fn int parseFichierHTML(char* str)
 * \brief Fonction permettant de parser une longue chaîne de caractères (page PHP sauvée), afin de trouver les options de matières de TD/TP
 *
 * \param str Une chaîne valant la page PHP de sélection de projets
 * \param tabMatieres Un tableau de chaînes de caractères, valant toutes une matière
 * \return Un entier: 0 si la fonction s'est bien exécuté - 1 si la balise EOPTION n'a pas été trouvé...
 */
int parseFichierMatiere(char* str, char** tabMatieres) {

	int positionEOption = 0;
	int i = 0;

	/*Tableau de caractères, qui va contenir la matière*/
	char* option = malloc(sizeof(char) * 100);

	/*
	Tant qu'il y a des options...
	*/
	while ((str = strstr(str, OOPTION)) != NULL) {

		/*
		Décalage de la longueur de OPTION
		*/
		str = str + (strlen(OOPTION)+4);

		char* finOption = malloc(sizeof(char) * strlen(str));

		/*
		On recherche après la fin de la balise
		*/
		if ((finOption = strstr(str, EOPTION)) != NULL) {
			
			/*
			Longueur de l'option
			*/
			positionEOption = finOption - str;

			strncpy(option, str, positionEOption);

			option[positionEOption] = '\0';

			/*
			Enregistrement
			*/
			strcpy(tabMatieres[i],option);

			/*free(finOption);*/

			i++;

		}
		/*
		Si pas de balise de fin, on s'arrête (car le WebDev' a fait une bêtise!!)
		*/
		else {
			free(finOption);
			return 1;
		}

	}

	free(option);

	return 0;

}

/**
 * \fn int parseFichierRendus(char* str, char** tabRendus)
 * \brief Fonction permettant de parser le fichier HTML/PHP contenant tous les rendus accessibles pour une matière
 *
 * \param str Une chaîne valant la page PHP de sélection de projets
 * \param tabRendus Un tableau de chaînes de caractères, valant toutes un rendu pour la matière demandée
 * \return Un entier: 0 si la fonction s'est bien exécuté - 1 si la balise EOPTION n'a pas été trouvé...
 */
int parseFichierRendus(char* str, char** tabRendus) {

	int positionERendu = 0;
	int i = 0;

	/*Chaîne de caractères valant le nom du rendu*/
	char* rendu = malloc(sizeof(char) * 100);

	/*
	Tant qu'il y a des options...
	*/
	while ((str = strstr(str, OAHREF)) != NULL) {

		/*
		Décalage de la longueur de OAHREFX')"> || OAHREFXX')">
		*/
		if (i < 10)
			str = str + (strlen(OAHREF)+5);
		else
			str = str + (strlen(OAHREF)+6);

		char* finRendu = malloc(sizeof(char) * strlen(str));

		/*
		On recherche après la fin de la balise
		*/
		if ((finRendu = strstr(str, EAHREF)) != NULL) {
			
			/*
			Longueur de l'option
			*/
			positionERendu = finRendu - str;

			strncpy(rendu, str, positionERendu);

			rendu[positionERendu] = '\0';

			/*
			Enregistrement
			*/
			strcpy(tabRendus[i],rendu);

			i++;

		}
		/*
		Si pas de balise de fin, on s'arrête (car le WebDev' a fait une bêtise!!)
		*/
		else {
			free(finRendu);
			return 1;
		}

	}

	free(rendu);

	return 0;

}
