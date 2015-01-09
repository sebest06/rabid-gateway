#include "fabrica.h"
#include "almacen.h"
#include "informante.h"
#include "visor.h"

#include <cstring>
#include <cstdlib>

//#include "banca.h"
//#include "generico.h"
//#include "visor.h"
//#include "operador.h"

Fabrica* Fabrica::s_pInstance = 0;
Fabrica::Fabrica()
{
    //ctor
    m_Ukids = 0;
    registerType("informante",new CreateInformante());
    registerType("visor",new CreateVisor());

}

Fabrica::~Fabrica()
{
    //dtor
}

Cliente* Fabrica::fabricar(char* buffer, int len, int socket)
{
    Cliente *c;

    char *pch;
    pch = strtok (buffer," ,.-/\r\n");
    if(pch != NULL)
    {
        if(strcmp(pch,"visor") == 0)
        {
            c = create("visor");
            c->setId(m_Ukids);
            m_Ukids++;

        }
        else if(strcmp(pch,"informante") == 0)
        {
            c = create("informante");
            c->setId(m_Ukids);
            m_Ukids++;
        }
        else
        {
            c = NULL;
        }
    }
    else
    {
        c = NULL;
    }

    if(c != NULL)
    {
        c->setSocket(socket);
    }
    return c;

}

bool Fabrica::registerType(std::string tipo, BaseCreator* base)
{
    std::map<std::string, BaseCreator*>::iterator it = m_creators.find(tipo);

    // if the type is already registered, do nothing
    if(it != m_creators.end())
    {
        delete base;
    }

    m_creators[tipo] = base;

    return true;
}

Cliente* Fabrica::create(std::string typeID)
{
    std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

    if(it == m_creators.end())
    {
//        std::cout << "could not find type: " << typeID << "\n";
        return NULL;
    }

    BaseCreator* pCreator = (*it).second;
    return pCreator->createObject();
}

