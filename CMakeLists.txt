cmake_minimum_required(VERSION 3.15)

project("pizza"
    VERSION 0.0.1
    DESCRIPTION "Example of use of cpp-commander"
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(commander
  GIT_REPOSITORY https://github.com/turbodt/cpp-commander.git
  GIT_TAG main
)
FetchContent_MakeAvailable(commander)

add_executable(
  ${PROJECT_NAME}
  src/main.cpp
  src/utils.cpp
  src/order.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE src/)
target_link_libraries(${PROJECT_NAME} PRIVATE Commander)


