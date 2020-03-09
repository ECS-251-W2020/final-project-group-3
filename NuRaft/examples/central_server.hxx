/****************************************
 * central_server.hxx
 * 
 * Date: 3/1/2020
 * Author: Julian Angeles
 * 
 * This class acts as the servers api
 * with the central server. Functionality
 * includes the ability to join public/private
 * lobbies and update it if the server becomes
 * the new leader.
 ***************************************/ 
#ifndef CENTRAL_SERVER_HXX
#define CENTRAL_SERVER_HXX

#include <string>
#include <vector>
#include <memory>
namespace cs {

typedef bool (*callback_function)(const std::vector<std::string>&);

class central_server_impl;
class central_server {
    public:
        central_server();
        central_server(callback_function pFunc);
        //central_server(asio::io_context io_context, std::string address);
        void connect(std::string address);
        void join_lobby(int id, int port);
        // FUTURE FEATURES
        void connect(); // USING HOST NAME
        void join_lobby(int lobby_id);
        void create_private_lobby(std::string lobby_id, std::string password);
        void join_private_lobby(std::string password); // NOT SECURE!!
        void update_leader();
        ~central_server();
    private:
        std::shared_ptr<central_server_impl> impl_;
};
};
#endif