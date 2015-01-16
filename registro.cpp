#include "registro.h"
#include <sstream>

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

void Registro::setWidget(unsigned int posicion, unsigned int direccion)
{
    m_widget[posicion] = direccion;
    Setting &root = cfg.getRoot();
    Setting &xbees = root["inventario"]["xbees"];

    int count = xbees.getLength();
    int pos;
    std::string dir;

    for(int i = 0; i < count; ++i)
    {
        const Setting &xbee = xbees[i];
        if(!(xbee.lookupValue("posicion", pos)
           && xbee.lookupValue("direccion", dir)))
        continue;

        if(pos == posicion)
        {
            std::stringstream ss;
            ss << std::hex << direccion;

            xbees.remove(i);
            Setting &xbeeAdd = xbees.add(Setting::TypeGroup);

            xbeeAdd.add("posicion", Setting::TypeInt) = (int)posicion;
            xbeeAdd.add("direccion", Setting::TypeString) = ss.str();
        }
    }

    try
    {
        cfg.writeFile(m_fileName.c_str());
//        cerr << "Updated configuration successfully written to: " << output_file
//            << endl;

    }
    catch(const FileIOException &fioex)
    {
  //      cerr << "I/O error while writing file: " << output_file << endl;
        return;
    }

}

bool Registro::setConfigFile(std::string name)
{

    m_fileName = name;
    try
    {
        cfg.readFile(name.c_str());
    }
    catch(const FileIOException &fioex)
    {
        std::cerr << "I/O error while reading file." << std::endl;
        return false;
    }
    catch(const ParseException &pex)
    {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
              << " - " << pex.getError() << std::endl;
        return false;
    }
    Setting &root = cfg.getRoot();

    if(! root.exists("inventario"))
    {
        return false;
    }
    //root.add("inventario", Setting::TypeGroup);

    Setting &inventory = root["inventario"];

    if(! inventory.exists("xbees"))
    {
        return false;
    }
    //inventory.add("xbees", Setting::TypeList);

    Setting &xbees = inventory["xbees"];

    int count = xbees.getLength();
    int pos;
    unsigned int direccion;
    std::string dir;

    for(int i = 0; i < count; ++i)
    {
        const Setting &xbee = xbees[i];
        if(!(xbee.lookupValue("posicion", pos)
           && xbee.lookupValue("direccion", dir)))
        continue;

        direccion = stoi(dir,0,16);
        std::cout << pos << " : " << dir << " | " << direccion << "\n";

        m_widget[pos] = direccion;
    }

  return true;
}
