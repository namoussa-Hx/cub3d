// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// size_t    count_strings(const char *s, char c)
// {
//     size_t    nb_strings;

//     nb_strings = 0;
//     while (*s != '\0')
//     {
//         if (*s != c)
//         {
//             while (*s != '\0' && *s != c)
//                 s++;
//             nb_strings++;
//             continue ;
//         }
//         s++;
//     }
//     return (nb_strings);
// }

// const char    *dup_word(char **dest, const char *src, char c)
// {
//     size_t    len;
//     size_t    i;

//     while (*src == c)
//         src++;
//     len = 0;
//     while (src[len] != '\0' && src[len] != '\n' && src[len] != c)
//             len++;
//     if(len == 0)
//         return (NULL);
//     *dest = (char *)malloc(sizeof(char) * (len + 1));
//     if (*dest == NULL)
//         return (NULL);
//     i = 0;
//     while (i < len)
//     {
//         (*dest)[i] = src[i];
//         i++;
//     }
//     (*dest)[i] = '\0';
//     src += len + 1;
//     return (src);
// }

// void    free_strs(char ***strs, size_t len)
// {
//     size_t    i;

//     i = 0;
//     while (i < len)
//     {
//         free((*strs)[i]);
//         i++;
//     }
//     free(*strs);
//     *strs = NULL;
// }

// char    **ft_split(const char *s, char c)
// {
//     char    **strs;
//     size_t    nbr_strings;
//     size_t    i;

//     printf("s = %s\n", s);
//     if (s == NULL)
//         return (NULL);
//     printf("s = %s\n", s);
//     nbr_strings = count_strings(s, c);
//     printf("nbr_strings = %zu\n", nbr_strings);
//     if(nbr_strings != 3)
//     {
//         printf("nbr_strings = %zu\n", nbr_strings);
//         return (NULL);
//     }
//     strs = (char **)malloc(sizeof(char *) * (nbr_strings + 1));
//     if (strs != NULL)
//     {
//         strs[nbr_strings] = NULL;
//         i = 0;
//         while (i < nbr_strings)
//         {
//             s = dup_word(strs + i, s, c);
//             if (s == NULL)
//             {
//                 free_strs(&strs, i);
//                 return (NULL);
//             }
//             i++;
//         }
//     }
//     return (strs);
// }
// int main ()
// {
//     char *str = "23, 45, 67";
//     char **str2 = ft_split(str, ' ');
//     printf("%s\n", str2[0]);
//     printf("%s\n", str2[1]);
//     printf("%s\n", str2[2]);
//     return (0);

// }
