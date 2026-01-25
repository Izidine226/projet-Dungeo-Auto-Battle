#ifndef JOUEUR_H
#define JOUEUR_H

#include <string>
#include <vector>
#include <iostream>
#include "Hero.h"

/**
 * Classe Joueur
 * Gère une collection de héros (max 6)
 * Permet la sélection d'une équipe de combat (max 3)
 */
class Joueur {
private:
    std::string nom;
    std::vector<Hero*> heros;           // Tous les héros du joueur (max 6)
    std::vector<Hero*> equipeSelectionnee; // Équipe active pour le combat (max 3)
    
    static const int MAX_HEROS = 6;
    static const int MAX_EQUIPE = 3;

public:
    // Constructeur & Destructeur
    Joueur(const std::string& nom);
    ~Joueur();
    
    // Gestion des héros
    bool ajouterHero(Hero* h);
    void afficherHeros() const;
    void afficherEquipe() const;
    
    // Sélection d'équipe
    bool selectionnerEquipe();
    bool selectionnerEquipeAleatoire();
    void resetEquipe(); // Réinitialise les PV après combat
    
    // Getters
    std::string getNom() const { return nom; }
    const std::vector<Hero*>& getHeros() const { return heros; }
    const std::vector<Hero*>& getEquipeSelectionnee() const { return equipeSelectionnee; }
    std::vector<Hero*>& getEquipeSelectionnee() { return equipeSelectionnee; }
    
    // État du joueur
    bool aDesHerosVivants() const;
    int nbHerosVivants() const;
};

#endif
