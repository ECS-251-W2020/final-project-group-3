#ifndef CENTRAL_SERVER_FUNCTIONS_HXX
#define CENTRAL_SERVER_FUNCTIONS_HXX

#include "central_server.hxx"

void listen_to_server() {
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

void connect_to_central_server() {
    cs::central_server app;

    app.join_lobby();

    std::thread(listen_to_server, &app);

    // Maybe return pointer of cs for program
    // update leader of lobby in case of election?
};

#endif