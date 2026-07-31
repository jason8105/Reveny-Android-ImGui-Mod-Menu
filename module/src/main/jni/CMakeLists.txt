cmake_minimum_required(VERSION 3.22)
project(reveny_hook)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(
    log-lib REQUIRED
)

add_library(
    reveny_hook SHARED
    main.cpp
)

target_link_libraries(
    reveny_hook
    ${log-lib}
)
