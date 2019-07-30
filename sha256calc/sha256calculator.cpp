// vim: set shiftwidth=4 tabstop=4 expandtab:

#include <iostream>
#include <cstring>
#include "sha256.h"
#include "sha256calculator.h"

void session_callback::write_hash_callback(void* data, size_t data_size) {}

SHA256Calculator::SHA256Calculator()
{
  char hash_data[SHA256_LENGTH_IN_HEX_CHAR + 1];
  SHA256 sha256stream;
};

using namespace std;

void SHA256Calculator::dataread(char* data, size_t bytes_transferred, session_callback* session) {
      do {
          void* newlinepos = memchr(data, '\n', bytes_transferred);
          if (newlinepos)
          {
              size_t strlen = ((char*)newlinepos - data);
              this->sha256stream.add(data, strlen);

              this->hash_data[SHA256_LENGTH_IN_HEX_CHAR] = '\n';
              std::memcpy(this->hash_data, sha256stream.getHash().data(), SHA256_LENGTH_IN_HEX_CHAR);
              sha256stream.reset();
              session->write_hash_callback(&this->hash_data, SHA256_LENGTH_IN_HEX_CHAR + 1);

              bytes_transferred = bytes_transferred - strlen - 1;
          } else {
              this->sha256stream.add(data, bytes_transferred);
              break;
          }
          data = (char*)newlinepos + 1;
      } while(bytes_transferred >= 0);
}
