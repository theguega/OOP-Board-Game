-- Fichier pour taper les requetes SQLite
-- Pour voir la BDD en mode graphique : extension SQLite sur VSCode
-- Execution : sqlite3 data_carte.sqlite < cartes.sql

/*
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
    capacite TEXT,
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

INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 0, 0, 3, 0, 0, 'TakeJetonFromBonus', 'vert', 1, 0, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 1, 1, 0, 1, 1, 0, 'None', 'vert', 1, 0, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 0, 0, 2, 2, 1, 'NewTurn', 'vert', 1, 0, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 3, 0, 0, 0, 2, 0, 'None', 'vert', 1, 0, 1);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 0, 2, 2, 0, 0, 'TakeJetonFromBonus', 'noir', 1, 0, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 1, 1, 1, 1, 0, 0, 'None', 'noir', 1, 0, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 3, 0, 0, 0, 0, 0, 'None', 'noir', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 2, 3, 0, 0, 0, 'None', 'noir', 1, 0, 1);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 2, 2, 0, 0, 0, 1, 'NewTurn', 'noir', 1, 0, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 2, 2, 0, 0, 0, 'TakeJetonFromBonus', 'rouge', 1, 0, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 1, 1, 1, 0, 1, 0, 'None', 'rouge', 1, 0, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 0, 0, 0, 3, 0, 'None', 'rouge', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 2, 0, 0, 0, 2, 1, 'NewTurn', 'rouge', 1, 0, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 2, 2, 0, 0, 0, 0, 'None', 'rouge', 1, 0, 1);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 0, 2, 2, 0, 1, 'NewTurn', 'bleu', 1, 0, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 0, 0, 2, 3, 0, 'None', 'bleu', 1, 0, 1);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 2, 0, 0, 0, 2, 0, 'TakeJetonFromBonus', 'bleu', 1, 0, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 0, 3, 0, 0, 0, 'None', 'bleu', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 1, 0, 1, 1, 1, 0, 'None', 'bleu', 1, 0, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 0, 0, 3, 0, 0, 'None', 'blanc', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 0, 0, 3, 0, 0, 'None', 'blanc', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 0, 0, 3, 0, 0, 'None', 'blanc', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 0, 0, 3, 0, 0, 'None', 'blanc', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 0, 0, 3, 0, 0, 'None', 'blanc', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 0, 0, 3, 0, 0, 'None', 'indt', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 0, 0, 3, 0, 0, 'None', 'indt', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 0, 0, 3, 0, 0, 'None', 'indt', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 0, 0, 3, 0, 0, 'None', 'indt', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv1', 0, 0, 0, 3, 0, 0, 'None', 'indt', 0, 1, 0);


--Cartes Niveau 2

INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv2', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);

--Cartes Niveau 3

INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv3', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv3', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv3', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv3', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv3', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv3', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv3', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv3', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv3', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv3', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv3', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv3', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);
INSERT INTO carte (type_carte, prix_blanc, prix_bleu, prix_vert, prix_rouge, prix_noir, prix_perle, capacite, couleur_bonus, nb_bonus, nb_couronnes, nb_pts_privilege) VALUES ('Niv3', 0, 0, 0, 3, 0, 0, 'None', 'vert', 1, 1, 0);

*/

