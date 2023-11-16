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
    type TEXT
);

CREATE TABLE infopartie (
    tour INTERGER,
    joueurCourant  INTEGER
);