#include <iostream>
#include "mythread.h"
#include "server.h"
#include "registro.h"

using namespace std;

int main() {
  cout << "Running!" << endl;

  ElRegistro::Instance()->setConfigFile("gateway.cfg");

//    ElRegistro::Instance()->setWidget(8,0x101010FF);
  Server *s;
  s = new Server();

  //Main loop
  s->AcceptAndDispatch();

  return 0;
}
