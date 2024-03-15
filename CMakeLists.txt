cmake_minimum_required(VERSION 3.0.0)
project(audio_tester_server VERSION 0.1.0 LANGUAGES C CXX)
# SET(CMAKE_CXX_COMPILER /usr/bin/g++)
include(CTest)
enable_testing()

find_package(glog REQUIRED)    
find_package(nlohmann_json REQUIRED)
find_package(PkgConfig)

pkg_check_modules(Pistache REQUIRED IMPORTED_TARGET libpistache)
#include_directories(${GLOG_INCLUDE_DIR})   

include_directories(${PROJECT_SOURCE_DIR}/include)
aux_source_directory(${PROJECT_SOURCE_DIR}/src src)
aux_source_directory(${PROJECT_SOURCE_DIR}/model model)
aux_source_directory(${PROJECT_SOURCE_DIR}/utils utils)

#add_library(Mylog SHARED utils/MyLogger.cpp)
include_directories(/usr/include/mysql)
include_directories(/usr/include/jsoncpp)
link_directories(/usr/lib/x86_64-linux-gnu)


set(MYSQL_LIBS 
    mysqlclient pthread ssl crypto dl resolv m rt
    )

# add_library(mysqlConn SHARED src/mysql_conn.cpp)
# add_library(connPool SHARED src/connection_pool.cpp)

# target_link_libraries(${PROJECT_NAME} log4cpp)
add_executable(audio_tester_server main.cpp ${src} ${model} ${utils})

target_link_libraries(audio_tester_server glog PkgConfig::Pistache nlohmann_json::nlohmann_json ${MYSQL_LIBS} 
    /usr/lib/x86_64-linux-gnu/libjsoncpp.so.1.9.5 
    /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30
    /usr/lib/x86_64-linux-gnu/libcrypto++.a 
    /usr/lib/x86_64-linux-gnu/libcurl.so.4.7.0
    /usr/lib/x86_64-linux-gnu/libhiredis.so.0.14)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
