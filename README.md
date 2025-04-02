# 🚀 Pipex - 42 Project

<p align="center">
  <img src="https://github.com/mbah24-dev/mbah24-dev/blob/main/42_badges/pipexe.png" alt="Pipex 42 project badge"/>
</p>

Bienvenue sur **Pipex**, un projet du cursus **42** qui permet de recréer le fonctionnement du pipe `|` en ligne de commande ! 🔥

---

## 📌 Objectif du projet

Ce projet a pour but de nous faire comprendre **comment fonctionne les redirections et les pipes** en Unix, en recréant le comportement de la commande suivante :

```sh
$> < file1 cmd1 | cmd2 > file2
```

Ton programme devra être exécuté ainsi :

```sh
$> ./pipex file1 cmd1 cmd2 file2
```

Où il devra reproduire le comportement de :

```sh
$> < file1 cmd1 | cmd2 > file2
```

⚠️ **Attention : Pas de triche !** Ne copiez pas ce code tel quel, essayez de comprendre ce qu'il fait. 💡

---

## 🛠️ Compilation

Pour compiler le projet, utilise **Makefile** :

```sh
make
```

Cela génère l'exécutable `pipex`. 🚀

---

## 💻 Utilisation

### Syntaxe :
```sh
./pipex file1 "cmd1" "cmd2" file2
```

### Exemple d'exécution :
```sh
./pipex input.txt "cat" "wc -l" output.txt
```

Cela équivaut à :
```sh
cat < input.txt | wc -l > output.txt
```

### Gestion des **Here Document** (Bonus) 🎯

Si tu as implémenté l'option **here_doc**, alors l'utilisation sera :

```sh
./pipex here_doc LIMITER cmd1 cmd2 output.txt
```

---

## 📜 Fonctions Autorisées

- `open`
- `close`
- `read`
- `write`
- `malloc`
- `free`
- `perror`
- `strerror`
- `access`
- `dup`
- `dup2`
- `execve`
- `exit`
- `fork`
- `pipe`
- `unlink`
- `wait`
- `waitpid`

---

## 🚀 Fonctionnalités Bonus

✅ **Gestion de "here_doc"** (heredoc pour redirection d'entrée)
✅ **Gestion de plusieurs pipes** (simulation de `|` multiples)
✅ **Gestion des erreurs avancée**
✅ **Support des arguments avec espaces**

---

## 🏆 Crédits

👨‍💻 Projet réalisé par **Mamadou BAH** dans le cadre de l'école **42** 🎓

Si ce projet t'a aidé, n'hésite pas à mettre une ⭐ sur ton dépôt ! 😎🔥

---

### 🎯 Happy coding et bon courage pour 42 ! 🎯
