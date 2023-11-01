-- Fichier pour taper les requetes SQLite
-- Pour voir la BDD en mode graphique : extension SQLite sur VSCode
-- Execution : sqlite3 Data.sqlite < query.sql

-- Création de la table "jetons" pour définir les différents types de jetons
CREATE TABLE jetons (
    id INTEGER PRIMARY KEY,
    couleur TEXT NOT NULL,
    nombre_max INTEGER NOT NULL
);

-- Insertion des types de jetons avec leur nombre maximal
INSERT INTO jetons (couleur, nombre_max) VALUES ('ROUGE', 4);
INSERT INTO jetons (couleur, nombre_max) VALUES ('BLEU', 4);
INSERT INTO jetons (couleur, nombre_max) VALUES ('VERT', 4);
INSERT INTO jetons (couleur, nombre_max) VALUES ('NOIR', 4);
INSERT INTO jetons (couleur, nombre_max) VALUES ('BLANC', 4);
INSERT INTO jetons (couleur, nombre_max) VALUES ('OR', 3);
INSERT INTO jetons (couleur, nombre_max) VALUES ('PERLE', 2);
