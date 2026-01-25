#include "Combat.h"
#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <algorithm>

using namespace std;

/**
 * Affiche un séparateur visuel
 */
void afficherSeparateur() {
    cout << "\n----------------------------------------\n";
}

/**
 * Affiche le titre d'un combat
 */
void afficherTitreCombat(const Hero* h1, const Hero* h2) {
    afficherSeparateur();
    cout << "Combat : " << h1->getNom() << " (" << h1->getClasseStr() << ")"
         << " vs " << h2->getNom() << " (" << h2->getClasseStr() << ")\n";
    afficherSeparateur();
}

/**
 * Combat 1v1 entre deux héros
 * Gère la logique complète d'un affrontement
 *
 * @param h1 Premier héros
 * @param h2 Deuxième héros
 * @return 1 si h1 gagne, 2 si h2 gagne
 */
int combat(Hero* h1, Hero* h2) {
    if (h1 == nullptr || h2 == nullptr) {
        cerr << "Erreur : heros invalide dans combat()\n";
        return 0;
    }

    // Détermination de qui commence (basé sur la vitesse)
    Hero* attaquant;
    Hero* defenseur;

    int vitesseH1 = h1->getVitesse();
    int vitesseH2 = h2->getVitesse();

    // Probabilité basée sur la vitesse
    int totalVitesse = vitesseH1 + vitesseH2;
    int chanceH1 = (totalVitesse > 0) ? (vitesseH1 * 100) / totalVitesse : 50;
    int roll = rand() % 100;

    if (roll < chanceH1) {
        attaquant = h1;
        defenseur = h2;
    } else {
        attaquant = h2;
        defenseur = h1;
    }

    // Boucle de combat
    while (h1->estVivant() && h2->estVivant()) {
        // Effets début de tour
        attaquant->effetDebutTour();

        // Calcul des dégâts
        int degats = attaquant->calculerDegats(*defenseur);

        // Application des dégâts
        defenseur->perdrePV(degats);

        // Effets fin de tour
        attaquant->effetFinTour();

        // Vérifier si le combat est terminé
        if (!defenseur->estVivant()) {
            break;
        }

        // Changement de rôle
        swap(attaquant, defenseur);
    }

    // Détermination du vainqueur
    if (h1->estVivant()) {
        return 1;
    } else {
        return 2;
    }
}

/**
 * Affiche l'état actuel du combat
 */
void afficherEtatCombat(Joueur& j1, Joueur& j2, int tour) {
    cout << "\n=== ETAT DU COMBAT - Tour " << tour << " ===\n";

    cout << "\n" << j1.getNom() << " :\n";
    cout << "  Heros vivants : " << j1.nbHerosVivants() << "/3\n";
    auto& equipe1 = j1.getEquipeSelectionnee();
    for (size_t i = 0; i < equipe1.size(); ++i) {
        Hero* h = equipe1[i];
        if (h->getPv() > 0) {
            cout << "    ✅ " << h->getNom() << " (" << h->getPv() << "/" << h->getPvMax() << " PV)\n";
        } else {
            cout << "    ❌ " << h->getNom() << " (VAINCU)\n";
        }
    }

    cout << "\n" << j2.getNom() << " :\n";
    cout << "  Heros vivants : " << j2.nbHerosVivants() << "/3\n";
    auto& equipe2 = j2.getEquipeSelectionnee();
    for (size_t i = 0; i < equipe2.size(); ++i) {
        Hero* h = equipe2[i];
        if (h->getPv() > 0) {
            cout << "    ✅ " << h->getNom() << " (" << h->getPv() << "/" << h->getPvMax() << " PV)\n";
        } else {
            cout << "    ❌ " << h->getNom() << " (VAINCU)\n";
        }
    }
    cout << "\n";
}

/**
 * Combat entre deux équipes de joueurs
 * Les héros combattent dans l'ordre de sélection
 *
 * @param j1 Premier joueur
 * @param j2 Deuxième joueur
 * @return 1 si j1 gagne, 2 si j2 gagne
 */
int combatEquipes(Joueur& j1, Joueur& j2) {
    // Vérifications
    if (j1.getEquipeSelectionnee().empty() || j2.getEquipeSelectionnee().empty()) {
        cerr << "Erreur : equipe vide !\n";
        return 0;
    }

    cout << "\n🏟️  Le combat oppose " << j1.getNom() << " contre " << j2.getNom() << " !\n";

    // Récupération des équipes
    vector<Hero*>& equipe1 = j1.getEquipeSelectionnee();
    vector<Hero*>& equipe2 = j2.getEquipeSelectionnee();

    size_t idx1 = 0; // Index du héros actuel de l'équipe 1
    size_t idx2 = 0; // Index du héros actuel de l'équipe 2

    int tourCombat = 1; // Compteur global des tours

    // État initial
    afficherEtatCombat(j1, j2, 0);

    // Boucle principale : les héros s'affrontent 1v1 dans l'ordre
    while (idx1 < equipe1.size() && idx2 < equipe2.size()) {
        // Vérifier les conditions de victoire avant chaque combat
        if (!j1.aDesHerosVivants()) {
            cout << "\n🏆 " << j2.getNom() << " remporte l'affrontement !\n";
            cout << "   " << j1.getNom() << " n'a plus de heros en vie.\n";
            return 2;
        }
        if (!j2.aDesHerosVivants()) {
            cout << "\n🏆 " << j1.getNom() << " remporte l'affrontement !\n";
            cout << "   " << j2.getNom() << " n'a plus de heros en vie.\n";
            return 1;
        }

        Hero* h1 = equipe1[idx1];
        Hero* h2 = equipe2[idx2];

        // Vérifier que les héros sont vivants
        if (h1->getPv() <= 0) {
            idx1++;
            continue;
        }
        if (h2->getPv() <= 0) {
            idx2++;
            continue;
        }

        cout << "\n⚔️  Combat " << tourCombat << " : " << h1->getNom() << " vs " << h2->getNom() << "\n";

        // Combat 1v1
        int resultat = combat(h1, h2);

        // Gestion du résultat
        if (resultat == 1) {
            cout << "   🏅 " << h1->getNom() << " l'emporte et regagne ses PV !\n";
            // h1 gagne : le héros gagnant regagne ses PV
            h1->soignerCompletement();
            idx2++; // Le héros 2 est éliminé, on passe au suivant
        } else if (resultat == 2) {
            cout << "   🏅 " << h2->getNom() << " l'emporte et regagne ses PV !\n";
            // h2 gagne : le héros gagnant regagne ses PV
            h2->soignerCompletement();
            idx1++; // Le héros 1 est éliminé, on passe au suivant
        }

        // Afficher l'état tous les 10 tours
        if (tourCombat % 10 == 0) {
            afficherEtatCombat(j1, j2, tourCombat);
        }

        tourCombat++;
    }

    // État final
    afficherEtatCombat(j1, j2, tourCombat - 1);

    // Détermination du gagnant
    if (j1.aDesHerosVivants()) {
        cout << "\n🎉 VICTOIRE FINALE : " << j1.getNom() << " remporte l'affrontement ! 🎉\n";
        return 1;
    } else {
        cout << "\n🎉 VICTOIRE FINALE : " << j2.getNom() << " remporte l'affrontement ! 🎉\n";
        return 2;
    }
}
