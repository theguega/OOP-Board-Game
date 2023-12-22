#include <QScreen>
#include <QSize>
#include <QApplication>
#include "pageCreation.h"
#include "toutesPages.h"
#include "pageJeu.h"
#include <QPalette>




pageJeu::pageJeu(QString statut_partie, QString pseudo_j_1, type type_j_1, QString pseudo_j_2, type type_j_2, QWidget *parent) : QWidget(parent) {
    setWindowIcon(QIcon("gif/splendor.jpg"));
    setWindowTitle("SplendorDuel");

    control = new Controller(statut_partie, pseudo_j_1, type_j_1, pseudo_j_2, type_j_2);
    if(statut_partie=="New")
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

    boutonSauvegarder = new QPushButton("Sauvegarder");
    connect(boutonSauvegarder, &QPushButton::clicked, this, [this](){
        control->sauvegardePartie();
        sauvegardeFait = true;
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

    partieBasse -> addWidget(boutonSauvegarder);
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
    connect(vPlateau, &vuePlateau::signalValiderPrivilegeAppuye, this, &pageJeu::validerSelectionJetonPrivi);
    connect(vPyramide, &vuePyramide::cardClicked, this, &pageJeu::validerSelectionCarte);
    connect(vPyramide, &vuePyramide::cardClickedResa, this, &pageJeu::validerResaCarte);
    connect(vPyramide, &vuePyramide::paquetClique, this, &pageJeu::validerResaCartePioche);
    connect(joueur1, &pageJoueur::acheterCarteReservee, this, &pageJeu::validerAchatCarteReservee);
    connect(joueur2, &pageJoueur::acheterCarteReservee, this, &pageJeu::validerAchatCarteReservee);
    connect(bSac, &QPushButton::clicked, this, &pageJeu::remplirPlateau);

    if (control -> getJoueurCourant().getTypeDeJoueur() == type::IA)
        control -> Tour_ia();

    refresh();
}




void pageJeu::validerSelectionJeton() {
    if(capa_en_cours.first == false && resa_en_cours == false){       // Action obligatoire recup jeton
        std::pair<bool, QString> validationResult = control->verifJetons(vPlateau->getSelectionJetons());   // Verif de la validite de la selection de jetons
        bool isValid = validationResult.first;
        const QString& message = validationResult.second;

        // Traiter le résultat de la validation
        if(isValid){
            control->recupererJetons(vPlateau->getSelectionJetons());
            control->changerJoueurCourantGraphique();

            refresh();
        }
        else{
            popUpInfo* infos = new popUpInfo(nullptr, message.toStdString());
            connect(this, &pageJeu::fermerPopUp, infos, &popUpInfo::close);
            infos->show();
        }
    } else if (capa_en_cours.first == true) {        // correspond à la récupération de jeton lors d'une capacité
        std::vector<std::pair<int, int>> coord = vPlateau->getSelectionJetons();
        if(coord.size() == 0)
        {
            popUpInfo* infos = new popUpInfo(nullptr, "Veuillez sélectionner un jeton");
            connect(this, &pageJeu::fermerPopUp, infos, &popUpInfo::close);
            infos->show();
        } else if(coord.size() > 1)
        {
            popUpInfo* infos = new popUpInfo(nullptr, "Vous ne pouvez sélectionner qu'un seul jeton grâce à votre capacité");
            connect(this, &pageJeu::fermerPopUp, infos, &popUpInfo::close);
            infos->show();
        } else
        {
            const Jeton* j_tmp = control->getPlateau().getJeton(coord[0].first, coord[0].second);
            if(j_tmp->getCouleur() == capa_en_cours.second)
            {
                control->recupererJetons(vPlateau->getSelectionJetons());
                vPyramide->setEnabled(true);
                vPlateau->getBoutonValiderPriv()->setEnabled(true);
                bSac->setEnabled(true);
                capa_en_cours = make_pair(false, Couleur::INDT);
                control->changerJoueurCourantGraphique();
                control->setNouveauTour(false);
                refresh();
            }else
            {
                popUpInfo* infos = new popUpInfo(nullptr, "Vous devez sélectionner un jeton de la couleur de la carte");
                connect(this, &pageJeu::fermerPopUp, infos, &popUpInfo::close);
                infos->show();
            }
        }
    }
    else if(resa_en_cours == true){
        std::vector<std::pair<int, int>> coord = vPlateau->getSelectionJetons();
        if(coord.size() == 0)
        {
            popUpInfo* infos = new popUpInfo(nullptr, "Veuillez sélectionner un jeton Or");
            //connect(this, &pageJeu::fermerPopUp, infos, &popUpInfo::close);
            infos->show();
        } else if(coord.size() > 1)
        {
            popUpInfo* infos = new popUpInfo(nullptr, "Vous ne pouvez sélectionner qu'un seul jeton Or");
            connect(this, &pageJeu::fermerPopUp, infos, &popUpInfo::close);
            infos->show();
        } else
        {
            const Jeton* j_tmp = control->getPlateau().getJeton(coord[0].first, coord[0].second);
            if(j_tmp->getCouleur() == Couleur::OR)
            {
                control->recupererJetons(vPlateau->getSelectionJetons());
                vPyramide->setEnabled(true);
                vPlateau->getBoutonValiderPriv()->setEnabled(true);
                bSac->setEnabled(true);
                resa_en_cours = false;
                control->changerJoueurCourantGraphique();
                control->setNouveauTour(false);
                refresh();
            }else
            {
                popUpInfo* infos = new popUpInfo(nullptr, "Vous devez sélectionner un jeton Or");
                    connect(this, &pageJeu::fermerPopUp, infos, &popUpInfo::close);
                infos->show();
            }
        }
    }

    popUpInfo* info_rendre_jeton = new popUpInfo(nullptr, "Il faut rendre les jetons en trop!");
    popUpChoixJetonRendre* popUpRendu = new popUpChoixJetonRendre(control);
    connect(this, &pageJeu::fermerPopUp, info_rendre_jeton, &popUpInfo::close);



    while (control->getJoueurCourant().getNbJetons()>10) {
        Couleur coulRendu;
        if (popUpRendu->exec() == QDialog::Accepted) {
            coulRendu = popUpRendu->getSelectedOption();
            if(coulRendu != Couleur::INDT){
                control->getJoueurCourant().supJetonNb(1,coulRendu,control->getEspaceJeux());
                if(capa_en_cours.first==false){
                    control->changerJoueurCourantGraphique();
                }
            }
        }
    }
}




void pageJeu::validerSelectionJetonPrivi() {
    // Appeler la méthode verifJetons avec la sélection actuelle de la vue
    std::pair<bool, QString> validationResult = control->verifJetons(vPlateau->getSelectionJetons());
    bool isValid = validationResult.first;
    const QString& message = validationResult.second;

    // Traiter le résultat de la validation
    if(isValid){
        if(control->getJoueurCourant().getNbPrivileges() >= vPlateau->getSelectionJetons().size()) {

            for (int i = 1; i <= vPlateau->getSelectionJetons().size();i++){
                control -> getEspaceJeux().getPlateau().poserPrivilege(control -> getJoueurCourant().supPrivilege());
            }

            control->recupererJetons(vPlateau->getSelectionJetons());

            refresh();
        }
        else{
            const QString& message = " Pas assez de privileges ! ";
            popUpInfo* infos = new popUpInfo(nullptr, message.toStdString());
            connect(this, &pageJeu::fermerPopUp, infos, &popUpInfo::close);
            infos->show();
        }
    }
    else{
        popUpInfo* infos = new popUpInfo(nullptr, message.toStdString());
        connect(this, &pageJeu::fermerPopUp, infos, &popUpInfo::close);
        infos->show();
    }
}




void pageJeu::validerSelectionCarte(position* pos){
    std::pair<bool, QString> validationResult = control->verifAchatCarte(std::make_pair(pos->getx(), pos->gety()));
    bool isValid = validationResult.first;
    const QString& message = validationResult.second;

    if(isValid){    // Achat valide
        modalPopup* validation = new modalPopup(this, message, "Voulez-vous valider ?");
        int result =validation->exec();
        if (result == QDialog::Accepted){
            pageJeu::handleValidationCarte(pos);
        }
        delete validation;
        refresh();
    }
    else{           // Achat impossible
        popUpInfo* infos = new popUpInfo(nullptr, message.toStdString());
        infos->show();
    }
}

void pageJeu::handleValidationCarte(position* p){
    std::pair<int, int> coord = std::make_pair(p->getx(), p->gety());
    const Carte* carte_tmp = control->getPyramide().getCarte(coord.first, coord.second);
    popUpInfo* info_nouveau_tour = new popUpInfo(nullptr, "La capacité de la carte vous permet de joueur un nouveau tour");
    popUpInfo* info_take_jeton_from_bonus = new popUpInfo(nullptr, "La capacité de la carte vous permet de recuperer un jeton de la couleur du bonus de la carte. Veuillez sélectionner un jeton");

    popUpChoixAssociationBonus* popUpAssos = new popUpChoixAssociationBonus(control);
    popUpChoixJetonAdv* popUpAdv = new popUpChoixJetonAdv(control);

    connect(this, &pageJeu::fermerPopUp, info_nouveau_tour, &popUpInfo::close);
    connect(this, &pageJeu::fermerPopUp, info_take_jeton_from_bonus, &popUpInfo::close);

    Couleur coulAsso;
    Couleur coulAdv;


    if(carte_tmp->getCapacite1()!=Capacite::None){

        switch(carte_tmp->getCapacite1()){

        case Capacite::AssociationBonus:
            if (popUpAssos->exec() == QDialog::Accepted) {
                coulAsso = popUpAssos->getSelectedOption();
                if(coulAsso != Couleur::INDT){
                    control->acheterCarteJoaillerie(coord, coulAsso);
                    if(capa_en_cours.first==false){
                        control->changerJoueurCourantGraphique();
                    }
                }
            }
            break;

        case Capacite::NewTurn:
            info_nouveau_tour->show();
            connect(this, &pageJeu::fermerPopUp, info_nouveau_tour, &popUpInfo::close);
            control->acheterCarteJoaillerie(coord);
            control->setNouveauTour(true);
            control->changerJoueurCourantGraphique();
            control->setNouveauTour(false);
            break;

        case Capacite::TakeJetonFromBonus:
            if(control->getPlateau().contientCouleur(carte_tmp->getBonus().getCouleur())){
                info_take_jeton_from_bonus->show();
                //connect(this, &pageJeu::fermerPopUp, info_take_jeton_from_bonus, &popUpInfo::close);
                control->acheterCarteJoaillerie(coord);
                //permet de forcer le joueur a recup un jeton
                capa_en_cours = std::make_pair(true, carte_tmp->getBonus().getCouleur());
                vPyramide->setEnabled(false);
                vPlateau->getBoutonValiderPriv()->setEnabled(false);
                bSac->setEnabled(false);
            }
            break;

        case Capacite::TakeJetonToAdv:
            if (popUpAdv->exec() == QDialog::Accepted) {
                coulAdv = popUpAdv->getSelectedOption();
                if(coulAdv != Couleur::INDT){
                    control->acheterCarteJoaillerie(coord);
                    const Jeton &jeton = control->getJoueurAdverse().RecupJetonCoul(coulAdv);
                    control->getJoueurCourant().addJeton(jeton);
                    if(capa_en_cours.first==false){
                        control->changerJoueurCourantGraphique();
                    }
                }
            }
            break;

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
            control->acheterCarteJoaillerie(coord);
            control->changerJoueurCourantGraphique();
            break;

        default:
            break;
        }
    }
    else{
        control->acheterCarteJoaillerie(coord);
        if(capa_en_cours.first==false){
            control->changerJoueurCourantGraphique();
            control->setNouveauTour(false);
        }
    }
}




void pageJeu::validerResaCartePioche(int nivPioche){
    bool isValidOr;
    QString messageOr;

    if(!vPlateau->selecteOr()){
        isValidOr = false;
        messageOr = QString("Sélectionnez un 2 jeton Or.");

    }
    else {
        std::pair<bool, QString> validationResultJeton = control->verifJetonOr(std::make_pair(vPlateau->selecteOr()->getx(), vPlateau->selecteOr()->gety()));
        isValidOr = validationResultJeton.first;
        messageOr = validationResultJeton.second;
    }

    std::pair<bool, QString> validationResult = control->verifReservationCartePioche(nivPioche);
    bool isValid = validationResult.first;
    const QString& message = validationResult.second;


    if(isValid && isValidOr){
        modalPopup* validation = new modalPopup(this, message, "Voulez-vous valider ?");
        int result =validation->exec();

        // Check the result (optional).
        if (result == QDialog::Accepted){
            // Modification
            pageJeu::handleReservationCartePioche(nivPioche, vPlateau->selecteOr());
        }
        delete validation;
    }
    else if (!isValid){
        popUpInfo* infos = new popUpInfo(nullptr, message.toStdString());
        connect(this, &pageJeu::fermerPopUp, infos, &popUpInfo::close);
        infos->show();
    }
    else if (!isValidOr){
        popUpInfo* infos = new popUpInfo(nullptr, messageOr.toStdString());
        connect(this, &pageJeu::fermerPopUp, infos, &popUpInfo::close);
        infos->show();
    }

    refresh();

    /*// alternative
    std::pair<bool, QString> validationResult = control->verifReservationCarte();
    bool isValid = validationResult.first;
    const QString& message = validationResult.second;

    if(isValid){    // Resa valide
        modalPopup* validation = new modalPopup(this, message, "Voulez-vous valider ?");
        int result =validation->exec();
        if (result == QDialog::Accepted){
            pageJeu::handleValidationCarte(pos);
        }
        delete validation;
        refresh();
    }
    else{           // Resa impossible
        popUpInfo* infos = new popUpInfo(nullptr, message.toStdString());
        infos->show();
    }*/

}




void pageJeu::handleReservationCartePioche(int nivPioche, position* pJ){
    std::pair<int, int> coordJeton  = std::make_pair(pJ->getx(), pJ->gety());
    std::vector<std::pair<int, int>> tmp;
    tmp.push_back(coordJeton);

    //std::pair<int, int> coord = std::make_pair(p->getx(), p->gety());
    //const Carte* carte_tmp = control->getPyramide().getCarte(coord.first, coord.second);
    bool next = true;

    if(next){
        control->orReserverCartePioche(nivPioche);
        control->recupererJetons(tmp);
        control->changerJoueurCourantGraphique();
        control->setNouveauTour(false);
    }
}




void pageJeu::validerResaCarte(position* pos){
    /*bool isValidOr;
    QString messageOr;

    if(vPlateau->selecteOr()== nullptr){
        isValidOr = false;
        messageOr = QString("Sélectionnez un 3 jeton Or.");

    }
    else {
        std::pair<bool, QString> validationResultJeton = control->verifJetonOr(std::make_pair(vPlateau->selecteOr()->getx(), vPlateau->selecteOr()->gety()));
        isValidOr = validationResultJeton.first;
        messageOr = validationResultJeton.second;
    }


    std::pair<bool, QString> validationResult = control->verifReservationCarte(std::make_pair(pos->getx(), pos->gety()));
    bool isValid = validationResult.first;
    const QString& message = validationResult.second;

    if(isValid && isValidOr){
        modalPopup* validation = new modalPopup(this, message, "Voulez-vous valider ?");
        int result =validation->exec();

        // Check the result (optional).
        if (result == QDialog::Accepted){
            // Modification
            pageJeu::handleReservationCarte(pos, vPlateau->selecteOr());
        }
        delete validation;
    }
    else if (!isValid){
        popUpInfo* infos = new popUpInfo(nullptr, message.toStdString());
        connect(this, &pageJeu::fermerPopUp, infos, &popUpInfo::close);
        infos->show();
    }
    else if (!isValidOr){
        popUpInfo* infos = new popUpInfo(nullptr, messageOr.toStdString());
        connect(this, &pageJeu::fermerPopUp, infos, &popUpInfo::close);
        infos->show();
    }

    refresh();*/

    // alternative
    std::pair<bool, QString> validationResult = control->verifReservationCarte();
    bool isValid = validationResult.first;
    const QString& message = validationResult.second;

    if(isValid){    // Resa valide
        modalPopup* validation = new modalPopup(this, message, "Voulez-vous valider ?");
        int result =validation->exec();
        if (result == QDialog::Accepted){
            pageJeu::handleReservationCarte(pos);
        }
        delete validation;
        refresh();
    }
    else{           // Resa impossible
        popUpInfo* infos = new popUpInfo(nullptr, message.toStdString());
        infos->show();
    }

}




void pageJeu::handleReservationCarte(position* p, position* pJ){
    /*// Ajouter achat jeton
    std::pair<int, int> coordJeton  = std::make_pair(pJ->getx(), pJ->gety());
    std::vector<std::pair<int, int>> tmp;
    tmp.push_back(coordJeton);

    std::pair<int, int> coord = std::make_pair(p->getx(), p->gety());
    //const Carte* carte_tmp = control->getPyramide().getCarte(coord.first, coord.second);
    bool next = true;

    if(next){
        control->orReserverCarte(coord);
        control->recupererJetons(tmp);
        control->changerJoueurCourantGraphique();
        control->setNouveauTour(false);
    }*/

    // alternative
    std::pair<int, int> coord = std::make_pair(p->getx(), p->gety());
    control->orReserverCarte(coord);
    resa_en_cours = true;
    vPyramide->setEnabled(false);
    vPlateau->getBoutonValiderPriv()->setEnabled(false);
    bSac->setEnabled(false);
    popUpInfo* infoResa = new popUpInfo(nullptr, "Veuillez prendre un jeton Or");
    infoResa->show();
    update();
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
    for(unsigned int i = 0; i < control->getPlateau().getNbPrivileges(); i++){
        listePrivileges[i] -> show();
    }
    for(unsigned int i = control->getPlateau().getNbPrivileges(); i < listePrivileges.size(); i++){
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
    emit fermerPopUp();
    sauvegardeFait = false;
    update();
}




void pageJeu::remplirPlateau() {
    //verification si le sac est vide
    if(!control->getPartie().getEspaceJeux().getSac().estVide()) {
        Plateau& plateau = control->getPartie().getEspaceJeux().getPlateau();
        Sac& sac = control->getPartie().getEspaceJeux().getSac();

        qDebug()<<"Le joueur rempli le plateau :\n" << plateau << '\n';

        //on donne un privilege au joueur adverse
        control->donPrivilegeAdverse();
        //on remplit le plateau
        plateau.remplirPlateau(sac);

        qDebug()<<"Nouveau plateau : \n" << plateau;
    } else{
        popUpInfo* infos = new popUpInfo(nullptr, "Le sac est vide, vous ne pouvez pas remplir le plateau");
        connect(this, &pageJeu::fermerPopUp, infos, &popUpInfo::close);
        infos->show();
        return;
    }
    refresh();
    update();
}




void pageJeu::validerAchatCarteReservee(const Carte* carte){
    if(&control->getJoueurCourant() == joueur1->getJoueur()){
        if(joueur1->positionDansMap(carte) != -1){
            if(control->verifAchatCarte(carte)){
                return;
            }
            else{
                popUpInfo* infos = new popUpInfo(nullptr, "Vous ne pouvez pas acheter cette carte");
                connect(this, &pageJeu::fermerPopUp, infos, &popUpInfo::close);
            }
        }
        else{
            popUpInfo* infos = new popUpInfo(nullptr, "Vous n'avez pas cette carte");
            connect(this, &pageJeu::fermerPopUp, infos, &popUpInfo::close);
        }
    }
    else if(&control->getJoueurCourant() == joueur2->getJoueur()){
        if(joueur1->positionDansMap(carte) != -1){
            if(control->verifAchatCarte(carte)){
                return;
            }
            else{
                popUpInfo* infos = new popUpInfo(nullptr, "Vous ne pouvez pas acheter cette carte");
                connect(this, &pageJeu::fermerPopUp, infos, &popUpInfo::close);
            }
        }
        else{
            popUpInfo* infos = new popUpInfo(nullptr, "Vous n'avez pas cette carte");
            connect(this, &pageJeu::fermerPopUp, infos, &popUpInfo::close);
        }
    }
    refresh();
}
