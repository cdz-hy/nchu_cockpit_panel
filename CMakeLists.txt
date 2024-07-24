cmake_minimum_required(VERSION 3.15)
project(B737_800_Instrument_Simulator LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

# ============================================================
# EGE Graphics Library (required)
# Set EGE_ROOT to the path containing include/ and lib/
# ============================================================
if(NOT DEFINED EGE_ROOT)
    set(EGE_ROOT "${CMAKE_SOURCE_DIR}/../编译所需文件/新版本的ege库文件" CACHE PATH "EGE library root")
endif()

# ============================================================
# cURL (required for MapReceive)
# Set CURL_ROOT to the cURL installation directory
# ============================================================
if(NOT DEFINED CURL_ROOT)
    set(CURL_ROOT "D:/cURL/curl-8.8.0_2-win64-mingw" CACHE PATH "cURL installation root")
endif()

# ============================================================
# Main Application Sources
# ============================================================
set(MAIN_SOURCES
    # Core
    src/core/main.cpp
    src/core/G_variable.cpp

    # Communication
    src/communication/DataReceive.cpp
    src/communication/DataReceive2.cpp
    src/communication/MapReceive.cpp
    src/communication/xplaneConnect.c

    # Instruments - Mechanical
    src/instruments/mechanical/DrawAI.cpp
    src/instruments/mechanical/DrawAirspeed.cpp
    src/instruments/mechanical/DrawAlt.cpp
    src/instruments/mechanical/DrawCompass.cpp
    src/instruments/mechanical/DrawRMI.cpp
    src/instruments/mechanical/DrawRCDI.cpp

    # Instruments - PFD
    src/instruments/pfd/DrawPFD.cpp

    # Instruments - Standby
    src/instruments/standby/DrawPFDStandby.cpp
    src/instruments/standby/DrawChronometer.cpp

    # Instruments - ND
    src/instruments/nd/DrawND.cpp
    src/instruments/nd/DrawNDInfo.cpp

    # Instruments - EICAS
    src/instruments/eicas/DrawEICAS.cpp

    # Instruments - FMC
    src/instruments/fmc/FMCmain.cpp
    src/instruments/fmc/FMCmain_2.cpp
    src/instruments/fmc/FMCviewIndex1.cpp
    src/instruments/fmc/FMCviewIndex2.cpp
    src/instruments/fmc/FMCviewIndex3.cpp
    src/instruments/fmc/FMCviewIndex4.cpp
    src/instruments/fmc/FMCviewIndex5.cpp
    src/instruments/fmc/FMCviewIndex6.cpp
    src/instruments/fmc/FMCviewIndex7.cpp
    src/instruments/fmc/FMCviewIndex8.cpp
    src/instruments/fmc/FMCviewIndex9.cpp

    # Panels
    src/panels/DrawPanels.cpp
    src/panels/DrawAutoControl.cpp
    src/panels/DrawEHISControl.cpp
    src/panels/DrawLightControl.cpp
    src/panels/DrawBackground.cpp
    src/panels/DrawSteeringWheel.cpp

    # Display (subprocess management)
    src/display/ShowPFD.cpp
    src/display/ShowND.cpp
    src/display/ShowEICAS.cpp
    src/display/ShowEICAS2.cpp
    src/display/ShowFMC.cpp
    src/display/ShowMap.cpp

    # Utility
    src/utility/ReadFiles.cpp
    src/utility/KeyboardControl.cpp
    src/utility/NewWindows.cpp

    # External
    src/external/DrawFrame.cpp
    src/external/DrawLight.cpp
    src/external/DrawScrew.cpp
)

# ============================================================
# Main Executable
# ============================================================
add_executable(${PROJECT_NAME} ${MAIN_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/src/communication
    ${CMAKE_SOURCE_DIR}/src/instruments/mechanical
    ${CMAKE_SOURCE_DIR}/src/instruments/pfd
    ${CMAKE_SOURCE_DIR}/src/instruments/nd
    ${CMAKE_SOURCE_DIR}/src/instruments/eicas
    ${CMAKE_SOURCE_DIR}/src/instruments/fmc
    ${CMAKE_SOURCE_DIR}/src/instruments/standby
    ${CMAKE_SOURCE_DIR}/src/panels
    ${CMAKE_SOURCE_DIR}/src/display
    ${CMAKE_SOURCE_DIR}/src/utility
    ${CMAKE_SOURCE_DIR}/src/external
    ${EGE_ROOT}/include
    ${CURL_ROOT}/include
)

target_link_directories(${PROJECT_NAME} PRIVATE
    ${EGE_ROOT}
    ${CURL_ROOT}/lib
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    graphics64
    ws2_32
    uuid
    msimg32
    gdi32
    imm32
    ole32
    oleaut32
    winmm
    gdiplus
    curl
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -O2
    -pipe
    -finput-charset=UTF-8
    -fexec-charset=gbk
)

target_link_options(${PROJECT_NAME} PRIVATE
    -mwindows
    -static
)

# ============================================================
# Subprocess Executables
# ============================================================

# PFD Subprocess
add_executable(PFD
    subprocess/PFD/main.cpp
    subprocess/PFD/DrawFrame.cpp
)
target_include_directories(PFD PRIVATE ${EGE_ROOT}/include)
target_link_directories(PFD PRIVATE ${EGE_ROOT})
target_link_libraries(PFD PRIVATE graphics64 ws2_32 gdi32 gdiplus)
target_compile_options(PFD PRIVATE -O2 -pipe -finput-charset=UTF-8 -fexec-charset=gbk)
target_link_options(PFD PRIVATE -mwindows -static)

# ND Subprocess
add_executable(ND
    subprocess/ND/main.cpp
    subprocess/ND/DrawFrame.cpp
)
target_include_directories(ND PRIVATE ${EGE_ROOT}/include)
target_link_directories(ND PRIVATE ${EGE_ROOT})
target_link_libraries(ND PRIVATE graphics64 ws2_32 gdi32 gdiplus)
target_compile_options(ND PRIVATE -O2 -pipe -finput-charset=UTF-8 -fexec-charset=gbk)
target_link_options(ND PRIVATE -mwindows -static)

# MFD1 (EICAS) Subprocess
add_executable(MFD1
    subprocess/MFD1/main.cpp
    subprocess/MFD1/DrawFrame.cpp
)
target_include_directories(MFD1 PRIVATE ${EGE_ROOT}/include)
target_link_directories(MFD1 PRIVATE ${EGE_ROOT})
target_link_libraries(MFD1 PRIVATE graphics64 ws2_32 gdi32 gdiplus)
target_compile_options(MFD1 PRIVATE -O2 -pipe -finput-charset=UTF-8 -fexec-charset=gbk)
target_link_options(MFD1 PRIVATE -mwindows -static)

# MFD2 (EICAS2) Subprocess
add_executable(MFD2
    subprocess/MFD2/main.cpp
)
target_include_directories(MFD2 PRIVATE ${EGE_ROOT}/include)
target_link_directories(MFD2 PRIVATE ${EGE_ROOT})
target_link_libraries(MFD2 PRIVATE graphics64 ws2_32 gdi32 gdiplus)
target_compile_options(MFD2 PRIVATE -O2 -pipe -finput-charset=UTF-8 -fexec-charset=gbk)
target_link_options(MFD2 PRIVATE -mwindows -static)

# FMC Subprocess
add_executable(FMC
    subprocess/FMC/main.cpp
    subprocess/FMC/FMCviewIndex1.cpp
    subprocess/FMC/FMCviewIndex2.cpp
    subprocess/FMC/FMCviewIndex3.cpp
    subprocess/FMC/FMCviewIndex4.cpp
    subprocess/FMC/FMCviewIndex5.cpp
    subprocess/FMC/FMCviewIndex6.cpp
    subprocess/FMC/FMCviewIndex7.cpp
    subprocess/FMC/FMCviewIndex8.cpp
    subprocess/FMC/FMCviewIndex9.cpp
)
target_include_directories(FMC PRIVATE ${EGE_ROOT}/include)
target_link_directories(FMC PRIVATE ${EGE_ROOT})
target_link_libraries(FMC PRIVATE graphics64 ws2_32 gdi32 gdiplus)
target_compile_options(FMC PRIVATE -O2 -pipe -finput-charset=UTF-8 -fexec-charset=gbk)
target_link_options(FMC PRIVATE -mwindows -static)

# Map Subprocess
add_executable(MapTest
    subprocess/Map/main.cpp
)
target_include_directories(MapTest PRIVATE ${EGE_ROOT}/include)
target_link_directories(MapTest PRIVATE ${EGE_ROOT})
target_link_libraries(MapTest PRIVATE graphics64 ws2_32 gdi32 gdiplus)
target_compile_options(MapTest PRIVATE -O2 -pipe -finput-charset=UTF-8 -fexec-charset=gbk)
target_link_options(MapTest PRIVATE -mwindows -static)
