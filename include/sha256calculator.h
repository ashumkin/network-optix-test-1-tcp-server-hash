#include "sha256.h"

class session_callback
{
public:
    void virtual write_hash_callback(void* data, size_t data_size);
};

class SHA256Calculator
{
public:
    SHA256Calculator();


    void dataread(char* data, size_t bytes_transferred, session_callback* session);

private:
    SHA256 sha256stream;
    enum
    {
        SHA256_LENGTH_IN_HEX_CHAR = 64
    };

    char hash_data[SHA256_LENGTH_IN_HEX_CHAR + 1];
};
