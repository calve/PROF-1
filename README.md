PROF
====

Programme de Remise Officieuse de Fichiers - C/C++
--------------------------------------------------

Licence GNUGpl - Version 2

**PROF** est un programme permettant de rendre automatiquement des fichiers (TP/TD) sur... PROF (**Plateforme de Remise Officielle de Fichiers**, dispositif créé/utilisé dès 2005 - _Université Lille1_).

Encore en développement - test sur machine **Gnu/Linux** et **FreeBSD** (_MacOS 10.9_).

Utilisation de _Doxygen_ pour la génération de la documentation du programme (Free Software - [site internet](http://www.stack.nl/~dimitri/doxygen/)).

Utilisation de l'interface _libcurl_ (voir [site internet](http://curl.haxx.se/libcurl/) pour la documentation et l'installation).

Utilisation de la librairie _libzip_ (voir [site internet](http://www.nih.at/libzip/) pour la documentation et l'installation).

####TODO:

1.	Contact la plateforme PROF
2.	Implémenter un main totalement fonctionnel
3.	Synchronisation automatique des TP (avec horlogerie)

####Un soucis?

1.	Assurez-vous d'avoir tous les outils nécessaires pour compiler le projet (gcc),
2.	Assurez-vous d'avoir bien installé libcurl (voir site interet plus haut),
3.	Assurez-vous de bien avoir, dans /usr/lib le binaire libzip.so.2.1.0. Si vous détenez libzip.so.x -> super-utilisateur -> cp /usr/local/lib/libzip/libzip.so.2.1.0 /usr/lib && mv /usr/lib/libzip.so.2 /usr/lib/libzip.so.2_old && mv /usr/lib/libzip.so.2.1.0 /usr/lib/libzip.so.2
4.	Merci de m'envoyer un e-mail (voir ci-dessous) si les trois options présentées ci-dessus ne fonctionnent pas.

####Contact:

Carette Antonin

[Envoyer un e-mail](mailto:antonin.carette@gmail.com)
