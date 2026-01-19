#ifndef HERO_H
#define HERO_H

#include <iostream>
#include <string>
#include <algorithm> 

using namespace std;

class Hero {
protected:
    string nom;
    int pv;
    int pvMax;    
    int attaque;
    int defense;
    int vitesse;

public:
   // constructeur
    Hero(string nom, int pv, int attaque, int defense, int vitesse) 
        : nom(nom), pv(pv), pvMax(pv), attaque(attaque), defense(defense), vitesse(vitesse) {}

    // Destructeur virtuel 
    virtual ~Hero() {}


    // Affiche les stats du héros
    void afficherStats() const {
        cout << "Hero : " << nom 
             << "PV: " << pv << "/" << pvMax 
             << "Attaque: " << attaque 
             << "Defense: " << defense 
             << "Vitesse: " << vitesse << endl;
    }

    // Indique si le héros est toujours en vie
    bool estVivant() const {
        return pv > 0;
    }

    // Remet les PV au max comme a linitial 
    void soignerCompletement() {
        pv = pvMax;
    }

    // Getters utiles pour le combat
    int getVitesse() const { return vitesse; }
    int getDefense() const { return defense; }
    string getNom() const { return nom; }
    int getPv() const { return pv; }
    int getPvMax() const { return pvMax; }

    //Méthodes Virtuelles Pures (Abstraction) 
    
    // Doit renvoyer un ID de classe (ex: 1=Guerrier, 2=Mage...) 
    virtual int getClasse() const = 0; 

    // Calcul des dégâts infligés à une cible
    virtual int calculerDegats(const Hero& cible) = 0;

    // Gestion de la perte de PV (virtuelle car l'Archer peut esquiver) 
    virtual void perdrePV(int montant) {
        pv -= montant;
        if (pv < 0) pv = 0;
    }

    // Optionnels , on les met vides par défaut
    virtual void effetDebutTour() {}
    virtual void effetFinTour() {}
};

#endif