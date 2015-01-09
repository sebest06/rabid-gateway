#ifndef FABRICA_H
#define FABRICA_H
#include "cliente.h"
#include "basecreator.h"
#include <map>

class Fabrica
{
    public:
        static Fabrica* Instance()
        {
            if(s_pInstance == 0)
            {
                s_pInstance = new Fabrica();
                return s_pInstance;
            }
            return s_pInstance;
        }
        virtual ~Fabrica();

        Cliente* fabricar(char* buffer, int len, int socket);

        bool registerType(std::string tipo,BaseCreator* base);
        Cliente* create(std::string typeID);


    protected:
    private:
        Fabrica();
        static Fabrica* s_pInstance;
        long int m_Ukids;
        std::map<std::string, BaseCreator*> m_creators;

};
typedef Fabrica LaFabrica;
#endif // FABRICA_H
