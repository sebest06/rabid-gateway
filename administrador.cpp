#include "administrador.h"
#include "almacen.h"
#include "servidor.h"
#include "registro.h"
#include <map>

const std::string Administrador::s_type = "ADMINISTRADOR";

Administrador::Administrador()
{
    //ctor
}

Administrador::~Administrador()
{
    //dtor
}

void Administrador::procesarDatos(char* buffer, int len)
{
    char *pch;
    std::map<unsigned int,unsigned int> *dato;
    std::vector<char> salida;
    char *send;
    int sizeBuf  = 0;
    pch = strtok (buffer," ,.-/\r\n");
    int n;
    if(pch != NULL)
    {
        if(strcmp(pch,"datos") == 0)
        {
            dato = ElRegistro::Instance()->getRegistro();
            send = new char[dato->size()*6];
            std::cout << "Size = " << dato->size() << "\n";
            for (std::map<unsigned int,unsigned int>::iterator it=dato->begin(); it!=dato->end(); ++it)
            {
                std::cout << it->first << " => " << it->second << '\n';

                send[sizeBuf+0] = (it->first & 0xff000000) >> 24;
                send[sizeBuf+1] = (it->first & 0xff0000) >> 16;
                send[sizeBuf+2] = (it->first & 0xff00) >> 8;
                send[sizeBuf+3] = it->first & 0xff;
                send[sizeBuf+4] = (it->second & 0xff00) >> 8;
                send[sizeBuf+5] = it->second & 0xff;
                sizeBuf += 6;
            }
            for(size_t i=0; i<ElAlmacen::Instance()->clientes.size(); i++)
            {
                if((ElAlmacen::Instance()->clientes[i]->getStateID() == "ADMINISTRADOR")&&(ElAlmacen::Instance()->clientes[i]->getId() == getId()))
                {
                    n = TheServidor::Instance()->sendData(ElAlmacen::Instance()->clientes[i]->getSocket(),send, sizeBuf, 0);
                    std::cout << n << " bytes sent." << std::endl;
                }
            }
        }
        else if(strcmp(pch,"mapa") == 0)
        {
            dato = ElRegistro::Instance()->getWidget();
            send = new char[dato->size()*6];
            std::cout << "Size = " << dato->size() << "\n";
            for (std::map<unsigned int,unsigned int>::iterator it=dato->begin(); it!=dato->end(); ++it)
            {
                std::cout << it->first << " => " << it->second << '\n';

                send[sizeBuf+0] = (it->first & 0xff00) >> 8;
                send[sizeBuf+1] = it->first & 0xff;
                send[sizeBuf+2] = (it->second & 0xff000000) >> 24;
                send[sizeBuf+3] = (it->second & 0xff0000) >> 16;
                send[sizeBuf+4] = (it->second & 0xff00) >> 8;
                send[sizeBuf+5] = it->second & 0xff;
                sizeBuf += 6;
            }
            for(size_t i=0; i<ElAlmacen::Instance()->clientes.size(); i++)
            {
                if((ElAlmacen::Instance()->clientes[i]->getStateID() == "ADMINISTRADOR")&&(ElAlmacen::Instance()->clientes[i]->getId() == getId()))
                {
                    n = TheServidor::Instance()->sendData(ElAlmacen::Instance()->clientes[i]->getSocket(),send, sizeBuf, 0);
                    std::cout << n << " bytes sent." << std::endl;
                }
            }
        }
        else if(strcmp(pch,"dato") == 0)
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
        else if(strcmp(pch,"setmapa") == 0)
        {
            unsigned int direccion;
            unsigned int posicion;

            pch = strtok (NULL," ,.-/\r\n");
            if(pch == NULL){return;}
            posicion = atoi(pch);
            pch = strtok (NULL," ,.-/\r\n");
            if(pch == NULL){return;}
            direccion = atoi(pch);

            ElRegistro::Instance()->setWidget(posicion,direccion);
        }
    }
}
