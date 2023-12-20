
#include <QScreen>
#include <QSize>
#include <QApplication>
#include "pageCreation.h"
#include "toutesPages.h"
#include "pageJeu.h"
#include <QPalette>


pageJeu::pageJeu(QString statut_partie, QString pseudo_j_1, type type_j_1, QString pseudo_j_2, type type_j_2, QWidget *parent) : QWidget(parent) {
    control = new Controller(statut_partie, pseudo_j_1, type_j_1, pseudo_j_2, type_j_2);
    control->lancerPartie();
    ecran = QGuiApplication::primaryScreen();
    tailleEcran = ecran->availableGeometry().size();

    tailleLargeur = tailleEcran.width();
    tailleHauteur = tailleEcran.height();

    vPlateau = new vuePlateau(nullptr, tailleHauteur - 150, (tailleLargeur-150) / 2, control->getPlateau());
    vPyramide = new vuePyramide(nullptr, tailleHauteur - 100, (tailleLargeur-30) / 2, control->getPyramide());
    joueur1 = new pageJoueur(nullptr, control->getPartie().getJoueur1(), (vPlateau->height() - 130)/4, 30, vPyramide->height()/(vPyramide->getHauteur() + 1), vPyramide->width()/(vPyramide->getHauteur() + 4), vPlateau->getTailleJeton());
    joueur2 = new pageJoueur(nullptr, control->getPartie().getJoueur2(), (vPlateau->height() - 130)/4, 30, vPyramide->height()/(vPyramide->getHauteur() + 1), vPyramide->width()/(vPyramide->getHauteur() + 4), vPlateau->getTailleJeton());

    std::string texteBoutonJ1 = "Afficher " + control->getPartie().getJoueur1()->getPseudo();
    std::string texteBoutonJ2 = "Afficher " + control->getPartie().getJoueur2()->getPseudo();
    afficherJ1 = new QPushButton(QString::fromStdString(texteBoutonJ1));
    afficherJ2 = new QPushButton(QString::fromStdString(texteBoutonJ2));

    connect(afficherJ1, &QPushButton::clicked, this, [this]() {
        this->joueur1->hide();
        this->joueur1->show();
    });
    connect(afficherJ2, &QPushButton::clicked, this, [this]() {
        this->joueur1->hide();
        this->joueur2->show();
    });

    partieHaute = new QHBoxLayout;
    partieMoyenne = new QHBoxLayout;
    partieBasse = new QHBoxLayout;
    layout = new QVBoxLayout;
    layoutPrivileges = new QVBoxLayout;

    for(int i = 0; i < 3; i++){
        listePrivileges.push_back(new vuePrivilege((vPlateau->height() - 130)/4, 30));
        layoutPrivileges->addWidget(listePrivileges[i]);
    }

    bSac = new boutonSac(nullptr, (vPlateau->height() - 130)/4, 30);
    layoutPrivileges->addWidget(bSac);
    connect(bSac, &QPushButton::clicked, this, &pageJeu::remplirPlateau);




    labelJC = new QLabel;

    QPalette palette = labelJC->palette();
    palette.setColor(QPalette::WindowText, Qt::white);
    labelJC->setPalette(palette);


    partieHaute -> addWidget(labelJC);
    partieHaute -> setAlignment(Qt::AlignCenter);
    setLabelJC();

    partieMoyenne -> addLayout(layoutPrivileges);
    partieMoyenne -> addWidget(vPlateau);
    partieMoyenne -> addWidget(vPyramide);
    partieMoyenne -> setAlignment(Qt::AlignVCenter);

    partieBasse -> addWidget(afficherJ1);
    partieBasse -> addWidget(afficherJ2);

    layout -> addLayout(partieHaute);
    layout -> addLayout(partieMoyenne);
    layout -> addLayout(partieBasse);
    setLayout(layout);

    aSauvegarde = new popUpValider(nullptr, "quitter sans sauvegarder", "", "quitter");
    connect(aSauvegarde -> getBoutonOui(), &QPushButton::clicked, this, &pageJeu::quitter);
    connect(aSauvegarde -> getBoutonNon(), &QPushButton::clicked, this, &pageJeu::rester);
    connect(vPlateau, &vuePlateau::signalValiderAppuye, this, &pageJeu::validerSelectionJeton);
    connect(vPyramide, &vuePyramide::cardClicked, this, &pageJeu::validerSelectionCarte);
    connect(vPyramide, &vuePyramide::cardClickedResa, this, &pageJeu::validerResaCarte);


    refresh();

}


void pageJeu::validerSelectionJeton()
{
    // Appeler la méthode verifJetons avec la sélection actuelle de la vue
    std::pair<bool, QString> validationResult = control->verifJetons(vPlateau->getSelectionJetons());
    bool isValid = validationResult.first;
    const QString& message = validationResult.second;

    // Traiter le résultat de la validation
    if(isValid){
        control->recupererJetons(vPlateau->getSelectionJetons());
        control->changerJoueurCourant();

        refresh();
    }
    else{
        popUpInfo* infos = new popUpInfo(nullptr, message.toStdString());
        infos->show();
    }
}

void pageJeu::validerSelectionCarte(position* pos){
    std::pair<bool, QString> validationResult = control->verifAchatCarte(std::make_pair(pos->getx(), pos->gety()));
    bool isValid = validationResult.first;
    const QString& message = validationResult.second;

    if(isValid){
        modalPopup* validation = new modalPopup(this, message, "Voulez-vous valider ?");
        int result =validation->exec();

        // Check the result (optional).
        if (result == QDialog::Accepted){
            pageJeu::handleValidationCarte(pos);
        }
        delete validation;

        refresh();
    }
    else{
        popUpInfo* infos = new popUpInfo(nullptr, message.toStdString());
        infos->show();
    }
}

void pageJeu::validerResaCarte(position* pos){
    std::pair<bool, QString> validationResult = control->verifReservationCarte(std::make_pair(pos->getx(), pos->gety()));
    bool isValid = validationResult.first;
    const QString& message = validationResult.second;

    if(isValid){
        modalPopup* validation = new modalPopup(this, message, "Voulez-vous valider ?");
        int result =validation->exec();

        // Check the result (optional).
        if (result == QDialog::Accepted){
            // Modification
            pageJeu::handleReservationCarte(pos);
        }
        delete validation;

        vPyramide->changerPointeurs();
        setLabelJC();
        update();
    }
    else{
        popUpInfo* infos = new popUpInfo(nullptr, message.toStdString());
        infos->show();
    }
}


void pageJeu::handleReservationCarte(position* p){
    // Ajouter achat jeton

    std::pair<int, int> coord = std::make_pair(p->getx(), p->gety());
    //const Carte* carte_tmp = control->getPyramide().getCarte(coord.first, coord.second);
    bool next = true;

    if(next){
        control->orReserverCarte(coord);
        control->changerJoueurCourant();
        control->setNouveauTour(false);
    }
}

void pageJeu::handleValidationCarte(position* p){
    std::pair<int, int> coord = std::make_pair(p->getx(), p->gety());
    const Carte* carte_tmp = control->getPyramide().getCarte(coord.first, coord.second);
    bool next = true;
    if(carte_tmp->getCapacite1()!=Capacite::None || carte_tmp->getCapacite2()!=Capacite::None){
        next = handleCapa(carte_tmp->getCapacite1(), carte_tmp->getCapacite2());
    }
    if(next){
        control->acheterCarteJoaillerie(coord);
        control->changerJoueurCourant();
        control->setNouveauTour(false);
    }
}



bool pageJeu::handleCapa(Capacite capa1, Capacite capa2){
    popUpInfo* info_nouveau_tour = new popUpInfo(nullptr, "La capacité de la carte vous permetd e joueur un nouveau tour");
    popUpChoixCouleur choixCouleur(control);
    int valid;
    switch(capa1){
    case Capacite::AssociationBonus:
        valid = choixCouleur.exec();
        if(valid==QDialog::Accepted){
            return true;
        }
        break;
    case Capacite::NewTurn:
        info_nouveau_tour->show();
        control->setNouveauTour(true);
        return true;
    case Capacite::TakeJetonFromBonus:
        return true;
    case Capacite::TakeJetonToAdv:
        return true;
    case Capacite::TakePrivilege:
        if (control->getPlateau().getNbPrivileges()==0){
            //si il n'y a plus de privileges sur le plateau
            if(control->getJoueurCourant().getNbPrivileges()!=3) {

                control->getJoueurCourant().addPrivilege(control->getJoueurAdverse().supPrivilege());
            }
        } else {
            //si il y a un jetons sur le plateau, le joueur le recupere

            control->getJoueurCourant().addPrivilege(control->getPlateau().recupererPrivilege());
        }
        return true;
    case Capacite::None:
        return true;
    default:
        return true;
    }
    switch(capa2){
    case Capacite::AssociationBonus:
        valid = choixCouleur.exec();
        if(valid==QDialog::Accepted){
            return true;
        }
        break;
    case Capacite::NewTurn:
        info_nouveau_tour->show();
        control->setNouveauTour(true);
        return true;
    case Capacite::TakeJetonFromBonus:
        return true;
    case Capacite::TakeJetonToAdv:
        return true;
    case Capacite::TakePrivilege:
        if (control->getPlateau().getNbPrivileges()==0){
            //si il n'y a plus de privileges sur le plateau
            if(control->getJoueurCourant().getNbPrivileges()!=3) {

                control->getJoueurCourant().addPrivilege(control->getJoueurAdverse().supPrivilege());
            }
        } else {
            //si il y a un jetons sur le plateau, le joueur le recupere

            control->getJoueurCourant().addPrivilege(control->getPlateau().recupererPrivilege());
        }
        return true;
    case Capacite::None:
        return true;
    default:
        return true;
    }
    return false;
}




void pageJeu::paintEvent(QPaintEvent *event){
    QWidget::paintEvent(event);
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    painter.setBrush(QColor("#252525")); //On definie la couleur du pinceau en blanc
    painter.drawPolygon(rect()); //On colorie le polygone

    painter.setPen(QPen(Qt::black, 5)); //On def le pinceau comme etant de couleur noir et de taille 2 (pour faire un rebord)
    painter.drawRect(rect()); //On peind ce rectangle (permet de fair eun contour de la carte)
}

void pageJeu::afficherPrivileges(){
    for(int i = 0; i < control->getPlateau().getNbPrivileges(); i++){
        listePrivileges[i] -> show();
    }
    for(int i = control->getPlateau().getNbPrivileges(); i < listePrivileges.size(); i++){
        listePrivileges[i] -> hide();
    }
}

void pageJeu::refresh(){
    afficherPrivileges();
    vPyramide->changerPointeurs();
    joueur1->refreshJoueur(&control->getJoueurCourant());
    joueur2->refreshJoueur(&control->getJoueurCourant());
    setLabelJC();
    vPlateau->changerPointeurs();
    update();
}

void pageJeu::remplirPlateau() {
    //verification si le sac est vide
    if(!control->getPartie().getEspaceJeux().getSac().estVide()) {
        //verification si le joueur a des privilege
        if(control->getJoueurCourant().getNbPrivileges()!=0) {
            //remplir le plateau
            control->getEspaceJeux().getPlateau().remplirPlateau(control->getEspaceJeux().getSac());

            //refresh
            refresh();
        } else {
            popUpInfo* infos = new popUpInfo(nullptr, "Vous n'avez pas de privilege");
            infos->show();
            return;
        }
    } else{
        popUpInfo* infos = new popUpInfo(nullptr, "Le sac est vide, vous ne pouvez pas remplir le plateau");
        infos->show();
        return;
    }
    refresh();
}
