#ifndef PERSONA_H
#define PERSONA_H

#include <iostream>

#define TAM_COD 20
#define TAM_NOM 20
#define TAM_APE 20

#define AUSENTE  false
#define PRESENTE true

#define NOPASS -1

using namespace std;

class PERSONA
{
    private:
        char    m_cod[TAM_COD];     ///'Codigo' asociado a la tarjeta RFID
        char    m_ape[TAM_APE];
        char    m_nom[TAM_NOM];
        bool    m_est;              ///Flag 'Estado': PRESENTE o AUSENTE
        int     m_pss;              ///'Password' personal de 4 numeros ingresados por teclado


    public:
        //Atributos staticos
        static unsigned int m_cant;

        //Constructores y Desturctores
        PERSONA();
        PERSONA(char*,char*,char*);
        ~PERSONA();

        //Modificadores
        void setCod     (const char *);
        void setApe     (const char*);
        void setNom     (const char*);
        void setEst     (bool);
        void setPss     (int);

        char* getCod    (void);
        char* getNom    (void);
        char* getApe    (void);
        bool getEst     (void);
        int getPss     (void);

        static unsigned int getCant (void);

        //Operators
        PERSONA& operator= (const PERSONA&);
        friend ostream& operator<< (ostream&,const PERSONA&);
};

#endif // PERSONA_H

