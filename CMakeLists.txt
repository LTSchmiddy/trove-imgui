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



# If you're using Boost:


# add_executable(${TARGET_NAME} "./src/cpp/sdl_opengl_player.cpp")
add_executable(${TARGET_NAME})
add_subdirectory("./src/cpp")

# Adding Python
find_package(Python 3.10 COMPONENTS Development Interpreter REQUIRED)
target_link_libraries(${TARGET_NAME} PRIVATE Python::Python Python::Module)


# Adding Boost
find_package(Boost 1.70.0 COMPONENTS filesystem REQUIRED)
target_link_libraries(${TARGET_NAME} PRIVATE Boost::filesystem)

# Once again, boost-python proves to be more trouble than it's worth.

# Apparently, the flag for boost using python debug has to be set AFTER the rest of boost is loaded.
# Otherwise, boost::filesystem can't load properly.
# if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
#     set(Boost_USE_DEBUG_PYTHON ON)
# endif()

# find_package(Boost 1.70.0 COMPONENTS filesystem python310 REQUIRED)
# target_link_libraries(${TARGET_NAME} PRIVATE Boost::filesystem  Boost::python310)

# find_package(Boost 1.70.0 COMPONENTS python310 REQUIRED)
# target_link_libraries(${TARGET_NAME} PRIVATE Boost::python310)

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

find_package(OpenGL COMPONENTS OpenGL REQUIRED)
message(STATUS ${OPENGL_FOUND})
target_link_libraries(${TARGET_NAME} PRIVATE OpenGL::GL)

# Adding GLEW
find_package(GLEW REQUIRED)
target_link_libraries(${TARGET_NAME} PRIVATE GLEW::GLEW)


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
message(STATUS "Copying Python assets...")
file(COPY ${Python_EXECUTABLE}/../ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
