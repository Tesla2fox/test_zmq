include_directories (../include)


set(file_list Agent.hpp Agent.cpp main.cpp)

add_executable(test_zmq ${file_list})

target_link_libraries(test_zmq libZMQ)




