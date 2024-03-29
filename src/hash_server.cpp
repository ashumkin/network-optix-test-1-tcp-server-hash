//# vim: set shiftwidth=2 tabstop=2 expandtab:
//
// async_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include "asio.hpp"
#include "sha256calculator.h"

using asio::ip::tcp;

class session : session_callback
{
public:
  session(asio::io_context &io_context)
      : socket_(io_context)
  {
  }

  tcp::socket &socket()
  {
    return socket_;
  }

  void start()
  {
    socket_.async_read_some(asio::buffer(data_, max_length),
                            boost::bind(&session::handle_read, this,
                                        asio::placeholders::error,
                                        asio::placeholders::bytes_transferred));
  }

  void write_hash_callback(void* data, size_t data_size)
  {
    asio::async_write(socket_,
        asio::buffer(data, data_size),
        boost::bind(&session::handle_write, this,
          asio::placeholders::error));
  }

private:

  void handle_read(const asio::error_code &error,
                   size_t bytes_transferred)
  {
    if (!error)
    {
      sha256calculator.dataread(data_, bytes_transferred, this);

      socket_.async_read_some(asio::buffer(data_, max_length),
                              boost::bind(&session::handle_read, this,
                                          asio::placeholders::error,
                                          asio::placeholders::bytes_transferred));

      std::stringstream received;
      received << "Received " << bytes_transferred << " bytes";
      std::cerr << received.str() << std::endl;
    }
  }

  void handle_write(const asio::error_code &error)
  {
    if (!error)
    {
      socket_.async_read_some(asio::buffer(data_, max_length),
                              boost::bind(&session::handle_read, this,
                                          asio::placeholders::error,
                                          asio::placeholders::bytes_transferred));
    }
  }

  tcp::socket socket_;
  enum
  {
    max_length = 1024
  };
  char data_[max_length + 1] = {0};
  SHA256Calculator sha256calculator;
};

class server
{
public:
  server(asio::io_context &io_context, short port)
      : io_context_(io_context),
        acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
  {
    start_accept();
  }

private:
  void start_accept()
  {
    session *new_session = new session(io_context_);
    acceptor_.async_accept(new_session->socket(),
                           boost::bind(&server::handle_accept, this, new_session,
                                       asio::placeholders::error));
  }

  void handle_accept(session *new_session,
                     const asio::error_code &error)
  {
    if (!error)
    {
      new_session->start();
    }
    else
    {
      delete new_session;
    }

    start_accept();
  }

  asio::io_context &io_context_;
  tcp::acceptor acceptor_;
};

int main(int argc, char *argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: hash_server <port>\n";
      return 1;
    }

    asio::io_context io_context;

    using namespace std; // For atoi.
    server s(io_context, atoi(argv[1]));

    io_context.run();
  }
  catch (std::exception &e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
