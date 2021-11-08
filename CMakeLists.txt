cmake_minimum_required(VERSION 3.0.0)
set(TARGET_NAME trove)
project(${TARGET_NAME} VERSION 0.1.0)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 

include_directories(${LIBVLC_INCLUDE}) 
include_directories(${VLCPP_INCLUDE}) 

cmake_policy(SET CMP0076 NEW)
set (CMAKE_CXX_STANDARD 17)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 

# Disables linking against the Debug version of Python
# set (Python_FIND_ABI "OFF" "ANY" "ANY")

# set(PYTHON_DEPS 
#     sqlalchemy 
#     cython
#     pywin32
#     python-vlc
#     python-telnet-vlc
#     debugpy
#     ansicolors
# )

# set(PYTHON_DEBUG_DEPS)

# If you're using Boost:
add_executable(${TARGET_NAME})
add_subdirectory("./src/cpp")
include_directories("./src/cpp")

# Adding Python
find_package(Python 3.10 COMPONENTS Development Interpreter REQUIRED)
target_link_libraries(${TARGET_NAME} PRIVATE Python::Python)

message(STATUS PY-SOABI: ${Python_SOABI})

# Adding Boost
find_package(Boost 1.70.0 COMPONENTS filesystem REQUIRED)
target_link_libraries(${TARGET_NAME} PRIVATE Boost::filesystem)

# Once again, boost-python proves to be more trouble than it's worth.

# Adding SDL2
find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${TARGET_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)

# Adding SDL2-Image
find_package(sdl2-image CONFIG REQUIRED)
target_link_libraries(${TARGET_NAME} PRIVATE SDL2::SDL2_image)

# Adding SDL2-Net
find_package(sdl2-net CONFIG REQUIRED)
target_link_libraries(${TARGET_NAME} PRIVATE SDL2::SDL2_net)

# Adding SDL2-TFF
find_package(sdl2-ttf CONFIG REQUIRED)
target_link_libraries(${TARGET_NAME} PRIVATE SDL2::SDL2_ttf)

# Adding IMGUI
find_package(imgui CONFIG REQUIRED)
target_link_libraries(${TARGET_NAME} PRIVATE imgui::imgui)

# Adding OpenGL
find_package(OpenGL COMPONENTS OpenGL REQUIRED)
target_link_libraries(${TARGET_NAME} PRIVATE OpenGL::GL)

# Adding GLEW
find_package(GLEW REQUIRED)
target_link_libraries(${TARGET_NAME} PRIVATE GLEW::GLEW)

# Linking LibVLC
target_link_libraries(${TARGET_NAME} PRIVATE ${LIBVLC_LIB})

set_target_properties(${TARGET_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "./arc/"
    LIBRARY_OUTPUT_DIRECTORY "./lib/"
    RUNTIME_OUTPUT_DIRECTORY "./bin/"
)

set(VLC_COPY ${LIBVLC_RELEASE_ASSETS})
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(VLC_COPY ${LIBVLC_DEBUG_ASSETS})

    message(STATUS "Copying VLC debug assets...")
else()
    message(STATUS "Copying VLC release assets...")
endif()
file(COPY ${VLC_COPY}/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)



# Copying Python Data
if(NOT DEFINED PYTHON_LIB_LOCATION)
    set (PYTHON_LIB_LOCATION ${Python_EXECUTABLE}/../Lib)
endif()

if(NOT DEFINED PYTHON_DLLS_LOCATION)
    set (PYTHON_DLLS_LOCATION ${Python_EXECUTABLE}/../DLLs)
endif()

message(STATUS "Copying Python assets...")
file(COPY ${Python_EXECUTABLE} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)
file(COPY ${PYTHON_LIB_LOCATION} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)

message(STATUS " -> Using native modules from ${PYTHON_DLLS_LOCATION}")
file(COPY ${PYTHON_DLLS_LOCATION} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)

message(STATUS "Installing Python/Pip dependencies...")
# Collecting Python dependencies
exec_program(
    ${Python_EXECUTABLE}
    ARGS -m pip install --no-warn-script-location --target=\"${CMAKE_CURRENT_BINARY_DIR}/bin/Lib/site-packages\" -r ${CMAKE_SOURCE_DIR}/requirements.txt 
)

# Copying Python source code. To avoid needing different commands depending 
# on the platform, we'll have the python interpreter that we loaded to copy the files.
add_custom_command(
    TARGET ${TARGET_NAME}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/bin/python
    ARGS ${CMAKE_SOURCE_DIR}/py_build.py ${CMAKE_CURRENT_BINARY_DIR}
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
