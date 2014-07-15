/**
 * \file structStr.c
 * \brief Module de sauvegarde de page HTML (select_project.php)
 * \author Carette Antonin
 * \version 0.1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * \struct string structStr.c Structure permettant de sauver une chaîne, et sa longueur
 */
struct string {
  char *ptr;
  size_t len;
};

/**
 * \fn void initStructString(struct string *s)
 * \brief Fonction permettant d'initialiser la structure string
 *
 * \param s Une structure string
 */
void initStructString(struct string *s) {
  s->len = 0;
  s->ptr = malloc(s->len+1);
  if (s->ptr == NULL) {
    printf("ERREUR: malloc!\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

/**
 * \fn size_t writeFonction(void *ptr, size_t size, size_t nmemb, struct string *s)
 * \brief Fonction permettant de sauver une chaîne de caractères, ainsi que sa longueur
 *
 * \param ptr Un pointeur vers les données voulues
 * \param size Taille des données voulues
 * \param nmemb NULL
 * \param s La structure string dans laquelle enregistrer les données, ainsi que la taille de celles-ci
 * \return La taille totale de la page HTML/PHP voulue
 */
size_t writeFonction(void *ptr, size_t size, size_t nmemb, struct string *s) {
  size_t new_len = s->len + size*nmemb;
  s->ptr = realloc(s->ptr, new_len+1);
  if (s->ptr == NULL) {
    printf("ERREUR: realloc!\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr+s->len, ptr, size*nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size*nmemb;
}