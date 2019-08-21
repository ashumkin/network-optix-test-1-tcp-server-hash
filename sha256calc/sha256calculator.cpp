// vim: set shiftwidth=2 tabstop=2 expandtab:

#include <iostream>
#include <cstring>
#include "sha256.h"
#include "sha256calculator.h"

void session_callback::write_hash_callback(void* data, size_t data_size) {}

SHA256Calculator::SHA256Calculator()
{
};

using namespace std;

void SHA256Calculator::dataread(char* data, size_t bytes_transferred, session_callback* session) {
  do {
    // find NL
    void* newlinepos = memchr(data, '\n', bytes_transferred);
    if (newlinepos)
    {
      // if there is a NL, calc hash of a buffered bytes
      size_t strlen = ((char*)newlinepos - data);
      this->sha256stream.add(data, strlen);

      // add a NL to the output string
      this->hash_data[SHA256_LENGTH_IN_HEX_CHAR] = '\n';
      std::memcpy(this->hash_data, sha256stream.getHash().data(), SHA256_LENGTH_IN_HEX_CHAR);
      sha256stream.reset();
      // respond with the calculated hash
      session->write_hash_callback(&this->hash_data, SHA256_LENGTH_IN_HEX_CHAR + 1);

      bytes_transferred = bytes_transferred - strlen - 1;
    } else {
      // if there's no NL in a received buffer, just add the buffer to the calculated hash
      this->sha256stream.add(data, bytes_transferred);
      break;
    }
    data = (char*)newlinepos + 1;
  } while (bytes_transferred >= 0);
}
