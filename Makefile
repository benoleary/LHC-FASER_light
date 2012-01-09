#
# Example Makefile.
#

SHELL = /bin/sh

CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=LHC-FASER_light_tester_main.cpp \
 LHC-FASER_base_lepton_distribution_stuff.cpp \
 LHC-FASER_cross-section_stuff.cpp \
 LHC-FASER_global_stuff.cpp \
 LHC-FASER_input_handling_stuff.cpp \
 LHC-FASER_light.cpp \
 LHC-FASER_sparticle_decay_stuff.cpp \
 CppSLHA/CppSLHA_BLOCK.cpp \
 CppSLHA/CppSLHA_EW_scale_spectrum.cpp \
 CppSLHA/CppSLHA_file_reading_stuff.cpp \
 CppSLHA/CppSLHA_global_stuff.cpp \
 CppSLHA/CppSLHA_particle_data.cpp \
 CppSLHA/CppSLHA_PDG_codes_and_data.cpp \
 CppSLHA/CppSLHA_waiting_on_subprocess_executor.cpp \
 CppSLHA/CppSLHA.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=LHC-FASER_Light.exe

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o $(EXECUTABLE)

