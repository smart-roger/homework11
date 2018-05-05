cmake_minimum_required(VERSION 3.9)
project(async VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
#project(async VERSION 0.0)

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

set_target_properties(async PROPERTIES PUBLIC_HEADER async.h)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT __shurik@list.ru)

install (Targets)

include(CPack)