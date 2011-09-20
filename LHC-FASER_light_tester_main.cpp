/*
 * LHC-FASER_light_tester_main.cpp
 *
 *  Created on: 08 Jun 2011
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2011 Ben O'Leary
 *
 *      THIS (particular version of this) CODE IS INTENDED TO BE PRIVATE CODE,
 *      AND IS PROVIDED ONLY AS-IS TO THOSE REQUESTING IT.
 *      I am releasing it under the GNU GPL anyway, but I would prefer that it
 *      is only used by those obtaining it directly from me. If you would like
 *      to redistribute it, I would prefer that you just direct intended
 *      recipients to ask me for it. As long as they ask nicely, there should
 *      be no problem in getting it.  ;]
 *
 *      This file is part of "LHC-FASER light".
 *
 *      "LHC-FASER light" is free software: you can redistribute it and/or
 *      modify it under the terms of the GNU General Public License as
 *      published by the Free Software Foundation, either version 3 of the
 *      License, or (at your option) any later version.
 *
 *      "LHC-FASER light" is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with "LHC-FASER light".  If not, see
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

/* this program is to demonstrate the classes that form LHC-FASER_light, a
 * cut-down version of LHC-FASER that just provides total cross-sections for
 * colored sparticle production based on interpolating on a pre-calculated
 * grid. It does not combine this with the jets+MET acceptance grids (which are
 * not included anyway), nor with the lepton acceptance calculation (though
 * much of the necessary code is already in here), nor even with the BR
 * combinatorics.
 */


#include "CppSLHA/CppSLHA.hpp"
#include "LHC-FASER_input_handling_stuff.hpp"
#include "LHC-FASER_cross-section_stuff.hpp"


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
    CppSLHA::CppSLHA2 slhaData( argumentStrings[ 1 ] );
    slhaData.read_file();
    LHC_FASER::readier_for_new_point localReadier;
    LHC_FASER::input_handler inputs( &slhaData,
                                     slhaData.get_particle_spectrum(),
                                     "./grids",
                                     &localReadier );
    std::cout
    << std::endl
    << "path to grids = "
    << *(inputs.get_path_to_grids())
    << std::endl;

    inputs.set_using_NLO( false );
    LHC_FASER::cross_section_handler loCrossSectionHandler( &inputs );
    LHC_FASER::cross_section_table_set*
    loCrossSectionsAtSevenTev = loCrossSectionHandler.get_table_set( 7 );
    LHC_FASER::cross_section_table_set*
    loCrossSectionsAtFourteenTev = loCrossSectionHandler.get_table_set( 14 );
    std::vector< LHC_FASER::cross_section_table* >
    channelLoCrossSectionsAtSevenTev;
    std::vector< LHC_FASER::cross_section_table* >
    channelLoCrossSectionsAtFourteenTev;
    int numberOfChannels = 0;
    for( std::vector< LHC_FASER::signed_particle_shortcut_pair*
                                                              >::const_iterator
         channelIterator
         = inputs.get_sparticle_production_combinations()->begin();
         inputs.get_sparticle_production_combinations()->end()
         > channelIterator;
         ++channelIterator )
    {
      channelLoCrossSectionsAtSevenTev.push_back(
                    loCrossSectionsAtSevenTev->get_table( *channelIterator ) );
      channelLoCrossSectionsAtFourteenTev.push_back(
                 loCrossSectionsAtFourteenTev->get_table( *channelIterator ) );
      ++numberOfChannels;
    }

    inputs.set_using_NLO( true );
    LHC_FASER::cross_section_handler nloCrossSectionHandler( &inputs );
    LHC_FASER::cross_section_table_set*
    nloCrossSectionsAtSevenTev = nloCrossSectionHandler.get_table_set( 7 );
    LHC_FASER::cross_section_table_set*
    nloCrossSectionsAtFourteenTev = nloCrossSectionHandler.get_table_set( 14 );
    std::vector< LHC_FASER::cross_section_table* >
    channelNloCrossSectionsAtSevenTev;
    std::vector< LHC_FASER::cross_section_table* >
    channelNloCrossSectionsAtFourteenTev;
    for( std::vector< LHC_FASER::signed_particle_shortcut_pair*
                                                              >::const_iterator
         channelIterator
         = inputs.get_sparticle_production_combinations()->begin();
         inputs.get_sparticle_production_combinations()->end()
         > channelIterator;
         ++channelIterator )
    {
      channelNloCrossSectionsAtSevenTev.push_back(
                   nloCrossSectionsAtSevenTev->get_table( *channelIterator ) );
      channelNloCrossSectionsAtFourteenTev.push_back(
                nloCrossSectionsAtFourteenTev->get_table( *channelIterator ) );
    }


    channelLoCrossSectionsAtSevenTev.at( 0 )->get_pair();
    std::cout
    << "WARNING! THE FLAVOR BREAKDOWN OF THE CROSS-SECTIONS IS ONLY"
    << " APPROXIMATE! IT IS BASED ON DIVIDING UP THE FLAVOR-SUMMED RESULT FROM"
    << " PROSPINO 2.1, WHICH WAS CALCULATED USING MSTW2008 PARTON DISTRIBUTION"
    << " FUNCTIONS."
    << std::endl
    << "The cross-sections (in picobarns) are:"
    << std::endl
    << "-----------------------"
    << std::endl;
    for( int channelCounter = 0;
         numberOfChannels > channelCounter;
         ++channelCounter )
    {
      std::cout
      << *(channelLoCrossSectionsAtSevenTev.at( channelCounter
                      )->get_pair()->get_first_pointer()->get_name_or_antiname(
                            channelLoCrossSectionsAtSevenTev.at( channelCounter
                          )->get_pair()->first_is_not_antiparticle() ))
      << "+"
      << *(channelLoCrossSectionsAtSevenTev.at( channelCounter
                     )->get_pair()->get_second_pointer()->get_name_or_antiname(
                            channelLoCrossSectionsAtSevenTev.at( channelCounter
                                 )->get_pair()->second_is_not_antiparticle() ))
      << ":"
      << std::endl
      << " sigma_LO (07TeV) = "
      << channelLoCrossSectionsAtSevenTev.at( channelCounter )->get_value()
      << ", sigma_NLO (07TeV) = "
      << channelNloCrossSectionsAtSevenTev.at( channelCounter )->get_value()
      << " (K-factor = "
      << ( channelNloCrossSectionsAtSevenTev.at( channelCounter )->get_value()
           / channelLoCrossSectionsAtSevenTev.at( channelCounter
                                                               )->get_value() )
      << ")"
      << std::endl
      << " sigma_LO (14TeV) = "
      << channelLoCrossSectionsAtFourteenTev.at( channelCounter )->get_value()
      << ", sigma_NLO (14TeV) = "
      << channelNloCrossSectionsAtFourteenTev.at( channelCounter )->get_value()
      << " (K-factor = "
      << ( channelNloCrossSectionsAtFourteenTev.at( channelCounter
                                                                 )->get_value()
           / channelLoCrossSectionsAtFourteenTev.at( channelCounter
                                                               )->get_value() )
      << ")"
      << std::endl
      << std::endl;
    }

  }

  return EXIT_SUCCESS;
}
