/*
 * README.txt
 *
 *  Created on: 20 Sep 2011
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2011 Ben O'Leary
 *
 *      This file is part of "LHC-FASER Light".
 *      "LHC-FASER Light" is publically available from its GitHub repository:
 *      https://github.com/benoleary/LHC-FASER_light
 *
 *      "LHC-FASER Light" is free software: you can redistribute it and/or
 *      modify it under the terms of the GNU General Public License as
 *      published by the Free Software Foundation, either version 3 of the
 *      License, or (at your option) any later version.
 *
 *      "LHC-FASER Light" is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with "LHC-FASER Light".  If not, see
 *      <http://www.gnu.org/licenses/>.
 *
 *      The GNU General Public License should be in GNU_public_license.txt
 *      the files of "LHC-FASER Light" are:
 *      LHC-FASER_base_lepton_distribution_stuff.hpp
 *      LHC-FASER_base_lepton_distribution_stuff.cpp
 *      LHC-FASER_cross-section_stuff.hpp
 *      LHC-FASER_cross-section_stuff.cpp
 *      LHC-FASER_global_stuff.hpp
 *      LHC-FASER_global_stuff.cpp
 *      LHC-FASER_input_handling_stuff.hpp
 *      LHC-FASER_input_handling_stuff.cpp
 *      LHC-FASER_light.hpp
 *      LHC-FASER_light.cpp
 *      LHC-FASER_light_tester_main.cpp
 *      LHC-FASER_sparticle_decay_stuff.hpp
 *      LHC-FASER_sparticle_decay_stuff.cpp
 *      LHC-FASER_template_classes.cpp
 *      Makefile
 *      README.txt
 *      and the CppSLHA library, which is released under its own GNU GPL.
 *      (2 example spectrum files in SLHA format for SPS1a is included,
 *      SPS1a_spectrum.txt & SPS2_spectrum.txt, which were created with
 *      SPheno.)
 */

/* This program is to demonstrate the classes that form LHC-FASER Light, a
 * cut-down version of LHC-FASER that just provides total cross-sections for
 * colored sparticle production based on interpolating on a pre-calculated
 * grid. It does not combine this with the jets+MET acceptance grids (which are
 * not included anyway), nor with the lepton acceptance calculation (though
 * much of the necessary code is already in here), nor even with the BR
 * combinatorics.
 * 
 *
 * HOW TO USE:
 *
 * 1) How to use the standalone executable:
 *
 * Run make, and if that doesn't work, ask a colleague how to compile C++ code.
 * Most likely, the following should work:
 * g++ -o LHC-FASER_Light.exe *.cpp ./CppSHLA/*.cpp
 * Now you should have an executable file called LHC-FASER_Light.exe. If your
 * spectrum file is called exampleSpectrum.txt, you can run
 * ./LHC-FASER_Light.exe exampleSpectrum.txt
 * and you should get a wall of text with the various cross-sections. Feel free
 * to modify the output printing statements in LHC-FASER_light_tester_main.cpp
 * to better suit your needs, if for example you want to have the output in a
 * certain format to be read in by another program. In this case, however, it'd
 * be best to have LHC-FASER_Light.exe open & write a separate output file,
 * though this requires some knowledge of C++. I am usually happy to respond to
 * emails (address above), and may even write a custom executable that will
 * write the output in a requested format if I am asked nicely.
 *
 * 
 * 2) How to use as a class for a C++ program:
 * 
 * Well, remember to #include LHC-FASER_light.hpp and to include all the source
 * files (.cpp) that come with it (may be easiest to have
 * g++ ./LHC-FASER_light/*.cpp ./LHC-FASER_light/CppSLHA/*.cpp which should do
 * the trick, remembering to remove or rename LHC-FASER_light_tester_main.cpp
 * first).
 * Then it's just a matter of creating an instance of the lhcFaserLight class,
 * as on line 79 of LHC-FASER_light_tester_main.cpp, and using the public
 * functions getLoSevenTevCrossSection( int, int ),
 * getNloSevenTevCrossSection( int, int ),
 * getLoFourteenTevCrossSection( int, int ), &
 * getLoFourteenTevCrossSection( int, int ), where the argument ints are the
 * PDG codes for the required sparticles. This is demonstrated in the rest of
 * the file, along with how to make the lhcFaserLight object use a spectrum
 * from a different file, with updateForNewSlhaFile( std::string ), as shown on
 * line 202 of the LHC-FASER_light_tester_main.cpp file. If the file name has
 * not changed, but the file has been overwritten with new data,
 * updateForNewSlhaFile() can be used with no arguments.
 */