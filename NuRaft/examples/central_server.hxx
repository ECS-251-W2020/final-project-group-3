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
namespace cs {

class central_server_impl;
class central_server {
    public:
        central_server();
        central_server(std::string address);
        //central_server(asio::io_context io_context, std::string address);
        void connect(std::string address);
        void join_lobby();
        // FUTURE FEATURES
        void connect(); // USING HOST NAME
        void join_lobby(int lobby_id);
        void create_private_lobby(std::string lobby_id, std::string password);
        void join_private_lobby(std::string password); // NOT SECURE!!
        void update_leader();
        ~central_server();
    private:
        //std::shared_ptr<central_server_impl> impl_;
        central_server_impl* impl_;
};
};
#endif