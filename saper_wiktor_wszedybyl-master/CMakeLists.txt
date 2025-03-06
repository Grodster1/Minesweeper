cmake_minimum_required(VERSION 3.27)
project(Lab_2)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic -Werror=return-type -Werror=parentheses -Werror=vla -Werror=array-bounds -Wcast-qual -Wmaybe-uninitialized)


file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})


add_executable(Lab_2 main.cpp
        MinesweeperBoard.h
        MinesweeperBoard.cpp
        MSBoardTextView.cpp
        MSBoardTextView.h
        MSTextController.cpp
        MSTextController.h
)

IF (WIN32)
    set(SFML_DIR "C:/SFML-2.6.1/lib/cmake/SFML")
    set(SFML_STATIC_LIBRARIES TRUE)
ENDIF()

find_package(SFML 2.6 COMPONENTS graphics audio REQUIRED)

add_executable(saper_sfml main-sfml.cpp MinesweeperBoard.cpp MSBSFMLView.cpp MSBSFMLController.cpp MSBSFMLController.h MSBSFMLMenu.h MSBSFMLMenu.cpp)
target_link_libraries(saper_sfml sfml-graphics)

