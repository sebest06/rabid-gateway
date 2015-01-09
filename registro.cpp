#include "registro.h"

Registro* Registro::s_pInstance = 0;
Registro::Registro()
{
    //ctor
}

Registro::~Registro()
{
    //dtor
}

void Registro::setRegistro(unsigned int direccion, unsigned int valor)
{
    m_registro[direccion] = valor;
}
