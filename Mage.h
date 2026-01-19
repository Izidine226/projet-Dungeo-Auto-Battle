#ifndef MAGE_H
#define MAGE_H

#include "Hero.h"
#include <iostream>

using namespace std;

class Mage : public Hero {
public:
    Mage(string nom, int pv, int attaque, int defense, int vitesse) 
        : Hero(nom, pv, attaque, defense, vitesse) {}

    // Identifiant du Mage 
    int getClasse() const override { 
        return 2; 
    }

    // La Spécialité du Mage : La Pénétration Magique
    // Règle : "Ignore 30% de la défense ennemie"
    int calculerDegats(const Hero& cible) override {
        
        // 1. On calcule la défense réduite de la cible
    
        int defenseReduite = (int)(cible.getDefense() * 0.7);

        // 2. Formule standard, mais avec la défense réduite
        int degats = attaque / max(1, defenseReduite);

        return degats;
    }
};

#endif