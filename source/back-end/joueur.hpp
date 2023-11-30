#ifndef PROJET_LO21_JOUEUR_HPP
#define PROJET_LO21_JOUEUR_HPP

#include <unordered_map>

#include "jetons.hpp"
#include "carte.hpp"
#include "strategy.hpp"
// rajouter itération cartes + jetons + privilèges

// acheter carte noble acheter carte niveau 4 DONE
// Exceptions --> gérer les exceptions DONE
// bonus DONE
// voir nb couronnes DONE
// Voir diagonale DONE~
// voir estGagnant DONE
// couleurs pour carte reservee DONE

// CApa
// Voir achat carte en fonction des gemmes DONE
// Choix action aléatoire
// Voir strategy pour l'IA



class JoueurException
{
public:
    JoueurException(const std::string& i) :info(i) {}
    std::string getInfo() const { return info; }
private:
    std::string info;
};



enum class type { IA, HUMAIN };

std::string toStringType(type t);

type toType(std::string s);

class Joueur {
private:
    static  std::vector<Joueur*> joueurs;
    const string pseudo;
    const type typeDeJoueur;
    unsigned int ptsPrestige;
    unsigned int nbCouronnes;
    bool gagnant;

    std::unordered_map<Couleur, std::vector<const Carte*>> cartes;
    std::unordered_map<Couleur, std::vector<const Carte*>> cartesReservees;
    std::unordered_map<Couleur, std::vector<const Jeton*>> jetons;
    std::vector<const Carte*> cartesNobles;
    std::vector<const Privilege*> privileges;

    std::unordered_map<Couleur, unsigned int> bonus;

    Strategy* strategy;
public:
    // Constructeur done
    Joueur(string pseudo, type typeDeJoueur);

    // Destructeur
    ~Joueur();



    // Getters
    std::string getPseudo() const { return pseudo; };
    type getTypeDeJoueur() const { return typeDeJoueur; };
    unsigned int getptsPrestige() const { return ptsPrestige; };
    unsigned int getnbCouronnes() const { return nbCouronnes; };
    size_t getNbCartes() const;
    size_t getNbCartes(Couleur c) const { return cartes.at(c).size(); }
    size_t getNbCartesReservees() const;
    size_t getNbCartesNobles() const { return cartesNobles.size(); }
    size_t getNbCartesReservees(Couleur c) const { return cartesReservees.at(c).size(); }
    size_t getNbJetons() const;
    size_t getNbJetons(Couleur c) const { return jetons.at(c).size(); }
    size_t getNbPrivileges() const { return privileges.size(); }
    const Carte& getCarte(Couleur c, size_t i) const { return *cartes.at(c).at(i); }
    const Carte& getCarteReservee(Couleur c, size_t i) const { return *cartesReservees.at(c).at(i); }
    const Carte& getCarteNoble(size_t i) const { return *cartesNobles[i]; }
    unsigned int getNbCouronnes ()const { return nbCouronnes; }


    // Setters
    void updatePtsPrestige(int pts) { ptsPrestige += pts; };
    void updateNbCouronnes(int couronnes) { nbCouronnes += couronnes; };

    void addCarte(const Carte &carte);
    void addCarteReservee(const Carte &carte) ;
    void addCarteNoble(const Carte& carte);
    void addJeton(const Jeton &jeton);
    void addPrivilege(const Privilege &privilege);


    void supCarte(Carte &carte);
    void supCarteReservee(const Carte &carte);
    void supCarteNoble(const Carte& carte);
    void supJeton(Jeton *jeton, EspaceJeux& espaceJeux);
    void supJetonNb(unsigned int nb, Couleur c, EspaceJeux& espaceJeux);
    const Privilege& supPrivilege(Plateau& plateau);

    // Affichage Done
    void afficherJoueur() const;
    void afficherCartes() const;
    void afficherJetons() const;
    void afficherPrivileges() const{
        std::cout << "Nombre de privilèges : " << &privileges << std::endl;
    }


    bool verifAchatCarte(const Carte& carte,  EspaceJeux& espaceJeux);
    // Actions optionnelles
    void utiliserPrivilege(Plateau& plateau);
    void remplirPlateau(Plateau& plateau, Sac& sac, Joueur& joueurAdverse);

    // Actions obligatoires
    void recupererJetons(Plateau& plateau);
    void acheterCarteJoaillerie (EspaceJeux& espaceJeux);
    void acheterCarteNoble (Pyramide& pyramide);
    void orReserverCarte (Pyramide& pyramide, Plateau& plateau);

    // Sauvegarde + Gagne
    bool nbPtsPrestigeParCouleurSupDix() const;
    bool estGagnant() const { return gagnant;}


};


#endif //PROJET_LO21_JOUEUR_HPP
