CREATE TABLE carte_noble (
    id INTEGER PRIMARY KEY,
    capacite TEXT,
    nb_pts_privilege INTEGER NOT NULL
);

CREATE TABLE carte (
    id INTEGER PRIMARY KEY,
    type TEXT NOT NULL,
    prix_blanc INTEGER NOT NULL,
    prix_bleu INTEGER NOT NULL,
    prix_vert INTEGER NOT NULL,
    prix_rouge INTEGER NOT NULL,
    prix_noir INTEGER NOT NULL,
    prix_perle INTEGER NOT NULL,
    prix_joker INTEGER NOT NULL,
    capacite TEXT,
    couleur_bonus TEXT,
    nb_bonus INTEGER,
    nb_couronnes INTEGER,
    nb_pts_victoire INTEGER,
);

--Cartes Noble
INSERT INTO carte_noble (capacite, nb_pts_privilege) VALUES ('TakeJetonToAdv', 2);
INSERT INTO carte_noble (capacite, nb_pts_privilege) VALUES ('TakePrivilege', 2);
INSERT INTO carte_noble (capacite, nb_pts_privilege) VALUES ('NewTurn', 2);
INSERT INTO carte_noble (capacite, nb_pts_privilege) VALUES ('', 3);

--Cartes Niveau 1

--Cartes Niveau 2

--Cartes Niveau 3