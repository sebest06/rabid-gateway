#include "informante.h"
#include "almacen.h"
#include "servidor.h"
#include "registro.h"


const std::string Informante::s_type = "INFORMANTE";

Informante::Informante()
{
    //ctor
}

Informante::~Informante()
{
    //dtor
}
void Informante::procesarDatos(char* buffer, int len)
{
    char *pch;
    pch = strtok (buffer," ,.-/\r\n");
    if(pch != NULL)
    {
        if(strcmp(pch,"dato") == 0)
        {
            unsigned int direccion;
            unsigned int valor;

            pch = strtok (NULL," ,.-/\r\n");
            if(pch == NULL){return;}
            direccion = atoi(pch);
            pch = strtok (NULL," ,.-/\r\n");
            if(pch == NULL){return;}
            valor = atoi(pch);
            ElRegistro::Instance()->setRegistro(direccion,valor);
        }
    }
}
