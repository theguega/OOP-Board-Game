#include "carte.hpp"

using namespace std;

std::initializer_list<TypeCarte> TypesCarte = { TypeCarte::Niv1, TypeCarte::Niv2, TypeCarte::Niv3, TypeCarte::Noble };
std::initializer_list<Capacite> Capacites = { Capacite::NewTurn, Capacite::TakePrivilege, Capacite::TakeJetonFromBonus, Capacite::TakeJetonToAdv, Capacite::AssociationBonus, Capacite::None };


string TypeCartetoString(TypeCarte t){
    switch (t) {
        case TypeCarte::Niv1: return "Niv1";
        case TypeCarte::Niv2: return "Niv2";
        case TypeCarte::Niv3: return "Niv3";
        case TypeCarte::Noble: return "Noble";
        default: throw CarteException("Type inconnue");
    }
}
ostream& operator<<(ostream& f, TypeCarte t) { f << TypeCartetoString(t); return f; }


string CapacitetoString(Capacite c){
    switch (c) {
        case Capacite::NewTurn: return "NewTurn";
        case Capacite::TakePrivilege: return "TakePrivilege";
        case Capacite::TakeJetonFromBonus: return "TakeJetonFromBonus";
        case Capacite::TakeJetonToAdv: return "TakeJetonToAdv";
        case Capacite::AssociationBonus: return "AssociationBonus";
        case Capacite::None: return "None";
        default: throw CarteException("Capacite inconnue");
    }
}
ostream& operator<<(ostream& f, Capacite c) { f << CapacitetoString(c); return f; }

std::map<std::string, Capacite> stringToCapaciteMap = {
        {"NewTurn", Capacite::NewTurn},
        {"TakePrivilege", Capacite::TakePrivilege},
        {"TakeJetonFromBonus", Capacite::TakeJetonFromBonus},
        {"TakeJetonToAdv", Capacite::TakeJetonToAdv},
        {"AssociationBonus", Capacite::AssociationBonus},
        {"None", Capacite::None}
};

Capacite StringToCapacite(const std::string& capaciteStr){
    auto tmp = stringToCapaciteMap.find(capaciteStr);
    if (tmp != stringToCapaciteMap.end()) {
        return tmp->second;
    }
    else {
        return Capacite::None;
    }
}


ostream& operator<<(ostream& f, const Prix& p){
	f << "Blanc : " << p.getBlanc() << "    " << "Bleu :  " << p.getBleu() << "\n";
    f << "Vert :  " << p.getVert() << "    " << "Noir :  " << p.getNoir() << "\n";
    f << "Rouge : " << p.getRouge() << "    " << "Perle : " << p.getPerle() << "\n";
    return f;
}


ostream& operator<<(ostream& f, const Bonus& b){
    f << b.getNbBonus() << " " << b.getCouleur();
    return f;
}


Carte::Carte(TypeCarte t, Prix& p, Capacite c1, Capacite c2, Bonus& b, unsigned int nbC, unsigned int nbP, unsigned int id) : type(t), prix(p), capacite1(c1), capacite2(c2), bonus(b), nbCouronnes(nbC), nbPtsPrivilege(nbP), id(id) {
    if (t == TypeCarte::Noble)
        throw CarteException("Veuillez utiliser le constructeur approprie");
}


Carte::Carte(TypeCarte t, Capacite c, unsigned int nbP, unsigned int id) : type(t), prix(0, 0, 0, 0, 0, 0), capacite1(c), capacite2(Capacite::None), bonus(), nbCouronnes(0), nbPtsPrivilege(nbP), id(id) {
    if (t != TypeCarte::Noble)
        throw CarteException("Veuillez utiliser le constructeur approprie");
}


ostream& operator<<(ostream& f, const Carte& c){
    f << "-------------------------------------\n";
    f << c.getType() << "        " << "Bonus : " << c.getBonus() << "\n";
    f << "-------------------------------------\n";
    f << "Capacite : " << c.getCapacite1() << ", " << c.getCapacite2() << "\n";
    f << "-------------------------------------\n";
    f << "Prix :\n" << c.getPrix() << "\n";
    f << "-------------------------------------\n";
    f << "Privileges : " << c.getNbPtsPrivilege() << "        " << "Couronnes : " << c.getNbCouronnes() << "\n";
    f << "-------------------------------------\n";
    return f;
}


JeuCarte::JeuCarte(){
    sqlite3* db;
    sqlite3_stmt* stmt;
    sqlite3_stmt* stmt2;

    //on ajoute le chemin relatif au chemin absolue du projet
    std::string relativePath = "data/data_carte.sqlite";
    std::filesystem::path absolutePath = projectPath / relativePath;
    std::string absolutePathStr = absolutePath.string();

    int rc = sqlite3_open("data/data_carte.sqlite", &db); //conversion en char* pour sqlite3_open

    if (rc != SQLITE_OK) {
        std::cerr << "Impossible d'ouvrir la base de donnees 1: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    rc = sqlite3_prepare_v2(db, "SELECT * FROM 'carte'", -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur de preparation de la requete : " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        unsigned int id = sqlite3_column_int(stmt, 0);
        string type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        unsigned int p_blanc = sqlite3_column_int(stmt, 2);
        unsigned int p_bleu = sqlite3_column_int(stmt, 3);
        unsigned int p_vert = sqlite3_column_int(stmt, 4);
        unsigned int p_noir = sqlite3_column_int(stmt, 5);
        unsigned int p_rouge = sqlite3_column_int(stmt, 6);
        unsigned int p_perle = sqlite3_column_int(stmt, 7);
        string capacite1 = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8));
        string capacite2 = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9));
        string couleur_bonus = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10));
        unsigned int bonus = sqlite3_column_int(stmt, 11);
        unsigned int nb_couronnes = sqlite3_column_int(stmt, 12);
        unsigned int nb_pts_privileges = sqlite3_column_int(stmt, 13);

        Prix p(p_blanc, p_bleu, p_vert, p_noir, p_rouge, p_perle);
        Bonus b(StringToCouleur(couleur_bonus), bonus);
        if (type == "Niv1") {
            cartes_nv1.push_back(new Carte(TypeCarte::Niv1, p, StringToCapacite(capacite1), StringToCapacite(capacite2), b, nb_couronnes, nb_pts_privileges, id));
        }
        else if (type == "Niv2") {
            cartes_nv2.push_back(new Carte(TypeCarte::Niv2, p, StringToCapacite(capacite1), StringToCapacite(capacite2), b, nb_couronnes, nb_pts_privileges, id));
        }
        else if (type == "Niv3") {
            cartes_nv3.push_back(new Carte(TypeCarte::Niv3, p, StringToCapacite(capacite1), StringToCapacite(capacite2), b, nb_couronnes, nb_pts_privileges, id));
        }
        else {
            throw CarteException("Erreur de construction, le type de carte ne convient pas ici");
        }
    }
    rc = sqlite3_prepare_v2(db, "SELECT * FROM 'carte_noble'", -1, &stmt2, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur de preparation de la requete : " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }
    while (sqlite3_step(stmt2) == SQLITE_ROW) {
        string capacite = reinterpret_cast<const char*>(sqlite3_column_text(stmt2, 1));
        unsigned int nb_pts_privileges = sqlite3_column_int(stmt2, 2);
        unsigned int id = sqlite3_column_int(stmt2, 3);
        cartes_nobles.push_back(new Carte(TypeCarte::Noble, StringToCapacite(capacite), nb_pts_privileges, id));
    }
    sqlite3_finalize(stmt);
    sqlite3_finalize(stmt2);
    sqlite3_close(db);
}


JeuCarte::~JeuCarte(){
    for (size_t i = 0; i < getNbCartes_nv1(); ++i) {
		delete cartes_nv1[i];
	}
    for (size_t i = 0; i < getNbCartes_nv2(); ++i) {
        delete cartes_nv2[i];
    }
    for (size_t i = 0; i < getNbCartes_nv3(); ++i) {
        delete cartes_nv3[i];
    }
    for (size_t i = 0; i < getNbCartes_nobles(); ++i) {
        delete cartes_nobles[i];
    }
}


const Carte& JeuCarte::getCarteNiv1(size_t i) const{
    if (i >= getNbCartes_nv1())
        throw CarteException("Il n'y a que 30 cartes de niveau 1");
    return *cartes_nv1[i];
}


const Carte& JeuCarte::getCarteNiv2(size_t i) const{
    if (i >= getNbCartes_nv2())
        throw CarteException("Il n'y a que 24 cartes de niveau 2");
    return *cartes_nv2[i];
}


const Carte& JeuCarte::getCarteNiv3(size_t i) const{
    if (i >= getNbCartes_nv2())
        throw CarteException("Il n'y a que 13 cartes de niveau 3");
    return *cartes_nv3[i];
}


const Carte& JeuCarte::getCarteNoble(size_t i) const{
    if (i >= getNbCartes_nobles())
        throw CarteException("Il n'y a que 4 cartes nobles");
    return *cartes_nobles[i];
}


Pioche::Pioche(const JeuCarte& j, TypeCarte t) : type_carte(t){
    if (t == TypeCarte::Niv1) {
        for (size_t i = 0; i < j.getNbCartes_nv1(); i++)
            cartes.push_back(&j.getCarteNiv1(i));
    }
    else if (t == TypeCarte::Niv2) {
        for (size_t i = 0; i < j.getNbCartes_nv2(); i++)
            cartes.push_back(&j.getCarteNiv2(i));
    }
    else if (t == TypeCarte::Niv3) {
        for (size_t i = 0; i < j.getNbCartes_nv3(); i++)
            cartes.push_back(&j.getCarteNiv3(i));
    }
    else if (t == TypeCarte::Noble) {
        for (size_t i = 0; i < j.getNbCartes_nobles(); i++)
            cartes.push_back(&j.getCarteNoble(i));
    }
    else {
        throw CarteException("Type de cartes inconnu");
    }
}


Pioche::~Pioche(){
    for (size_t i = 0; i < getNbCartes(); i++)
        cartes[i] = nullptr;
}


const Carte& Pioche::piocher(){
    if (estVide())
        throw CarteException("Plus de cartes dans cette pioche");

    //génération d'un indice aléatoire
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, static_cast<int>(cartes.size()) - 1);
    size_t i = distrib(gen);

    const Carte* c = cartes[i];
    cartes.erase(cartes.begin() + i);

    return *c;
}

const Carte& Pioche::piocher(int id){
    if (estVide())
        throw CarteException("Plus de cartes dans cette pioche");

    auto it = std::find_if(cartes.begin(), cartes.end(), [id](const Carte* carte) {
        return carte->getId() == id;
        });

    if (it != cartes.end()) {
        const Carte* carteTrouvee = *it;
        cartes.erase(it);
        return *carteTrouvee;
    }
    else 
        throw CarteException("Aucune carte avec l'ID spécifié n'a été trouvée dans cette pioche"); 
}
