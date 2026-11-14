cmake_minimum_required(VERSION 3.22)
project(dynamic_dash LANGUAGES CXX)

option(DYNAMIC_DASH_BUILD_COCOS "Build the Cocos2d-x Android game" OFF)

add_library(dynamic_dash SHARED
    src/dynamic_dash.cpp
    src/loading_screen.cpp
    src/prototype.cpp
)
target_include_directories(dynamic_dash PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(dynamic_dash PUBLIC cxx_std_17)
target_compile_options(dynamic_dash PRIVATE -Wall -Wextra -Wpedantic)

include(CTest)
if(BUILD_TESTING)
    add_executable(dynamic_dash_prototype_test tests/prototype_test.cpp)
    target_link_libraries(dynamic_dash_prototype_test PRIVATE dynamic_dash)
    add_test(NAME prototype_flow COMMAND dynamic_dash_prototype_test)
endif()

if(DYNAMIC_DASH_BUILD_COCOS)
    if(NOT ANDROID)
        message(FATAL_ERROR "The Cocos2d Android application must be configured with the Android NDK.")
    endif()
    set(COCOS2DX_ROOT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cocos2d")
    if(NOT EXISTS "${COCOS2DX_ROOT_PATH}/cocos/CMakeLists.txt")
        message(FATAL_ERROR "Cocos2d-x v4 source missing. Run scripts/setup-cocos2d.sh first.")
    endif()
    set(CMAKE_MODULE_PATH "${COCOS2DX_ROOT_PATH}/cmake/Modules/")
    include(CocosBuildSet)
    set(BUILD_LUA_LIBS OFF CACHE BOOL "" FORCE)
    set(BUILD_EDITOR_COCOSTUDIO OFF CACHE BOOL "" FORCE)
    set(BUILD_EDITOR_SPINE OFF CACHE BOOL "" FORCE)
    set(BUILD_EXTENSIONS OFF CACHE BOOL "" FORCE)
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)

    add_library(MyGame SHARED
        src/cocos/AppDelegate.cpp
        src/cocos/GameScenes.cpp
        android/app/jni/main.cpp
    )
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos/platform/android ${ENGINE_BINARY_PATH}/cocos/platform)
    target_include_directories(MyGame PRIVATE src/cocos ${COCOS2DX_ROOT_PATH}/cocos/audio/include)
    target_link_libraries(MyGame PRIVATE dynamic_dash cocos2d
        -Wl,--whole-archive cpp_android_spec -Wl,--no-whole-archive)
    setup_cocos_app_config(MyGame)
endif()
