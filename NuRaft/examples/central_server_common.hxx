#ifndef CENTRAL_SERVER_COMMON_HXX
#define CENTRAL_SERVER_COMMON_HXX

#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <thread>
#include <utility>

const int max_length = 1024;

enum MSG_TYPE { JOIN,
                ADD_SERVER,
                REPLY,
                MSG_COUNT
};

struct request {
   MSG_TYPE m_type;
   std::string m_id;
   std::string m_port;
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
};


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


#endif