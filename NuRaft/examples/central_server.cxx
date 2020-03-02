/****************************************
 * central_server.cxx
 * 
 * Date: 3/1/2020
 * Author: Julian Angeles
 * 
 * Implementation file of the central 
 * server api.
 ***************************************/ 
#include "central_server.hxx"

/****************************************
 * Default constructor 
 * 
 * Simply sets up the socket variable
 ***************************************/ 
central_server::central_server() {
    io_context = io_context();
    socket = socket(io_context();
}

/****************************************
 * Establishes a connection with the central
 * server with a given ip address
 * 
 * @input address: ip address of CS
 ***************************************/ 
void central_server::connect(std::string address) {
    tcp::resolver resolver(io_context);
    // Hardcoded port for now. Will want to replace eventually.
    asio::connect(socket, resolver.resolve(address, "5000"))
}

/****************************************
 * Tells server to connect it to a leader
 * of a lobby. If there is no leader yet,
 * then it should become the leader.
 ***************************************/ 
void central_server::join() {
}

/****************************************
 * Establishes a connection with the central
 * server with a given ip address
 * 
 * @input address: ip address of CS
 ***************************************/ 
/****************************************
 * Establishes a connection with the central
 * server with a given ip address
 * 
 * @input address: ip address of CS
 ***************************************/ 
/****************************************
 * Establishes a connection with the central
 * server with a given ip address
 * 
 * @input address: ip address of CS
 ***************************************/ 
/****************************************
 * Establishes a connection with the central
 * server with a given ip address
 * 
 * @input address: ip address of CS
 ***************************************/ 
/****************************************
 * Establishes a connection with the central
 * server with a given ip address
 * 
 * @input address: ip address of CS
 ***************************************/ 
/****************************************
 * Establishes a connection with the central
 * server with a given ip address
 * 
 * @input address: ip address of CS
 ***************************************/ 
/****************************************
 * Establishes a connection with the central
 * server with a given ip address
 * 
 * @input address: ip address of CS
 ***************************************/ 
/****************************************
 * Establishes a connection with the central
 * server with a given ip address
 * 
 * @input address: ip address of CS
 ***************************************/ 
/****************************************
 * Destructor
 * 
 * Must ensure that the socket is closed
 * before the instance is destroyed
 ***************************************/ 
~central_server::central_server() {
    if (socket.is_open()) {
        //std::unique_lock<std::mutex> l(socket_lock_, std::try_to_lock);
        //if (l.owns_lock() && socket_.is_open()) {
            socket.close();
        //}
    }
}