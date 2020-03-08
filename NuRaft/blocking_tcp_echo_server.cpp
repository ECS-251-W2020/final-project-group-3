//
// blocking_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2018 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <map>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>
#include <utility>
#include "asio.hpp"

using asio::ip::tcp;

const int max_length = 1024;
std::map<int, std::string> leaders;
std::map<std::string, std::shared_ptr<tcp::socket>> sockets;

enum MSG_TYPE { JOIN,
                ADD_SERVER,
                REPLY,
                MSG_COUNT
              };

struct request {
   MSG_TYPE m_type;
   int m_id;
   int m_port;
   std::string m_message;
};

std::ostream &operator<<(std::ostream &out, request const &r) {
   return out << r.m_type << ";" << r.m_id << ";" << r.m_port << ";"
              << r.m_message.length() << ";" << r.m_message;
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
          && in >> r.m_id
          && in >> separator && separator == ';'
          && in >> r.m_port
          && in >> separator && separator == ';'
          && in >> length
          && in >> separator && separator == ';'
          ;
   if (ok) { //WHY DOES THIS DO THIS????
      r.m_message.resize(length);
      in.read(&r.m_message[0], length);

      r.m_message.resize(in.gcount());
}

   ok = ok && (r.m_message.length() == length);

   if (!ok)
      in.setstate(std::ios::failbit);

   return in;
}

void session(tcp::socket sock)
{
  asio::streambuf buf;
  asio::streambuf reply;
  asio::streambuf leader_msg;
  request received;
  std::string address = sock.remote_endpoint().address().to_string();
  
  sockets.insert({ address, std::make_shared<tcp::socket>(std::move(sock)) });

  if (leaders.find(0) == leaders.end()) {
    std::cout << "New leader: " << address << std::endl;
    leaders.insert({ 0, address });
  } else {
    std::cout << leaders[0] << " is leader of lobby 0" << std::endl;
  }
  // connections.push_back(std::shared_ptr<tcp::socket>(std::move(sock)));
  // std::shared_ptr<tcp::socket> = 
  //    std::shared_ptr<tcp::socket>(std::move(sock));
  try
  {
    for (;;)
    {
      char data[max_length];

      asio::error_code error;
      size_t length = sockets[address]->read_some(asio::buffer(data), error);
      //size_t n = sock.receive(buf);

      //auto bytes_transferred = asio::read(sock, asio::buffer(data, max_length));
      //std::cout << buf.data() << error << std::endl;
      //std::cout << "Bytes transferred: " << bytes_transferred << std::endl;
      std::cout << "Message length:    " << length << std::endl;
      if (error == asio::error::eof){
        sockets.erase(address);
        break; // Connection closed cleanly by peer.
      }
      else if (error) {
        sockets.erase(address);
        throw asio::system_error(error); // Some other error.
      }
      std::ostream(&buf) << data;

      if (std::istream(&buf) >> received) {
         std::cout << "Message Type: " << received.m_type << std::endl;
         std::cout << "Message:      " << received.m_message << std::endl;

         if (received.m_type == JOIN) {
            if (leaders[0] != address) {
              std::ostream(&reply) << request{ REPLY, 0, 0, "You want to join!" };
              std::ostream(&leader_msg) << request{ ADD_SERVER, received.m_id,  
                 received.m_port, "add " + std::to_string(received.m_id) + " " 
                 + address + ":" + std::to_string(received.m_port) };

              size_t l = sockets[leaders[0]]->send(leader_msg.data());
              leader_msg.consume(l);
            } else {
              std::ostream(&reply) << request{ REPLY, 0, 0, "You are the leader!" };
            }
         } else {
            std::ostream(&reply) << request{ REPLY, 0, 0, "Error!!" };
         }
      } else {
         std::cout << "Couldn't receive request\n";
      }
      //buf.commit(length);

      //std::cout << reply << std::endl;
      //std::ostream(&buf) << reply;

      size_t n = sockets[address]->send(reply.data());
      reply.consume(n);
      /*std::string test(data);
      if (test == "hi") { data[0] = 'b'; } else { data[0] = 'l'; }
      std::cout << test;
      std::cout << std::endl;*/
      //asio::write(sock, asio::buffer(data, length));
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception in thread: " << e.what() << "\n";
  }
}

void server(asio::io_context& io_context, unsigned short port)
{
  tcp::acceptor a(io_context, tcp::endpoint(tcp::v4(), port));
  for (;;)
  {
    std::thread(session, a.accept()).detach();
  }
}

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: blocking_tcp_echo_server <port>\n";
      return 1;
    }

    asio::io_context io_context;

    server(io_context, std::atoi(argv[1]));
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}