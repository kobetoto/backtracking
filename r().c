/* ************************************************************************** */
/*   rip.c  —  garde ta structure initiale, juste les corrections nécessaires */
/*   Fonctions autorisées : puts, write                                       */
/* ************************************************************************** */

#include <stdlib.h>   /* strdup, free */
#include <unistd.h>   /* write */
#include <string.h>   /* write */
#include <stdlib.h>   /* write */

/* petite utilité pour puts-like avec write */
static int  ft_strlen(const char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return (i);
}
static void ft_puts(const char *s)
{
    write(1, s, ft_strlen(s));
    write(1, "\n", 1);
}

/* -------------------------------------------------------------------------- */
/* 1) Calcule le **nombre total** de parenthèses à supprimer (remL + remR)    */
/* -------------------------------------------------------------------------- */
int ft_balance(const char *src)
{
    int open = 0;
    int remR = 0;
    int i = 0;

    while (src[i])
    {
        if (src[i] == '(')
            open++;
        else if (src[i] == ')')
        {
            if (open)
                open--;
            else
                remR++;
        }
        i++;
    }
    return (open + remR);   /* total à supprimer */
}

/* -------------------------------------------------------------------------- */
/* 2) Backtracking — conserve ta logique, mais :                              */
/*    • avance avec i+1                                                        */
/*    • utilise une chaîne DUPLIQUÉE (modifiable)                              */
/* -------------------------------------------------------------------------- */
void backTrack(char *src, int changes, int pos, int balance)
{
    int i, c;

    if (changes == balance && ft_balance(src) == 0)
    {
        ft_puts(src);
        return;
    }
    i = pos;
    while (src[i])
    {
        if (src[i] == '(' || src[i] == ')')
        {
            c = src[i];
            src[i] = ' ';                           /* suppression */
            backTrack(src, changes + 1, i + 1, balance); /* !! i+1 */
            src[i] = c;                             /* undo */
        }
        i++;
    }
}

/* -------------------------------------------------------------------------- */
/* 3) main : duplique argv[1] avant de modifier                                */
/* -------------------------------------------------------------------------- */
int main(int ac, char **av)
{
    if (ac != 2 || *av[1] == '\0')
        return (1);

    char *word = strdup(av[1]);           /* copie modifiable */
    if (!word)
        return (1);

    int balance = ft_balance(word);
    if (balance == 0)                     /* déjà équilibré */
    {
        ft_puts(word);
        free(word);
        return (0);
    }
    backTrack(word, 0, 0, balance);

    free(word);
    return (0);
}
