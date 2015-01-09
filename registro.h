#ifndef REGISTRO_H
#define REGISTRO_H
#include <vector>
#include <map>
#include <string>

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
    protected:
    private:
        Registro();
        static Registro* s_pInstance;
        std::map<unsigned int,unsigned int> m_registro;
};

typedef Registro ElRegistro;
#endif // REGISTRO_H
