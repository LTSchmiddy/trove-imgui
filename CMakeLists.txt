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
# find_package(Boost 1.45.0 COMPONENTS filesystem) 


# add_executable(${TARGET_NAME} "./src/cpp/sdl_opengl_player.cpp")
add_executable(${TARGET_NAME})
add_subdirectory("./src/cpp")

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

# Adding Python
find_package(Python3 COMPONENTS Development REQUIRED)
target_link_libraries(${TARGET_NAME} PRIVATE Python3::Python)

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

    message(STATUS "Using VLC debug assets...")
endif()

file(COPY ${VLC_COPY}/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})



# add_executable(r_test "./src/cpp/sdl_opengl_player.cpp")
# target_link_libraries(r_test PRIVATE SDL2::SDL2 SDL2::SDL2main)
# target_link_libraries(r_test PRIVATE SDL2::SDL2_image)
# target_link_libraries(r_test PRIVATE SDL2::SDL2_net)
# target_link_libraries(r_test PRIVATE SDL2::SDL2_ttf)
# target_link_libraries(r_test PRIVATE imgui::imgui)
# target_link_libraries(r_test PRIVATE GLEW::GLEW)
# target_link_libraries(r_test PRIVATE Python3::Python)
# target_link_libraries(r_test PRIVATE ${LIBVLC_LIB})
# set_target_properties(r_test
#     PROPERTIES
#     ARCHIVE_OUTPUT_DIRECTORY "./arc/"
#     LIBRARY_OUTPUT_DIRECTORY "./lib/"
#     RUNTIME_OUTPUT_DIRECTORY "./bin/"
# )