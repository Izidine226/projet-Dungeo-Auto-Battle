#ifndef MAGE_H
#define MAGE_H

#include "Hero.h"
#include <iostream>
#include <cstdlib> // Pour rand()

using namespace std;

class Mage : public Hero {
public:
    Mage(string nom, int pv, int attaque, int defense, int vitesse) 
        : Hero(nom, pv, attaque, defense, vitesse) {}

    // Identifiant du Mage 
    int getClasse() const override { 
        return 2; 
    }

    // La Spécialité du Mage : La Pénétration Magique et Dégâts Variables
    // Règle : "Ignore 30% de la défense ennemie" et "dégâts plus variables"
    int calculerDegats(const Hero& cible) override {
        
        // 1. On calcule la défense réduite de la cible
        int defenseReduite = (int)(cible.getDefense() * 0.7);

        // 2. Formule standard, mais avec la défense réduite
        int degatsDeBase = attaque / max(1, defenseReduite);

        // 3. On ajoute la variabilité (+/- 20%)
        // On génère un flottant entre 0.8 et 1.2
        float facteurAleatoire = 0.8f + (rand() % 41) / 100.0f; // 0.80 à 1.20
        int degatsFinaux = (int)(degatsDeBase * facteurAleatoire);

        return degatsFinaux;
    }
};

#endif