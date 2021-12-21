#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct pixel {
    int r;
    int v;
    int b;
};

char charInt(int nb)
{
    if(nb>224) //
        return 46;
    else if(nb>196)
        return 44;
    else if(nb>168)
        return 43;
    else if(nb>140)
        return 42;
    else if(nb>112)
        return 35;
    else if(nb>84)
        return 38;
    else if(nb>56)
        return 64;
    else if(nb>28)
        return 20;
    else
        return 22;
}

bool asciiArt(string nomFichier)
{
    ifstream lcr(nomFichier);

    if(!lcr)
        return 0;
    string poubelle;
    int largeur, hauteur;

    lcr>>poubelle>>largeur>>hauteur>>poubelle;

    vector<vector<int>>img(hauteur, vector<int>(largeur));

    double r, v, b;
    int tmp;

    for(int i=0; i<hauteur; ++i)
    {
        for(int j=0; j<largeur; ++j)
        {
            lcr>>r>>v>>b;

            r*=0.2126;
            v*=0.7152;
            b*=0.0722;

            tmp = r+v+b;

            img[i][j] = tmp;
        }
    }

    int largeur_pixel = 3;
    int hauteur_pixel = 5;
    int nb_Pixel = 20;

    int nb_char_largeur = largeur/largeur_pixel;
    int nb_char_hauteur = hauteur/hauteur_pixel;

    int moy=0;

    for(int i=0; i<nb_char_hauteur; ++i)
    {
        for(int j=0; j<nb_char_largeur; ++j)
        {
            moy=0;
            for(int k=i*hauteur_pixel; k<(i+1)*hauteur_pixel; ++k)
            {
                for(int l=j*largeur_pixel; l<(j+1)*largeur_pixel; ++l)
                {
                    moy+=img[k][l];
                }
            }
            moy/=nb_Pixel;
            cout<<charInt(moy);
        }
        cout<<endl;
    }
    return 1;
}

int main()
{
    cout<<asciiArt("rrdd.ppm")<<endl;

    return 0;
}

