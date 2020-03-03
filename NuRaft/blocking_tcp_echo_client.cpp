//
// blocking_tcp_echo_client.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2018 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include "asio.hpp"

using asio::ip::tcp;

enum { max_length = 1024 };
enum MSG_TYPE { JOIN,
                ADD_SERVER,
                REPLY,
                MSG_COUNT
              };

struct request {
    MSG_TYPE m_type;
    std::string m_message;
};

std::ostream &operator<<(std::ostream &out, request const &r) {
   return out << r.m_type << ";" << r.m_message.length() << ";" << r.m_message;
}

std::istream &operator>>(std::istream &in, MSG_TYPE &m) {
   unsigned int m_type;

   if (!(in >> m_type))
      return in;
   if (m_type >= MSG_COUNT) {
      in.setstate(in.rdstate() | std::ios::failbit);
      return in;
   }

   m = static_cast<MSG_TYPE>(m_type);
   return in;
}

std::istream &operator>>(std::istream &in, request &r) {
   char separator;
   size_t length;

   bool ok = in >> r.m_type
          && in >> separator && separator == ';'
          && in >> length
          && in >> separator && separator == ';'
          ;
   if (ok) {
      r.m_message.resize(length);
      in.read(&r.m_message[0], length);

      r.m_message.resize(in.gcount());
   }

   ok = ok && (r.m_message.length() == length);

   if (!ok)
      in.setstate(std::ios::failbit);

   return in;
}

int main(int argc, char* argv[])
{
  asio::streambuf buf;
  asio::streambuf reply;
  request test;
  request reply_q;

  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
      return 1;
    }

    asio::io_context io_context;

    tcp::socket s(io_context);
    tcp::resolver resolver(io_context);
    asio::connect(s, resolver.resolve(argv[1], argv[2]));

    std::ostream(&buf) << request{ JOIN, "Hello World!" };
    size_t n = s.send(buf.data());

    request received;

    if (std::istream(&buf) >> received) {
       std::cout << "Message Type: " << received.m_type << std::endl;
       std::cout << "Message:      " << received.m_message << std::endl;
    }  else {
       std::cout << "Couldn't receive request\n";
    }

    buf.consume(n);

    char reply_data[max_length];
    asio::error_code error;
    size_t reply_length = s.read_some(asio::buffer(reply_data), error);
    std::cout << "And here!" << std::endl;
    std::cout << "Reply is: ";
    std::ostream(&reply) << reply_data;
    if (std::istream(&reply) >> reply_q) {
       std::cout << "Message: " << reply_q.m_message << std::endl;
       std::cout << "Length: " << reply_length << std::endl;
    }

    //std::ostringstream ss;
    //ss << buf;
    //std::string reply = ss.str();
    /*std::cout << "Enter message: ";
    char request[max_length];
    std::cin.getline(request, max_length);
    size_t request_length = std::strlen(request);
    asio::write(s, asio::buffer(request, request_length));

    char reply[max_length];
    size_t reply_length = asio::read(s,
        asio::buffer(reply, request_length));
    std::cout << "Reply is: ";
    std::cout.write(reply, reply_length);
    std::cout << "\n";*/
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}