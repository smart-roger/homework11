cmake_minimum_required(VERSION 3.9)
project(async)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_library(async SHARED 
				async.cpp 
				async.h
				include/TBlockProcessor.h
				include/TCommandProcessor.h
				include/TCommandStore.h
				include/TConsole.h
				include/TObserver.h
				src/TBlockProcessor.cpp
				src/TCommandProcessor.cpp
				src/TCommandStore.cpp
				src/TConsole.cpp
				src/TObserver.cpp)

add_executable(async_cli main.cpp)

target_link_libraries(async_cli async)