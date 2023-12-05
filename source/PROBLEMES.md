# Problemes Splendor Duel

## reserver carte (tout a revoir en gros mdr):
* lors de la reserevation d'un carte, il faut faire recuperer un jeton or (donc afficher plateau et recup d'abord)
* donc d'abord : plateau, puis affichage des cartes

* si pas de carte reserve : erreur quand on essaye d'acheter une carte reserver

## achat carte (tout a revoir en gros aussi...)
* voir affichage clean + debug

## recuperration de jeton :
* si le joueur recup 3 jetons mm couleur ou 2 jetons perle -> son adv recup un privilege
* la méthode ne verifiat pas si les jetons étaient à cote, même s'ils etaient alignes. Problème corrigé pour ligne et colonne, pas diago

## Crash (IA)
* l'IA choisit d'acheter une carte reserver (alors qu'elle na pas reserver de carte)
* l'IA bute apres "carte achetable avec X jetons utilises"
* l'IA va dans la pyramide/pioche 3

## Verif :
* verification et methode de fin de tour : si le joeur a 10 jetons
* ajouter la verif et la methode pour reposer des jetons

## Pioche : 
* pioche vide en IA IA sur la reservation DONE normalement 

## restitution :
* instant crash

## Liste toute les regles et specificites chiantes
- [x] : la tâche est faite
- [x] Interdiction de prendre un jeton Or avec un privilege
- [ ] Si un joueur rempli le plateau -> son adversaire recoit un privilege
- [ ] Si on doit prendre un privilege mais aucun sur le plateau on le prend a l'adversaire
- [ ] Si aucune action obligatoire possible -> rempli le plateau puis action obligatoire
- [x] Pas de jeton Or ou vide dans la selection de jeton 
- [ ] 3 jetons de même couleur ou 2 perles dans la selection -> adversaire recoit 1 privilege
- [ ] Si aucun jeton Or sur le plateau on peut pas reserver de carte
- [ ] Si deja 3 cartes reservees on peut pas reserver plus de carte
- [ ] interdit d'acheter une carte de bonus indt si on a pas de carte avec un bonus defini devant nous
- [ ] Reserver une carte est l'unique moyen d'avoir un jeton OR
- [ ] Chaque jeton Or est un joker qui remplace un jeton de couleur au choix
- [ ] Des qu'un joueur a 3 ou 6 couronnes il prend une carte Noble et applique la capacite
- [ ] Un joueur doit avoir au plus 10 jetons a la fin d'un tour (pendant on s'en fout)

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

