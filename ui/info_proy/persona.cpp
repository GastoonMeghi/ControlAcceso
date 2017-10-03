#include "persona.h"
#include <string.h>
#include <cstdio>

unsigned int PERSONA::m_cant=0;


//Constructores y Desturctores

PERSONA::PERSONA()
{
    strcpy(m_cod, "NoCOD");
    strcpy(m_ape, "NoApe");
    strcpy(m_nom, "NoNom");
    m_est = AUSENTE;
    m_pss = NOPASS;

    m_cant++;
}

PERSONA::PERSONA(char *cod, char* ape, char* nom)
{
    strcpy(m_cod, cod);
    strcpy(m_ape, ape);
    strcpy(m_nom, nom);
    m_est = AUSENTE;
    m_pss = NOPASS;

    m_cant++;
}


PERSONA::~PERSONA()
{
    m_cant--;
}


//Modificadores

void PERSONA::setCod(const char* cod)
{
    strcpy(m_cod,cod);
}

void PERSONA::setApe(const char* ape)
{
    strcpy(m_ape,ape);
}

void PERSONA::setNom(const char* nom)
{
    strcpy(m_nom,nom);
}

void PERSONA::setEst(bool est)
{
    m_est = est;
}

void PERSONA::setPss(int pss)
{
    m_pss = pss;
}



char* PERSONA::getCod(void)
{
    return m_cod;
}

char* PERSONA::getApe(void)
{
    return m_ape;
}

char* PERSONA::getNom(void)
{
    return m_nom;
}

bool PERSONA::getEst(void)
{
    return m_est;
}

int PERSONA::getPss(void)
{
    return m_pss;
}


unsigned int PERSONA::getCant(void)
{
    return m_cant;
}

//Operators

PERSONA& PERSONA::operator= (const PERSONA& per)
{
    strcpy(m_cod,per.m_cod);
    strcpy(m_ape,per.m_ape);
    strcpy(m_nom,per.m_nom);
    m_est = per.m_est;
    m_pss = per.m_pss;


    return (*this);
}

ostream& operator<< (ostream& cout, const PERSONA& per)
{
    cout << "Cod: " << per.m_cod << endl;
    cout << "Ape: " << per.m_ape << endl;
    cout << "Nom: " << per.m_nom << endl;
    cout << "Est: " << per.m_est << endl;
    cout << "Pss: " << per.m_pss << endl << endl;

    return cout;
}












