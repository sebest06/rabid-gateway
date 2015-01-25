#include <iostream>
#include "mythread.h"
#include "server.h"
#include "registro.h"

using namespace std;

int main() {

  cout << "Running!" << endl;

  ElRegistro::Instance()->setConfigFile("gateway.cfg");
  std::map<unsigned int,unsigned int> *test;
  test = ElRegistro::Instance()->getWidget();

  for (std::map<unsigned int,unsigned int>::iterator it=test->begin(); it!=test->end(); ++it)
    {
        printf("widget[%d] = %d\n",it->first,it->second);
    }

  Server *s;
  s = new Server();

  //Main loop
  s->AcceptAndDispatch();

  return 0;
}
