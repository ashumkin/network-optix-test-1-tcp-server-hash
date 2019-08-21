// vim: set shiftwidth=2 tabstop=2 expandtab:

#include <iostream>
#include <cstring>
#include "sha256calculator.h"

using namespace std;

class ConsoleWriter : public session_callback
{
public:
  void write_hash_callback(void* data, size_t data_size)
  {
    cout << string((char*)data, data_size);
  }
};

int main(int argc, char** argv)
{
  if (argc > 1) {
    SHA256Calculator sha256Calculator;
    ConsoleWriter consoleWriter;
    for(int i = 1; i < argc; i++)
    {
      sha256Calculator.dataread(argv[i], strlen(argv[i]), &consoleWriter);
    }
  }
}
