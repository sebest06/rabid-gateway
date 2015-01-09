#ifndef BASECREATOR_H_INCLUDED
#define BASECREATOR_H_INCLUDED
#include "cliente.h"

class BaseCreator
{
    public:
        BaseCreator(){}
        virtual ~BaseCreator(){}
        virtual Cliente* createObject() = 0;
};

#endif // BASECREATOR_H_INCLUDED
