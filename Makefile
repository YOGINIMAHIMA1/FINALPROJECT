# Define compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Define targets and their dependencies
all: client server

client: client.o
	$(CXX) $(CXXFLAGS) -o client client.o

server: server.o
	$(CXX) $(CXXFLAGS) -o server server.o

# Compile the client source file
client.o: client.cpp
	$(CXX) $(CXXFLAGS) -c client.cpp

# Compile the server source file
server.o: server.cpp
	$(CXX) $(CXXFLAGS) -c server.cpp

# Clean up build files
clean:
	rm -f *.o client server

.PHONY: all clean
