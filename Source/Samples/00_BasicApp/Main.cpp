#include <iostream>

#include "Engine/Application.h"

int main() {
  Application app;

  app.Init();

  app.Run();

  app.Terminate();

  return 0;
}
