#include "HeroFactory.h"
#include "Guerrier.h"
#include "Mage.h"
#include "Archer.h"
#include <vector>
#include <string>
#include <cstdlib> 

using namespace std;

Hero* genererHeroAleatoire() {
    // 1. Liste de noms pour ne pas avoir juste "Hero1", "Hero2"
    vector<string> noms = {"Lancelot", "Merlin", "Legolas", "Arthur", "Gandalf", "Conan", "Robin", "Geralt"};
    string nom = noms[rand() % noms.size()];

    // 2. Génération des stats entre 50 et 100 
    // Formule : rand() % (Max - Min + 1) + Min
    int pv = (rand() % 51) + 50; 
    int attaque = (rand() % 51) + 50;
    int defense = (rand() % 51) + 50;
    int vitesse = (rand() % 51) + 50;

    // 3. Choix aléatoire de la classe (0, 1 ou 2)
    int type = rand() % 3;
    
    Hero* h = nullptr;

    switch (type) {
        case 0:
            // Pour le Guerrier, on booste un peu la défense (stat principale)
            // On s'assure qu'elle est dans le haut du panier (ex: 80-100)
            defense = (rand() % 21) + 80; 
            h = new Guerrier(nom + " (Guerrier)", pv, attaque, defense, vitesse);
            break;
        case 1:
            // Pour le Mage, on booste l'attaque
            attaque = (rand() % 21) + 80;
            h = new Mage(nom + " (Mage)", pv, attaque, defense, vitesse);
            break;
        case 2:
            // Pour l'Archer, on booste la vitesse
            vitesse = (rand() % 21) + 80;
            h = new Archer(nom + " (Archer)", pv, attaque, defense, vitesse);
            break;
    }

    return h;
}