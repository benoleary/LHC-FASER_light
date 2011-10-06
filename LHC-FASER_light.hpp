/*
 * LHC-FASER_light.hpp
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

#ifndef LHC_FASER_LIGHT_HPP_
#define LHC_FASER_LIGHT_HPP_

#include "CppSLHA/CppSLHA.hpp"
#include "LHC-FASER_input_handling_stuff.hpp"
#include "LHC-FASER_cross-section_stuff.hpp"

namespace LHC_FASER
{
  class lhcFaserLight
  {
  public:
    lhcFaserLight( std::string const slhaSpectrumFileName,
                   std::string const pathToGrids = "./NLO_grids" );
    ~lhcFaserLight();

    void
    setGridLocation( std::string pathToGrids );
    double
    getLoSevenTevCrossSection( int const firstSparticlePdgCode,
                               int const secondSparticlePdgCode );
    double
    getNloSevenTevCrossSection( int const firstSparticlePdgCode,
                                int const secondSparticlePdgCode );
    double
    getLoFourteenTevCrossSection( int const firstSparticlePdgCode,
                                  int const secondSparticlePdgCode );
    double
    getNloFourteenTevCrossSection( int const firstSparticlePdgCode,
                                   int const secondSparticlePdgCode );
    void
    updateForNewSlhaFile();
    void
    updateForNewSlhaFile( std::string const slhaSpectrumFile );
    std::string const*
    getExampleOutput();
    double
    getSumOfNloCrossSectionsAtSevenTeV();
    double
    getSumOfNloCrossSectionsAtFourteenTeV();

  protected:
    CppSLHA::CppSLHA2 slhaData;
    readierForNewPoint localReadier;
    inputHandler* loInput;
    inputHandler* nloInput;
    crossSectionHandler* loCrossSectionHandler;
    crossSectionHandler* nloCrossSectionHandler;
    std::string exampleOutput;
    signedParticleShortcutPair* defaultBadProductionPair;

    double
    getCrossSection( crossSectionHandler* whichCrossSectionHandler,
                     int const beamEnergy,
                     int const firstSparticlePdgCode,
                     int const secondSparticlePdgCode );
    double
    getSumOfNloCrossSections( int const beamEnergy );
  };





  // inline functions:


  inline double
  lhcFaserLight::getLoSevenTevCrossSection( int const firstSparticlePdgCode,
                                            int const secondSparticlePdgCode )
  {
    return getCrossSection( loCrossSectionHandler,
                            7,
                            firstSparticlePdgCode,
                            secondSparticlePdgCode );
  }

  inline double
  lhcFaserLight::getNloSevenTevCrossSection( int const firstSparticlePdgCode,
                                             int const secondSparticlePdgCode )
  {
    return getCrossSection( nloCrossSectionHandler,
                            7,
                            firstSparticlePdgCode,
                            secondSparticlePdgCode );
  }

  inline double
  lhcFaserLight::getLoFourteenTevCrossSection( int const firstSparticlePdgCode,
                                            int const secondSparticlePdgCode )
  {
    return getCrossSection( loCrossSectionHandler,
                            14,
                            firstSparticlePdgCode,
                            secondSparticlePdgCode );
  }

  inline double
  lhcFaserLight::getNloFourteenTevCrossSection( int const firstSparticlePdgCode,
                                                int const secondSparticlePdgCode )
  {
    return getCrossSection( nloCrossSectionHandler,
                            14,
                            firstSparticlePdgCode,
                            secondSparticlePdgCode );
  }

  inline void
  lhcFaserLight::updateForNewSlhaFile()
  {
    slhaData.read_file();
    localReadier.readyObserversForNewPoint();
  }

  inline void
  lhcFaserLight::updateForNewSlhaFile( std::string const slhaSpectrumFile )
  {
    slhaData.read_file( slhaSpectrumFile );
    localReadier.readyObserversForNewPoint();
  }

  inline double
  lhcFaserLight::getSumOfNloCrossSectionsAtSevenTeV()
  {
    return getSumOfNloCrossSections( 7 );
  }

  inline double
  lhcFaserLight::getSumOfNloCrossSectionsAtFourteenTeV()
  {
    return getSumOfNloCrossSections( 14 );
  }

  inline double
  lhcFaserLight::getSumOfNloCrossSections( int const beamEnergy )
  {
    double returnValue( 0.0 );
    for( std::vector< signedParticleShortcutPair* >::const_iterator
         channelIterator(
                      nloInput->getScoloredProductionCombinations()->begin() );
         nloInput->getScoloredProductionCombinations()->end()
         > channelIterator;
         ++channelIterator )
    {
      returnValue
      += nloCrossSectionHandler->getTable( beamEnergy,
                                           *channelIterator )->getValue();
    }
    return returnValue;
  }

}  // end of LHC_FASER namespace

#endif /* LHC_FASER_LIGHT_HPP_ */
