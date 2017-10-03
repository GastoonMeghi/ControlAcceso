#ifndef LIST_PERSONA_H
#define LIST_PERSONA_H

#include <iostream>
#include "persona.h"

#define ERROR 0
#define OK 1

typedef struct nodo
{
    PERSONA per;
    struct nodo *next;
} NODO;

class LIST_PERSONA
{
    private:
        NODO *h;

    public:
        //Constructores y Destructores
        LIST_PERSONA();
        ~LIST_PERSONA();

        //Modificadores
        void agregar(PERSONA&);
        ///al apretar el boton, llama a esta funcion y reserva memoria para ingresar a una nueva persona de forma ordenada segun el codigo, y lo guarda en un archivo TXT list_persona.txt

        void modificar(PERSONA&/*discutir a partir de que atributo identificamos a una persona*/);
        ///a partir del parametro de indentificacion(debe ser un parametro inmodificable y unico de una persona, como el codigo de la tarjeta), selecciona a la persona a modificar

        void eliminar(PERSONA&/*discutir a partir de que atributo identificamos a una persona*/);

        void mostrarpersonal();///por qt
        ///tiene opciones para ordenar por nombre, apellido, edad, codigo y cargo

        ///contar cantidad de empleados reutilizando la funcion "static unsigned int getCant (void);" de mi clase PERSONA

        bool guardarFile (FILE**);

};

/*CARGAR LIST_PERSONA CON UN FILE "list_personal"*/

#endif // LIST_PERSONA_H
