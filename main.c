#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LLETRES 8
#define MAX_PARAULES 10
#define MAX_LLETRESRENDICIO 10
#define MAX_FITXER 50

/* Definicio del tipus per a desar les dades de la sopa de lletres */
/* Es una proposta que podeu canviar, ampliar, etc. */

typedef struct
{
    char ll[MAX_LLETRES + 1];   /* Lletres de la paraula (comptem centinella) */
    bool enc;   /* La paraula s'ha encertat */
} paraula_t;

typedef struct
{
    int dim;        // Nombre de files = nombre de columnes */
    char *lletres;  // Taula amb les lletres
    bool *encertades;   // Les lletres son d'una paraula que s'ha encertat
    paraula_t par[MAX_PARAULES];    // Les paraules
    int n_par;  // Nombre de paraules
    int n_encerts;    // Nombre de paraules encertades
} sopa_t;

/* Aquesta funcio genera la sopa de lletres, a partir del fitxer i altres parametres */
/* que ja decidireu. En aquest cas nom�s l'emplena amb una SOPA d'EXEMPLE, es a dir */
/* que haureu de fer la vostra pr�pia. */

bool hay_letra_d(sopa_t *s, int posiciolletra, int longitud)
{
    bool resultado;
    int i;

    for(i = 0; i < longitud; i++)
    {
        if(s->lletres[posiciolletra+i] != '1')
        {
            resultado = true;
        }
        else
        {
            resultado = false;
        }
    }
    return(resultado);
}

bool hay_letra_i(sopa_t *s, int posiciolletra, int longitud)
{
    bool resultado;
    int i;

    for(i = 0; i < longitud; i++)
    {
        if(s->lletres[posiciolletra-i] != '1')
        {
            resultado = true;
        }
        else
        {
            resultado = false;
        }
    }
    return(resultado);
}

bool hay_letra_a(sopa_t *s, int posiciolletra, int longitud)
{
    bool resultado;
    int i;

    for(i = 0; i < longitud; i++)
    {
        if(s->lletres[posiciolletra - s->dim*i] != '1')
        {
            resultado = true;
        }
        else
        {
            resultado = false;
        }
    }
    return(resultado);
}

bool hay_letra_b(sopa_t *s, int posiciolletra, int longitud)
{
    bool resultado;
    int i;

    for(i = 0; i < longitud; i++)
    {
        if(s->lletres[posiciolletra + s->dim*i] != '1')
        {
            resultado = true;
        }
        else
        {
            resultado = false;
        }
    }
    return(resultado);
}


void genera_sopa(sopa_t *s)
{
    int posiciolletra, longitud, i, j, c, columna, fila;
       // Mida m�xima: 40 x 40
    s->lletres = malloc(s->dim * s->dim * sizeof(char));   // Espai per a les lletres
    s->encertades = malloc(s->dim * s->dim * sizeof(bool)); // Per saber si una lletra correspon a encert

    for(i = 0; i <s->dim * s->dim; i++)
    {
        s->lletres[i] = '1';
    }

    c = (rand() % 4) + 1; printf("opcio: %d\n", c);
    switch(c)
    {
        case 1:
        {
            for(j = 0; j < s->n_par; j++)
            {
                posiciolletra = rand() % ((s->dim)*(s->dim));
                columna = posiciolletra % s->dim;

                longitud = strlen(s->par[j].ll);

                while(longitud > s->dim - columna || hay_letra_d(s, posiciolletra, longitud))
                {
                    posiciolletra = rand() % ((s->dim)*(s->dim));
                    columna = posiciolletra % s->dim;
                }

                for(i = 0; i < longitud; i++)
                {
                    s->lletres[posiciolletra + i] = s->par[j].ll[i];
                }
            }

            for (i = 0; i < s->dim * s->dim; i++)
            {
                s->encertades[i] = false;
                if(s->lletres[i] == '1')
                {
                     // Generem una lletra aleatoriament
                    s->lletres[i] = 'A' + (rand() % ('Z'-'A' + 1));
                }
            }
            break;
        }
        //primer caso (derecha)

        case 2:
        {
            for(j = 0; j < s->n_par; j++)   //(posiciolletra)
            {
                posiciolletra = rand() % ((s->dim)*(s->dim));
                columna = posiciolletra % s->dim;

                longitud = strlen(s->par[j].ll);

                while(longitud > (columna + 1) || hay_letra_i(s, posiciolletra, longitud))
                {
                    posiciolletra = rand() % ((s->dim)*(s->dim));
                    columna = posiciolletra % s->dim;;
                }

                for(i = 0; i < longitud; i++)
                {
                    s->lletres[posiciolletra - i] = s->par[j].ll[i];
                }
            }

            for (i = 0; i < s->dim * s->dim; i++)
            {
                s->encertades[i] = false;
                if(s->lletres[i] == '1')
                {
                     // Generem una lletra aleatoriament
                    s->lletres[i] = 'A' + (rand() % ('Z'-'A' + 1));
                }
            }
            break;
        }
        //segundo caso (izquierda)

        case 3:
        {
            for(j = 0; j < s->n_par; j++)   //(posiciolletra)
            {
                posiciolletra = rand() % ((s->dim)*(s->dim));
                fila = posiciolletra / s->dim;

                longitud = strlen(s->par[j].ll);

                while(longitud > fila || hay_letra_a(s, posiciolletra, longitud))
                {
                    printf("No cabe\n");
                    posiciolletra = rand() % ((s->dim)*(s->dim));
                    fila = posiciolletra / s->dim;
                }

                for(i = 0; i < longitud; i++)
                {
                    s->lletres[posiciolletra - s->dim*i] = s->par[j].ll[i];
                }
            }

            for (i = 0; i < s->dim * s->dim; i++)
            {
                s->encertades[i] = false;
                if(s->lletres[i] == '1')
                {
                     // Generem una lletra aleatoriament
                    s->lletres[i] = 'A' + (rand() % ('Z'-'A' + 1));
                }
            }
            break;
        }
        //tercer caso (arriba)

        case 4:
        {
            for(j = 0; j < s->n_par; j++)   //(posiciolletra)
            {
                posiciolletra = rand() % ((s->dim)*(s->dim));
                fila = posiciolletra / s->dim;

                longitud = strlen(s->par[j].ll);

                while(longitud > s->dim - fila || hay_letra_b(s, posiciolletra, longitud))
                {
                    posiciolletra = rand() % ((s->dim)*(s->dim));
                    fila = posiciolletra / s->dim;
                }

                for(i = 0; i < longitud; i++)
                {
                    s->lletres[posiciolletra + s->dim*i] = s->par[j].ll[i];
                }
            }

            for (i = 0; i < s->dim * s->dim; i++)
            {
                s->encertades[i] = false;
                if(s->lletres[i] == '1')
                {
                     // Generem una lletra aleatoriament
                    s->lletres[i] = 'A' + (rand() % ('Z'-'A' + 1));
                }
            }
            break;
        }
        // cuarto paso(abajo)
    }
}

/* Mostra la sopa de lletres pel terminal */
/* En principi, NO HAURIEU DE MODIFICAR AQUEST CODI SI NO TOQUEU LES ESTRUCTURES DE DADES*/
void mostra_sopa (sopa_t *s)
{
    int j = 1;
    // Mostrem els numeros de columna
    printf("\033[0;31m");   // Color
    printf("  ");
    for (int i = 10; i < s->dim + 1; i+=10)
    {
        for (int j=0; j < 18; j++)
            printf(" ");
        printf(" %d", i/10);

    }
    printf("\n  ");
    for (int i = 0; i < s->dim; i++)
    {
        int p = (i % 10) + 1;
        p != 10 ? printf(" %d", p) : printf(" 0");
    }

    printf("\n");
    printf("\033[0m");  // Tornem al color per defecte


    // Mostrem les lletres. Cada lletra ocupa dos espais:
    // Si correspon a un encert, es marca
    for (int i = 0; i < s->dim ; i++)
    {
        printf("\033[0;31m");   // Color
        printf("%-2d", i + 1);  // Mostrar numero de linia
        printf("\033[0m");  // Tornem al color per defecte

        for (int j = 0; j < s->dim; j++)
        {
            if (s->encertades[i * s->dim + j])
            {
                printf("\033[0;42m");   // Color verd de fons
                printf(" %c", s->lletres[i * s->dim + j]);
                printf("\033[0m");  // Tornem al color per defecte
            }
            else
            {
                printf(" %c", s->lletres[i * s->dim + j]);
            }
        }
        printf("\n");
    }
    printf("\n");

    printf("Portes %d encerts.\n", s->n_encerts);
    printf("Paraules a trobar: %d\n", s->n_par - s->n_encerts);
    for (int i = 0; i < s->n_par; i++)
    {
        //if (!s->par[i].enc)
            printf("%d- ", j);
            printf("%s\n", s->par[i].ll);
            j++;
    }

}
void missatge_benvinguda ()
{
   printf("******************************************************\nUs donem la benvinguda al joc de la sopa de lletres!\n");
   printf("Autors: Nicolas Canton Vela, Raul Martin Morales, David Quintana Palomar, Judith Mateu Domingo\n*****************************************************\n");
}

void dimensio_taula(sopa_t *s)
{
    printf("De quina dimensio vols la tabla? MIN 10 MAX 40\n");
    scanf("%d", &s->dim);
    while ((s->dim>40) || (s->dim<10))
    {
        printf("Introduce un valor correcto\n");
        scanf("%d", &s->dim);
    }
}

void llegir_fitxer(sopa_t *s)
{
    //  char tab [MAX_LLETRES];
    FILE *fitxer;
    int i, j;
    i = 0;
    j = 1;
    fitxer = fopen("fitxer.txt", "r");
    if (fitxer == NULL)
    {
        printf("El fitxer no s'ha pogut obrir correctament\n");
    }
    else
    {
        while(!feof(fitxer))
        {
            fgets(s->par[i].ll, MAX_LLETRES, fitxer);
            s->par[i].ll[strcspn(s->par[i].ll, "\n")] = '\0';
            printf("%d- ", j);
            printf("%s\n", s-> par[i].ll);
            i++;
            j++;
        }
    }
    s->n_par = i;
    s->n_encerts = 0;
}


void demanar_paraula(sopa_t *s, bool *fi_joc)
{
    int nparaula, nfila, ncolumna, nlletres, i, iposicio, fposicio, direccio ;
    int trobat;
    char rendirse[MAX_LLETRESRENDICIO];
    //bool fi_joc;
   // char par_trobada[MAX_LLETRES];
   //  while ((c = getchar()) != '\n' && c != EOF) {}
   // fgets (par_trobada, 10, stdin);
    printf("Has trobat alguna paraula 0-Si 1-Et Reindeixes?\n");
    scanf("%d", &trobat);

    if(trobat ==0)
        {
           printf("Quina paraula has trobat? (indica el numero) \n");
            scanf("%d", &nparaula);
            printf("En quina fila es troba la inicial de la paraula?\n");
            scanf("%d", &nfila);
            printf("En quina columna es troba la inicial de la paraula?\n");
            scanf("%d", &ncolumna);
            printf("Entra la direccio de la paraula (1: dreta, 2: esquerra, 3: cap a baix, 4: cap a dalt)\n");
            scanf("%d", &direccio);
            nparaula = nparaula-1;
            iposicio = (nfila-1) * s->dim + (ncolumna-1);
            nlletres = strlen(s->par[nparaula].ll);
            if (direccio == 1)
                {
                    fposicio = iposicio + nlletres-1;
                    if(s->lletres[iposicio] == s->par[nparaula].ll[0])
                    {
                        s->par[nparaula].enc = true;
                        for(i = iposicio; i<= fposicio; i++)
                        {
                            s->encertades[i] = true;
                        }
                    printf("Has trobat la paraula '%s'!\n", s->par[nparaula].ll);
                    s->n_encerts += 1;


                    }
                    else
                    {
                    printf("No hi ha cap paraula a la posició que has indicat\n");
                    }
               }
            if (direccio == 2)
                {
                    fposicio = iposicio - (nlletres - 1);
                    if(s->lletres[iposicio] == s->par[nparaula].ll[0])
                    {
                        s->par[nparaula].enc = true;
                        for(i = iposicio; i >= fposicio; i--)
                        {
                            s->encertades[i] = true;
                        }
                    printf("Has trobat la paraula '%s'!\n", s->par[nparaula].ll);
                    s->n_encerts += 1;


                    }
                    else
                    {
                    printf("No hi ha cap paraula a la posició que has indicat\n");
                    }
               }
            if (direccio == 3)
                {
                    fposicio = iposicio + (nlletres-1) * s->dim;
                    if(s->lletres[iposicio] == s->par[nparaula].ll[0])
                    {
                        s->par[nparaula].enc = true;
                        for(i = 0; i< nlletres; i++)
                        {
                            s->encertades[iposicio + (i * s->dim)] = true;
                        }
                    printf("Has trobat la paraula '%s'!\n", s->par[nparaula].ll);
                    s->n_encerts += 1;


                    }
                    else
                    {
                    printf("No hi ha cap paraula a la posició que has indicat\n");
                    }
               }
            if (direccio == 4)
                {
                    fposicio = iposicio - (nlletres-1) * s->dim;
                    if(s->lletres[iposicio] == s->par[nparaula].ll[0])
                    {
                        s->par[nparaula].enc = true;
                        for(i = 0; i < nlletres; i++)
                        {
                            s->encertades[iposicio - (i* s->dim)] = true;
                        }
                    printf("Has trobat la paraula '%s'!\n", s->par[nparaula].ll);
                    s->n_encerts += 1;


                    }
                    else
                    {
                    printf("No hi ha cap paraula a la posició que has indicat\n");
                    }
               }
               *fi_joc=false;
        }
        if(trobat==1)
        {
         printf("Introdueix RENDICIO:\n");
        scanf("%s", rendirse);
        if(strcmp(rendirse, "RENDICIO")==0)
        {
        printf("T'has rendit\n");
        *fi_joc = true; //Rendicio
        }

        }
}

void missatge_comiat ()
{
   printf("******************************************************\nS'ha acabat el joc\n");
   printf("*****************************************************\n");
}
int main()
{
    bool fi;
    //char paraula_fit[MAX_FITXER];
    char par_jugador[MAX_LLETRESRENDICIO+1];
    int i = 0;
    fi=false;
    srand(time(NULL));                   // Inicializa la semilla para los números aleatorios

    sopa_t sopa;                           // La sopa de lletres

    missatge_benvinguda();                   //Missatge de benvinguda

    dimensio_taula(&sopa);      // Demanem la dimensio de la taula

    llegir_fitxer(&sopa);                         //Llegir el fitxer

    genera_sopa(&sopa);                    // La generem (exemple)

    do
    {
    mostra_sopa(&sopa);                    // La mostrem per pantalla

    demanar_paraula(&sopa, &fi); //Demanem a l'usuari una paraula que pensi que ha trobat
    //comprovar_paraula(par_jugador, &sopa);       //Comprovem si la paraula anterior es correcta

    //fi_joc=comprovar_rendicio(par_jugador);

    }while (fi==false);

    missatge_comiat();                       //Missatge de comiat

    return 0;
}
