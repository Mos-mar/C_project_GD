#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "gd.h"

/* Énoncé : 3 int puis 3 string et nommage string en argument ./programme
argument lors de l'appell de la fonction

pie -p 40,50,10 -l USA,CANADA,FRANCE Alcooliques.png

pie -p 40,50,10 -l USA,CANADA,FRANCE -t histo Alcooliques.png

*/

int main(int argc, char *argv[])
{

    /*--------Librarie gd-------- */

    gdImagePtr im;
    gdPointPtr p;
    gdFontPtr fp;
    //test git



    /* couleurs */
    int black;
    int white;
    int yellow;
    int blue;
    int red;
    int green;
    int purple;



    /*creation image 2400x1600 */
    im = gdImageCreate(2400, 1600);
    gdImageColorAllocate(im, 255, 255, 255);


    /* Allocate the color white (red, green and blue all maximum). */
    black  = gdImageColorAllocate(im, 0, 0, 0);
    white  = gdImageColorAllocate(im, 255, 255, 255);
    yellow = gdImageColorAllocate(im, 255, 255, 0);
    blue   = gdImageColorAllocate(im, 0, 0, 255);
    red    = gdImageColorAllocate(im, 255, 0, 0);
    green  = gdImageColorAllocate(im, 0, 255, 0);
    purple = gdImageColorAllocate(im, 255, 0, 255);




    /*---------------------------- Dessins ----------------------------------------------*/

    /*  CERCLE 360, diamètre = 1200 , contour blanc  */
    gdImageArc (im, 1200,800 , 1200, 1200, 0, 360, black);

    /* Camembert_line
fonction utilisée : void gdImageFilledArc(gdImagePtr im, int cx,int cy,int w,int h,int s,int e,int color,int style)
int s(start) à int e(end) definira le % de la part.*/

    /******************************************/

    // on récupère les arguments
    int s; // position angle début
    int e; // position angle fin
    int i; // i pour la for
    int n = 6; // nombre d'arcs
    int colors[n]; // tableau de couleurs
    colors[0] = yellow;
    colors[1] = green;
    colors[2] = blue;
    colors[3] = red;
    colors[4] = white;
    colors[5] = purple;
    colors[6] = black;
    char *fontpath = "/usr/share/fonts/truetype/dejavu/DejaVuSerif-Bold.ttf";

    /*Version loop sur les arcs*/
    printf("nombre de arguments %d\n",argc);
    // declare variables
    int x; // for numerical arguments
    char *bbox; // for string arguments
    int is_number; // flag to indicate if argument is a number
    for(int j = 1 ; j < argc ; j++)
    {
        printf("affichage argv[j] : %s\n",argv[j]);

        // initialize flag
        is_number = 1;

        // loop through each character of argument
        for (int i = 0; argv[j][i] != '\0'; i++) {
            // if character is not a digit, set flag to false and break loop
            if (!isdigit(argv[j][i])) {
                is_number = 0;
                break;
            }
        }

        // if argument is a number, convert it to int and assign it to x
        if (is_number) {
            // do not use int here
            x = strtol(argv[j],NULL, 10);
            printf("x : %d\n",x);
            e = (s + x * 360 / 100);
            gdImageFilledArc(im, 1200, 800, 1200, 1200, s, e, colors[j], 100); // draw the arc
            s = e; // update the start angle
            //printf("j : %d x : %d e : %d s : %d\n",j,x,e,s);
        }

        // else, argument is a string, assign it to bbox
        else {
            // do not use char* here
            bbox = gdImageStringFT(NULL, NULL, colors[6], fontpath, 20, 0, 0, 0, argv[j]);
            // calcul du centre
            int cx = 1200 / 2;
            int cy = 800 / 2;
            // calcul de la médiane de l'arc
            int mx = cx + cos((s + e) / 2 * M_PI / 180) * 600;
            int my = cy + sin((s + e) / 2 * M_PI / 180) * 600;
            // calcul de la largeur et de la hauteur du texte
            int tw = bbox[2] - bbox[0];
            int th = bbox[3] - bbox[5];
            // calcul de compensation du texte par rapport à la médiane de l'arc
            int ox = tw / 2;
            int oy = th / 2;
            // calcul de l'angle du texte
            double angle = (s + e) / 2 - 90;
            // texte
            gdImageStringFT(im, NULL, colors[6], fontpath, 20, angle * M_PI / 180, mx - ox, my + oy, argv[j]);
        }
    }


        /*----------------------------------------------------------------------------------------------*/
        // en "dur"
        //    int s1 = 0;
        //

        //gdImageFilledArc(im,1200,800 , 1200, 1200 , s1 , e1 ,yellow, 100);

        //int s2 = e1;
        //int e2 = x * (360/100) + e1;
        //gdImageFilledArc(im,1200,800 , 1200, 1200 , s2 , e2 ,green, 100);

        //int s3 = e2;
        //int e3 = x * (360/100) + e2;
        //gdImageFilledArc(im,1200,800 , 1200, 1200 , s3 , e3 ,blue, 100);

        /*------------------------------------------------------------*/

        /* Output en format PNG. */
        //    char *filename = argv[1];
        //    FILE *fp = fopen(filename, "wb");
        //    // écriture image
        //    gdImagePng(im, fp);
        //    // fermeture fichier
        //    fclose(fp);
        //    // destruction image
        //    gdImageDestroy(im);
        //    return 0;


        /* Output the image to the disk file in PNG format. */
        FILE *testpng;
        testpng = fopen("../test.png", "wb");
        gdImagePng(im, testpng);

        fclose(testpng);

        gdImageDestroy(im);
        return 0;
    }
