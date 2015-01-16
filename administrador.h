#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include "cliente.h"
#include "basecreator.h"


class Administrador : public Cliente
{
    public:
        Administrador();
        virtual ~Administrador();
        virtual int getSocket(){return m_socket;}
        virtual void setSocket(int socket){m_socket = socket;}
        virtual void setName(std::string name){m_name = name;}
        virtual std::string getName(void){return m_name;}
        virtual void procesarDatos(char* buffer, int len);
        virtual void setId(int id){m_id = id;}
        virtual int getId(void){return m_id;}
        virtual std::string getStateID() const {return s_type;}
    protected:
    private:
        static const std::string s_type;
        std::string m_name;
        int m_id;
        bool m_registrada;
        int m_socket;
};

class CreateAdministrador : public BaseCreator
{
    public:
        CreateAdministrador(){};
        ~CreateAdministrador(){};
        virtual Cliente* createObject()
        {
            return new Administrador();
        }
};

#endif // ADMINISTRADOR_H
