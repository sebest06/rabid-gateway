#ifndef REGISTRO_H
#define REGISTRO_H
#include <vector>
#include <map>
#include <string>


#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <libconfig.h++>
using namespace libconfig;

class Registro
{
    public:
        static Registro* Instance()
        {
            if(s_pInstance == 0)
            {
                s_pInstance = new Registro();
                return s_pInstance;
            }
            return s_pInstance;
        }
        virtual ~Registro();
        std::map<unsigned int,unsigned int>* getRegistro(){return &m_registro;};
        void setRegistro(unsigned int direccion, unsigned int valor);
        std::map<unsigned int,unsigned int>* getWidget(){return &m_widget;};
        void setWidget(unsigned int posicion, unsigned int direccion);

        bool setConfigFile(std::string name);


    protected:
    private:
        Registro();
        static Registro* s_pInstance;
        std::map<unsigned int,unsigned int> m_registro;
        std::map<unsigned int,unsigned int> m_widget;
        Config cfg;
        std::string m_fileName;
};

typedef Registro ElRegistro;
#endif // REGISTRO_H
