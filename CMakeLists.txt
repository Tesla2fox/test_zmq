
#最小版本的要求
cmake_minimum_required(VERSION 3.0)



# macro(use_cxx11)
# if (CMAKE_VERSION VERSION_LESS "3.1")
#   if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
#     set (CMAKE_CXX_FLAGS "-std=gnu++11 ${CMAKE_CXX_FLAGS}")
#   endif ()
# else ()
#   set (CMAKE_CXX_STANDARD 11)
# endif ()
# endmacro(use_cxx11)
# message("use the c++ 11")


set (CMAKE_CXX_STANDARD 14)

set(CMAKE_C_STANDARD 11)

# define  1

# add_definitions(-__STDC_WANT_LIB_EXT1__)
#项目名称
project(zmqPro)

message("PROJECT_SOURCE_DIR" ${PROJECT_SOURCE_DIR})
#添加外部dll
add_library(libZMQ SHARED IMPORTED)

if(WIN32)
	set_target_properties(libZMQ PROPERTIES
	IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/libzmq.dll 
	IMPORTED_IMPLIB   ${PROJECT_SOURCE_DIR}/lib/libzmq.lib)
else()
	set_target_properties(libZMQ PROPERTIES
	IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/libzmq.so) 
	# IMPORTED_IMPLIB   ${PROJECT_SOURCE_DIR}/lib/libzmq.lib
endif()



#测试主函数的文件夹
add_subdirectory(src test_zmq)