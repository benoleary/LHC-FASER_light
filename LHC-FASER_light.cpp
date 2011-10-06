/*
 * LHC-FASER_light.cpp
 *
 *  Created on: Oct 5, 2011
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

#include "LHC-FASER_light.hpp"

namespace LHC_FASER
{
  lhcFaserLight::lhcFaserLight( std::string const slhaSpectrumFileName,
                                std::string const pathToGrids ) :
    slhaData( slhaSpectrumFileName )
  {
    loInput = new inputHandler( &slhaData,
                                slhaData.get_particle_spectrum(),
                                pathToGrids,
                                &localReadier );
    loInput->setUsingNloFlag( false );
    loCrossSectionHandler = new crossSectionHandler( loInput );
    nloInput = new inputHandler( &slhaData,
                                 slhaData.get_particle_spectrum(),
                                 pathToGrids,
                                 &localReadier );
    nloInput->setUsingNloFlag( true );
    nloCrossSectionHandler = new crossSectionHandler( nloInput );
    updateForNewSlhaFile();
    defaultBadProductionPair
    = new signedParticleShortcutPair( nloInput->getStopTwo(),
                                      true,
                                      nloInput->getStopTwo(),
                                      true );
  }

  lhcFaserLight::~lhcFaserLight()
  {
    delete loCrossSectionHandler;
    delete nloCrossSectionHandler;
    delete defaultBadProductionPair;
    delete loInput;
    delete nloInput;
  }


  std::string const*
  lhcFaserLight::getExampleOutput()
  {
    crossSectionTableSet*
    loCrossSectionsAtSevenTev( loCrossSectionHandler->getTableSet( 7 ) );
    crossSectionTableSet*
    loCrossSectionsAtFourteenTev( loCrossSectionHandler->getTableSet( 14 ) );
    std::vector< crossSectionTable* > channelLoCrossSectionsAtSevenTev;
    std::vector< crossSectionTable* > channelLoCrossSectionsAtFourteenTev;
    crossSectionTableSet*
    nloCrossSectionsAtSevenTev( nloCrossSectionHandler->getTableSet( 7 ) );
    crossSectionTableSet*
    nloCrossSectionsAtFourteenTev( nloCrossSectionHandler->getTableSet( 14 ) );
    std::vector< crossSectionTable* > channelNloCrossSectionsAtSevenTev;
    std::vector< crossSectionTable* > channelNloCrossSectionsAtFourteenTev;
    int numberOfChannels( 0 );
    for( std::vector< signedParticleShortcutPair* >::const_iterator
         channelIterator(
                      nloInput->getScoloredProductionCombinations()->begin() );
         nloInput->getScoloredProductionCombinations()->end()
         > channelIterator;
         ++channelIterator )
    {
      channelLoCrossSectionsAtSevenTev.push_back(
                     loCrossSectionsAtSevenTev->getTable( *channelIterator ) );
      channelLoCrossSectionsAtFourteenTev.push_back(
                  loCrossSectionsAtFourteenTev->getTable( *channelIterator ) );
      channelNloCrossSectionsAtSevenTev.push_back(
                    nloCrossSectionsAtSevenTev->getTable( *channelIterator ) );
      channelNloCrossSectionsAtFourteenTev.push_back(
                 nloCrossSectionsAtFourteenTev->getTable( *channelIterator ) );
      ++numberOfChannels;
    }
    channelLoCrossSectionsAtSevenTev.at( 0 )->getPair();
    std::stringstream stringBuilder;
    stringBuilder
    << "WARNING! THE FLAVOR BREAKDOWN OF THE CROSS-SECTIONS IS ONLY"
    << " APPROXIMATE! IT IS BASED ON DIVIDING UP THE FLAVOR-SUMMED RESULT FROM"
    << " PROSPINO 2.1, WHICH WAS CALCULATED USING MSTW2008 PARTON DISTRIBUTION"
    << " FUNCTIONS."
    << std::endl
    << "The cross-sections (in picobarns) are:"
    << std::endl
    << "-----------------------"
    << std::endl;
    for( int channelCounter( 0 );
         numberOfChannels > channelCounter;
         ++channelCounter )
    {
      stringBuilder
      << *(channelLoCrossSectionsAtSevenTev.at( channelCounter
                        )->getPair()->getFirstParticle()->get_name_or_antiname(
                            channelLoCrossSectionsAtSevenTev.at( channelCounter
                          )->getPair()->firstIsNotAntiparticle() ))
      << "+"
      << *(channelLoCrossSectionsAtSevenTev.at( channelCounter
                       )->getPair()->getSecondParticle()->get_name_or_antiname(
                            channelLoCrossSectionsAtSevenTev.at( channelCounter
                                 )->getPair()->secondIsNotAntiparticle() ))
      << ":"
      << std::endl
      << " sigma_LO (07TeV) = "
      << channelLoCrossSectionsAtSevenTev.at( channelCounter )->getValue()
      << ", sigma_NLO (07TeV) = "
      << channelNloCrossSectionsAtSevenTev.at( channelCounter )->getValue()
      << " (K-factor = "
      << ( channelNloCrossSectionsAtSevenTev.at( channelCounter )->getValue()
           / channelLoCrossSectionsAtSevenTev.at( channelCounter
                                                                )->getValue() )
      << ")"
      << std::endl
      << " sigma_LO (14TeV) = "
      << channelLoCrossSectionsAtFourteenTev.at( channelCounter )->getValue()
      << ", sigma_NLO (14TeV) = "
      << channelNloCrossSectionsAtFourteenTev.at( channelCounter )->getValue()
      << " (K-factor = "
      << ( channelNloCrossSectionsAtFourteenTev.at( channelCounter
                                                                  )->getValue()
           / channelLoCrossSectionsAtFourteenTev.at( channelCounter
                                                                )->getValue() )
      << ")"
      << std::endl
      << std::endl;
    }
    exampleOutput.assign( stringBuilder.str() );
    return &exampleOutput;
  }

  double
  lhcFaserLight::getCrossSection(
                                 crossSectionHandler* whichCrossSectionHandler,
                                  int const beamEnergy,
                                  int const firstSparticlePdgCode,
                                  int const secondSparticlePdgCode )
  {
    signedParticleShortcutPair* channelPair( defaultBadProductionPair );
    int firstComparisonPdgCode;
    int secondComparisonPdgCode;
    for( std::vector< signedParticleShortcutPair* >::const_iterator
         channelIterator(
                      nloInput->getScoloredProductionCombinations()->begin() );
         nloInput->getScoloredProductionCombinations()->end()
         > channelIterator;
         ++channelIterator )
    {
      firstComparisonPdgCode
      = (*channelIterator)->getFirstParticle()->get_PDG_code();
      if( !((*channelIterator)->firstIsNotAntiparticle()) )
      {
        firstComparisonPdgCode = -firstComparisonPdgCode;
      }
      secondComparisonPdgCode
      = (*channelIterator)->getSecondParticle()->get_PDG_code();
      if( !((*channelIterator)->secondIsNotAntiparticle()) )
      {
        secondComparisonPdgCode = -secondComparisonPdgCode;
      }
      if( ( ( firstSparticlePdgCode == firstComparisonPdgCode )
            &&
            ( secondSparticlePdgCode == secondComparisonPdgCode ) )
          ||
          ( ( firstSparticlePdgCode == secondComparisonPdgCode )
            &&
            ( secondSparticlePdgCode == firstComparisonPdgCode ) ) )
      {
        channelPair = *channelIterator;
        channelIterator = nloInput->getScoloredProductionCombinations()->end();
      }
    }
    return whichCrossSectionHandler->getTable( beamEnergy,
                                               channelPair )->getValue();
  }

}  // end of LHC_FASER namespace
