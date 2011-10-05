/*
 * LHC-FASER_light_tester_main.cpp
 *
 *  Created on: 08 Jun 2011
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
 *      the files of "LHC-FASER Light" are:
 *      LHC-FASER_cross-section_stuff.hpp
 *      LHC-FASER_cross-section_stuff.cpp
 *      LHC-FASER_global_stuff.hpp
 *      LHC-FASER_global_stuff.cpp
 *      LHC-FASER_input_handling_stuff.hpp
 *      LHC-FASER_input_handling_stuff.cpp
 *      LHC-FASER_lepton_distributions.hpp
 *      LHC-FASER_lepton_distributions.cpp
 *      LHC-FASER_light.hpp
 *      LHC-FASER_light_tester_main.cpp
 *      LHC-FASER_sparticle_decay_stuff.hpp
 *      LHC-FASER_sparticle_decay_stuff.cpp
 *      Makefile
 *      README.txt
 *      and the CppSLHA library, which is released under its own GNU GPL.
 *      (An example spectrum file in SLHA format for SPS1a is included,
 *      SPS1a_spectrum.txt, which was created with SPheno.)
 */

/* This program is to demonstrate the classes that form LHC-FASER Light, a
 * cut-down version of LHC-FASER that just provides total cross-sections for
 * colored sparticle production based on interpolating on a pre-calculated
 * grid. It does not combine this with the jets+MET acceptance grids (which are
 * not included anyway), nor with the lepton acceptance calculation (though
 * much of the necessary code is already in here), nor even with the BR
 * combinatorics.
 */


#include "LHC-FASER_light.hpp"


// the main program:

int main( int argumentCount,
          char* argumentStrings[] )
{
  if( 2 != argumentCount )
  // if the input was definitely wrong...
  {
    std::cout
    << std::endl
    << "error! this program requires a string as its argument, as the name of"
    << " the SLHA-format file providing the spectrum.";
    std::cout << std::endl;  // let the user know the format.
  }
  else  // otherwise, do what is supposed to be done.
  {
    LHC_FASER::lhcFaserLight exampleLhcFaserLight( argumentStrings[ 1 ] );

    std::cout
    << std::endl
    << "demonstration of get[Lo/Nlo][Seven/Fourteen]TevCrossSection():"
    << std::endl
    << "LO, 7 TeV, gluino ( " << CppSLHA::PDG_code::gluino << " ) + gluino ( "
    << CppSLHA::PDG_code::gluino << " ) = "
    << exampleLhcFaserLight.getLoSevenTevCrossSection(
                                                     CppSLHA::PDG_code::gluino,
                                                   CppSLHA::PDG_code::gluino );
    std::cout
    << std::endl
    << "NLO, 7 TeV, gluino ( " << CppSLHA::PDG_code::gluino << " ) + gluino ( "
    << CppSLHA::PDG_code::gluino << " ) = "
    << exampleLhcFaserLight.getNloSevenTevCrossSection(
                                                     CppSLHA::PDG_code::gluino,
                                                   CppSLHA::PDG_code::gluino );
    std::cout
    << std::endl
    << "LO, 14 TeV, gluino ( " << CppSLHA::PDG_code::gluino << " ) + gluino ( "
    << CppSLHA::PDG_code::gluino << " ) = "
    << exampleLhcFaserLight.getLoFourteenTevCrossSection(
                                                     CppSLHA::PDG_code::gluino,
                                                   CppSLHA::PDG_code::gluino );
    std::cout
    << std::endl
    << "NLO, 14 TeV, gluino ( " << CppSLHA::PDG_code::gluino << " ) + gluino ( "
    << CppSLHA::PDG_code::gluino << " ) = "
    << exampleLhcFaserLight.getNloFourteenTevCrossSection(
                                                     CppSLHA::PDG_code::gluino,
                                                   CppSLHA::PDG_code::gluino );
    std::cout
    << std::endl
    << "NLO, 7 TeV, gluino ( " << CppSLHA::PDG_code::gluino << " ) + gluino ( "
    << CppSLHA::PDG_code::gluino << " ) again = "
    << exampleLhcFaserLight.getNloSevenTevCrossSection(
                                                     CppSLHA::PDG_code::gluino,
                                                   CppSLHA::PDG_code::gluino );
    std::cout
    << std::endl
    << "NLO, 7 TeV, gluino ( " << CppSLHA::PDG_code::gluino << " ) + sdownL ( "
    << CppSLHA::PDG_code::sdown_L << " ) = "
    << exampleLhcFaserLight.getNloSevenTevCrossSection(
                                                     CppSLHA::PDG_code::gluino,
                                                  CppSLHA::PDG_code::sdown_L );
    std::cout
    << std::endl
    << "NLO, 7 TeV, sdownL ( " << CppSLHA::PDG_code::sdown_L
    << " ) + gluino ( " << CppSLHA::PDG_code::gluino << " ) = "
    << exampleLhcFaserLight.getNloSevenTevCrossSection(
                                                    CppSLHA::PDG_code::sdown_L,
                                                   CppSLHA::PDG_code::gluino );
    std::cout
    << std::endl
    << "NLO, 7 TeV, sdownL ( " << CppSLHA::PDG_code::sdown_L
    << " ) + scharmL ( " << CppSLHA::PDG_code::scharm_L << " ) = "
    << exampleLhcFaserLight.getNloSevenTevCrossSection(
                                                    CppSLHA::PDG_code::sdown_L,
                                                 CppSLHA::PDG_code::scharm_L );
    std::cout
    << std::endl
    << "NLO, 7 TeV, sdownL ( " << CppSLHA::PDG_code::sdown_L
    << " ) + sdownL ( " << CppSLHA::PDG_code::sdown_L << " ) = "
    << exampleLhcFaserLight.getNloSevenTevCrossSection(
                                                    CppSLHA::PDG_code::sdown_L,
                                                  CppSLHA::PDG_code::sdown_L );
    std::cout
    << std::endl
    << "NLO, 7 TeV, sdownL ( " << CppSLHA::PDG_code::sdown_L
    << " ) + antisdownL ( " << -CppSLHA::PDG_code::sdown_L << " ) = "
    << exampleLhcFaserLight.getNloSevenTevCrossSection(
                                                    CppSLHA::PDG_code::sdown_L,
                                                 -CppSLHA::PDG_code::sdown_L );
    std::cout
    << std::endl
    << "NLO, 7 TeV, sdownL ( " << CppSLHA::PDG_code::sdown_L
    << " ) + photon ( " << CppSLHA::PDG_code::photon << " ) = "
    << exampleLhcFaserLight.getNloSevenTevCrossSection(
                                                    CppSLHA::PDG_code::sdown_L,
                                                   CppSLHA::PDG_code::photon );
    std::cout
    << std::endl
    << "NLO, 7 TeV, gluino ( " << CppSLHA::PDG_code::gluino << " ) + gluino ( "
    << CppSLHA::PDG_code::gluino << " ) again = "
    << exampleLhcFaserLight.getNloSevenTevCrossSection(
                                                     CppSLHA::PDG_code::gluino,
                                                   CppSLHA::PDG_code::gluino );
    std::cout
    << std::endl
    << std::endl;

    std::cout << *(exampleLhcFaserLight.getExampleOutput());
  }

  return EXIT_SUCCESS;

}
