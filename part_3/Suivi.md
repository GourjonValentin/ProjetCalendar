## Task list pour la partie 3
- [ ] Rechercher un contact, et proposer une complétion automatique à partir de la 3ème lettre entrée
   pour le nom (il faudra donc faire la saisie du nom de recherche caractère par caractère) - WOrk In PRogress
- [x] Afficher les rendez-vous d’un contact `print_events_for_contact`
- [x] Créer un contact (avec insertion dans la liste)
  - [x] Créer un contact `create_contact`
  - [x] Ajouter le contact à la liste des contacts `insert_sorted1`
- [ ] Créer un rendez-vous pour un contact (avec insertion dans la liste si le contact n’existe pas) ;
  - [x] Crée un rendez-vous `create_event_for_contact`
  - [ ] Recherche si le contact existe déjà
    - [x] Si oui, ajoute le rendez-vous à la liste des rendez-vous du contact `add_event_to_contact`
    - [x] Si non, crée le contact et ajoute le rendez-vous à la liste des rendez-vous du contact (appeler `create_contact` et `add_event_to_contact`)
- [x] Supprimer un rendez-vous `del_event_from_contact`
- [ ] Sauvegarder le fichier de tous les rendez-vous
- [ ] Charger un fichier de rendez-vous
- [ ] Fournir les temps de calcul pour une insertion de nouveau contact : voir point 2)


