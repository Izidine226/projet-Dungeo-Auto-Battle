#include "Joueur.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
#include <random>

using namespace std;

// Constructeur
Joueur::Joueur(const std::string& nom) : nom(nom) {}

// Destructeur : TRES IMPORTANT
// Il doit libérer la mémoire de tous les héros créés dynamiquement
Joueur::~Joueur() {
    for (Hero* h : heros) {
        delete h;
    }
    // Les vecteurs se vident automatiquement
}

// Ajoute un héros à la liste du joueur (ne doit pas dépasser MAX_HEROS)
bool Joueur::ajouterHero(Hero* h) {
    if (heros.size() < MAX_HEROS) {
        heros.push_back(h);
        return true;
    }
    // Si on a déjà 6 héros, on n'ajoute pas le nouveau et on le supprime pour éviter une fuite de mémoire
    delete h; 
    return false;
}

// Affiche tous les héros possédés par le joueur
void Joueur::afficherHeros() const {
    cout << "Héros de " << nom << " :" << endl;
    if (heros.empty()) {
        cout << "  Aucun héros." << endl;
        return;
    }
    for (size_t i = 0; i < heros.size(); ++i) {
        cout << "  " << (i + 1) << ". ";
        heros[i]->afficherStats();
    }
}

// Affiche l'équipe sélectionnée pour le combat
void Joueur::afficherEquipe() const {
    cout << "Équipe de " << nom << " :" << endl;
    if (equipeSelectionnee.empty()) {
        cout << "  Aucun héros sélectionné." << endl;
        return;
    }
    for (const Hero* h : equipeSelectionnee) {
        h->afficherStats();
    }
}

// Logique pour qu'un joueur choisisse ses 3 héros
bool Joueur::selectionnerEquipe() {
    equipeSelectionnee.clear();
    if (heros.empty()) {
        cout << "Vous n'avez aucun héros à sélectionner !" << endl;
        return false;
    }

    cout << "Sélectionnez jusqu'à " << MAX_EQUIPE << " héros pour le combat." << endl;
    afficherHeros();

    vector<int> indicesChoisis;
    int choix;

    while (equipeSelectionnee.size() < MAX_EQUIPE) {
        cout << "Entrez le numéro du héros à ajouter (ou 0 pour terminer) : ";
        cin >> choix;

        if (cin.fail()) {
            cout << "Entrée invalide. Veuillez entrer un nombre." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choix == 0) {
            break;
        }

        if (choix > 0 && choix <= (int)heros.size()) {
            // Vérifier si le héros n'a pas déjà été choisi
            bool dejaChoisi = false;
            for(int index : indicesChoisis) {
                if (index == choix - 1) {
                    dejaChoisi = true;
                    break;
                }
            }

            if (!dejaChoisi) {
                equipeSelectionnee.push_back(heros[choix - 1]);
                indicesChoisis.push_back(choix - 1);
                cout << "Héros " << heros[choix - 1]->getNom() << " ajouté à l'équipe." << endl;
            } else {
                cout << "Ce héros est déjà dans votre équipe." << endl;
            }
        } else {
            cout << "Numéro de héros invalide." << endl;
        }
    }

    if (equipeSelectionnee.empty()) {
        cout << "Aucun héros sélectionné. L'équipe est vide." << endl;
        return false;
    }
    
    return true;
}

// Sélectionne une équipe de 3 héros au hasard
bool Joueur::selectionnerEquipeAleatoire() {
    equipeSelectionnee.clear();
    if (heros.empty()) return false;

    // Mélanger les héros
    shuffle(heros.begin(), heros.end(), default_random_engine{});

    // Prendre les 3 premiers (ou moins si le joueur en a moins)
    for (size_t i = 0; i < heros.size() && i < MAX_EQUIPE; ++i) {
        equipeSelectionnee.push_back(heros[i]);
    }

    return !equipeSelectionnee.empty();
}

// Soigne tous les héros de l'équipe
void Joueur::resetEquipe() {
    for (Hero* h : equipeSelectionnee) {
        h->soignerCompletement();
    }
}

// Vérifie si le joueur a encore des héros capables de se battre
bool Joueur::aDesHerosVivants() const {
    for (const Hero* h : equipeSelectionnee) {
        if (h->estVivant()) {
            return true;
        }
    }
    return false;
}

// Compte le nombre de héros encore en vie dans l'équipe
int Joueur::nbHerosVivants() const {
    int compteur = 0;
    for (const Hero* h : equipeSelectionnee) {
        if (h->estVivant()) {
            compteur++;
        }
    }
    return compteur;
}