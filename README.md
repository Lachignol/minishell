# Minishell

## Description
Le projet **minishell** de l'école 42 consiste à recréer un shell minimaliste en C, inspiré de Bash. Ce projet vise à comprendre les mécanismes fondamentaux d'un interpréteur de commandes Unix, tels que la gestion des processus, des redirections, des pipes et des signaux. Avec les bonus, il inclut également la gestion des opérateurs logiques (`&&`, `||`) et des parenthèses pour structurer les commandes.

---

## Fonctionnalités

### Partie Obligatoire
Le shell doit inclure les fonctionnalités suivantes :
- **Prompt interactif** : Affiche un prompt pour saisir les commandes.
- **Exécution de commandes** :
  - Supporte les commandes externes comme `ls`, `cat`, etc.
  - Gestion du chemin via la variable d'environnement `PATH`.
- **Commandes internes (built-ins)** :
  - `echo` : Affiche un message avec ou sans option `-n`.
  - `cd` : Change le répertoire courant.
  - `pwd` : Affiche le répertoire courant.
  - `export` : Ajoute ou modifie une variable d'environnement.
  - `unset` : Supprime une variable d'environnement.
  - `env` : Affiche toutes les variables d'environnement.
  - `exit` : Quitte le shell.
- **Gestion des redirections** :
  - `<` : Redirection d'entrée.
  - `>` et `>>` : Redirection de sortie (écrasement ou ajout).
- **Gestion des pipes (`|`)** :
  - Permet l'exécution de plusieurs commandes en pipeline.
- **Gestion des signaux** :
  - Interruption avec `Ctrl+C`.
  - Ignorer `Ctrl+\`.
  - Gestion de fin de fichier avec `Ctrl+D`.

---

### Bonus
Les fonctionnalités bonus ajoutent une expérience utilisateur plus riche :
1. **Opérateurs logiques (`&&`, `||`)** :
   - Permet l'exécution conditionnelle de commandes.
   - Exemple :
     ```
     cmd1 && cmd2
     ```
     Exécute `cmd2` uniquement si `cmd1` réussit (retourne un code de sortie 0).
     ```
     cmd1 || cmd2
     ```
     Exécute `cmd2` uniquement si `cmd1` échoue (retourne un code de sortie non nul).

2. **Gestion des parenthèses** :
   - Permet de structurer les commandes en groupes pour gérer les priorités d'exécution.
   - Exemple :
     ```
     (cmd1 && cmd2) || cmd3
     ```
     Les parenthèses garantissent que la logique entre `cmd1` et `cmd2` est évaluée avant d'exécuter ou non `cmd3`.

3. **Heredoc (`<<`)** :
   - Permet de lire une entrée utilisateur jusqu'à un délimiteur spécifié.

4. **Wildcards (`*`)** :
   - Expansion automatique pour correspondre aux fichiers du répertoire courant.

5. **Mode non-interactif** :
   - Exécution de commandes directement depuis un script ou une ligne de commande.

---

## Installation et Compilation
Clonez le projet depuis GitHub et compilez-le avec `make` :
- git clone <URL_du_projet>
- cd 
- minishell
- make

Pour compiler avec les bonus :
- make bonus
---

## Exemple d'Utilisation

### Partie Obligatoire
Lancez le shell avec la commande suivante :

```
./minishell
```
Exemple d'exécution interactive :

```
minishell$ echo “Hello World” Hello World minishell$ ls | grep .c > files.txt minishell$ cat files.txt
```

### Bonus : Opérateurs Logiques et Parenthèses
Exemples avec opérateurs logiques et parenthèses :

``
minishell$ mkdir test && cd test || echo “Erreur” minishell$ (echo “OK” && ls) || echo “KO”
``

---

## Authors
- Arthur Oger | 42: aoger | GitHub: arthoge
- Alexandre Scordilis | 42: ascordil | GitHub: lachignol


