Le théorème de Kleene établit que les expressions régulières et les automates finis déterminent les mêmes langages. En pratique, cela signifie que pour chaque langage défini par une expression régulière, il existe un automate fini qui accepte ce langage, et vice versa.

Voyons comment appliquer cela à l'exercice 5 en utilisant une expression régulière avec la commande `grep`.

### Exercice 5

**Enoncé** : Comptez le nombre de lignes qui commencent par "if" et qui se terminent par "n" dans le fichier `/etc/bash.bashrc`.

Pour cela, nous allons utiliser la commande `grep` avec l'option `-c` pour compter les lignes et `-E` pour utiliser les expressions régulières étendues.

### Commande `grep`

L'expression régulière doit capturer les lignes qui :
1. Commencent par "if".
2. Se terminent par "n".

En notation d'expression régulière :
- `^` : Indique le début d'une ligne.
- `if` : Le texte "if".
- `.*` : Correspond à zéro ou plusieurs caractères quelconques.
- `n$` : Indique que la ligne se termine par "n".

En combinant ces éléments, l'expression régulière est `'^if.*n$'`.

La commande complète pour compter les lignes correspondantes est :

```bash
grep -c -E '^if.*n$' /etc/bash.bashrc
```

### Explication de la commande

- `grep` : Commande utilisée pour rechercher du texte.
- `-c` : Option pour compter les lignes qui correspondent au motif.
- `-E` : Option pour utiliser des expressions régulières étendues.
- `'^if.*n$'` : Expression régulière pour correspondre aux lignes commençant par "if" et se terminant par "n".
- `/etc/bash.bashrc` : Chemin du fichier à analyser.

