cmake_minimum_required(VERSION 3.24)

project(sm0k34P1 VERSION 4.1.3)

include(KoalaBox/cmake/KoalaBox.cmake)
add_subdirectory(KoalaBox)
add_subdirectory(tools)

set(sm0k3_4P1_STATIC_SOURCES
    static/sm0k3_4P1/interfaces/steam_apps.hpp
    static/sm0k3_4P1/interfaces/steam_apps.cpp
    static/sm0k3_4P1/interfaces/steam_http.hpp
    static/sm0k3_4P1/interfaces/steam_http.cpp
    static/sm0k3_4P1/interfaces/steam_inventory.hpp
    static/sm0k3_4P1/interfaces/steam_inventory.cpp
    static/sm0k3_4P1/interfaces/steam_user.hpp
    static/sm0k3_4P1/interfaces/steam_user.cpp
    static/sm0k3_4P1/api.hpp
    static/sm0k3_4P1/api.cpp
    static/sm0k3_4P1/cache.hpp
    static/sm0k3_4P1/cache.cpp
    static/sm0k3_4P1/config.hpp
    static/sm0k3_4P1/config.cpp
    static/sm0k3_4P1/types.hpp
    static/sm0k3_4P1/types.cpp
    static/sm0k3_4P1/steamclient/steamclient.hpp
)

if(IS_LINUX)
    set(GENERATED_SOURCES_DIR src/generated/${BITNESS})
    file(MAKE_DIRECTORY ${GENERATED_SOURCES_DIR})
    set(GENERATED_SOURCES
        ${GENERATED_SOURCES_DIR}/proxy_exports.hpp
        ${GENERATED_SOURCES_DIR}/proxy_exports.cpp
    )

    foreach(SRC IN LISTS GENERATED_SOURCES)
        file(TOUCH ${SRC})
    endforeach()
endif()

set(sm0k3_4P1_SOURCES
    ${sm0k3_4P1_STATIC_SOURCES}
    ${GENERATED_SOURCES}
    src/sm0k3_4P1/sm0k3_4P1.cpp
    src/sm0k3_4P1/sm0k3_4P1.hpp
    src/steam_api/virtuals/isteamapps.cpp
    src/steam_api/virtuals/isteamclient.cpp
    src/steam_api/virtuals/isteamgameserver.cpp
    src/steam_api/virtuals/isteamhttp.cpp
    src/steam_api/virtuals/isteaminventory.cpp
    src/steam_api/virtuals/isteamuser.cpp
    src/steam_api/virtuals/steam_api_virtuals.hpp
    src/steam_api/steam_client.hpp
    src/steam_api/steam_client.cpp
    src/steam_api/steam_interfaces.cpp
    src/steam_api/steam_interfaces.hpp
    src/steamclient/steamclient.cpp
)

if(WIN32)
    set_32_and_64(STEAM_API_MODULE steam_api)
    set_32_and_64(STEAMCLIENT_DLL steamclient)

    list(APPEND sm0k3_4P1_SOURCES src/main_win.cpp)
else()
    set(STEAM_API_MODULE libsteam_api)
    set(STEAMCLIENT_DLL steamclient)

    list(APPEND sm0k3_4P1_SOURCES src/main_linux.cpp)
endif()
set_32_and_64(sm0k3_4P1_FILENAME sm0k3_4P132 sm0k3_4P164)

configure_build_config(extra_build_config)

### sm0k34P1 interface

add_library(sm0k34P1_common INTERFACE)
add_library(sm0k34P1::common ALIAS sm0k34P1_common)

target_include_directories(sm0k34P1_common INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/static>"
)
target_link_libraries(sm0k34P1_common INTERFACE KoalaBox $<TARGET_OBJECTS:KoalaBox>)

### Static sm0k34P1

add_library(sm0k34P1_static STATIC ${sm0k3_4P1_STATIC_SOURCES})
add_library(sm0k34P1::static ALIAS sm0k34P1_static)

target_link_libraries(sm0k34P1_static PUBLIC sm0k34P1::common)

### Shared sm0k34P1

add_library(sm0k34P1 SHARED ${sm0k3_4P1_SOURCES})
target_link_libraries(sm0k34P1 PUBLIC sm0k34P1::common)
set_target_properties(sm0k34P1 PROPERTIES OUTPUT_NAME ${sm0k3_4P1_FILENAME})
configure_include_directories()

## https://github.com/batterycenter/embed
target_compile_definitions(sm0k34P1 PUBLIC B_PRODUCTION_MODE)
CPMAddPackage(
    URI "gh:batterycenter/embed@1.2.19"
    OPTIONS "B_PRODUCTION_MODE ON"
)
b_embed(sm0k34P1 "res/interface_lookup.json")

if(WIN32)
    configure_version_resource(
        TARGET sm0k34P1
        FILE_DESC "Steamworks DLC unlocker"
        ORIG_NAME ${sm0k3_4P1_FILENAME}
    )
    configure_linker_exports(
        TARGET sm0k34P1
        HEADER_NAME "linker_exports_for_steam_api.h"
        FORWARDED_DLL_NAME "${STEAM_API_MODULE}_o"
        LIB_FILES_GLOB "${CMAKE_CURRENT_SOURCE_DIR}/res/steamworks/*/binaries/${STEAM_API_MODULE}.dll"
        SOURCES_INPUT_PATH ""
    )

    set(HEADER_CONTENT "#pragma once\n\n")

    foreach(WIN_DLL version winhttp winmm)
        set(HEADER_NAME "linker_exports_for_${WIN_DLL}.h")
        configure_linker_exports(
            TARGET sm0k34P1
            HEADER_NAME "${HEADER_NAME}"
            FORWARDED_DLL_NAME "C:/Windows/System32/${WIN_DLL}.dll"
            LIB_FILES_GLOB "C:/Windows/System32/${WIN_DLL}.dll"
            SOURCES_INPUT_PATH ""
        )

        set(HEADER_CONTENT "${HEADER_CONTENT}#include <${HEADER_NAME}>\n")
    endforeach()

    file(GENERATE
        OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/generated/linker_exports_for_windows_dlls.h"
        CONTENT "${HEADER_CONTENT}"
    )

    # Ignore linker warnings regarding COM-related private exports
    set_target_properties(sm0k34P1 PROPERTIES LINK_FLAGS "/ignore:4104")
endif()
