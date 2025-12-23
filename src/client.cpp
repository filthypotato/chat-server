#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <stdio.h>

struct Client
{
    std::string ip{};
    int port{};
    std::string tcp{};

    Client(); // constructor

    Client(std::string ip, int port, std::string tcp); // Constructor with parameters

    ~Client();

    void show() const; // shows connecting to IP with port
};

Client::Client()    // Constructor
{
    ip = "127.0.0.1";
    port = 8080;
    tcp = "TCP";
};

Client::Client(std::string ip, int port, std::string tcp) // Constructor with parameters
{
    this->ip    = ip;
    this->port  = port;
    this->tcp   = tcp;
}

Client::~Client()
{
    std::cout << "Deconstuctor coming in hot! \n";
}

void Client::show() const
{
    std::cout << "You are connecting to IP: " << ip << "\n"
                                  "On port: " << port << "\n";

};


int main()
{
    // Makes a client with defaults (127.0.0.1:8080)
    Client client;
    client.show();

    // Initalize Winsock
    WSADATA wsaData{};
    int res = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (res != 0) {
        std::cout << "WSAStartup failed: " << res << "\n";
        return 1;
    }

    // Create client socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cout << "socket() failed: " << WSAGetLastError() << "\n";
        WSACleanup();
        return 1;
    }

    // Server address
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(client.port);
    // convert string IP ("127.0.0.1") to binary
    inet_pton(AF_INET, client.ip.c_str(), &serverAddress.sin_addr);

    // Connects to the client to the server
    if (connect(clientSocket,
        reinterpret_cast<sockaddr*>(&serverAddress),
        sizeof(serverAddress)) == SOCKET_ERROR)
    {
        std::cout << "connect() failed: " << WSAGetLastError() << "\n";
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Connected to server!\n";

    std::string message{};
    std::cout << "Send a message: ";
    std::getline(std::cin, message);

    send(clientSocket, message.c_str(), static_cast<int>(message.size()), 0);
    
 

    // Sends some data to the server
    //const char* message = "Hello, server!";
    //send(clientSocket, message, static_cast<int>(strlen(message)), 0);

    // Close the client socket
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
