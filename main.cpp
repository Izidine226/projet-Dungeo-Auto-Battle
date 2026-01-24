#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include "Hero.h"
#include "Guerrier.h"
#include "Mage.h"
#include "Archer.h"
#include "Joueur.h"
#include "Combat.h"

using namespace std;

// Déclaration de la fonction de génération aléatoire
extern Hero* genererHeroAleatoire();

/**
 * Affiche le menu de sélection de classe
 */
void afficherMenuClasses() {
    cout << "\n=== CHOIX DE LA CLASSE ===\n";
    cout << "1. Guerrier - Fort en defense, rage quand PV < 30%\n";
    cout << "2. Mage - Fort en attaque, ignore 30% de la defense ennemie\n";
    cout << "3. Archer - Fort en vitesse, coup critique possible\n";
    cout << "Votre choix (1-3) : ";
}

/**
 * Crée un héros selon le choix de l'utilisateur
 */
Hero* creerHeroInteractif() {
    int choix;
    string nom;

    cout << "\nNom du heros : ";
    cin >> nom;

    afficherMenuClasses();

    while (true) {
        cin >> choix;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entree invalide. Choisissez 1, 2 ou 3 : ";
            continue;
        }

        switch (choix) {
            case 1:
                return new Guerrier(nom + " (Guerrier)", 50 + rand() % 51, 50 + rand() % 51, 80 + rand() % 21, 50 + rand() % 51);
            case 2:
                return new Mage(nom + " (Mage)", 50 + rand() % 51, 80 + rand() % 21, 50 + rand() % 51, 50 + rand() % 51);
            case 3:
                return new Archer(nom + " (Archer)", 50 + rand() % 51, 50 + rand() % 51, 50 + rand() % 51, 80 + rand() % 21);
            default:
                cout << "Choix invalide. Choisissez 1, 2 ou 3 : ";
        }
    }
}

/**
 * Crée un joueur avec sélection interactive des héros
 */
Joueur* creerJoueurInteractif(const string& nom, int nbHeros = 6) {
    Joueur* j = new Joueur(nom);

    cout << "\n=== CREATION DE L'EQUIPE : " << nom << " ===\n";
    cout << "Vous allez choisir " << nbHeros << " heros.\n";

    for (int i = 0; i < nbHeros; i++) {
        cout << "\n--- Heros " << (i + 1) << "/" << nbHeros << " ---";
        Hero* h = creerHeroInteractif();
        j->ajouterHero(h);
        cout << "Heros ajoute : " << h->getNom() << "\n";
    }

    cout << "\nEquipe complete pour " << nom << " !\n";
    return j;
}

/**
 * Point d'entrée principal
 */
int main() {
    // Initialisation du générateur aléatoire
    srand(time(0));

    cout << "=== DUNGEON AUTO-BATTLE ===\n";
    cout << "Bienvenue dans le combat automatique de heros !\n\n";

    // Création interactive des joueurs
    Joueur* j1 = creerJoueurInteractif("Joueur 1", 6);
    Joueur* j2 = creerJoueurInteractif("Joueur 2", 6);

    // Sélection des équipes (interactive pour le joueur 1, aléatoire pour le joueur 2)
    cout << "\n=== SELECTION DES EQUIPES ===\n";

    cout << "\n--- Selection pour " << j1->getNom() << " ---";
    j1->selectionnerEquipe();

    cout << "\n--- Selection automatique pour " << j2->getNom() << " ---";
    j2->selectionnerEquipeAleatoire();

    // Affichage des équipes
    cout << "\n=== EQUIPES FINALES ===\n";
    j1->afficherEquipe();
    j2->afficherEquipe();

    cout << "\nAppuyez sur Entree pour commencer le combat...";
    cin.ignore();
    cin.get();

    // Combat !
    cout << "\n=== DEBUT DU COMBAT ===\n";
    combatEquipes(*j1, *j2);

    // Nettoyage
    delete j1;
    delete j2;

    cout << "\nMerci d'avoir joue !\n";
    return 0;
}
