#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {

    // La chaine de caractères à traiter.
    char str[] = "1452/257/1";
    // La définitions de séparateurs connus.
    const char * separators = "/";
    int valeurX,valeurY,valeurT;
    // On cherche à récupérer, un à un, tous les mots (token) de la phrase
    // et on commence par le premier.
    char * strToken = strtok ( str, separators );
    for(int i=0;i<3;i++)
    {
        if(i==0)
        {
            valeurX=(int)strToken;
        }
        if(i==1)
        {
            valeurY=(int)strToken;
        }
        if(i==2)
        {
            valeurT=(int)strToken;
        }
        strToken = strtok ( NULL, separators );
    }
    printf("X= %s,Y= %s,T= %s",valeurX,valeurY,valeurT);
    return EXIT_SUCCESS;
}