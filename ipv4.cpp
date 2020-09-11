#include "ipv4.h"
#include <math.h>

/**
 * @brief Ipv4::Ipv4
 * @param _adresse
 * @param _cidr
 */
Ipv4::Ipv4(const unsigned char * _adresse,const unsigned char _cidr)
{
    adresse = new unsigned char [4];
    masque = new unsigned char [4];
    for(int indice = 0; indice<4;indice++)
        adresse[indice]= _adresse[indice];
    if(_cidr<=32)
        CalculerMasque(_cidr);
}
Ipv4::Ipv4(const unsigned char * _adresse,const unsigned char * _masque)
{
    adresse = new unsigned char [4];
    masque = new unsigned char [4];
    for(int indice = 0; indice<4;indice++)
    {
        adresse[indice] =_adresse[indice];
        masque[indice] = _masque[indice];
    }
}
Ipv4::~Ipv4()
{
    delete [] adresse;
    delete [] masque;
}
void Ipv4::CalculerMasque(unsigned char _cidr)
{
    int indice;
    //Le masque est remis a 0 -> 0.0.0.0
    for(indice=0;indice<4;indice++)
        masque[indice]=0;

    indice=0;
    //tant que le cide un multiple de 8
    while (_cidr>=8)
    {
     masque[indice++] =255;
     _cidr -=8;
    }

    //Complément pour la fin du cidr (<8)
    unsigned char puissance = 128;
    while (_cidr-- > 0) //Après le test la variable est décrémentée
    {   // les puissance de 2 sont ajoutées à l'octet Valeur décroissante
        masque[indice] += puissance;
        puissance /=2;
    }
}
void Ipv4::ObtenirMasque(unsigned char *_masque)
{
    for(int indice = 0 ; indice < 4 ; indice++)
        _masque[indice] = masque[indice];
}
void Ipv4::ObtenirAdresseReseau(unsigned char *_reseau)
{
    for(int  indice = 0; indice<4;indice++)
        _reseau[indice] = adresse[indice] & masque[indice];
}
void Ipv4::ObtenirAdresseDiffusion(unsigned char *_diffusion)
{
    unsigned char adresseDuResseau[4];
    ObtenirAdresseReseau(adresseDuResseau);
    for(int indice = 0;indice<4;indice++)
        _diffusion[indice] = adresseDuResseau[indice] | ~masque[indice];
}

void Ipv4::ObtenirPremiereAdresseReseau(unsigned char *_reseau, unsigned char *_premier)
{
     ObtenirAdresseReseau(_reseau);
     for(int indice = 0;indice<4;indice++)
          _premier[indice] = _reseau[indice];
      _premier[3] = _premier[3]+1;

}

void Ipv4::ObtenirDreniereAdresseReseau( unsigned char *_diffusion, unsigned char *_derniere)
{
    ObtenirAdresseDiffusion(_diffusion);
    for(int indice = 0;indice<4;indice++)
     _derniere[indice] = _diffusion[indice];
    _derniere[3] = _derniere[3]-1;
}

/**
 * @brief Ipv4::NombreDeMachine
 * @return
 */
int Ipv4::NombreDeMachine()
{   int save=0;
    double nbMachine;

    unsigned char tab[4];
    for(int indice=0;indice<4;indice++)
            tab[indice]=~masque[indice];
   for(int i =3;i>=0;i--)
   {

       int pui=1;
    while(tab[i] > 0)
    {

              tab[i]-=pui;
              pui+=pui;
              save++;

    }
   }
    nbMachine=pow(2,save);

    return nbMachine-2;
}


