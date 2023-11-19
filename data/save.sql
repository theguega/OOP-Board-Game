CREATE TABLE plateau (
    i INTEGER,
    j INTEGER,
    couleur TEXT
);

CREATE TABLE pyramide (
    i INTEGER,
    j INTEGER,
    id INTEGER
);

CREATE TABLE joueur (
    id INTEGER,
    nom TEXT,
    prenom TEXT,
    type TEXT,
    privileges INTEGER
);

CREATE TABLE infopartie (
    tour INTERGER,
    joueurCourant  INTEGER
);

CREATE TABLE jetons_joueur (
    id_joueur INTEGER,
    couleur TEXT
);

CREATE TABLE cartes_joueur (
    id_joueur INTEGER,
    id_carte INTEGER
);