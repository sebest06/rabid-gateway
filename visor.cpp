#include "visor.h"

#include "almacen.h"
#include "servidor.h"
#include "registro.h"
#include <map>

const std::string Visor::s_type = "VISOR";

Visor::Visor()
{
    //ctor
}

Visor::~Visor()
{
    //dtor
}

void Visor::procesarDatos(char* buffer, int len)
{
    char *pch;
    std::map<unsigned int,unsigned int> *dato;
    std::vector<char> salida;
    char *send;
    int sizeBuf  = 0;
    double duracion;
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
                if(ElRegistro::Instance()->checkAlive(it->first))
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
            }
            for(size_t i=0; i<ElAlmacen::Instance()->clientes.size(); i++)
            {
                if((ElAlmacen::Instance()->clientes[i]->getStateID() == "VISOR")&&(ElAlmacen::Instance()->clientes[i]->getId() == getId()))
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
                if((ElAlmacen::Instance()->clientes[i]->getStateID() == "VISOR")&&(ElAlmacen::Instance()->clientes[i]->getId() == getId()))
                {
                    n = TheServidor::Instance()->sendData(ElAlmacen::Instance()->clientes[i]->getSocket(),send, sizeBuf, 0);
                    std::cout << n << " bytes sent." << std::endl;
                }
            }
        }
    }
}
