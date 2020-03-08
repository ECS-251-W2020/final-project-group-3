#ifndef CENTRAL_SERVER_FUNCTIONS_HXX
#define CENTRAL_SERVER_FUNCTIONS_HXX

#include "central_server.hxx"

void connect_to_central_server() {
    cs::central_server app;

    app.join_lobby();

    // Maybe return pointer of cs for program
    // update leader of lobby in case of election?
};

#endif