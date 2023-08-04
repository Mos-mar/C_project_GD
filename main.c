#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "gd.h"

int *p_int_half = NULL;
char **tag_string = NULL;

int main(int argc, char *argv[])
{

    // Déclaration et instanciation de variables

    gdImagePtr im;
    
    int xpercent; // pour les arguments chiffre    
    int black;
    int white;
    int yellow;
    int blue;
    int red;
    int green;
    int purple;
    int s; // position angle début
    int e; // position angle fin

    int colors[7]; // tableau de couleurs

    int taux = 1; // recupérer le pourcentages de l'argv
    int n = 6;    // nombre d'arcs
    int half_array = (argc - 1) / 2;    
    char *fontpath = "/usr/share/fonts/truetype/dejavu/DejaVuSerif-Bold.ttf";
    int j = 0;
    char *text = "";

    /*creation image 2400x1600 */
    im = gdImageCreate(2400, 1600);
    gdImageColorAllocate(im, 255, 255, 255);

    /* Allocation des codes couleurs */
    black = gdImageColorAllocate(im, 0, 0, 0);
    white = gdImageColorAllocate(im, 255, 255, 255);
    yellow = gdImageColorAllocate(im, 255, 255, 0);
    blue = gdImageColorAllocate(im, 0, 0, 255);
    red = gdImageColorAllocate(im, 255, 0, 0);
    green = gdImageColorAllocate(im, 0, 255, 0);
    purple = gdImageColorAllocate(im, 255, 0, 255);

    /*Couleurs*/
    colors[0] = yellow;
    colors[1] = green;
    colors[2] = blue;
    colors[3] = red;
    colors[4] = white;
    colors[5] = purple;
    colors[6] = black;


    //Vérification que le nombre d'arguments passés de type "0123" est égal au nombre d'arguments "abc"
    if (argc % 2 == 0)
    {
        printf("Error : nombre de pourcent != du nombre de tag entrée\n");
        return 1;
    }

    //Allocation mémoire pour les arguments passés de type char "abc"
    tag_string = malloc(sizeof(char) * half_array);
    //Allocation mémoire pour les arguments passés de type char "123" qu'on convertira en int
    p_int_half = malloc(sizeof(int) * half_array);


    //Boucles pour modifier nos arguments passés
    for (int i = 1; i <= half_array; i++)
    {        
        p_int_half[j] = strtol(argv[i], NULL, 10); //Convertit les arguments de type "123" en int (1, 2, 3)
        tag_string[j] = argv[i + half_array];//Séparation des arguments type "abc"
        j++;
    }

    j = 0;

    //Boucles pour vérifier chaque arguments passés
    for (int i = 0; i < half_array; i++)
    {
        printf("percent : %d\n", p_int_half[i]);
        printf("tag : %s\n", tag_string[i]);
    }

    

    /*---------------------------- Dessins ----------------------------------------------*/

    /*  CERCLE 360, diamètre = 1200 , contour blanc  */
    gdImageArc(im, 1200, 800, 1200, 1200, 0, 360, black);

    /* Camembert_line fonction utilisée : void gdImageFilledArc(gdImagePtr im, int cx,int cy,int w,int h,int s,int e,int color,int style)
    int s(start) à int e(end) definira le % de la part.*/

    
    printf("nombre de arguments %d\n", argc); //Vérifie le nombre d'arguments passés au total ("123"+"abc")
    

    for (int i = 0; i < half_array; i++)
    {
        xpercent = p_int_half[i]; //Liens avec les "123" convertit en int pour attribuer la part des pourcents du Camembert
        e = (s + xpercent * 360 / 100);         
        gdImageFilledArc(im, 1200, 800, 1200, 1200, s, e, colors[i], 100); // Dessine un arc       

        /* Liens avec les strings("abc") passés en argument pour attribuer les bons tag à leurs pourcent respectif*/

        //Création du rectangle qui acceuillera les tags 
        int rectangle[8];
        char *text = tag_string[i];
        printf("text[i] =   %s\n", text);

        // calcul du centre
        int cx = 1200 / 2;
        int cy = 800 / 2;

        // calcul de la médiane de l'arc
        int mx = cx + cos((s + e) / 2 * M_PI / 180) + 700;
        int my = cy + sin((s + e) / 2 * M_PI / 180) + 700;

        
        gdImageStringFT(NULL, rectangle, colors[i], fontpath, 20, 0, 0, 0, text);

        //Calcul de la largeur et de la hauteur du texte
        int tw = rectangle[2] - rectangle[0];
        int th = rectangle[3] - rectangle[5];

        //Calcul de compensation du texte par rapport à la médiane de l'arc
        int ox = tw / 2;
        int oy = th / 2;

        //Calcul de l'angle du texte
        double angle = (s + e) / 2 - 90;

        //Génération des tags sur l'image
        gdImageStringFT(im, rectangle, black, fontpath, 20, angle, mx - ox, my + oy, text);

        s = e; //Mis à jour de l'angle de départ
    }

    /* Output de l'image en format PNG */
    FILE *testpng;
    testpng = fopen("test.png", "wb+");
    gdImagePng(im, testpng);

    fclose(testpng);

    gdImageDestroy(im);

    free(tag_string);//Liberation de la mémoire attribuée à la ligne 70
    free(p_int_half);//Liberation de la mémoire attribuée à la ligne 72
    return 0;
}
