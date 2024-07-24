# ============================================================
# Boeing 737-800 / 727-200F Instrument Simulator - Makefile
# For MinGW-w64 GCC (Red Panda C++ compatible)
# ============================================================

CPP      = g++.exe
CC       = gcc.exe

# ============================================================
# Paths - adjust these to your environment
# ============================================================
EGE_ROOT  = ../编译所需文件/新版本的ege库文件
CURL_ROOT = D:/cURL/curl-8.8.0_2-win64-mingw

# ============================================================
# Compiler & Linker Flags
# ============================================================
CXXFLAGS = -I"$(EGE_ROOT)/include" -I"$(CURL_ROOT)/include" -O2 -pipe -finput-charset=UTF-8 -fexec-charset=gbk
CFLAGS   = -I"$(EGE_ROOT)/include" -O2 -pipe -finput-charset=UTF-8 -fexec-charset=gbk
LIBS     = -L"$(EGE_ROOT)" -L"$(CURL_ROOT)/lib" -lgraphics64 -lws2_32 -mwindows \
           -lgraphics -luuid -lmsimg32 -lgdi32 -limm32 -lole32 -loleaut32 -lwinmm -lgdiplus \
           $(CURL_ROOT)/lib/libcurl.a $(CURL_ROOT)/lib/libssl.a $(CURL_ROOT)/lib/libcrypto.a \
           $(CURL_ROOT)/lib/libz.a $(CURL_ROOT)/lib/libssh2.a $(CURL_ROOT)/lib/libnghttp2.a \
           $(CURL_ROOT)/lib/libbrotlidec.a $(CURL_ROOT)/lib/libbrotlicommon.a \
           $(CURL_ROOT)/lib/libpsl.a $(CURL_ROOT)/lib/libzstd.a -static

LDFLAGS  = -mwindows -static

# ============================================================
# Main Application Object Files
# ============================================================
MAIN_OBJS = \
	src/core/main.o \
	src/core/G_variable.o \
	src/communication/DataReceive.o \
	src/communication/DataReceive2.o \
	src/communication/MapReceive.o \
	src/communication/xplaneConnect.o \
	src/instruments/mechanical/DrawAI.o \
	src/instruments/mechanical/DrawAirspeed.o \
	src/instruments/mechanical/DrawAlt.o \
	src/instruments/mechanical/DrawCompass.o \
	src/instruments/mechanical/DrawRMI.o \
	src/instruments/mechanical/DrawRCDI.o \
	src/instruments/pfd/DrawPFD.o \
	src/instruments/standby/DrawPFDStandby.o \
	src/instruments/standby/DrawChronometer.o \
	src/instruments/nd/DrawND.o \
	src/instruments/nd/DrawNDInfo.o \
	src/instruments/eicas/DrawEICAS.o \
	src/instruments/fmc/FMCmain.o \
	src/instruments/fmc/FMCmain_2.o \
	src/instruments/fmc/FMCviewIndex1.o \
	src/instruments/fmc/FMCviewIndex2.o \
	src/instruments/fmc/FMCviewIndex3.o \
	src/instruments/fmc/FMCviewIndex4.o \
	src/instruments/fmc/FMCviewIndex5.o \
	src/instruments/fmc/FMCviewIndex6.o \
	src/instruments/fmc/FMCviewIndex7.o \
	src/instruments/fmc/FMCviewIndex8.o \
	src/instruments/fmc/FMCviewIndex9.o \
	src/panels/DrawPanels.o \
	src/panels/DrawAutoControl.o \
	src/panels/DrawEHISControl.o \
	src/panels/DrawLightControl.o \
	src/panels/DrawBackground.o \
	src/panels/DrawSteeringWheel.o \
	src/display/ShowPFD.o \
	src/display/ShowND.o \
	src/display/ShowEICAS.o \
	src/display/ShowEICAS2.o \
	src/display/ShowFMC.o \
	src/display/ShowMap.o \
	src/utility/ReadFiles.o \
	src/utility/KeyboardControl.o \
	src/utility/NewWindows.o \
	src/external/DrawFrame.o \
	src/external/DrawLight.o \
	src/external/DrawScrew.o

# ============================================================
# Targets
# ============================================================
.PHONY: all clean main pfd nd mfd1 mfd2 fmc map

all: main pfd nd mfd1 mfd2 fmc map

main: B737_800_Simulator.exe

pfd: subprocess/PFD/PFD.exe

nd: subprocess/ND/ND.exe

mfd1: subprocess/MFD1/MFD1.exe

mfd2: subprocess/MFD2/MFD2.exe

fmc: subprocess/FMC/FMC.exe

map: subprocess/Map/MapTest.exe

# ============================================================
# Main Application
# ============================================================
B737_800_Simulator.exe: $(MAIN_OBJS)
	$(CPP) $(MAIN_OBJS) -o $@ $(LIBS)

# ============================================================
# Subprocess: PFD
# ============================================================
subprocess/PFD/PFD.exe: subprocess/PFD/main.o subprocess/PFD/DrawFrame.o
	$(CPP) $^ -o $@ -L"$(EGE_ROOT)" -lgraphics64 -lws2_32 -lgdi32 -lgdiplus $(LDFLAGS)

# ============================================================
# Subprocess: ND
# ============================================================
subprocess/ND/ND.exe: subprocess/ND/main.o subprocess/ND/DrawFrame.o
	$(CPP) $^ -o $@ -L"$(EGE_ROOT)" -lgraphics64 -lws2_32 -lgdi32 -lgdiplus $(LDFLAGS)

# ============================================================
# Subprocess: MFD1 (EICAS)
# ============================================================
subprocess/MFD1/MFD1.exe: subprocess/MFD1/main.o subprocess/MFD1/DrawFrame.o
	$(CPP) $^ -o $@ -L"$(EGE_ROOT)" -lgraphics64 -lws2_32 -lgdi32 -lgdiplus $(LDFLAGS)

# ============================================================
# Subprocess: MFD2 (EICAS2)
# ============================================================
subprocess/MFD2/MFD2.exe: subprocess/MFD2/main.o
	$(CPP) $^ -o $@ -L"$(EGE_ROOT)" -lgraphics64 -lws2_32 -lgdi32 -lgdiplus $(LDFLAGS)

# ============================================================
# Subprocess: FMC
# ============================================================
FMC_OBJS = subprocess/FMC/main.o \
	subprocess/FMC/FMCviewIndex1.o subprocess/FMC/FMCviewIndex2.o \
	subprocess/FMC/FMCviewIndex3.o subprocess/FMC/FMCviewIndex4.o \
	subprocess/FMC/FMCviewIndex5.o subprocess/FMC/FMCviewIndex6.o \
	subprocess/FMC/FMCviewIndex7.o subprocess/FMC/FMCviewIndex8.o \
	subprocess/FMC/FMCviewIndex9.o

subprocess/FMC/FMC.exe: $(FMC_OBJS)
	$(CPP) $^ -o $@ -L"$(EGE_ROOT)" -lgraphics64 -lws2_32 -lgdi32 -lgdiplus $(LDFLAGS)

# ============================================================
# Subprocess: Map
# ============================================================
subprocess/Map/MapTest.exe: subprocess/Map/main.o
	$(CPP) $^ -o $@ -L"$(EGE_ROOT)" -lgraphics64 -lws2_32 -lgdi32 -lgdiplus $(LDFLAGS)

# ============================================================
# Pattern Rules
# ============================================================
src/core/%.o: src/core/%.cpp
	$(CPP) -c $< -o $@ $(CXXFLAGS)

src/communication/%.o: src/communication/%.cpp
	$(CPP) -c $< -o $@ $(CXXFLAGS)

src/communication/%.o: src/communication/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

src/instruments/mechanical/%.o: src/instruments/mechanical/%.cpp
	$(CPP) -c $< -o $@ $(CXXFLAGS)

src/instruments/pfd/%.o: src/instruments/pfd/%.cpp
	$(CPP) -c $< -o $@ $(CXXFLAGS)

src/instruments/nd/%.o: src/instruments/nd/%.cpp
	$(CPP) -c $< -o $@ $(CXXFLAGS)

src/instruments/eicas/%.o: src/instruments/eicas/%.cpp
	$(CPP) -c $< -o $@ $(CXXFLAGS)

src/instruments/fmc/%.o: src/instruments/fmc/%.cpp
	$(CPP) -c $< -o $@ $(CXXFLAGS)

src/instruments/standby/%.o: src/instruments/standby/%.cpp
	$(CPP) -c $< -o $@ $(CXXFLAGS)

src/panels/%.o: src/panels/%.cpp
	$(CPP) -c $< -o $@ $(CXXFLAGS)

src/display/%.o: src/display/%.cpp
	$(CPP) -c $< -o $@ $(CXXFLAGS)

src/utility/%.o: src/utility/%.cpp
	$(CPP) -c $< -o $@ $(CXXFLAGS)

src/external/%.o: src/external/%.cpp
	$(CPP) -c $< -o $@ $(CXXFLAGS)

subprocess/%.o: subprocess/%.cpp
	$(CPP) -c $< -o $@ $(CXXFLAGS)

# ============================================================
# Clean
# ============================================================
clean:
	-del /s /q *.o 2>NUL
	-del B737_800_Simulator.exe 2>NUL
	-del subprocess\PFD\PFD.exe 2>NUL
	-del subprocess\ND\ND.exe 2>NUL
	-del subprocess\MFD1\MFD1.exe 2>NUL
	-del subprocess\MFD2\MFD2.exe 2>NUL
	-del subprocess\FMC\FMC.exe 2>NUL
	-del subprocess\Map\MapTest.exe 2>NUL
