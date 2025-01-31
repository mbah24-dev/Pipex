# 🚀 Pipex 

<p align="center">
  <img src="https://github.com/mbah24-dev/mbah24-dev/blob/main/42_badges/pipexe.png" alt="FDF 42 project badge"/>
</p>

Bienvenue dans **Pipex** ! Un projet emblématique de l'école **42** qui va te faire comprendre en profondeur les pipes et la redirection en **C** ! 🛠️💡

## 📌 Sujet

L'objectif de Pipex est de **reproduire** le fonctionnement de la commande shell suivante :

```sh
< file1 cmd1 | cmd2 > file2
```

Ce projet t'apprend à manipuler les **processus**, les **pipes** et la **duplication de descripteurs de fichiers** en profondeur. 🤓🔍

🚨 **La triche est strictement interdite !** Respecte l'esprit de 42 et code par toi-même. 💪🔥

## 📜 Installation & Compilation

Cloner le repo :

```sh
git clone https://github.com/votre-repo/pipex.git && cd pipex
```

Compiler avec :

```sh
make
```

## 🚀 Utilisation

Exécuter Pipex avec :

```sh
./pipex file1 "cmd1" "cmd2" file2
```

Exemple concret :

```sh
./pipex input.txt "grep hello" "wc -l" output.txt
```

## 🛠️ Fonctions Autorisées

- `open`, `close`, `read`, `write`
- `malloc`, `free`, `perror`, `strerror`
- `access`, `dup`, `dup2`, `execve`
- `fork`, `pipe`, `unlink`, `wait`, `waitpid`

## 🔥 Bonus

- **Gestion du mode here_doc** (`<< LIMITER`)
- **Gestion des multiples pipes** (ex : `cmd1 | cmd2 | cmd3 | ...`)

## 🏆 Auteur

👨‍💻 **BAH Mamadou** - Étudiant @ **42** 🎓

🚀 **Bon courage et que la force des pipes soit avec toi !** 🛠️🔥
