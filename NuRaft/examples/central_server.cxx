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
#include "central_server_common.hxx"
#include "asio.hpp"

//using asio::ip::tcp;

namespace cs {
/****************************************
 * Central Server Implementation
 * 
 * Necessary to prevent asio compile issues
 ***************************************/ 
class central_server_impl {
    public:
        central_server_impl();
        void connect(std::string address);
        void send(request message);
        void listen_to_server();
        ~central_server_impl();
    private:
        asio::io_context        io_context;
        asio::ip::tcp::socket   socket;
        asio::ip::tcp::resolver resolver;
};

/****************************************
 * Default constructor 
 * 
 * Simply sets up the socket variable
 ***************************************/ 
central_server_impl::central_server_impl() 
   : io_context()
   , socket(io_context)
   , resolver(io_context)
   {}

/****************************************
 * Establishes a connection with the central
 * server with a given ip address
 * 
 * @input address: ip address of CS
 ***************************************/ 
void central_server_impl::connect(std::string address) {
    //asio::ip::tcp::resolver resolver(io_context);
    // Hardcoded port for now. Will want to replace eventually.
    asio::connect(socket, resolver.resolve(address, "5000"));

    std::thread(listen_to_server);
}

/****************************************
 * Send a message to the central server
 * 
 * Simply sets up the socket variable
 ***************************************/ 
void central_server_impl::send(request message) {
    asio::streambuf sending;
    asio::streambuf receiving;
    request reply;

    try
    {
        std::ostream(&sending) << message;
        size_t n = socket.send(sending.data());

        // request received;

        // if (std::istream(&sending) >> received) {
        // std::cout << "Message Type: " << received.m_type << std::endl;
        // std::cout << "Message:      " << received.m_message << std::endl;
        // }  else {
        // std::cout << "Couldn't receive request\n";
        // }

        sending.consume(n);

        char reply_data[max_length];
        asio::error_code error;
        size_t reply_length = socket.read_some(asio::buffer(reply_data), error);
        std::cout << "And here!" << std::endl;
        std::cout << "Reply is: ";
        std::ostream(&receiving) << reply_data;
        if (std::istream(&receiving) >> reply) {
        std::cout << "Message: " << reply.m_message << std::endl;
        std::cout << "Length: " << reply_length << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }    
}

/****************************************
 * Listen to server
 * 
 ***************************************/ 
void central_server_impl::listen_to_server() {
    asio::streambuf receiving;
    request reply;

    for(;;) {
        char reply_data[max_length];
        asio::error_code error;
        size_t reply_length = socket.read_some(asio::buffer(reply_data), error);
        std::cout << "Message from server!" << std::endl;
        std::ostream(&receiving) << reply_data;
        if (std::istream(&receiving) >> reply) {
            std::cout << "Message: " << reply.m_message << std::endl;
            std::cout << "Length: " << reply_length << std::endl;        
        } 
    }
}

/****************************************
 * Destructor
 * 
 * Must ensure that the socket is closed
 * before the instance is destroyed
 ***************************************/ 
central_server_impl::~central_server_impl() {
    if (socket.is_open()) {
        //std::unique_lock<std::mutex> l(socket_lock_, std::try_to_lock);
        //if (l.owns_lock() && socket_.is_open()) {
            socket.close();
        //}
    }
}

/****************************************
 * Default constructor 
 * 
 * Simply sets up the socket variable
 ***************************************/ 
central_server::central_server() 
   : impl_(new central_server_impl()) {
       impl_->connect("35.188.155.151");
   }

/****************************************
 * Tells server to connect it to a leader
 * of a lobby. If there is no leader yet,
 * then it should become the leader.
 ***************************************/ 
void central_server::join_lobby() {
    request message = { JOIN, "Hello World"};
    
    impl_->send(message);
}

/****************************************
 * Destructor
 * 
 * Must ensure that the socket is closed
 * before the instance is destroyed
 ***************************************/ 
central_server::~central_server() {
    delete impl_;
}
};