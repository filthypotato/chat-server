cmake_minimum_required(VERSION 3.20)
project(ChatStuff LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

# server exe
add_executable(chat_server
    src/server.cpp
)

# client exe
add_executable(chat_client
    src/client.cpp
)

if (WIN32)
  target_link_libraries(chat_server PRIVATE ws2_32)
  target_link_libraries(chat_client PRIVATE ws2_32)
endif()
