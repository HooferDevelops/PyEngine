cmake_minimum_required (VERSION 3.8)

set (TARGET_NAME Main)

set(PYBIND11_PYTHON_VERSION 3.10.2 CACHE STRING "")
find_package(pybind11 CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(magic_enum CONFIG REQUIRED)

# If you want SFML to provide an implementation of main():
#target_link_libraries(main PRIVATE sfml-main)

add_executable (${TARGET_NAME} "Main.cpp" "render/window.cpp" "render/window.h" )

target_link_libraries(${TARGET_NAME} PRIVATE pybind11::lto pybind11::embed pybind11::module)
target_link_libraries(${TARGET_NAME} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
target_link_libraries(${TARGET_NAME} PRIVATE magic_enum::magic_enum)
#target_link_libraries(${TARGET_NAME} PRIVATE pybind11::embed pybind11::module pybind11::pybind11)

# set binary filenames
set_target_properties( ${TARGET_NAME} PROPERTIES OUTPUT_NAME_DEBUG ${TARGET_NAME}-debug )
set_target_properties( ${TARGET_NAME} PROPERTIES OUTPUT_NAME_RELWITHDEBINFO ${TARGET_NAME}-relwidthdebinfo )
set_target_properties( ${TARGET_NAME} PROPERTIES OUTPUT_NAME_RELEASE ${TARGET_NAME}-release )
set_target_properties( ${TARGET_NAME} PROPERTIES OUTPUT_NAME_MINSIZEREL ${TARGET_NAME}-minsizerel )

# set warning levels
if (MSVC)
	target_compile_options(${TARGET_NAME} PUBLIC /W4 /permissive)
else()
	target_compile_options(${TARGET_NAME} PUBLIC -Wall -Wextra -pedantic)
endif()