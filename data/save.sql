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

