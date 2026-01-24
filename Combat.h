#ifndef COMBAT_H
#define COMBAT_H

#include "Hero.h"
#include "Joueur.h"

/**
 * Gestion des combats
 */

// Combat 1v1 entre deux héros
int combat(Hero* h1, Hero* h2);

// Combat entre deux équipes de héros
int combatEquipes(Joueur& j1, Joueur& j2);

// Fonctions utilitaires
void afficherSeparateur();
void afficherTitreCombat(const Hero* h1, const Hero* h2);
void pause(int ms = 1000);

#endif
