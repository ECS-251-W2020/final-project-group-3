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

namespace cs {

typedef bool (*callback_function)(const std::vector<std::string>&);

/****************************************
 * Central Server Implementation
 * 
 * Necessary to prevent asio compile issues
 ***************************************/ 
class central_server_impl : public std::enable_shared_from_this<central_server_impl> {
    public:
        central_server_impl();
        void connect(std::string address);
        void send(request message);
        void receive();
        void handle_connect(const asio::error_code& ec);
        void handle_read(const asio::error_code ec, std::size_t bytes_transferred);
        void set_function(callback_function pFunc);
        std::shared_ptr<central_server_impl> sp() { return shared_from_this(); }
        ~central_server_impl();
    private:
        char                     reply_data[max_length];
        asio::io_context         io_context;
        asio::ip::tcp::socket    socket;
        asio::ip::tcp::resolver  resolver;
        std::vector<std::string> tokens;
        callback_function        do_cmd;
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
    // Hardcoded port for now. Will want to replace eventually.
    asio::async_connect(socket, resolver.resolve(address, "5000"),
       std::bind(&central_server_impl::handle_connect, shared_from_this(), std::placeholders::_1));

    std::thread([this](){ io_context.run(); }).detach(); // Have to think about correctly joining later
}

/****************************************
 * Send a message to the central server
 * 
 * Simply sets up the socket variable
 ***************************************/ 
void central_server_impl::send(request message) {
    asio::streambuf sending;

    try
    {
        std::ostream(&sending) << message;
        size_t n = socket.send(sending.data());

        sending.consume(n);
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }    
}

/****************************************
 * Receives a message from the central server
 ***************************************/ 
void central_server_impl::receive() {
    socket.async_read_some(asio::buffer(reply_data, max_length), 
       std::bind(&central_server_impl::handle_read, shared_from_this(),
       std::placeholders::_1, std::placeholders::_2));
}

/****************************************
 * Handler for asynchronous connection
 ***************************************/ 
void central_server_impl::handle_connect(const asio::error_code& ec) {
    if (!ec) {
        receive();
    } // Maybe add check to close socket?
}

/****************************************
 * Handler for asynchronous reads
 ***************************************/ 
void central_server_impl::handle_read(const asio::error_code ec, std::size_t bytes_transferred) {
    if (!ec) {
        request         reply;
        asio::streambuf receiving;

        if (ec == asio::error::eof)
            socket.close();
        else if (ec)
            throw asio::system_error(ec);

        std::ostream(&receiving) << reply_data;
        if (std::istream(&receiving) >> reply) {
            if (reply.m_type == REPLY) {
                // std::cout << "Message: " << reply.m_message << std::endl;
                // std::cout << "Length: " << bytes_transferred << std::endl;        
            } else if (reply.m_type == ADD_SERVER) {
                // std::cout << "Message:   " << reply.m_message << std::endl;
                // std::cout << "Port:      " << reply.m_port    << std::endl;
                // std::cout << "Server ID: " << reply.m_id      << std::endl;
                std::stringstream ss(reply.m_message);
                std::string intermediate;

                if (tokens.size() > 0) { tokens.clear(); } // Make sure empty
                while(getline(ss, intermediate, ' ')) {
                    tokens.push_back(intermediate);
                }
                do_cmd(tokens);
            }
        } 

        receive();
    } else {
        socket.close();
    }
}

void central_server_impl::set_function(callback_function pFunc) {
    do_cmd = pFunc;
}

/****************************************
 * Destructor
 * 
 * Must ensure that the socket is closed
 * before the instance is destroyed
 ***************************************/ 
central_server_impl::~central_server_impl() {
    if (socket.is_open()) {
        socket.close();
    }
}

/****************************************
 * Default constructor 
 * 
 * Simply sets up the socket variable
 ***************************************/ 
central_server::central_server() 
   : impl_(std::make_shared<central_server_impl>()) {
       impl_->connect("35.188.155.151");
   }

/****************************************
 * Constructor that takes in a function
 * pointer
 * 
 * Necessary for the way they wrote
 * their code
 ***************************************/ 
central_server::central_server(callback_function pFunc)
   : impl_(std::make_shared<central_server_impl>()) {
       impl_->set_function(pFunc);
       impl_->connect("35.188.155.151");
   }

/****************************************
 * Tells server to connect it to a leader
 * of a lobby. If there is no leader yet,
 * then it should become the leader.
 ***************************************/ 
void central_server::join_lobby(int id, int port) {
    request message = { JOIN, id, port, "I want to join!"};
    
    impl_->send(message);
}

/****************************************
 * Destructor
 * 
 * Must ensure that the socket is closed
 * before the instance is destroyed
 ***************************************/ 
central_server::~central_server() {
    //delete impl_;
}
};