#ifdef _WIN32
  #include <winsock2.h>
  #include <ws2tcpip.h>
  #pragma comment(lib, "ws2_32.lib")
  using socket_t = SOCKET;
#else
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <unistd.h>
  #include <errno.h>
  using socket_t = int;
  #define INVALID_SOCKET (-1)
  #define SOCKET_ERROR   (-1)
#endif


int main()
{
    WSADATA wsaData{};  // Initalizes Winsock
    int res = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (res != 0) {
        std::cout << "WSAStartup failed: " << res << "\n";
        return 1;
    }

    // SOCKET used for type
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0); // Creates the server socket
    if (serverSocket == INVALID_SOCKET) {
        std::cout << "socket() failed: " << WSAGetLastError() << "\n";
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddress{}; // Defines server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(6667);     // port
    serverAddress.sin_addr.s_addr = INADDR_ANY; // any local IP

    // Binds the socket
    if (bind(serverSocket,
        reinterpret_cast<sockaddr*>(&serverAddress),
        sizeof(serverAddress)) == SOCKET_ERROR)
    {
        std::cout << "bind() failed: " << WSAGetLastError() << "\n";
        std::cout << "Check other running servers :) ";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Listening for incoming connections
    if (listen(serverSocket, 5) == SOCKET_ERROR) {
        std::cout << "listen() failed: " << WSAGetLastError() << "\n";
        std::cout << "You just might have another server open ;) \n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server listening on port " << serverAddress.sin_port << "....\n";

    // Accepts client incoming client connections
    SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
    if (clientSocket == INVALID_SOCKET) {
        std::cout << "accept() failed: " << WSAGetLastError() << "\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    std::cout << "Client connected!\n";

    // Receive data
    char buffer[1024] = {};
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        std::cout << "Message from client: " << buffer << "\n";
    }

    // Close sockets
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
