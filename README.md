# HEIG-VD - Projet de Groupe

## Idées pour le projet

- Discord-like (Idée proposée par Alberto)
- Un site qui permet de recommander des jeux entres amis, gestion de comptes, ajouter des amis, recommander des jeux (Idée proposée par Alberto)
- Un site qui permet de pin point une localisation et dire s'il y a eu une voiture grave stylé et on pourrait rechercher dans une liste des voitures qui existent. (Idée proposée par Alberto)
- Gestionnaire de mot de passe:
  - Les utilisateurs doivent pouvoir stocker:
    - Des identifiants de site web (nom d'utilisateur et mot de passe)
    - Cartes de crédit
    - Mots de passe wifi
  - Les données sont chiffrées localement avant l'envoi au serveur (le serveur ne reçoit jamais de données non-chiffrées)
  - Utilisation de suites cryptographique adaptées
  - Les utilisateurs déchiffre la base de données des mots de passes avec un master password (pas de mécanisme de récupération d'urgence prévu, possible si le temps le permet)
  - La synchronisation se fait automatiquement mais peut être demandée manuellement


## Gestionnaire de mot de passe

### Client

Client desktop avec Qt.

### Stockage des mots de passe

Les mots de passe seront stockés dans un fichier appelé **vault**. Le format de ce fichier est encore à définir mais pourrait s'inspirer du format ![Keepass KDBX](https://keepass.info/help/kb/kdbx.html).

### Synchronisation

La synchronisation entres différents clients consiste à uploader la *vault* chiffrée sur un serveur et tracker les versions de ce fichier.

Le processus de **download** est le suivant:

Le client:

1. Télécharge la *vault* depuis le serveur
2. Vérifie si la vault téléchargée est plus récente que la *vault* locale
2. Déchiffre la vault en mémoire et vérifie son intégrité
3. Sérialise la vault en JSON ou XML
4. Si ok, remplace la *vault* en local par le fichier téléchargé.

Le processus d'**upload** est le suivant:

Le client:

1. Considère la *vault* en local (avant modifications) comme la *base*
2. Télécharge, déchiffre et vérifie l'intégrité de la dernière version de la *vault* auprès du serveur que l'on traite comme la *remote*
3. Compare la *base*, la *remote* et la *diff* (modification faites en local à la base).
  - Ajoute les modifications de la *remote* qui n'ont pas été modifiée dans la *diff* à la *base*
  - Ajoute les modifications de la *diff* (indifféremment de si elles ont été modifiées par la *remote*) à la *base*.
4. Chiffre la *base* résultante et calcule le tag d'intégrité
5. Mets à jour le header de la *vault*
6. Upload la *vault* vers le serveur
