# Makefile for compiling and running the server and client

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11

# Source files
SERVER_SRC = server.cpp
CLIENT_SRC = client.cpp

# Executable files
SERVER_EXEC = server
CLIENT_EXEC = client

# Default target
all: $(SERVER_EXEC) $(CLIENT_EXEC)

# Compile server
$(SERVER_EXEC): $(SERVER_SRC)
	$(CXX) $(CXXFLAGS) -o $(SERVER_EXEC) $(SERVER_SRC)

# Compile client
$(CLIENT_EXEC): $(CLIENT_SRC)
	$(CXX) $(CXXFLAGS) -o $(CLIENT_EXEC) $(CLIENT_SRC)

# Clean up compiled files
clean:
	rm -f $(SERVER_EXEC) $(CLIENT_EXEC)

# Run server
run-server: $(SERVER_EXEC)
	./$(SERVER_EXEC)

# Run client
run-client: $(CLIENT_EXEC)
	./$(CLIENT_EXEC)

.PHONY: all clean run-server run-client
