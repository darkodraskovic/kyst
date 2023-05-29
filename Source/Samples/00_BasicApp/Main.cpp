#include <iostream>

#include "Engine/Application.h"

using namespace Kyst;

int main() {
  Application app;

  app.Init();

  app.Run();

  app.Terminate();

  return 0;
}
