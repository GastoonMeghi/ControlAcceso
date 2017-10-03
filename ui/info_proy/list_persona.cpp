#include "list_persona.h"
#include <string.h>
#include <ostream>



LIST_PERSONA::LIST_PERSONA()
{
    h=NULL;
}

LIST_PERSONA::~LIST_PERSONA()
{

}


void LIST_PERSONA::agregar(PERSONA& per)
{
    NODO *q = NULL;

    q = new NODO;
    q->per = per;
    q->next = h;
    h = q;
}

void LIST_PERSONA::mostrarpersonal(void)
{
    NODO *q = NULL;

    q = h;

    while(q)
    {
        cout << q->per;
        q = q->next;
    }

}

bool LIST_PERSONA::guardarFile (FILE** file)
{
    NODO *q = NULL;

    q = h;

    while(q)
    {
        fprintf(*file,"%s %s %s %d %d\n",q->per.getCod(),q->per.getApe(),q->per.getNom(),q->per.getEst(),q->per.getPss());
        q = q->next;
    }



    return OK;
}

