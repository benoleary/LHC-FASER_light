#
# very basic Makefile.
#

SHELL = /bin/sh

# There is no default behaviour!
all:
	$(CXX) $(CXXFLAGS) ./*.cpp ./CppSLHA/*.cpp -o LHC-FASER_Light.exe &> compileoutput.txt

