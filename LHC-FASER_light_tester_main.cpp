/*
 * LHC-FASER_light_tester_main.cpp
 *
 *  Created on: 08 Jun 2011
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
 */


#include "LHC-FASER_light.hpp"


// the main program:

int main( int argumentCount,
          char* argumentStrings[] )
{
  if( 3 != argumentCount )
  // if the input was definitely wrong...
  {
    std::cout
    << std::endl
    << "error! this program requires 2 strings as its arguments: the names of"
    << " 2 SLHA-format files providing the spectra.";
    std::cout << std::endl;  // let the user know the format.
  }
  else  // otherwise, do what is supposed to be done.
  {
    std::string firstSlhaFileName( argumentStrings[ 1 ] );
    // I could just give argumentStrings[ 1 ] as the argument for
    // the exampleLhcFaserLight constructor, but this is to make things clear.
    std::string secondSlhaFileName( argumentStrings[ 2 ] );
    LHC_FASER::lhcFaserLight exampleLhcFaserLight( firstSlhaFileName );
    exampleLhcFaserLight.setVerbosity( true );
    // this sets exampleLhcFaserLight to print warnings if values outside the
    // grids are requested.

    std::cout
    << std::endl
    << "demonstration of get[Lo/Nlo][Seven/Fourteen]TevCrossSection():"
    << std::endl
    << "LO, 7 TeV, gluino ( " << CppSLHA::PDG_code::gluino << " ) + gluino ( "
    << CppSLHA::PDG_code::gluino << " ) = "
    << exampleLhcFaserLight.getLoSevenTevCrossSection(
                                                     CppSLHA::PDG_code::gluino,
                                                    CppSLHA::PDG_code::gluino )
    << " pb";
    // the PDG particle code for the gluino is 1000021.
    // CppSLHA::PDG_code::gluino is a defined static constant int, and I use it
    // because it makes for much more readable code. However, the next function
    // call uses 1000021, as an example.
    std::cout
    << std::endl
    << "NLO, 7 TeV, gluino ( " << 1000021 << " ) + gluino ( "
    << 1000021 << " ) = "
    << exampleLhcFaserLight.getNloSevenTevCrossSection( 1000021,
                                                        1000021 )
    << " pb";
    std::cout
    << std::endl
    << "LO, 14 TeV, gluino ( " << CppSLHA::PDG_code::gluino << " ) + gluino ( "
    << CppSLHA::PDG_code::gluino << " ) = "
    << exampleLhcFaserLight.getLoFourteenTevCrossSection(
                                                     CppSLHA::PDG_code::gluino,
                                                    CppSLHA::PDG_code::gluino )
    << " pb";
    std::cout
    << std::endl
    << "NLO, 14 TeV, gluino ( " << CppSLHA::PDG_code::gluino << " ) + gluino ( "
    << CppSLHA::PDG_code::gluino << " ) = "
    << exampleLhcFaserLight.getNloFourteenTevCrossSection(
                                                     CppSLHA::PDG_code::gluino,
                                                    CppSLHA::PDG_code::gluino )
    << " pb";
    std::cout
    << std::endl
    << "NLO, 7 TeV, gluino ( " << CppSLHA::PDG_code::gluino << " ) + gluino ( "
    << CppSLHA::PDG_code::gluino << " ) again = "
    << exampleLhcFaserLight.getNloSevenTevCrossSection(
                                                     CppSLHA::PDG_code::gluino,
                                                    CppSLHA::PDG_code::gluino )
    << " pb";
    std::cout
    << std::endl
    << "NLO, 7 TeV, gluino ( " << CppSLHA::PDG_code::gluino << " ) + sdownL ( "
    << CppSLHA::PDG_code::sdown_L << " ) = "
    << exampleLhcFaserLight.getNloSevenTevCrossSection(
                                                     CppSLHA::PDG_code::gluino,
                                                   CppSLHA::PDG_code::sdown_L )
    << " pb";
    std::cout
    << std::endl
    << "NLO, 7 TeV, sdownL ( " << CppSLHA::PDG_code::sdown_L
    << " ) + gluino ( " << CppSLHA::PDG_code::gluino << " ) = "
    << exampleLhcFaserLight.getNloSevenTevCrossSection(
                                                    CppSLHA::PDG_code::sdown_L,
                                                    CppSLHA::PDG_code::gluino )
    << " pb";
    std::cout
    << std::endl
    << "NLO, 7 TeV, sdownL ( " << CppSLHA::PDG_code::sdown_L
    << " ) + scharmL ( " << CppSLHA::PDG_code::scharm_L << " ) = "
    << exampleLhcFaserLight.getNloSevenTevCrossSection(
                                                    CppSLHA::PDG_code::sdown_L,
                                                  CppSLHA::PDG_code::scharm_L )
    << " pb";
    std::cout
    << std::endl
    << "NLO, 7 TeV, sdownL ( " << CppSLHA::PDG_code::sdown_L
    << " ) + sdownL ( " << CppSLHA::PDG_code::sdown_L << " ) = "
    << exampleLhcFaserLight.getNloSevenTevCrossSection(
                                                    CppSLHA::PDG_code::sdown_L,
                                                   CppSLHA::PDG_code::sdown_L )
    << " pb";
    std::cout
    << std::endl
    << "NLO, 7 TeV, sdownL ( " << CppSLHA::PDG_code::sdown_L
    << " ) + antisdownL ( " << -CppSLHA::PDG_code::sdown_L << " ) = "
    << exampleLhcFaserLight.getNloSevenTevCrossSection(
                                                    CppSLHA::PDG_code::sdown_L,
                                                  -CppSLHA::PDG_code::sdown_L )
    << " pb";
    std::cout
    << std::endl
    << "NLO, 7 TeV, sdownL ( " << CppSLHA::PDG_code::sdown_L
    << " ) + photon ( " << CppSLHA::PDG_code::photon << " ) = "
    << exampleLhcFaserLight.getNloSevenTevCrossSection(
                                                    CppSLHA::PDG_code::sdown_L,
                                                    CppSLHA::PDG_code::photon )
    << " pb";
    std::cout
    << std::endl
    << "NLO, 7 TeV, gluino ( " << CppSLHA::PDG_code::gluino << " ) + gluino ( "
    << CppSLHA::PDG_code::gluino << " ) again = "
    << exampleLhcFaserLight.getNloSevenTevCrossSection(
                                                     CppSLHA::PDG_code::gluino,
                                                    CppSLHA::PDG_code::gluino )
    << " pb";
    std::cout
    << std::endl
    << "sum of NLO cross-sections at 7 TeV = "
    << exampleLhcFaserLight.getSumOfNloCrossSectionsAtSevenTeV()
    << std::endl
    << "sum of NLO cross-sections at 14 TeV = "
    << exampleLhcFaserLight.getSumOfNloCrossSectionsAtFourteenTeV()
    << std::endl;
    std::cout
    << std::endl
    << std::endl;
    std::cout << *(exampleLhcFaserLight.getExampleOutput());
    std::cout
    << std::endl
    << std::endl;

    exampleLhcFaserLight.updateForNewSlhaFile( secondSlhaFileName );
    std::cout
    << std::endl
    << "now subsequent cross-sections will use the spectrum from "
    << secondSlhaFileName
    << std::endl
    << "NLO, 7 TeV, gluino ( " << CppSLHA::PDG_code::gluino << " ) + gluino ( "
    << CppSLHA::PDG_code::gluino << " ) = "
    << exampleLhcFaserLight.getNloSevenTevCrossSection(
                                                     CppSLHA::PDG_code::gluino,
                                                    CppSLHA::PDG_code::gluino )
    << " pb";
    std::cout
    << std::endl
    << std::endl
    << *(exampleLhcFaserLight.getExampleOutput());
    std::cout
    << std::endl
    << std::endl;
  }

  return EXIT_SUCCESS;

}
