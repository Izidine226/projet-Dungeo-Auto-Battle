#ifndef GUERRIER_H
#define GUERRIER_H

#include "Hero.h" 

class Guerrier : public Hero {
public:
    // Constructeur : Il reçoit les stats et les passe directement au constructeur de Hero
    Guerrier(string nom, int pv, int attaque, int defense, int vitesse) 
        : Hero(nom, pv, attaque, defense, vitesse) {}

   
    // 1 = Guerrier
    int getClasse() const override { 
        return 1; 
    }

    //  gestion des dégâts
    int calculerDegats(const Hero& cible) override {
        // Formule de base (Attaque / Defense de la cible)
        // On utilise max(1, ...) pour ne jamais diviser par 0
        int degats = attaque / max(1, cible.getDefense());

        // Bonus Spécial Guerrier : +20% dégâts si PV < 30% 
        if (pv < (pvMax * 0.3)) {
            degats = (int)(degats * 1.2); 
        }

        return degats;
    }
};

#endif