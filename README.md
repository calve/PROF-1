PROF
====

Programme de Remise Officieuse de Fichiers - C/C++
--------------------------------------------------

Licence GNUGpl - Version 2

**PROF** est un programme permettant de rendre automatiquement des fichiers (TP/TD) sur... PROF (**Plateforme de Remise Officielle de Fichiers**, dispositif créé/utilisé dès 2005 - _Université Lille1_).

Encore en développement - test sur machine **Gnu/Linux** et **FreeBSD** (_MacOS 10.9_), compilateurs **GCC** et **CLang**.

Utilisation de _Doxygen_ pour la génération de la documentation du programme (Free Software - [site internet](http://www.stack.nl/~dimitri/doxygen/)).

Utilisation de la librairie _readline_ (voir [site internet](http://cnswww.cns.cwru.edu/php/chet/readline/rltop.html) pour la documentation et l'installation).

Utilisation de la librairie _libcurl_ (voir [site internet](http://curl.haxx.se/libcurl/) pour la documentation et l'installation).

Utilisation de la librairie _libzip_ (voir [site internet](http://www.nih.at/libzip/) pour la documentation et l'installation).

####Utilisation de doxygen:

Installer doxygen (voir ci-dessus), et modifier le fichier de configuration Doxyfile_config afin de mettre le chemin d'accès vers le répertoire doc/ du projet, pour votre machine (remplacer /PATH_TO_DOC_FOLDER, et /PATH_TO_PROF_FOLDER)

####TODO:

1.	Implémenter un main fonctionnel
	*	demande du login: OK
	*	demande du MDP: OK
	*	demande du chemin au fichier/dossier: OK
	*	vérification fichier/dossier: OK
	*	si fichier, vérification déjà zippé: OK
	*	zip automatique du fichier/dossier si non-zippé: OK - **A VERIFIER**
	*	connexion avec PROF: OK
	*	parser options/rendus des options: OK - **EN COURS**
	*	renommage du fichier zippé selon login + matière: **TODO**
	*	dépot du fichier zippé: **EN COURS**
	*	vérification de la bonne conformité du rendu: **AUTRE PROGRAMME**
2.	Synchronisation automatique des TP (avec horlogerie)

####Utilisation

*	Se placer dans le répertoire PROF/
*	Compilation: **make**
*	Exécution: **./bin/prof**
*	Nettoyage: **make cleanall**

####Un soucis?

1.	Assurez-vous d'avoir tous les outils nécessaires pour compiler le projet (gcc).
2.	Assurez-vous d'avoir bien installé libcurl (voir site internet plus haut) - si problème d'inclusion pour <zipconf.h>:
	*	Se placer dans le répertoire libzip téléchargé
	*	**su** ou **sudo su**
	*	**cp /REPERTOIRE_LIBZIP/lib/zipconf.h /usr/local/includes**
3.	Assurez-vous de bien avoir, dans /usr/lib le binaire libzip.so.2.1.0.
	Si vous détenez libzip.so.x:
	*	**su** ou **sudo su**
	*	**cp /usr/local/lib/libzip/libzip.so.2.1.0 /usr/lib**
	*	**mv /usr/lib/libzip.so.2 /usr/lib/libzip.so.2_old**
	*	**mv /usr/lib/libzip.so.2.1.0 /usr/lib/libzip.so.2**
4.	Assurez-vous de bien avoir installé la librairie libreadline (voir site internet plus haut).
5.	Merci de m'envoyer un e-mail (voir ci-dessous) si les trois options présentées ci-dessus ne fonctionnent pas.

####Contact:

*	Carette Antonin - [Envoyer un e-mail](mailto:antonin.carette@gmail.com)
