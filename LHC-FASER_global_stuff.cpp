/*
 * LHC-FASER_global_stuff.cpp
 *
 *  Created on: 12 Jan 2011
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

#include "LHC-FASER_global_stuff.hpp"


namespace LHC_FASER
{
  double
  lhcFaserGlobal::squareBilinearInterpolation( double const xFraction,
                                               double const yFraction,
                                               double const lowerLeftValue,
                                               double const lowerRightValue,
                                               double const upperRightValue,
                                               double const upperLeftValue )
  {
    if( 0.0 == xFraction )
      {
        return unitLinearInterpolation( yFraction,
                                        lowerLeftValue,
                                        upperLeftValue );
      }
    else if( 1.0 == xFraction )
      {
        return unitLinearInterpolation( yFraction,
                                        lowerRightValue,
                                        upperRightValue );
      }
    else if( 0.0 == yFraction )
      {
        return unitLinearInterpolation( xFraction,
                                        lowerLeftValue,
                                        lowerRightValue );
      }
    else if( 1.0 == yFraction )
      {
        return unitLinearInterpolation( xFraction,
                                        upperLeftValue,
                                        upperRightValue );
      }
    else
      {
        return unitLinearInterpolation( xFraction,
                                        unitLinearInterpolation( yFraction,
                                                                lowerLeftValue,
                                                              upperLeftValue ),
                                        unitLinearInterpolation( yFraction,
                                                               lowerRightValue,
                                                           upperRightValue ) );
      }
  }

  // this is where we decide what value marks when we throw away cascades
  // because the acceptance times branching ratio dropped too low:
  double const lhcFaserGlobal::negligibleBr( 0.001 );
  //double const lhcFaserGlobal::negligibleBr = 0.000001;
  /* 1 millionth seems conservative enough. even at design luminosity, no
   * MSSM point could generate more than a few million electroweakinos in a
   * year.
   */

  /* this is where we decide what value marks when we throw away channels
   * because the cross-section times acceptance times branching ratio dropped
   * too low:
   */
  double const lhcFaserGlobal::negligibleSigma( 0.001 );
  /* internally, picobarns are used as the unit of cross-section. if we would
   * not see at least 1 event from this channel in the 1st 1/fb of data (so
   * 1000 events in the 1st 1/ab of data, 3 years of LHC running at design
   * luminosity), the channel's cross-section is deemed negligible.
   */



  readierForNewPoint::readierForNewPoint()
  {
    // does nothing.
  }

  readierForNewPoint::~readierForNewPoint()
  {
    // the readierForNewPoint has to let all its obsevers know that its
    // destructor is being called:
    for( std::list< bool* >::iterator
         observerIterator( observerBoolsForReadierExistence.begin() );
         observerBoolsForReadierExistence.end() != observerIterator;
         ++observerIterator )
      // go through the list of observed bools...
      {
        *(*observerIterator) = false;
        // this should let any remaining observers know that they should *not*
        // attempt to de-register themselves from this readierForNewPoint.
      }
  }


  void
  readierForNewPoint::removeMe( bool* observerBoolForReadierExistence,
                                bool* observerBoolForReadying )
  /* this removes the observer from the readier's list of observers which is
   * used when the readier's destructor is called to let the observers know
   * to stop asking to be reset.
   */
  {
    bool notFoundRequested( true );
    for( std::list< bool* >::iterator
         boolIterator( observerBoolsForReadierExistence.begin() );
         ( ( observerBoolsForReadierExistence.end() != boolIterator )
           &&
           notFoundRequested );
         ++boolIterator )
      // look through the list for observer knowledge of readier existence...
      {
        if( observerBoolForReadierExistence == *boolIterator )
          // if we find the requested pointer...
          {
            boolIterator
            = observerBoolsForReadierExistence.erase( boolIterator );
            // remove the requested pointer from the list.
            notFoundRequested = false;
            // stop looking (there should only be 1 instance of this pointer).
          }
      }
    notFoundRequested = true;
    for( std::list< bool* >::iterator
         boolIterator( observerBoolsForReadying.begin() );
         ( ( observerBoolsForReadying.end() != boolIterator )
           &&
           notFoundRequested );
         ++boolIterator )
      // look through the list for readying bools...
      {
        if( observerBoolForReadying == *boolIterator )
          // if we find the requested pointer...
          {
            boolIterator
            = observerBoolsForReadying.erase( boolIterator );
            // remove the requested pointer from the list.
            notFoundRequested = true;
            // stop looking (there should only be 1 instance of this pointer).
          }
      }
  }



  getsReadiedForNewPoint::getsReadiedForNewPoint(
                                          readierForNewPoint* const readier ) :
    needsToPrepare( true ),
    readierStillExists( true ),
    readier( readier )
  /* the constructor gives a pointer to a bool pair to given_readier which
   * has values that given_readier changes. this object keeps a pointer to
   * given_readier so that it can de-register when its destructor is called.
   */
  {
    readier->includeMe( &readierStillExists );
  }

  getsReadiedForNewPoint::~getsReadiedForNewPoint()
  // the destructor tells readier, if it still exists, to stop modifying its
  // bools.
  {
    if( readierStillExists )
      // if the readier still exists...
      {
        readier->removeMe( &readierStillExists,
                           &needsToPrepare );
      }
  }



  publicGetsReadiedForNewPoint::publicGetsReadiedForNewPoint(
                                          readierForNewPoint* const readier ) :
    getsReadiedForNewPoint( readier )
  {
    // just an initialization of the base class.
  }

  publicGetsReadiedForNewPoint::~publicGetsReadiedForNewPoint()
  {
    // does nothing.
  }
}  // end of LHC_FASER namespace.

