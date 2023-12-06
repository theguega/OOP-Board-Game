# Problemes Splendor Duel

## Crash (IA)
* Plus de carte noble (doit aussi pas marcher pour les joueurs)

## restitution / sauvegarde
* pas encore fonctionnelle

## Liste toute les regles et specificites chiantes
- [x] = la tâche est faite
- [ ] Si aucune action obligatoire possible -> rempli le plateau puis action obligatoire
- [ ] interdit d'acheter une carte de bonus indt si on a pas de carte avec un bonus defini devant nous
- [ ] Reserver une carte est l'unique moyen d'avoir un jeton OR
- [ ] Chaque jeton Or est un joker qui remplace un jeton de couleur au choix
- [ ] Des qu'un joueur a 3 ou 6 couronnes il prend une carte Noble et applique la capacite

## Conditions de victoire
- [ ] \+ de 20 pts de prestige sur ses cartes joaillerie et Noble
- [ ] \+ de 10 couronnes sur ses cartes joaillerie
- [ ] \+ de 10 pts de prestige d'une même couleur de bonus (indt compris)

## Capacites
- [ ] NewTurn : le joueur finit son tour et en joue un nouveau
- [ ] AssociationBonus : associe une carte de bonus indt avec les cartes du bonus de son choix
- [ ] TakeJetonFromBonus : prend 1 jeton de la couleur du bonus de la carte, s'il n'y en a plus, c'est sans effet
- [ ] TakePrivilege : prend un privilege, a son adversaire si besoin
- [ ] TakeJettonToAdv : prend 1 jeton gemme ou perle a l'adversaire. Pas de jeton Or et sans effet si l'adv n'a pas de jetons

