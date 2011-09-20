/*
 * README.txt
 *
 *  Created on: 20 Sep 2011
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2011 Ben O'Leary
 *
 *      This file is part of "LHC-FASER Light".
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
 *      the files of "LHC-FASER light" are:
 *      LHC-FASER_cross-section_stuff.hpp
 *      LHC-FASER_cross-section_stuff.cpp
 *      LHC-FASER_global_stuff.hpp
 *      LHC-FASER_global_stuff.cpp
 *      LHC-FASER_input_handling_stuff.hpp
 *      LHC-FASER_input_handling_stuff.cpp
 *      LHC-FASER_lepton_distributions.hpp
 *      LHC-FASER_lepton_distributions.cpp
 *      LHC-FASER_light_tester_main.cpp
 *      LHC-FASER_sparticle_decay_stuff.hpp
 *      LHC-FASER_sparticle_decay_stuff.cpp
 *      and the CppSLHA library, which is released under its own GNU GPL.
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
 * The code on lines 74 to 80 of LHC-FASER_light_tester_main.cpp reads in the
 * SLHA spectrum and sets up where to find the grids. This is a little more
 * lengthy than it could be, but in the full version of LHC-FASER, most of that
 * is taken care of automatically. I hope that what's going on is clear enough:
 * there's a CppSLHA::CppSLHA2 object which is given a name for a file to read
 * in; there's a LHC_FASER::readier_for_new_point object which is necessary for
 * resetting parts of the calculation (most of the code objects cache values,
 * and need a LHC_FASER::readier_for_new_point to tell them when to recalculate
 * their cached values); and there is a LHC_FASER::input_handler object which
 * further interprets the SLHA file that was read in by the CppSLHA::CppSLHA2
 * object.
 * (On line 87, whether NLO K-factors are used or not is set by
 * inputs.set_using_NLO(), but it is true by default.)
 * On lines 88 to 92, a LHC_FASER::cross_section_handler object is
 * created and pointers to a LHC_FASER::cross_section_table_set for 7 TeV and
 * for 14 TeV are obtained. These then provide LHC_FASER::cross_section_table
 * pointers for various colored sparticle production combinations. To get a
 * LHC_FASER::cross_section_table pointer for e.g. sdown_L + gluino, a
 * LHC_FASER::signed_particle_shortcut_pair needs to be created (a list of all
 * the signed_particle_shortcut_pairs is created automatically in the
 * input_handler, but I did not write code to get individual 
 * signed_particle_shortcut_pairs directly). This can be done e.g. with
 * LHC_FASER::signed_particle_shortcut_pair
 * sdownLPlusGluino( inputs.get_sdown_L(),
 *                   true,
 *                   inputs.get_gluino(),
 *                   true );
 * which constructs the relevant object.
 * LHC_FASER::cross_section_table_set::get_table( &sdownLPlusGluino ) now gives
 * the LHC_FASER::cross_section_table pointer which provides the cross-section
 * for sdown_L+gluino with LHC_FASER::cross_section_table::get_value().
 * 
 * That's about it. Oh, LHC_FASER::readier_for_new_point::ready_for_new_point()
 * should be used to clear the cached values and let the objects know that
 * LHC_FASER::cross_section_table::get_value() should calculate the value
 * afresh, and also CppSLHA::CppSLHA2::read_file() should be used to read in
 * new sparticle masses.
 */