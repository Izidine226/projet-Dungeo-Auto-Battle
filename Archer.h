#ifndef ARCHER_H
#define ARCHER_H

#include "Hero.h"
#include <cstdlib> // For rand()

class Archer : public Hero {
private:
    // Probabilité de coup critique (ex: 25%)
    static const int CRITICAL_CHANCE = 25; 
    // Facteur pour l'esquive. L'esquive sera vitesse * facteur (ex: 0.2)
    static constexpr double DODGE_CHANCE_FACTOR = 0.2; 

public:
    Archer(string nom, int pv, int attaque, int defense, int vitesse) 
        : Hero(nom, pv, attaque, defense, vitesse) {}

    // Identifiant de l'Archer
    int getClasse() const override { 
        return 3; 
    }

    // Spécialité de l'Archer : Coups Critiques
    int calculerDegats(const Hero& cible) override {
        int degats = attaque / max(1, cible.getDefense());

        // Coup critique
        if ((rand() % 100) < CRITICAL_CHANCE) {
            degats *= 2;
        }

        return degats;
    }

    // Spécialité de l'Archer : Esquive
    void perdrePV(int montant) override {
        // Chance d'esquiver basée sur la vitesse
        int dodgeChance = (int)(vitesse * DODGE_CHANCE_FACTOR);
        if ((rand() % 100) < dodgeChance) {
            // Ne perd pas de PV
        } else {
            // Appelle la méthode de la classe de base si pas d'esquive
            Hero::perdrePV(montant);
        }
    }
};

#endif
