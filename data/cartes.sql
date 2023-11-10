-- Fichier pour taper les requetes SQLite
-- Pour voir la BDD en mode graphique : extension SQLite sur VSCode
-- Execution : sqlite3 data_carte.sqlite < cartes.sql

DROP TABLE IF EXISTS carte_noble;
DROP TABLE IF EXISTS carte;

CREATE TABLE carte_noble (
    id INTEGER PRIMARY KEY,
    capacite TEXT,
    nb_pts_privilege INTEGER NOT NULL
);

CREATE TABLE carte (
    id INTEGER PRIMARY KEY,
    type_carte TEXT NOT NULL,
    prix_blanc INTEGER NOT NULL,
    prix_bleu INTEGER NOT NULL,
    prix_vert INTEGER NOT NULL,
    prix_rouge INTEGER NOT NULL,
    prix_noir INTEGER NOT NULL,
    prix_perle INTEGER NOT NULL,
    capacite1 TEXT,
    capacite2 TEXT,
    couleur_bonus TEXT,
    nb_bonus INTEGER,
    nb_couronnes INTEGER,
    nb_pts_privilege INTEGER
);

--Cartes Noble
INSERT INTO carte_noble (capacite, nb_pts_privilege) VALUES ('TakeJetonToAdv', 2);
INSERT INTO carte_noble (capacite, nb_pts_privilege) VALUES ('TakePrivilege', 2);
INSERT INTO carte_noble (capacite, nb_pts_privilege) VALUES ('NewTurn', 2);
INSERT INTO carte_noble (capacite, nb_pts_privilege) VALUES ('', 3);

--Cartes Niveau 1

INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 0, 0, 3, 0, 0, 'None', 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 0, 0, 3, 0, 0, 'TakeJetonFromBonus', 'None','vert', 1, 0, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 1, 1, 0, 1, 1, 0, 'None', 'None','vert', 1, 0, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 0, 0, 2, 2, 1, 'NewTurn', 'None','vert', 1, 0, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 3, 0, 0, 0, 2, 0, 'None', 'None','vert', 1, 0, 1);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 0, 2, 2, 0, 0, 'TakeJetonFromBonus', 'None','noir', 1, 0, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 1, 1, 1, 1, 0, 0, 'None', 'None','noir', 1, 0, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 3, 0, 0, 0, 0, 0, 'None', 'None','noir', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 2, 3, 0, 0, 0, 'None', 'None','noir', 1, 0, 1);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 2, 2, 0, 0, 0, 1, 'NewTurn', 'None','noir', 1, 0, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 2, 2, 0, 0, 0, 'TakeJetonFromBonus', 'None','rouge', 1, 0, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 1, 1, 1, 0, 1, 0, 'None', 'None','rouge', 1, 0, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 0, 0, 0, 3, 0, 'None', 'None','rouge', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 2, 0, 0, 0, 2, 1, 'NewTurn', 'None','rouge', 1, 0, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 2, 2, 0, 0, 0, 0, 'None', 'None','rouge', 1, 0, 1);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 0, 2, 2, 0, 1, 'NewTurn', 'None','bleu', 1, 0, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 0, 0, 2, 3, 0, 'None', 'None','bleu', 1, 0, 1);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 2, 0, 0, 0, 2, 0, 'TakeJetonFromBonus', 'None','bleu', 1, 0, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 0, 3, 0, 0, 0, 'None', 'None','bleu', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 1, 0, 1, 1, 1, 0, 'None', 'None','bleu', 1, 0, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 0, 2, 3, 0, 0, 'None', 'None','blanc', 1, 0, 1);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 0, 0, 2, 2, 0, 'TakeJetonFromBonus', 'None','blanc', 1, 0, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 2, 2, 0, 0, 1, 'NewTurn', 'None','blanc', 1, 0, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 3, 0, 0, 0, 0, 'None', 'None','blanc', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 1, 1, 1, 1, 0, 'None', 'None','blanc', 1, 0, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 4, 0, 0, 0, 0, 1, 'AssociationBonus', 'None','indt', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 2, 0, 2, 1, 1, 'AssociationBonus', 'None','indt', 1, 0, 1);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 2, 0, 2, 0, 1, 1, 'AssociationBonus', 'None','indt', 1, 0, 1);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 0, 0, 0, 4, 1, 'AssociationBonus', 'None','indt', 1, 0, 1);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 0, 0, 4, 0, 1, 'None', 'None','indt', 0, 0, 3);


--Cartes Niveau 2

INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 0, 0, 5, 2, 0, 'None', 'vert', 2, 0, 1);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 2, 4, 0, 0, 1, 'TakePrivilege', 'vert', 1, 0, 2);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 3, 0, 0, 4, 0, 0, 'TakeJetonToAdv', 'vert', 1, 0, 1);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 2, 2, 0, 0, 2, 1, 'None', 'vert', 1, 1, 2);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 0, 0, 2, 4, 1, 'TakePrivilege', 'noir', 1, 0, 2);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 2, 2, 2, 0, 1, 'None', 'None','noir', 1, 1, 2);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 4, 0, 3, 0, 0, 0, 'TakeJetonToAdv', 'None','noir', 1, 0, 1);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 5, 2, 0, 0, 0, 0, 'None', 'None','noir', 2, 0, 1);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 0, 2, 4, 0, 1, 'TakePrivilege', 'None','rouge', 1, 0, 2);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 3, 0, 0, 4, 0, 'TakeJetonToAdv', 'None','rouge', 1, 0, 1);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 2, 2, 2, 0, 0, 1, 'None', 'None','rouge', 1, 1, 2);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 2, 0, 0, 0, 5, 0, 'None', 'None','rouge', 2, 0, 1);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 2, 0, 0, 2, 2, 1, 'None', 'None','bleu', 1, 1, 2);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 2, 4, 0, 0, 0, 1, 'TakePrivilege', 'None','bleu', 1, 0, 2);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 0, 4, 0, 3, 0, 'TakeJetonToAdv', 'None','bleu', 1, 0, 1);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 0, 5, 2, 0, 0, 'None', 'None','bleu', 2, 0, 1);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 4, 0, 0, 0, 2, 1, 'TakePrivilege', 'None','blanc', 1, 0, 2);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 4, 0, 3, 0, 0, 'TakeJetonToAdv', 'None','blanc', 1, 0, 1);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 0, 2, 2, 2, 1, 'None', 'None','blanc', 1, 1, 2);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 5, 2, 0, 0, 0, 'None', 'None','blanc', 2, 0, 1);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 0, 6, 0, 0, 1, 'AssociationBonus', 'None','indt', 1, 2, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 6, 0, 0, 0, 1, 'AssociationBonus', 'None','indt', 1, 2, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 0, 6, 0, 0, 1, 'AssociationBonus', 'None','indt', 1, 0, 2);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 6, 0, 0, 0, 1, 'None', 'None','indt', 0, 0, 5);

--Cartes Niveau 3

INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv3', 5, 3, 0, 3, 0, 1, 'None', 'None','vert', 1, 2, 3);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv3', 0, 2, 6, 2, 0, 0, 'None', 'None','vert', 1, 0, 4);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv3', 2, 6, 2, 0, 0, 0, 'None', 'None','bleu', 1, 0, 4);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv3', 3, 0, 3, 0, 5, 1, 'None', 'None','bleu', 1, 2, 3);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv3', 0, 0, 2, 6, 2, 0, 'None', 'None','rouge', 1, 0, 4);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv3', 0, 5, 3, 0, 3, 1, 'None', 'None','rouge', 1, 2, 3);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv3', 2, 0, 0, 2, 6, 0, 'None', 'None','noir', 1, 0, 4);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv3', 3, 0, 5, 3, 0, 1, 'None', 'None','noir', 1, 2, 3);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv3', 0, 3, 0, 5, 3, 1, 'None', 'None','blanc', 1, 2, 3);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv3', 6, 2, 0, 0, 2, 0, 'None', 'None','blanc', 1, 0, 4);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv3', 0, 0, 0, 0, 8, 0, 'AssociationBonus', 'None','indt', 1, 3, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv3', 0, 0, 0, 8, 0, 0, 'AssociationBonus', 'NewTurn','indt', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite1, capacite2, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv3', 8, 0, 0, 0, 0, 0, 'None', 'None','indt', 0, 0, 6);


