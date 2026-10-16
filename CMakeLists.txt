cmake_minimum_required(VERSION 3.24)

# Central provider used by the remaining separated plugins.
# VERSION/AUTHOR are deliberately not forwarded to add_commonlibsse_plugin
# because CommonLibSSE-NG 3.6.0 has a parser bug on that argument path.
project(UniversalKinematics VERSION 1.0.0 LANGUAGES CXX)

set(headers
    src/PCH.h
    src/UniversalKinematics.h
    src/UniversalKinematicsAPI.h
)

set(sources
    src/main.cpp
    src/UniversalKinematics.cpp
    src/UniversalKinematicsAPI.cpp
)

find_package(CommonLibSSE CONFIG REQUIRED)

add_commonlibsse_plugin(${PROJECT_NAME}
    NAME "UniversalKinematics"
    USE_ADDRESS_LIBRARY
    SOURCES ${headers} ${sources}
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_precompile_headers(${PROJECT_NAME} PRIVATE src/PCH.h)
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_compile_definitions(${PROJECT_NAME} PRIVATE UNIVERSAL_KINEMATICS_PROVIDER=1)

# Optional deployment. Set SKYRIM_SKSE64_PLUGIN_DIR to Data/SKSE/Plugins.
if(DEFINED ENV{SKYRIM_SKSE64_PLUGIN_DIR})
    add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:${PROJECT_NAME}>"
            "$ENV{SKYRIM_SKSE64_PLUGIN_DIR}"
        VERBATIM
    )
endif()

