#include <iostream>
#include <ipv4.h>

using namespace std;

void AfficherTableau(unsigned char *tab)
{
    for(int indice =0 ; indice <4 ; indice++)
    {
        cout<<static_cast<int>(tab[indice]);
        if(indice < 3)
            cout<< ".";
    }
    cout<< endl;
}

int main()
{

    unsigned char adresse[4] ={172,18,0,0};
    unsigned char masque[4]={255,255,255,0};
    unsigned char reseau[4];
    unsigned char diffusion[4];
    unsigned char premier[4];
    unsigned char derniere[4];
    int nbMachine;

    Ipv4 uneAdresse (adresse, 24); //instancition de la calsse ipv4
    cout<<"Adresse Ipv4 :";
    AfficherTableau(adresse);
    uneAdresse.ObtenirMasque(masque); //appel d'une méthode
    cout<< "Masque : ";
    AfficherTableau(masque);
    uneAdresse.ObtenirAdresseReseau(reseau);
    cout<<"Réseau : ";
    AfficherTableau(reseau);
    uneAdresse.ObtenirAdresseDiffusion(diffusion);
    cout<<"Diffusion : ";
    AfficherTableau(diffusion);
    cout<<"Première adressse : ";
    uneAdresse.ObtenirPremiereAdresseReseau(reseau,premier);
    AfficherTableau(premier);
    cout<<"Dernière adressse : ";
    uneAdresse.ObtenirDreniereAdresseReseau(diffusion,derniere);
    AfficherTableau(derniere);
    nbMachine=uneAdresse.NombreDeMachine();
    cout<<nbMachine;
    return 0;
}
