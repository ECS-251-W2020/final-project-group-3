CC=g++

#LD_FLAGS        := -L/asio/asio
CUR_DIR          := $(PWD)
ASIO_INCLUDE_DIR := /asio/asio/include
INCLUDES := -I$(CUR_DIR)$(ASIO_INCLUDE_DIR)

CC_FLAGS := -Wall -Werror $(INCLUDES) -std=c++11

asio_server: blocking_tcp_echo_client.cpp	
	$(CC) $(CC_FLAGS) -o $@ $^

asio_client: blocking_tcp_echo_server.cpp
	$(CC) $(CC_FLAGS) -o $@ $^

clean:
	rm asio_*
