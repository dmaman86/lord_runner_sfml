cmake_minimum_required (VERSION 3.14)

project (final_sfml)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
if (MSVC)
    add_compile_options (/permissive-)
endif ()

add_executable (final_sfml)

add_subdirectory (include)
add_subdirectory (src)
add_subdirectory (resources)

#this is for macos==============================
include_directories(/usr/local/include)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIRS})
    target_link_libraries(final_sfml sfml-window sfml-graphics sfml-audio sfml-network)
endif()
#=========================================
