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

bool imageRouge(string nomFichier, int n)
{
    nomFichier+=".ppm";
    ofstream ecr(nomFichier);

    if(!ecr)
        return 0;

    ecr<<"P3"<<endl<<n<<" "<<n<<endl<<255<<endl;

    for(int i=0; i<2*n; i++)
        for(int j=0; j<2*n; j++)
            ecr<<255<<" "<<0<<" "<<0<<" ";

    return 1;

}

bool genereW(string nomFichier, int n)
{
    nomFichier+=".ppm";
    ofstream ecr(nomFichier);

    if(!ecr)
        return 0;

    ecr<<"P3"<<endl<<2*n<<" "<<2*n<<endl<<255<<endl;

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
            ecr<<255<<" "<<0<<" "<<0<<" ";

        for(int k=0; k<n; k++)
            ecr<<0<<" "<<255<<" "<<0<<" ";

        ecr<<endl;
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
            ecr<<255<<" "<<255<<" "<<0<<" ";

        for(int k=0; k<n; k++)
            ecr<<0<<" "<<0<<" "<<255<<" ";

        ecr<<endl;
    }

    return 1;
}

bool niveauDeGris(string nomFichier)
{
    ifstream lcr(nomFichier);

    if(!lcr)
        return 0;

    string nomFichierCible;

    for(unsigned i=0; i<nomFichier.size()-4; i++)
        nomFichierCible+=nomFichier[i];

    nomFichierCible+="_GRIS.ppm";

    ofstream ecr(nomFichierCible);
    string poubelle;
    int largeur, hauteur;

    lcr>>poubelle>>largeur>>hauteur>>poubelle;
    ecr<<"P3"<<endl<<largeur<<" "<<hauteur<<endl<<255<<endl;

    double ir, iv, ib;
    int tmp;

    for(int i=0; i<hauteur; i++)
    {
        for(int j=0; j<largeur; j++)
        {
            lcr>>ir>>iv>>ib;

            ir*=0.2126;
            iv*=0.7152;
            ib*=0.0722;

            tmp=ir+iv+ib;

            ecr<<tmp<<" "<<tmp<<" "<<tmp<<" ";
        }
        ecr<<endl;
    }

    return 1;
}

bool niveauDeGrisROUGE(string nomFichier)
{
    ifstream lcr(nomFichier);

    if(!lcr)
        return 0;

    string nomFichierCible;

    for(unsigned i=0; i<nomFichier.size()-4; i++)
        nomFichierCible+=nomFichier[i];

    nomFichierCible+="_GRIS_ROUGE.ppm";

    ofstream ecr(nomFichierCible);
    string poubelle;
    int largeur, hauteur;

    lcr>>poubelle>>largeur>>hauteur>>poubelle;
    ecr<<"P3"<<endl<<largeur<<" "<<hauteur<<endl<<255<<endl;

    double ir, iv, ib;
    int tmp;

    for(int i=0; i<hauteur; i++)
    {
        for(int j=0; j<largeur; j++)
        {
            lcr>>ir>>iv>>ib;

            if(ir>iv*1.3 && ir>ib*1.3)
            {
                ecr<<ir<<" "<<iv<<" "<<ib<<" ";
            }
            else
            {
                ir*=0.2126;
                iv*=0.7152;
                ib*=0.0722;

                tmp=ir+iv+ib;

                ecr<<tmp<<" "<<tmp<<" "<<tmp<<" ";
            }
        }
        ecr<<endl;
    }

    return 1;
}

bool inverse(string nomFichier)
{
    ifstream lcr(nomFichier);

    if(!lcr)
        return 0;

    string nomFichierCible;

    for(int i=0; i<nomFichier.size()-4; i++)
        nomFichierCible+=nomFichier[i];

    nomFichierCible+="_inverse.ppm";

    ofstream ecr(nomFichierCible);
    string poubelle;
    int largeur, hauteur;

    lcr>>poubelle>>largeur>>hauteur>>poubelle;
    ecr<<"P3"<<endl<<largeur<<" "<<hauteur<<endl<<255<<endl;

    vector<pixel>img(largeur*hauteur);

    for(int i=0; i<largeur*hauteur; i++)
        {
            lcr>>img[i].r>>img[i].v>>img[i].b;
        }

    for(int i=largeur*hauteur-1; i>=0; i--)
        ecr<<img[i].r<<" "<<img[i].v<<" "<<img[i].b<<" ";

    return 1;
}

bool extraireImage(string nomFichier, int c1, int c2, int l1, int l2)
{
    ifstream lcr(nomFichier);

    if(!lcr)
        return 0;

    string nomFichierCible;

    for(int i=0; i<nomFichier.size()-4; i++)
        nomFichierCible+=nomFichier[i];

    nomFichierCible+="_extraire.ppm";

    ofstream ecr(nomFichierCible);
    string poubelle;
    int p;
    int r, v, b;
    int largeur, hauteur;

    lcr>>poubelle>>largeur>>hauteur>>poubelle;
    ecr<<"P3"<<endl<<c2-c1<<" "<<l2-l1<<endl<<255<<endl;

    for(int i=0; i<largeur*l1; i++)
        lcr>>p>>p>>p;

    for(int i=0; i<l2-l1; i++)
    {
        for(int j=0; j<c1; j++)
            lcr>>p>>p>>p;

        for(int j=0; j<c2-c1; j++)
            {
                lcr>>r>>v>>b;

                ecr<<r<<" "<<v<<" "<<b<<" ";
            }

        for(int j=0; j<largeur-c2; j++)
            lcr>>p>>p>>p;

            ecr<<endl;
    }
     return 1;
}

bool symetrieV(string nomFichier)
{
    ifstream lcr(nomFichier);

    if(!lcr)
        return 0;

    string nomFichierCible;

    for(int i=0; i<nomFichier.size()-4; i++)
        nomFichierCible+=nomFichier[i];

    nomFichierCible+="_symetrieV.ppm";

    ofstream ecr(nomFichierCible);

    string poubelle;
    int largeur, hauteur;

    lcr>>poubelle>>largeur>>hauteur>>poubelle;
    ecr<<"P3"<<endl<<largeur<<" "<<hauteur<<endl<<255<<endl;

    vector<vector<pixel>>img(hauteur, vector<pixel>(largeur));

    for(int i=0; i<hauteur; i++)
        for(int j=0; j<largeur; j++)
            lcr>>img[i][j].r>>img[i][j].v>>img[i][j].b;

    for(int i=0; i<hauteur; i++)
    {
        for(int j=largeur-1; j>=0; j--)
            ecr<<img[i][j].r<<" "<<img[i][j].v<<" "<<img[i][j].b<<" ";

        ecr<<endl;
    }

    return 1;
}

bool woaw(string nomFichier)
{
    ifstream lcr(nomFichier);

    if(!lcr)
        return 0;

    string nomFichierCible;

    for(int i=0; i<nomFichier.size()-4; i++)
        nomFichierCible+=nomFichier[i];

    nomFichierCible+="_WOAW.ppm";

    ofstream ecr(nomFichierCible);
    string poubelle;
    int largeur, hauteur;

    lcr>>poubelle>>largeur>>hauteur>>poubelle;
    ecr<<"P3"<<endl<<largeur<<" "<<hauteur<<endl<<255<<endl;

    double ir, iv, ib;
    int r, v, b;

    for(int i=0; i<hauteur; i++)
    {
        for(int j=0; j<largeur; j++)
        {
            lcr>>ir>>iv>>ib;


            ecr<<ir<<" "<<ib<<" "<<iv<<" ";
        }
        ecr<<endl;
    }

    return 1;
}

bool comboImage(string nomFichier)
{
    ifstream lcr(nomFichier);

    //symetrieV(nomFichier);

    if(!lcr)
        return 0;

    string nomFichierCible;
    string pb;

    for(int i=0; i<nomFichier.size()-4; i++)
        nomFichierCible+=nomFichier[i];

    ifstream lcrd(nomFichierCible+"_symetrieV.ppm");


    if(!lcrd)
        return 0;

    lcrd>>pb>>pb>>pb>>pb;

    nomFichierCible+="_comboImage.ppm";

    ofstream ecr(nomFichierCible);
    string poubelle;

    int r, v, b;
    int largeur, hauteur;

    lcr>>poubelle>>largeur>>hauteur>>poubelle;
    ecr<<"P3"<<endl<<largeur*2<<" "<<hauteur<<endl<<255<<endl;

    for(int i=0; i<hauteur; i++)
    {
        for(int j=0; j<largeur; j++)
        {
            lcrd>>r>>v>>b;
            ecr<<r<<" "<<v<<" "<<b<<" ";
        }

        for(int j=0; j<largeur; j++)
        {
            lcr>>r>>v>>b;
            ecr<<r<<" "<<v<<" "<<b<<" ";

        }
    }
    return 1;
}

bool filtreRouge(string nomFichier)
{
    ifstream lcr(nomFichier);

    if(!lcr)
        return 0;

    string nomFichierCible;

    for(int i=0; i<nomFichier.size()-4; i++)
        nomFichierCible+=nomFichier[i];

    nomFichierCible+="_FILTRE_ROUGE.ppm";

    ofstream ecr(nomFichierCible);
    string poubelle;
    int largeur, hauteur;

    lcr>>poubelle>>largeur>>hauteur>>poubelle;
    ecr<<"P3"<<endl<<largeur<<" "<<hauteur<<endl<<255<<endl;

    int r, pbl;

    for(int i=0; i<hauteur; ++i)
    {
        for(int j=0; j<largeur; ++j)
        {
            lcr>>r>>pbl>>pbl;
            ecr<<r<<" 0 0 ";
        }
        ecr<<endl;
    }
    return 1;
}

bool moitPPM(string nomFichier)
{
    ifstream lcr(nomFichier);

    if(!lcr)
        return 0;

    string nomFichierCible;

    for(int i=0; i<nomFichier.size()-4; i++)
        nomFichierCible+=nomFichier[i];

    nomFichierCible+="_moitPPM.ppm";

    ofstream ecr(nomFichierCible);
    string poubelle;
    int largeur, hauteur;

    lcr>>poubelle>>largeur>>hauteur>>poubelle;
    ecr<<"P3"<<endl<<largeur<<" "<<hauteur<<endl<<255<<endl;

    for(int i=0; i<hauteur; ++i)
    {
        vector<pixel> tmp(largeur/2);

        for(int j=0; j<largeur/2; ++j)
                lcr>>tmp[j].r>>tmp[j].v>>tmp[j].b;

        for(int j=0; j<largeur/2; ++j)
                {
                    int r, v, b;
                    lcr>>r>>v>>b;
                    ecr<<r<<" "<<v<<" "<<b<<" ";
                }

        for(int j=0; j<largeur/2; ++j)
                ecr<<tmp[j].r<<" "<<tmp[j].v<<" "<<tmp[j].b<<" ";

        ecr<<endl;
    }

    return 1;
}

int intensiteLaPlusFrequente(string nomFichier)
{
    ifstream lcr(nomFichier);

    string poubelle;
    int largeur, hauteur;

    lcr>>poubelle>>largeur>>hauteur>>poubelle;

    int r, v, b;
    vector<int>intense(255);

    for(int i=0; i<largeur*hauteur; ++i)
    {
        lcr>>r>>v>>b;

        int maxi=r;

        if(maxi<v)
            maxi=v;
        if(maxi<b)
            maxi=b;

        ++intense[maxi];
    }

    int returnMaxi=0, indiceMaxi=0;

    for(int i=0; i<intense.size(); ++i)
    {
        if(returnMaxi < intense[i])
        {
         returnMaxi = intense[i];
         indiceMaxi=i;
        }
    }

    return indiceMaxi;
}

bool rotation(string nomFichier)
{
    ifstream lcr(nomFichier);

    if(!lcr)
        return 0;

    string nomFichierCible;

    for(int i=0; i<nomFichier.size()-4; i++)
        nomFichierCible+=nomFichier[i];

    nomFichierCible+="_rotation.ppm";

    ofstream ecr(nomFichierCible);
    string poubelle;
    int largeur, hauteur;

    lcr>>poubelle>>largeur>>hauteur>>poubelle;
    ecr<<"P3"<<endl<<hauteur<<" "<<largeur<<endl<<255<<endl;

    vector<vector<pixel>>img(hauteur, vector<pixel>(largeur));

    for(int i=0; i<hauteur; ++i)
    {
        for(int j=0; j<largeur; ++j)
            lcr>>img[i][j].r>>img[i][j].v>>img[i][j].b;
    }

    for(int j=0; j<largeur; ++j)
    {
        for(int i=0; i<hauteur; ++i)
            ecr<<img[i][j].r<<" "<<img[i][j].v<<" "<<img[i][j].b<<" ";
    }
    return 1;

}

char charInt(int nb)
{
    /*vector<int>eqi(9);

    eqi[0]=46;
    eqi[1]=44;
    eqi[2]=43;
    eqi[3]=42;
    eqi[4]=35;
    eqi[5]=38;
    eqi[6]=64;
    eqi[7]=20;
    eqi[8]=22;*/

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

    //string nomFichierCible;

    /*for(int i=0; i<nomFichier.size()-4; i++)
        nomFichierCible+=nomFichier[i];

    nomFichierCible+="_rotation.ppm";*/

    //ofstream ecr(nomFichierCible);
    string poubelle;
    int largeur, hauteur;

    lcr>>poubelle>>largeur>>hauteur>>poubelle;
    //ecr<<"P3"<<endl<<hauteur<<" "<<largeur<<endl<<255<<endl;

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

    /*for(int i=0; i<hauteur; ++i)
        for(int j=0; j<largeur; ++j)
            cout<<img[i][j]<<endl;*/


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
