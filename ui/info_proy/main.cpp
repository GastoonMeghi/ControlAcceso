#include <iostream>
#include <string.h>
#include "persona.h"
#include "list_persona.h"

using namespace std;

int main()
{
    LIST_PERSONA A;
    PERSONA PA((char*)"022204",(char*)"Chon",(char*)"Kevin");
    PERSONA PB((char*)"022203",(char*)"Melvin",(char*)"Franco");
    PERSONA PC((char*)"022202",(char*)"Mark",(char*)"Taux");

    FILE *list_personal = fopen("list_personal.txt","a+");
    if(list_personal == NULL)
        perror("ERROR: Abriendo archivo 'list_personal.txt'.");

    A.agregar(PA);
    A.agregar(PB);
    A.agregar(PC);

    A.mostrarpersonal();

    A.guardarFile(&list_personal);

    fclose(list_personal);



    return 0;
}
