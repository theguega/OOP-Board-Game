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
    pseudo TEXT,
    type_joueur TEXT,
    privileges INTEGER,
    ptsPrestige INTEGER,
    nbCouronnes INTEGER
);

CREATE TABLE infopartie (
    tour INTEGER,
    joueurCourant  INTEGER
);

CREATE TABLE jetons_joueur (
    id_joueur INTEGER,
    couleur TEXT
);

CREATE TABLE cartes_joueur (
    id_joueur INTEGER,
    id_carte INTEGER,
    noble INTEGER,
    reserve INTEGER,
    couleur_associe INTEGER
);
