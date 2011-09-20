/*
 * LHC-FASER_lepton_distributions.hpp
 *
 *  Created on: 16 Mar 2011
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

// this is a set of classes used for the calculation of the fraction of leptons that pass various cuts at the moment.


#include "LHC-FASER_lepton_distributions.hpp"


namespace LHC_FASER
{

  lepton_distribution_expansion_term::lepton_distribution_expansion_term(
                                               int const given_power_of_energy,
                                            int const given_power_of_logarithm,
                                             double const given_coefficient ) :
    power_of_energy( given_power_of_energy ),
    power_of_logarithm( given_power_of_logarithm ),
    coefficient( given_coefficient )
  {

    // just an initialization list.

  }

  lepton_distribution_expansion_term::~lepton_distribution_expansion_term()
  {

    // does nothing.

  }


  double
  lepton_distribution_expansion_term::evaluate( double const given_energy )
  const
  // this evaluates this term for the given input energy.
  {

    // debugging:
    /**std::cout << std::endl << "debugging: "
    << "lepton_distribution_expansion_term::evaluate( " << given_energy
    << " ) called";
    std::cout << std::endl;**/


    double return_value = 0.0;

    if( ( 0.0 < given_energy )
        // only give a value if the energy is above 0.0 since otherwise the
        // logarithms are not going to work.
        &&
        ( 0.0 != coefficient ) )
      // & don't bother if the coefficient is 0.0 anyway.
      {

        if( -1 == power_of_energy )
          {

            return_value = ( coefficient / given_energy );

          }
        else if( 0 == power_of_energy )
          {

            return_value = coefficient;

          }
        else if( 1 == power_of_energy )
          {

            return_value = ( coefficient * given_energy );

          }
        else if( 2 == power_of_energy )
          {

            return_value = ( coefficient * given_energy * given_energy );

          }
        else if( 3 == power_of_energy )
          {

            return_value = ( coefficient * given_energy
                * given_energy * given_energy );

          }
        // I could set up something recursive, but there shouldn't be any
        // higher powers than 3.

        if( 0 < power_of_logarithm )
          {

            double log_energy = log( given_energy );

            /*for( int logarithm_counter = 0;
            logarithm_counter < power_of_logarithm;
            logarithm_counter++ )
            {

            return_value *= log_energy;

            }*/
            // go go super-irrelevant, premature optimization!
            if( 1 == power_of_logarithm )
              {

                return_value *= log_energy;

              }
            else if( 2 == power_of_logarithm )
              {

                return_value *= ( log_energy * log_energy );

              }
            else if( 3 == power_of_logarithm )
              {

                return_value *= ( log_energy * log_energy * log_energy );

              }

          }

      }

    return return_value;

  }


  segment_term_set::segment_term_set( double const given_start,
                                      double const given_end ) :
    segment_start( given_start ),
    segment_end( given_end )
  {

    // just an initialization list.

  }

  segment_term_set::~segment_term_set()
  {

    for( std::vector< lepton_distribution_expansion_term* >::iterator
           deletion_iterator = segment_terms.begin();
         segment_terms.end() > deletion_iterator;
         ++deletion_iterator )
      {

        delete *deletion_iterator;

      }

  }


  double
  segment_term_set::evaluate( double const given_energy )
  const
  // this evaluates the sum of the set of terms for the given input energy.
  {

    // debugging:
    /**std::cout << std::endl << "debugging: "
    << "segment_term_set::evaluate( " << given_energy
    << " ) called";
    std::cout << std::endl;**/

    double return_value = 0.0;

    // only evaluate if the input is within the segment's range:
    if( ( given_energy >= segment_start )
        &&
        ( given_energy <= segment_end ) )
      {

        // debugging:
        /**int segment_term_counter = 0;
        std::cout << std::endl << "debugging: "
        << "given_energy within range, segment_terms.size() = "
        << segment_terms.size();
        std::cout << std::endl;**/

        for( std::vector< lepton_distribution_expansion_term* >::const_iterator
               summation_iterator = segment_terms.begin();
             summation_iterator < segment_terms.end();
             ++summation_iterator )
          {

            // debugging:
            /**std::cout << std::endl << "debugging: "
            << "segment_term_counter = " << ++segment_term_counter;
            std::cout << std::endl;**/

            return_value += (*summation_iterator)->evaluate( given_energy );

          }

      }

    return return_value;

  }


  tau_decay_coefficient::tau_decay_coefficient()
  {

    // just an initialization.

  }

  tau_decay_coefficient::~tau_decay_coefficient()
  {

    // does nothing.

  }


  hard_muon_from_tau::hard_muon_from_tau() :
    tau_decay_coefficient()
  {

    // just an initialization.

  }

  hard_muon_from_tau::~hard_muon_from_tau()
  {

    // does nothing.

  }


  double
  hard_muon_from_tau::operator()( int const muon_energy_power
                            /* the power of the muon's energy for the term. */,
                                  int const muon_log_power
           /* the power of the logarithm of the muon's energy for the term. */,
                                  int const tau_energy_power
                      /* the power of the tau lepton's energy for the term. */,
                                  int const tau_log_power
     /* the power of the logarithm of the tau lepton's energy for the term. */,
                                  double const Emin
         /* the minimum of the range of the tau lepton energies considered. */,
                                  double const Emax
         /* the maximum of the range of the tau lepton energies considered. */,
                                  bool const is_inside_range )
  const
  /* this returns the coefficient for the muon distribution which would come
   * from a left-handed tau lepton distribution of the given power of the tau
   * lepton's energy & power of logarithm thereof, for requested integer powers
   * of the muon's energy or logarithm thereof, which also depends on whether
   * the muon's energy is inside the range of the tau lepton's energy for this
   * segment.
   */
  {

    // debugging:
    /**std::cout << std::endl << "debugging: "
    << "hard_muon_from_tau::operator()( " << muon_energy_power << ", "
    << muon_log_power << ", "
    << tau_energy_power << ", "
    << tau_log_power << ", "
    << Emin << ", "
    << Emax << ", "
    << is_inside_range
    << " ) called";
    std::cout << std::endl;**/

    double return_value = 0.0;

    if( ( -1 == tau_energy_power )
        &&
        ( 0 == tau_log_power ) )
      {

        if( ( -1 == muon_energy_power )
            &&
            ( 0 == muon_log_power ) )
          {

            if( is_inside_range )
              {

                return_value = 1.0;

              }

          }
        else if( ( 0 == muon_energy_power )
                 &&
                 ( 0 == muon_log_power ) )
          {

            return_value = ( -4.0 / ( 3.0 * Emax ) );

            if( !is_inside_range )
              {

                return_value += ( 4.0 / ( 3.0 * Emin ) );

              }

          }
        else if( ( 3 == muon_energy_power )
                 &&
                 ( 0 == muon_log_power ) )
          {

            return_value = ( 1.0 / ( 3.0 * Emax * Emax * Emax * Emax ) );

            if( !is_inside_range )
              {

                return_value -= ( 1.0 / ( 3.0 * Emin * Emin * Emin * Emin ) );

              }

          }

      }  // end of if( -1 == tau_energy_power ) && ( 0 == tau_log_power )
    else if( ( 0 == tau_energy_power )
             &&
             ( 0 == tau_log_power ) )
      {

        if( ( 0 == muon_energy_power )
            &&
            ( 0 == muon_log_power ) )
          {

            double log_max = log( Emax );

            return_value = ( ( 4.0 * log_max ) / 3.0 );

            if( is_inside_range )
              {

                return_value -= ( 4.0 / 9.0 );

              }
            else
              {

                double log_min = log( Emin );

                return_value -= ( ( 4.0 * log_min ) / 3.0 );

              }

          }
        else if( ( 0 == muon_energy_power )
                 &&
                 ( 1 == muon_log_power ) )
          {

            if( is_inside_range )
              {

                return_value = ( -4.0 / 3.0 );

              }

          }
        else if( ( 3 == muon_energy_power )
                 &&
                 ( 0 == muon_log_power ) )
          {

            return_value = ( 4.0 / ( 9.0 * Emax * Emax * Emax ) );

            if( !is_inside_range )
              {

                return_value -= ( 4.0 / ( 9.0 * Emin * Emin * Emin ) );

              }

          }

      }  // end of if( 0 == tau_energy_power ) && ( 0 == tau_log_power )
    else if( ( 0 == tau_energy_power )
             &&
             ( 1 == tau_log_power ) )
      {

        if( ( 0 == muon_energy_power )
            &&
            ( 0 == muon_log_power ) )
          {

            double log_max = log( Emax );

            return_value = ( ( 2.0 * log_max * log_max ) / 3.0 );

            if( is_inside_range )
              {

                return_value -= ( 4.0 / 27.0 );

              }
            else
              {

                double log_min = log( Emin );

                return_value -= ( ( 2.0 * log_min * log_min ) / 3.0 );

              }

          }

        else if( ( 0 == muon_energy_power )
                 &&
                 ( 1 == muon_log_power ) )
          {

            if( is_inside_range )
              {

                return_value = ( -4.0 / 9.0 );

              }

          }
        else if( ( 0 == muon_energy_power )
                 &&
                 ( 2 == muon_log_power ) )
          {

            if( is_inside_range )
              {

                return_value = ( -2.0 / 3.0 );

              }

          }
        else if( ( 3 == muon_energy_power )
                 &&
                 ( 0 == muon_log_power ) )
          {

            double log_max = log( Emax );

            return_value
            = ( ( 4.0 * ( 1.0 + 3.0 * log_max ) )
                / ( 27.0 * Emax * Emax * Emax ) );

            if( !is_inside_range )
              {

                double log_min = log( Emin );

                return_value -= ( ( 4.0 * ( 1.0 + 3.0 * log_min ) )
                                  / ( 27.0 * Emin * Emin * Emin ) );

              }

          }

      }  // end of if( 0 == tau_energy_power ) && ( 1 == tau_log_power )
    else if( ( 1 == tau_energy_power )
             &&
             ( 0 == tau_log_power ) )
      {

        if( ( 0 == muon_energy_power )
            &&
            ( 0 == muon_log_power ) )
          {

            return_value = ( ( 4.0 * Emax ) / 3.0 );

            if( !is_inside_range )
              {

                return_value -= ( ( 4.0 * Emin ) / 3.0 );

              }

          }
        else if( ( 1 == muon_energy_power )
                 &&
                 ( 0 == muon_log_power ) )
          {

            if( is_inside_range )
              {

                return_value = -2.0;

              }

          }
        else if( ( 3 == muon_energy_power )
                 &&
                 ( 0 == muon_log_power ) )
          {

            return_value = ( 2.0 / ( 3.0 * Emax * Emax ) );

            if( !is_inside_range )
              {

                return_value -= ( 2.0 / ( 3.0 * Emin * Emin ) );

              }

          }

      }  // end of if( 1 == tau_energy_power ) && ( 0 == tau_log_power )
    else if( ( 1 == tau_energy_power )
             &&
             ( 1 == tau_log_power ) )
      {

        if( ( 0 == muon_energy_power )
            &&
            ( 0 == muon_log_power ) )
          {

            double log_max = log( Emax );

            return_value = ( ( 4.0 * Emax * ( log_max - 1.0 ) ) / 3.0 );

            if( !is_inside_range )
              {

                double log_min = log( Emin );

                return_value += ( ( 4.0 * Emin * ( 1.0 - log_min ) ) / 3.0 );

              }

          }
        else if( ( 1 == muon_energy_power )
                 &&
                 ( 0 == muon_log_power ) )
          {

            if( is_inside_range )
              {

                return_value = 1.0;

              }

          }
        else if( ( 1 == muon_energy_power )
                 &&
                 ( 1 == muon_log_power ) )
          {

            if( is_inside_range )
              {

                return_value = -2.0;

              }

          }
        else if( ( 3 == muon_energy_power )
                 &&
                 ( 0 == muon_log_power ) )
          {

            double log_max = log( Emax );

            return_value = ( ( 1.0 + 2.0 * log_max ) / ( 3.0 * Emax * Emax ) );

            if( !is_inside_range )
              {

                double log_min = log( Emin );

                return_value
                -= ( ( 1.0 + 2.0 * log_min ) / ( 3.0 * Emin * Emin ) );

              }

          }

      }  // end of if( 1 == tau_energy_power ) && ( 1 == tau_log_power )
    else if( ( 2 == tau_energy_power )
             &&
             ( 0 == tau_log_power ) )
      {

        if( ( 0 == muon_energy_power )
            &&
            ( 0 == muon_log_power ) )
          {

            return_value = ( ( 2.0 * Emax * Emax ) / 3.0 );

            if( !is_inside_range )
              {

                return_value -= ( ( 2.0 * Emin * Emin ) / 3.0 );

              }

          }
        else if( ( 2 == muon_energy_power )
                 &&
                 ( 0 == muon_log_power ) )
          {

            if( is_inside_range )
              {

                return_value = -2.0;

              }

          }
        else if( ( 3 == muon_energy_power )
                 &&
                 ( 0 == muon_log_power ) )
          {

            return_value = ( 4.0 / ( 3.0 * Emax ) );

            if( !is_inside_range )
              {

                return_value -= ( 4.0 / ( 3.0 * Emin ) );

              }

          }

      }  // end of if( 2 == tau_energy_power ) && ( 0 == tau_log_power )

    return return_value;

  }


  soft_muon_from_tau::soft_muon_from_tau() :
    tau_decay_coefficient()
  {

    // just an initialization.

  }

  soft_muon_from_tau::~soft_muon_from_tau()
  {

    // does nothing.

  }


  double
  soft_muon_from_tau::operator()( int const muon_energy_power
                            /* the power of the muon's energy for the term. */,
                                  int const muon_log_power
           /* the power of the logarithm of the muon's energy for the term. */,
                                  int const tau_energy_power
                       /* the power of the tau lepton's energyfor the term. */,
                                  int const tau_log_power
     /* the power of the logarithm of the tau lepton's energy for the term. */,
                                  double const Emin
         /* the minimum of the range of the tau lepton energies considered. */,
                                  double const Emax
         /* the maximum of the range of the tau lepton energies considered. */,
                                  bool const is_inside_range )
  const
  /* this returns the coefficient for the muon distribution which would come
   * from a right-handed tau lepton distribution of the given power of the tau
   * lepton's energy & power of logarithm thereof, for requested integer powers
   * of the muon's energy or logarithm thereof, which also depends on whether
   * the muon's energy is inside the range of the tau lepton's energy for this
   * segment.
   */
  {

    double return_value = 0.0;

    if( ( -1 == tau_energy_power )
        &&
        ( 0 == tau_log_power ) )
      {

        if( ( -1 == muon_energy_power )
            &&
            ( 0 == muon_log_power ) )
          {

            if( is_inside_range )
              {

                return_value = 1.0;

              }

          }
        else if( ( 0 == muon_energy_power )
                 &&
                 ( 0 == muon_log_power ) )
          {

            return_value = ( -2.0 / Emax );

            if( !is_inside_range )
              {

                return_value += ( 2.0 / Emin );

              }

          }
        else if( ( 2 == muon_energy_power )
                 &&
                 ( 0 == muon_log_power ) )
          {

            return_value = ( 2.0 / ( Emax * Emax * Emax ) );

            if( !is_inside_range )
              {

                return_value -= ( 2.0 / ( Emin * Emin * Emin ) );

              }

          }
        else if( ( 3 == muon_energy_power )
                 &&
                 ( 0 == muon_log_power ) )
          {

            return_value = ( -1.0 / ( Emax * Emax * Emax * Emax ) );

            if( !is_inside_range )
              {

                return_value += ( 1.0 / ( Emin * Emin * Emin * Emin ) );

              }

          }

      }  // end of if( -1 == tau_energy_power ) && ( 0 == tau_log_power )
    else if( ( 0 == tau_energy_power )
             &&
             ( 0 == tau_log_power ) )
      {

        if( ( 0 == muon_energy_power )
            &&
            ( 0 == muon_log_power ) )
          {

            double log_max = log( Emax );

            return_value = ( 2.0 * log_max );

            if( is_inside_range )
              {

                return_value -= ( 5.0 / 3.0 );

              }
            else
              {

                double log_min = log( Emin );

                return_value -= ( 2.0 * log_min );

              }

          }
        else if( ( 0 == muon_energy_power )
                 &&
                 ( 1 == muon_log_power ) )
          {

            if( is_inside_range )
              {

                return_value = -2.0;

              }

          }
        else if( ( 2 == muon_energy_power )
                 &&
                 ( 0 == muon_log_power ) )
          {

            return_value = ( 3.0 / ( Emax * Emax ) );

            if( !is_inside_range )
              {

                return_value -= ( 3.0 / ( Emin * Emin ) );

              }

          }
        else if( ( 3 == muon_energy_power )
                 &&
                 ( 0 == muon_log_power ) )
          {

            return_value = ( -4.0 / ( 3.0 * Emax * Emax * Emax ) );

            if( !is_inside_range )
              {

                return_value += ( 4.0 / ( 3.0 * Emin * Emin * Emin ) );

              }

          }

      }  // end of if( 0 == tau_energy_power ) && ( 0 == tau_log_power )
    else if( ( 0 == tau_energy_power )
             &&
             ( 1 == tau_log_power ) )
      {

        if( ( 0 == muon_energy_power )
            &&
            ( 0 == muon_log_power ) )
          {

            double log_max = log( Emax );

            return_value = ( log_max * log_max );

            if( is_inside_range )
              {

                return_value -= ( 19.0 / 18.0 );

              }
            else
              {

                double log_min = log( Emin );

                return_value -= ( log_min * log_min );

              }

          }

        else if( ( 0 == muon_energy_power )
                 &&
                 ( 1 == muon_log_power ) )
          {

            if( is_inside_range )
              {

                return_value = ( -5.0 / 3.0 );

              }

          }
        else if( ( 0 == muon_energy_power )
                 &&
                 ( 2 == muon_log_power ) )
          {

            if( is_inside_range )
              {

                return_value = -1.0;

              }

          }
        else if( ( 2 == muon_energy_power )
                 &&
                 ( 0 == muon_log_power ) )
          {

            double log_max = log( Emax );

            return_value = ( ( 1.5 + 3.0 * log_max ) / ( Emax * Emax ) );

            if( !is_inside_range )
              {

                double log_min = log( Emin );

                return_value -= ( ( 1.5 + 3.0 * log_min ) / ( Emin * Emin ) );

              }

          }
        else if( ( 3 == muon_energy_power )
                 &&
                 ( 0 == muon_log_power ) )
          {

            double log_max = log( Emax );

            return_value = ( ( -4.0 * ( 1.0 + 3.0 * log_max ) )
                             / ( 9.0 * Emax * Emax * Emax ) );

            if( !is_inside_range )
              {

                double log_min = log( Emin );

                return_value += ( ( 4.0 * ( 1.0 + 3.0 * log_min ) )
                                  / ( 9.0 * Emin * Emin * Emin ) );

              }

          }

      }  // end of if( 0 == tau_energy_power ) && ( 1 == tau_log_power )
    else if( ( 1 == tau_energy_power )
             &&
             ( 0 == tau_log_power ) )
      {

        if( ( 0 == muon_energy_power )
            &&
            ( 0 == muon_log_power ) )
          {

            return_value = ( 2.0 * Emax );

            if( !is_inside_range )
              {

                return_value -= ( 2.0 * Emin );

              }

          }
        else if( ( 1 == muon_energy_power )
                 &&
                 ( 0 == muon_log_power ) )
          {

            if( is_inside_range )
              {

                return_value = -6.0;

              }

          }
        else if( ( 2 == muon_energy_power )
                 &&
                 ( 0 == muon_log_power ) )
          {

            return_value = ( 6.0 / Emax );

            if( !is_inside_range )
              {

                return_value -= ( 6.0 / Emin );

              }

          }
        else if( ( 3 == muon_energy_power )
                 &&
                 ( 0 == muon_log_power ) )
          {

            return_value = ( -2.0 / ( Emax * Emax ) );

            if( !is_inside_range )
              {

                return_value += ( 2.0 / ( Emin * Emin ) );

              }

          }

      }  // end of if( 1 == tau_energy_power ) && ( 0 == tau_log_power )
    else if( ( 1 == tau_energy_power )
             &&
             ( 1 == tau_log_power ) )
      {

        if( ( 0 == muon_energy_power )
            &&
            ( 0 == muon_log_power ) )
          {

            double log_max = log( Emax );

            return_value = ( 2.0 * Emax * ( log_max - 1.0 ) );

            if( !is_inside_range )
              {

                double log_min = log( Emin );

                return_value += ( 2.0 * Emin * ( 1.0 - log_min ) );

              }

          }
        else if( ( 1 == muon_energy_power )
                 &&
                 ( 0 == muon_log_power ) )
          {

            if( is_inside_range )
              {

                return_value = -3.0;

              }

          }
        else if( ( 1 == muon_energy_power )
                 &&
                 ( 1 == muon_log_power ) )
          {

            if( is_inside_range )
              {

                return_value = -6.0;

              }

          }
        else if( ( 2 == muon_energy_power )
                 &&
                 ( 0 == muon_log_power ) )
          {

            double log_max = log( Emax );

            return_value = ( ( 6.0 * ( 1.0 + log_max ) ) / Emax );

            if( !is_inside_range )
              {

                double log_min = log( Emin );

                return_value -= ( ( 6.0 * ( 1.0 + log_min ) ) / Emin );

              }

          }
        else if( ( 3 == muon_energy_power )
                 &&
                 ( 0 == muon_log_power ) )
          {

            double log_max = log( Emax );

            return_value = ( ( -1.0 * ( 1.0 + 2.0 * log_max ) )
                             / ( Emax * Emax ) );

            if( !is_inside_range )
              {

                double log_min = log( Emin );

                return_value += ( ( 1.0 + 2.0 * log_min ) / ( Emin * Emin ) );

              }

          }

      }  // end of if( 1 == tau_energy_power ) && ( 1 == tau_log_power )
    else if( ( 2 == tau_energy_power )
             &&
             ( 0 == tau_log_power ) )
      {

        if( ( 0 == muon_energy_power )
            &&
            ( 0 == muon_log_power ) )
          {

            return_value = ( Emax * Emax );

            if( !is_inside_range )
              {

                return_value -= ( Emin * Emin );

              }

          }
        else if( ( 2 == muon_energy_power )
                 &&
                 ( 0 == muon_log_power ) )
          {

            double log_max = log( Emax );

            return_value = ( -6.0 * log_max );

            if( is_inside_range )
              {

                return_value += 3.0;

              }
            else
              {

                double log_min = log( Emin );

                return_value += ( 6.0 * log_min );


              }

          }
        else if( ( 2 == muon_energy_power )
                 &&
                 ( 1 == muon_log_power ) )
          {

            if( is_inside_range )
              {

                return_value = 6.0;

              }

          }
        else if( ( 3 == muon_energy_power )
                 &&
                 ( 0 == muon_log_power ) )
          {

            return_value = ( -4.0 / ( Emax ) );

            if( !is_inside_range )
              {

                return_value += ( 4.0 / ( Emin ) );

              }

          }

      }  // end of if( 2 == tau_energy_power ) && ( 0 == tau_log_power )

    return return_value;

  }


  hard_pion_from_tau::hard_pion_from_tau() :
    tau_decay_coefficient()
  {

    // just an initialization.

  }

  hard_pion_from_tau::~hard_pion_from_tau()
  {

    // does nothing.

  }


  double
  hard_pion_from_tau::operator()( int const pion_energy_power
                            /* the power of the pion's energy for the term. */,
                                   int const pion_log_power
           /* the power of the logarithm of the pion's energy for the term. */,
                                   int const tau_energy_power
                      /* the power of the tau lepton's energy for the term. */,
                                   int const tau_log_power
     /* the power of the logarithm of the tau lepton's energy for the term. */,
                                   double const Emin
         /* the minimum of the range of the tau lepton energies considered. */,
                                   double const Emax
         /* the maximum of the range of the tau lepton energies considered. */,
                                   bool const is_inside_range )
  const
  /* this returns the coefficient for the pion distribution which would come
   * from a right-handed tau lepton distribution of the given power of the
   * tau lepton's energy & power of logarithm thereof, for requested integer
   * powers of the pion's energy or logarithm thereof, which also depends on
   * whether the pion's energy is inside the range of the tau lepton's energy
   * for this segment.
   */
  {

    double return_value = 0.0;

    if( ( -1 == tau_energy_power )
        &&
        ( 0 == tau_log_power ) )
      {

        if( ( -1 == pion_energy_power )
            &&
            ( 0 == pion_log_power ) )
          {

            if( is_inside_range )
              {

                return_value = 1.0;

              }

          }
        else if( ( 1 == pion_energy_power )
                 &&
                 ( 0 == pion_log_power ) )
          {

            double log_max = log( Emax );

            return_value
            = ( ( -1.0 * ( 1.0 + 2.0 * log_max ) ) / ( Emax * Emax ) );

            if( !is_inside_range )
              {

                double log_min = log( Emin );

                return_value
                += ( ( ( 1.0 + 2.0 * log_min ) ) / ( Emin * Emin ) );

              }

          }
        else if( ( 1 == pion_energy_power )
                 &&
                 ( 1 == pion_log_power ) )
          {

            return_value = ( 2.0 / ( Emax * Emax ) );

            if( !is_inside_range )
              {

                return_value -= ( 2.0 / ( Emin * Emin ) );

              }

          }

      }  // end of if( -1 == tau_energy_power ) && ( 0 == tau_log_power )
    else if( ( 0 == tau_energy_power )
             &&
             ( 0 == tau_log_power ) )
      {

        if( ( 0 == pion_energy_power )
            &&
            ( 0 == pion_log_power ) )
          {

            if( is_inside_range )
              {

                return_value = 4.0;

              }

          }
        else if( ( 1 == pion_energy_power )
                 &&
                 ( 0 == pion_log_power ) )
          {

            double log_max = log( Emax );

            return_value = ( ( -4.0 * ( 1.0 + log_max ) ) / Emax );

            if( !is_inside_range )
              {

                double log_min = log( Emin );

                return_value += ( ( 4.0 * ( 1.0 + log_min ) ) / Emin );

              }

          }
        else if( ( 1 == pion_energy_power )
                 &&
                 ( 1 == pion_log_power ) )
          {

            return_value = ( 4.0 / Emax );

            if( !is_inside_range )
              {

                return_value -= ( 4.0 / Emin );

              }

          }

      }  // end of if( 0 == tau_energy_power ) && ( 0 == tau_log_power )
    else if( ( 0 == tau_energy_power )
             &&
             ( 1 == tau_log_power ) )
      {

        if( ( 0 == pion_energy_power )
            &&
            ( 0 == pion_log_power ) )
          {

            if( is_inside_range )
              {

                return_value = 8.0;

              }

          }
        else if( ( 0 == pion_energy_power )
                 &&
                 ( 1 == pion_log_power ) )
          {

            if( is_inside_range )
              {

                return_value = 4.0;

              }

          }
        else if( ( 1 == pion_energy_power )
                 &&
                 ( 0 == pion_log_power ) )
          {

            double log_max = log( Emax );

            return_value
            = ( ( -4.0 * ( 2.0 + 2.0 * log_max + log_max * log_max ) )
                / Emax );

            if( !is_inside_range )
              {

                double log_min = log( Emin );

                return_value
                += ( ( 4.0 * ( 2.0 + 2.0 * log_min + log_min * log_min ) )
                     / Emin );

              }

          }
        else if( ( 1 == pion_energy_power )
                 &&
                 ( 1 == pion_log_power ) )
          {

            double log_max = log( Emax );

            return_value = ( ( 4.0 * ( 1.0 + log_max ) ) / Emax );

            if( !is_inside_range )
              {

                double log_min = log( Emin );

                return_value -= ( ( 4.0 * ( 1.0 + log_min ) ) / Emin );

              }

          }

      }  // end of if( 0 == tau_energy_power ) && ( 1 == tau_log_power )
    else if( ( 1 == tau_energy_power )
             &&
             ( 0 == tau_log_power ) )
      {

        if( ( 1 == pion_energy_power )
            &&
            ( 0 == pion_log_power ) )
          {

            double log_max = log( Emax );

            return_value = ( 2.0 * log_max * log_max );

            if( !is_inside_range )
              {

                double log_min = log( Emin );

                return_value -= ( 2.0 * log_min * log_min );

              }

          }
        else if( ( 1 == pion_energy_power )
                 &&
                 ( 1 == pion_log_power ) )
          {

            double log_max = log( Emax );

            return_value = ( -4.0 * log_max );

            if( !is_inside_range )
              {

                double log_min = log( Emin );

                return_value += ( 4.0 * log_min );

              }

          }
        else if( ( 1 == pion_energy_power )
                 &&
                 ( 2 == pion_log_power ) )
          {

            if( is_inside_range )
              {

                return_value = 2.0;

              }

          }

      }  // end of if( 1 == tau_energy_power ) && ( 0 == tau_log_power )
    else if( ( 1 == tau_energy_power )
             &&
             ( 1 == tau_log_power ) )
      {

        if( ( 1 == pion_energy_power )
            &&
            ( 0 == pion_log_power ) )
          {

            double log_max = log( Emax );

            return_value = ( ( 4.0 * log_max * log_max * log_max ) / 3.0 );

            if( !is_inside_range )
              {

                double log_min = log( Emin );

                return_value
                -= ( ( 4.0 * log_min * log_min * log_min ) / 3.0 );

              }

          }
        else if( ( 1 == pion_energy_power )
                 &&
                 ( 1 == pion_log_power ) )
          {

            double log_max = log( Emax );

            return_value = ( -2.0 * log_max * log_max );

            if( !is_inside_range )
              {

                double log_min = log( Emin );

                return_value += ( 2.0 * log_min * log_min );

              }

          }
        else if( ( 1 == pion_energy_power )
                 &&
                 ( 3 == pion_log_power ) )
          {

            if( is_inside_range )
              {

                return_value = ( 2.0 / 3.0 );

              }

          }

      }  // end of if( 1 == tau_energy_power ) && ( 1 == tau_log_power )
    else if( ( 2 == tau_energy_power )
             &&
             ( 0 == tau_log_power ) )
      {

        if( ( 1 == pion_energy_power )
            &&
            ( 0 == pion_log_power ) )
          {

            double log_max = log( Emax );

            return_value = ( 4.0 * Emax * ( log_max - 1.0 ) );

            if( !is_inside_range )
              {

                double log_min = log( Emin );

                return_value += ( 4.0 * Emin * ( 1.0 - log_min ) );

              }

          }
        else if( ( 1 == pion_energy_power )
                 &&
                 ( 1 == pion_log_power ) )
          {

            return_value = ( -4.0 * Emax );

            if( !is_inside_range )
              {

                return_value += ( 4.0 * Emin );

              }

          }
        else if( ( 2 == pion_energy_power )
                 &&
                 ( 0 == pion_log_power ) )
          {

            if( is_inside_range )
              {

                return_value = 4.0;

              }

          }

      }  // end of if( 2 == tau_energy_power ) && ( 0 == tau_log_power )

    return return_value;

  }


  soft_pion_from_tau::soft_pion_from_tau() :
    tau_decay_coefficient()
  {

    // just an initialization.

  }

  soft_pion_from_tau::~soft_pion_from_tau()
  {

    // does nothing.

  }


  double
  soft_pion_from_tau::operator()( int const pion_energy_power
                            /* the power of the pion's energy for the term. */,
                                   int const pion_log_power
           /* the power of the logarithm of the pion's energy for the term. */,
                                   int const tau_energy_power
                       /* the power of the tau lepton's energyfor the term. */,
                                   int const tau_log_power
     /* the power of the logarithm of the tau lepton's energy for the term. */,
                                   double const Emin
         /* the minimum of the range of the tau lepton energies considered. */,
                                   double const Emax
         /* the maximum of the range of the tau lepton energies considered. */,
                                   bool const is_inside_range )
  const
  /* this returns the coefficient for the pion distribution which would come
   * from a left-handed tau lepton distribution of the given power of the tau
   * lepton's energy & power of logarithm thereof, for requested integer
   * powers of the pion's energy or logarithm thereof, which also depends on
   * whether the pion's energy is inside the range of the tau lepton's energy
   * for this segment.
   */
  {

    double return_value = 0.0;

    if( ( -1 == tau_energy_power )
        &&
        ( 0 == tau_log_power ) )
      {

        if( ( -1 == pion_energy_power )
            &&
            ( 0 == pion_log_power ) )
          {

            if( is_inside_range )
              {

                return_value = 1.0;

              }

          }
        else if( ( 0 == pion_energy_power )
                 &&
                 ( 0 == pion_log_power ) )
          {

            return_value = ( -4.0 / Emax );

            if( !is_inside_range )
              {

                return_value += ( 4.0 / Emin );

              }

          }
        else if( ( 1 == pion_energy_power )
                 &&
                 ( 0 == pion_log_power ) )
          {

            double log_max = log( Emax );

            return_value = ( ( 2.0 * log_max + 3.0 ) / ( Emax * Emax ) );

            if( !is_inside_range )
              {

                double log_min = log( Emin );

                return_value -= ( ( 2.0 * log_min + 3.0 ) / ( Emin * Emin ) );

              }

          }
        else if( ( 1 == pion_energy_power )
                 &&
                 ( 1 == pion_log_power ) )
          {

            return_value = ( -2.0 / ( Emax * Emax ) );

            if( !is_inside_range )
              {

                return_value += ( 2.0 / ( Emin * Emin ) );

              }

          }

      }  // end of if( -1 == tau_energy_power ) && ( 0 == tau_log_power )
    else if( ( 0 == tau_energy_power )
             &&
             ( 0 == tau_log_power ) )
      {

        if( ( 0 == pion_energy_power )
            &&
            ( 0 == pion_log_power ) )
          {

            double log_max = log( Emax );

            return_value = ( 4.0 * log_max );

            if( is_inside_range )
              {

                return_value -= 8.0;

              }
            else
              {
                double log_min = log( Emin );

                return_value -= ( 4.0 * log_min );

              }

          }
        else if( ( 0 == pion_energy_power )
                 &&
                 ( 1 == pion_log_power ) )
          {

            if( is_inside_range )
              {

                return_value = -4.0;

              }

          }
        else if( ( 1 == pion_energy_power )
                 &&
                 ( 0 == pion_log_power ) )
          {

            double log_max = log( Emax );

            return_value = ( ( 4.0 * ( 2.0 + log_max ) ) / Emax );

            if( !is_inside_range )
              {

                double log_min = log( Emin );

                return_value -= ( ( 4.0 * ( 2.0 + log_min ) ) / Emin );

              }

          }
        else if( ( 1 == pion_energy_power )
                 &&
                 ( 1 == pion_log_power ) )
          {

            return_value = ( -4.0 / Emax );

            if( !is_inside_range )
              {

                return_value += ( 4.0 / Emin );

              }

          }

      }  // end of if( 0 == tau_energy_power ) && ( 0 == tau_log_power )
    else if( ( 0 == tau_energy_power )
             &&
             ( 1 == tau_log_power ) )
      {

        if( ( 0 == pion_energy_power )
            &&
            ( 0 == pion_log_power ) )
          {

            double log_max = log( Emax );

            return_value = ( 2.0 * log_max * log_max );

            if( is_inside_range )
              {

                return_value -= 12.0;

              }
            else
              {

                double log_min = log( Emin );

                return_value -= ( 2.0 * log_min * log_min );

              }

          }
        else if( ( 0 == pion_energy_power )
                 &&
                 ( 1 == pion_log_power ) )
          {

            if( is_inside_range )
              {

                return_value = -8.0;

              }

          }
        else if( ( 0 == pion_energy_power )
                 &&
                 ( 2 == pion_log_power ) )
          {

            if( is_inside_range )
              {

                return_value = -2.0;

              }

          }
        else if( ( 1 == pion_energy_power )
                 &&
                 ( 0 == pion_log_power ) )
          {

            double log_max = log( Emax );

            return_value
            = ( ( 4.0 * ( 3.0 + 3.0 * log_max + log_max * log_max ) ) / Emax );

            if( !is_inside_range )
              {

                double log_min = log( Emin );

                return_value
                -= ( ( 4.0 * ( 3.0 + 3.0 * log_min + log_min * log_min ) )
                     / Emin );

              }

          }
        else if( ( 1 == pion_energy_power )
                 &&
                 ( 1 == pion_log_power ) )
          {

            double log_max = log( Emax );

            return_value = ( ( -4.0 * ( 1.0 + log_max ) ) / Emax );

            if( !is_inside_range )
              {

                double log_min = log( Emin );

                return_value += ( ( 4.0 * ( 1.0 + log_min ) ) / Emin );

              }

          }

      }  // end of if( 0 == tau_energy_power ) && ( 1 == tau_log_power )
    else if( ( 1 == tau_energy_power )
             &&
             ( 0 == tau_log_power ) )
      {

        if( ( 0 == pion_energy_power )
            &&
            ( 0 == pion_log_power ) )
          {

            return_value = ( 4.0 * Emax );

            if( !is_inside_range )
              {

                return_value -= ( 4.0 * Emin );

              }

          }
        else if( ( 1 == pion_energy_power )
                 &&
                 ( 0 == pion_log_power ) )
          {

            double log_max = log( Emax );

            return_value = ( -2.0 * log_max * ( log_max + 2.0 ) );

            if( is_inside_range )
              {

                return_value -= 4.0;

              }
            else
              {

                double log_min = log( Emin );

                return_value += ( 2.0 * log_min * ( log_min + 2.0 ) );

              }

          }
        else if( ( 1 == pion_energy_power )
                 &&
                 ( 1 == pion_log_power ) )
          {

            double log_max = log( Emax );

            return_value = ( 4.0 * log_max );

            if( is_inside_range )
              {

                return_value += 4.0;

              }
            else
              {

                double log_min = log( Emin );

                return_value -= ( 4.0 * log_min );

              }

          }
        else if( ( 1 == pion_energy_power )
                 &&
                 ( 2 == pion_log_power ) )
          {

            if( is_inside_range )
              {

                return_value = -2.0;

              }

          }

      }  // end of if( 1 == tau_energy_power ) && ( 0 == tau_log_power )
    else if( ( 1 == tau_energy_power )
             &&
             ( 1 == tau_log_power ) )
      {

        if( ( 0 == pion_energy_power )
            &&
            ( 0 == pion_log_power ) )
          {

            double log_max = log( Emax );

            return_value = ( 4.0 * Emax * ( log_max - 1.0 ) );

            if( !is_inside_range )
              {

                double log_min = log( Emin );

                return_value += ( 4.0 * Emin * ( 1.0 - log_min ) );

              }

          }
        else if( ( 1 == pion_energy_power )
                 &&
                 ( 0 == pion_log_power ) )
          {

            double log_max = log( Emax );

            return_value
            = ( ( -2.0 * log_max * log_max * ( 3.0 + 2.0 * log_max ) ) / 3.0 );

            if( is_inside_range )
              {

                return_value += 4.0;

              }
            else
              {

                double log_min = log( Emin );

                return_value
                += ( ( 2.0 * log_min * log_min * ( 3.0 + 2.0 * log_min ) )
                     / 3.0 );

              }

          }
        else if( ( 1 == pion_energy_power )
                 &&
                 ( 1 == pion_log_power ) )
          {

            double log_max = log( Emax );

            return_value = ( 2.0 * log_max * log_max );

            if( is_inside_range )
              {

                return_value -= 4.0;

              }
            else
              {

                double log_min = log( Emin );

                return_value -= ( 2.0 * log_min * log_min );

              }

          }
        else if( ( 1 == pion_energy_power )
                 &&
                 ( 2 == pion_log_power ) )
          {

            if( is_inside_range )
              {

                return_value = 2.0;

              }

          }
        else if( ( 1 == pion_energy_power )
                 &&
                 ( 3 == pion_log_power ) )
          {

            if( is_inside_range )
              {

                return_value = ( -2.0 / 3.0 );

              }

          }

      }  // end of if( 1 == tau_energy_power ) && ( 1 == tau_log_power )
    else if( ( 2 == tau_energy_power )
             &&
             ( 0 == tau_log_power ) )
      {

        if( ( 0 == pion_energy_power )
            &&
            ( 0 == pion_log_power ) )
          {

            return_value = ( 2.0 * Emax * Emax );

            if( !is_inside_range )
              {

                return_value -= ( 2.0 * Emin * Emin );

              }

          }
        else if( ( 1 == pion_energy_power )
                 &&
                 ( 0 == pion_log_power ) )
          {

            double log_max = log( Emax );

            return_value = ( -4.0 * Emax * log_max );

            if( !is_inside_range )
              {

                double log_min = log( Emin );

                return_value += ( 4.0 * Emin * log_min );

              }

          }
        else if( ( 1 == pion_energy_power )
                 &&
                 ( 1 == pion_log_power ) )
          {

            return_value = ( 4.0 * Emax );

            if( !is_inside_range )
              {

                return_value -= ( 4.0 * Emin );

              }

          }
        else if( ( 2 == pion_energy_power )
                 &&
                 ( 0 == pion_log_power ) )
          {

            if( is_inside_range )
              {

                return_value = -2.0;

              }

          }

      }  // end of if( 2 == tau_energy_power ) && ( 0 == tau_log_power )

    return return_value;

  }


  lepton_energy_distribution::lepton_energy_distribution(
                                 CppSLHA::CppSLHA0 const* const given_spectrum,
                                                 double const given_first_mass,
                                                double const given_second_mass,
                                                 double const given_third_mass,
                                             double const given_fourth_mass ) :
    spectrum_data( given_spectrum ),
    first_mass( given_first_mass ),
    second_mass( given_second_mass ),
    third_mass( given_third_mass ),
    fourth_mass( given_fourth_mass )
  {

    // just an initialization list.

  }

  lepton_energy_distribution::~lepton_energy_distribution()
  {

    for( std::vector< segment_term_set* >::iterator
          deletion_iterator = segments.begin();
         segments.end() > deletion_iterator;
         ++deletion_iterator )
      {

        delete *deletion_iterator;
        *deletion_iterator = NULL;  // just to be safe.

      }

  }


  double
  lepton_energy_distribution::value_at( double const given_energy )
  const
  // this returns the value of the distribution at the given value, with
  // arbitrary normalization (different for each distribution).
  {

    double return_value = 0.0;

    for( std::vector<segment_term_set*>::const_iterator
           summation_iterator = segments.begin();
         summation_iterator != segments.end();
         ++summation_iterator )
      {

        return_value += (*summation_iterator)->evaluate( given_energy );

      }

    return return_value;

  }


  flat_near_muon_plus_antimuon::flat_near_muon_plus_antimuon(
                                 CppSLHA::CppSLHA0 const* const given_spectrum,
                    CppSLHA::particle_property_set const* const first_particle,
                                             double const effective_first_mass,
                   CppSLHA::particle_property_set const* const second_particle,
                 CppSLHA::particle_property_set const* const third_particle ) :
    lepton_energy_distribution( given_spectrum,
                                effective_first_mass,
                                second_particle->get_absolute_mass(),
                                third_particle->get_absolute_mass(),
                                0.0 )
  {

    production_frame_energy
    = ( ( ( second_mass * second_mass ) - ( third_mass * third_mass ) )
        / ( 2.0 * second_mass ) );

    minimum_energy
    = ( ( second_mass / first_mass ) * production_frame_energy );

    maximum_energy
    = ( ( first_mass / second_mass ) * production_frame_energy );


    // now we set up the coefficients of various terms, & use them to determine
    // the normalization:

    // well, in this case, the distribution is a constant in the only segment's
    // range, so I won't bother with writing
    //double MINtoMAX_const = 1.0;

    normalization = ( maximum_energy - minimum_energy );


    // debugging:
    /**std::cout
    << std::endl
    << "debugging: flat_near_muon_plus_antimuon constructor has"
    << std::endl << "first_mass = " << first_mass
    << std::endl << "second_mass = " << second_mass
    << std::endl << "production_frame_energy = " << production_frame_energy
    << std::endl << "minimum_energy = " << minimum_energy
    << std::endl << "maximum_energy = " << maximum_energy
    << std::endl << "normalization = " << normalization;
    std::cout << std::endl;**/


    // finally we fill the sets of terms, segment by segment:

    // MIN to MAX segment:
    segment_term_set* segment_filler = new segment_term_set( minimum_energy,
                                                             maximum_energy );

    // constant term:
    lepton_distribution_expansion_term*
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          0,
                                                     ( 1.0 / normalization ) );
    segment_filler->add_term( term_filler );


    // record the segment:
    segments.push_back( segment_filler );


  }

  flat_near_muon_plus_antimuon::~flat_near_muon_plus_antimuon()
  {

    // does nothing.

  }


  same_chirality_near_muon::same_chirality_near_muon(
                                 CppSLHA::CppSLHA0 const* const given_spectrum,
                    CppSLHA::particle_property_set const* const first_particle,
                                             double const effective_first_mass,
                   CppSLHA::particle_property_set const* const second_particle,
                 CppSLHA::particle_property_set const* const third_particle ) :
    lepton_energy_distribution( given_spectrum,
                                effective_first_mass,
                                second_particle->get_absolute_mass(),
                                third_particle->get_absolute_mass(),
                                0.0 )
  {

    production_frame_energy
    = ( ( ( second_mass * second_mass ) - ( third_mass * third_mass ) )
        / ( 2.0 * second_mass ) );

    minimum_energy
    = ( ( second_mass / first_mass ) * production_frame_energy );

    maximum_energy
    = ( ( first_mass / second_mass ) * production_frame_energy );

    normalization = ( maximum_energy - minimum_energy );


    // now we set up the coefficients of various terms, & use them to determine
    // the normalization:

    MINtoMAX_const = -minimum_energy;
    MINtoMAX_lin = 1.0;

    normalization = ( 0.5 * ( maximum_energy - minimum_energy )
                          * ( maximum_energy - minimum_energy ) );



    // finally we fill the sets of terms, segment by segment:

    // MIN to MAX segment:
    segment_term_set* segment_filler = new segment_term_set( minimum_energy,
                                                             maximum_energy );

    // linear term:
    lepton_distribution_expansion_term*
    term_filler = new lepton_distribution_expansion_term( 1,
                                                          0,
                                            ( MINtoMAX_lin / normalization ) );
    segment_filler->add_term( term_filler );

    // constant term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          0,
                                          ( MINtoMAX_const / normalization ) );
    segment_filler->add_term( term_filler );


    // record the segment
    segments.push_back( segment_filler );

  }

  same_chirality_near_muon::~same_chirality_near_muon()
  {

    // does nothing.

  }


  opposite_chirality_near_muon::opposite_chirality_near_muon(
                                 CppSLHA::CppSLHA0 const* const given_spectrum,
                    CppSLHA::particle_property_set const* const first_particle,
                                             double const effective_first_mass,
                   CppSLHA::particle_property_set const* const second_particle,
                 CppSLHA::particle_property_set const* const third_particle ) :
    lepton_energy_distribution( given_spectrum,
                                effective_first_mass,
                                second_particle->get_absolute_mass(),
                                third_particle->get_absolute_mass(),
                                0.0 )
  {

    production_frame_energy
    = ( ( ( second_mass * second_mass ) - ( third_mass * third_mass ) )
        / ( 2.0 * second_mass ) );

    minimum_energy
    = ( ( second_mass / first_mass ) * production_frame_energy );

    maximum_energy
    = ( ( first_mass / second_mass ) * production_frame_energy );

    normalization = ( maximum_energy - minimum_energy );


    // now we set up the coefficients of various terms, & use them to determine
    // the normalization.

    MINtoMAX_const = maximum_energy;
    MINtoMAX_lin = -1.0;

    normalization = ( 0.5 * ( maximum_energy - minimum_energy )
                          * ( maximum_energy - minimum_energy ) );



    // finally we fill the sets of terms, segment by segment:

    // MIN to MAX segment:
    segment_term_set* segment_filler = new segment_term_set( minimum_energy,
                                                             maximum_energy );

    // linear term:
    lepton_distribution_expansion_term*
    term_filler = new lepton_distribution_expansion_term( 1,
                                                          0,
                                            ( MINtoMAX_lin / normalization ) );
    segment_filler->add_term( term_filler );

    // constant term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          0,
                                          ( MINtoMAX_const / normalization ) );
    segment_filler->add_term( term_filler );


    // record the segment:
    segments.push_back( segment_filler );

  }

  opposite_chirality_near_muon::~opposite_chirality_near_muon()
  {

    // does nothing.

  }


  flat_far_muon_plus_antimuon::flat_far_muon_plus_antimuon(
                                 CppSLHA::CppSLHA0 const* const given_spectrum,
                    CppSLHA::particle_property_set const* const first_particle,
                                             double const effective_first_mass,
                   CppSLHA::particle_property_set const* const second_particle,
                    CppSLHA::particle_property_set const* const third_particle,
                CppSLHA::particle_property_set const* const fourth_particle ) :
    lepton_energy_distribution( given_spectrum,
                                effective_first_mass,
                                second_particle->get_absolute_mass(),
                                third_particle->get_absolute_mass(),
                                fourth_particle->get_absolute_mass() )
  {

    double mlSq = ( third_mass * third_mass );
    double mXSq = ( fourth_mass * fourth_mass );

    production_frame_energy = ( ( mlSq - mXSq ) / ( 2.0 * third_mass ) );

    minimum_energy = ( ( third_mass / first_mass ) * production_frame_energy );

    double Elk;
    double Ehk;

    // there are 2 kinematic cases for determining the kink energies in terms
    // of the cascade masses:
    if( ( first_mass / second_mass ) > ( second_mass / third_mass ) )
      {

        Elk = ( ( ( second_mass / first_mass ) * ( second_mass / third_mass ) )
                * production_frame_energy );

        Ehk = ( ( ( first_mass / second_mass ) * ( third_mass / second_mass ) )
                * production_frame_energy );

      }
    else
      {

        Elk = ( ( ( first_mass / second_mass ) * ( third_mass / second_mass ) )
                * production_frame_energy );

        Ehk = ( ( ( second_mass / first_mass ) * ( second_mass / third_mass ) )
                * production_frame_energy );

      }


    maximum_energy
    = ( ( first_mass / third_mass ) * production_frame_energy );


    // now we set up the coefficients of various terms, & use them to determine
    // the normalization:

    MINtoLK_const = -log( minimum_energy );
    MINtoLK_log = 1.0;

    LKtoHK_const = log( ( maximum_energy / Ehk ) );

    HKtoMAX_const = log( maximum_energy );
    HKtoMAX_log = -1.0;

    normalization
    = ( MINtoLK_const * ( Elk - minimum_energy )
        + MINtoLK_log * ( Elk * ( log( Elk ) - 1.0 )
                          - minimum_energy * ( log( minimum_energy ) - 1.0 ) )
        + LKtoHK_const * ( Ehk - Elk )
        + HKtoMAX_const * ( maximum_energy - Ehk )
        + HKtoMAX_log * ( maximum_energy * ( log( maximum_energy ) - 1.0 )
                          - Ehk * ( log( Ehk ) - 1.0 ) ) );

    // debugging:
    /**std::cout
    << std::endl
    << "debugging: flat_far_muon_plus_antimuon_distribution:";
    std::cout << std::endl << "normalization = " << normalization;
    std::cout << std::endl << "minimum_energy = " << minimum_energy;
    std::cout << std::endl << "Elk = " << Elk;
    std::cout << std::endl << "Ehk = " << Ehk;
    std::cout << std::endl << "maximum_energy = " << maximum_energy;
    std::cout << std::endl;**/


    // finally we fill the sets of terms, segment by segment:

    // MIN to LK segment:
    segment_term_set* segment_filler = new segment_term_set( minimum_energy,
                                                             Elk );

    // logarithm term:
    lepton_distribution_expansion_term*
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          1,
                                             ( MINtoLK_log / normalization ) );
    segment_filler->add_term( term_filler );

    // constant term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          0,
                                           ( MINtoLK_const / normalization ) );
    segment_filler->add_term( term_filler );


    // record the segment:
    segments.push_back( segment_filler );


    // LK to HK segment:
    segment_filler = new segment_term_set( Elk,
                                           Ehk );

    // constant term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          0,
                                            ( LKtoHK_const / normalization ) );
    segment_filler->add_term( term_filler );


    // record the segment:
    segments.push_back( segment_filler );


    // HK to MAX segment:
    segment_filler = new segment_term_set( Ehk,
                                           maximum_energy );

    // logarithm term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          1,
                                             ( HKtoMAX_log / normalization ) );
    segment_filler->add_term( term_filler );


    // constant term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          0,
                                           ( HKtoMAX_const / normalization ) );
    segment_filler->add_term( term_filler );


    // record the segment:
    segments.push_back( segment_filler );

  }

  flat_far_muon_plus_antimuon::~flat_far_muon_plus_antimuon()
  {

    // does nothing.

  }


  same_chirality_far_muon::same_chirality_far_muon(
                                 CppSLHA::CppSLHA0 const* const given_spectrum,
                    CppSLHA::particle_property_set const* const first_particle,
                                             double const effective_first_mass,
                   CppSLHA::particle_property_set const* const second_particle,
                    CppSLHA::particle_property_set const* const third_particle,
                CppSLHA::particle_property_set const* const fourth_particle ) :
    lepton_energy_distribution( given_spectrum,
                                effective_first_mass,
                                second_particle->get_absolute_mass(),
                                third_particle->get_absolute_mass(),
                                fourth_particle->get_absolute_mass() )
  {

    double mq = first_mass;
    double mqSq = ( mq * mq );
    double mNSq = ( second_mass * second_mass );
    double mlSq = ( third_mass * third_mass );
    double mXSq = ( fourth_mass * fourth_mass );

    production_frame_energy = ( ( mlSq - mXSq ) / ( 2.0 * third_mass ) );

    minimum_energy
    = ( ( third_mass / first_mass ) * production_frame_energy );

    double Elk;
    double Ehk;

    // there are 2 kinematic cases for determining the kink energies in terms
    // of the cascade masses.
    if( ( first_mass / second_mass ) > ( second_mass / third_mass ) )
      {

        Elk = ( ( ( second_mass / first_mass ) * ( second_mass / third_mass ) )
                * production_frame_energy );

        Ehk = ( ( ( first_mass / second_mass ) * ( third_mass / second_mass ) )
                * production_frame_energy );

      }
    else
      {

        Elk = ( ( ( first_mass / second_mass ) * ( third_mass / second_mass ) )
                * production_frame_energy );

        Ehk = ( ( ( second_mass / first_mass ) * ( second_mass / third_mass ) )
                * production_frame_energy );

      }


    maximum_energy = ( ( first_mass / third_mass ) * production_frame_energy );


    // now we set up the coefficients of various terms, & use them to determine
    // the normalization:

    MINtoLK_lin
    = ( ( 4.0 * mlSq * mNSq * mq )
        / ( ( mlSq - mNSq ) * ( mNSq + mqSq ) * ( mlSq - mXSq ) ) );

    MINtoLK_log = ( ( 2.0 * mNSq * ( mqSq - mlSq ) )
                    / ( ( mNSq - mlSq ) * ( mNSq + mqSq ) ) );

    MINtoLK_const
    = ( ( 2.0 * mNSq
          * ( 2.0 * mNSq - mqSq + mlSq
              + ( mqSq - mlSq ) * log( ( ( 2.0 * mq ) / ( mlSq - mXSq ) ) ) ) )
        / ( ( mNSq - mlSq ) * ( mNSq + mqSq ) ) );

    MINtoLK_inv = ( ( mNSq * ( 2.0 * mNSq - mqSq ) * ( mlSq - mXSq ) )
                    / ( mq * ( mlSq - mNSq ) * ( mNSq + mqSq ) ) );

    // there are 2 kinematic cases for determining the kink energies in terms
    // of the cascade masses.
    if( ( first_mass / second_mass ) < ( second_mass / third_mass ) )
      // if the assumption that the mass spectrum was SPS1a-like was
      // incorrect...
      {

        LKtoHK_const
        = ( 2.0 * ( ( mlSq + mNSq ) * ( mNSq - mqSq )
                    + mNSq * ( mlSq - mqSq ) * log( ( mNSq / mqSq ) ) )
            / ( ( mNSq - mlSq ) * ( mNSq + mqSq ) ) );

        LKtoHK_inv = ( ( 2.0 * mNSq * ( mNSq - mqSq ) * ( mlSq - mXSq ) )
                       / ( mq * ( mlSq - mNSq ) * ( mNSq + mqSq ) ) );

      }
    else
      {

        LKtoHK_const
        = ( ( 2.0 * ( ( mqSq - mNSq ) * ( mlSq - mNSq )
                      + mNSq * ( mlSq - mqSq ) * log( ( mlSq / mNSq ) ) ) )
            / ( ( mNSq - mlSq ) * ( mNSq + mqSq ) ) );

        LKtoHK_inv = 0.0;

      }

    HKtoMAX_lin = -MINtoLK_lin;

    HKtoMAX_log = -MINtoLK_log;

    HKtoMAX_const
    = ( ( 2.0 * mNSq * ( mlSq + mqSq
                         + ( mqSq - mlSq )
                           * log( ( ( 2.0 * mlSq )
                                    / ( ( mlSq - mXSq ) * mq ) ) ) ) )
        / ( ( mlSq - mNSq ) * ( mNSq + mqSq ) ) );

    HKtoMAX_inv = ( ( mNSq * mq * ( mlSq - mXSq ) )
                    / ( ( mNSq - mlSq ) * ( mNSq + mqSq ) ) );


    normalization
    = ( MINtoLK_lin * 0.5 * ( Elk * Elk - minimum_energy * minimum_energy )
        + MINtoLK_log * ( Elk * ( log( Elk ) - 1.0 )
                          - minimum_energy * ( log( minimum_energy ) - 1.0 ) )
        + MINtoLK_const * ( Elk - minimum_energy )
        + MINtoLK_inv * log( ( Elk / minimum_energy ) )
        + LKtoHK_const * ( Ehk - Elk )
        + LKtoHK_inv * log( ( Ehk / Elk ) )
        + HKtoMAX_lin * 0.5 * ( maximum_energy * maximum_energy - Ehk * Ehk )
        + HKtoMAX_log * ( maximum_energy * ( log( maximum_energy ) - 1.0 )
                          - Ehk * ( log( Ehk ) - 1.0 ) )
        + HKtoMAX_const * ( maximum_energy - Ehk )
        + HKtoMAX_inv * log( ( maximum_energy / Ehk ) ) );


    // debugging:
    /**std::cout
    << std::endl
    << "debugging: lepton_distribution_same_chirality_far_muon:";
    std::cout << std::endl << "normalization = " << normalization;
    std::cout << std::endl << "minimum_energy = " << minimum_energy;
    std::cout << std::endl << "Elk = " << Elk;
    std::cout << std::endl << "Ehk = " << Ehk;
    std::cout << std::endl << "maximum_energy = " << maximum_energy;
    std::cout << std::endl << "MINtoLK_lin = " << MINtoLK_lin;
    std::cout << std::endl << "MINtoLK_log = " << MINtoLK_log;
    std::cout << std::endl << "MINtoLK_const = " << MINtoLK_const;
    std::cout << std::endl << "MINtoLK_inv = " << MINtoLK_inv;
    std::cout << std::endl << "LKtoHK_const = " << LKtoHK_const;
    std::cout << std::endl << "LKtoHK_inv = " << LKtoHK_inv;
    std::cout << std::endl;**/


    // finally we fill the sets of terms, segment by segment:

    // MIN to LK segment:
    segment_term_set* segment_filler = new segment_term_set( minimum_energy,
                                                             Elk );

    // linear term:
    lepton_distribution_expansion_term*
    term_filler = new lepton_distribution_expansion_term( 1,
                                                          0,
                                             ( MINtoLK_lin / normalization ) );
    segment_filler->add_term( term_filler );

    // logarithm term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          1,
                                             ( MINtoLK_log / normalization ) );
    segment_filler->add_term( term_filler );

    // constant term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          0,
                                           ( MINtoLK_const / normalization ) );
    segment_filler->add_term( term_filler );

    // inverse term:
    term_filler = new lepton_distribution_expansion_term( -1,
                                                          0,
                                             ( MINtoLK_inv / normalization ) );
    segment_filler->add_term( term_filler );


    // record the segment:
    segments.push_back( segment_filler );


    // LK to HK segment:
    segment_filler = new segment_term_set( Elk,
                                           Ehk );

    // constant term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          0,
                                            ( LKtoHK_const / normalization ) );
    segment_filler->add_term( term_filler );

    // inverse term:
    term_filler = new lepton_distribution_expansion_term( -1,
                                                          0,
                                              ( LKtoHK_inv / normalization ) );
    segment_filler->add_term( term_filler );


    // record the segment:
    segments.push_back( segment_filler );


    // HK to MAX segment:
    segment_filler = new segment_term_set( Ehk,
                                           maximum_energy );

    // linear term:
    term_filler = new lepton_distribution_expansion_term( 1,
                                                          0,
                                             ( HKtoMAX_lin / normalization ) );
    segment_filler->add_term( term_filler );

    // logarithm term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          1,
                                             ( HKtoMAX_log / normalization ) );
    segment_filler->add_term( term_filler );

    // constant term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          0,
                                           ( HKtoMAX_const / normalization ) );
    segment_filler->add_term( term_filler );

    // inverse term:
    term_filler = new lepton_distribution_expansion_term( -1,
                                                          0,
                                             ( HKtoMAX_inv / normalization ) );
    segment_filler->add_term( term_filler );


    // record the segment:
    segments.push_back( segment_filler );

  }

  same_chirality_far_muon::~same_chirality_far_muon()
  {

    // does nothing.

  }


  opposite_chirality_far_muon::opposite_chirality_far_muon(
                                 CppSLHA::CppSLHA0 const* const given_spectrum,
                    CppSLHA::particle_property_set const* const first_particle,
                                             double const effective_first_mass,
                   CppSLHA::particle_property_set const* const second_particle,
                    CppSLHA::particle_property_set const* const third_particle,
                CppSLHA::particle_property_set const* const fourth_particle ) :
    lepton_energy_distribution( given_spectrum,
                                effective_first_mass,
                                second_particle->get_absolute_mass(),
                                third_particle->get_absolute_mass(),
                                fourth_particle->get_absolute_mass() )
  {

    double mq = first_mass;
    double mqSq = ( mq * mq );
    double mNSq = ( second_mass * second_mass );
    double mlSq = ( third_mass * third_mass );
    double mXSq = ( fourth_mass * fourth_mass );

    production_frame_energy = ( ( mlSq - mXSq ) / ( 2.0 * third_mass ) );

    minimum_energy = ( ( third_mass / first_mass ) * production_frame_energy );

    double Elk;
    double Ehk;

    // there are 2 kinematic cases for determining the kink energies in terms
    // of the cascade masses.
    if( ( first_mass / second_mass ) > ( second_mass / third_mass ) )
      {

        Elk = ( ( ( second_mass / first_mass ) * ( second_mass / third_mass ) )
                * production_frame_energy );

        Ehk = ( ( ( first_mass / second_mass ) * ( third_mass / second_mass ) )
                * production_frame_energy );

      }
    else
      {

        Elk = ( ( ( first_mass / second_mass ) * ( third_mass / second_mass ) )
                * production_frame_energy );

        Ehk = ( ( ( second_mass / first_mass ) * ( second_mass / third_mass ) )
                * production_frame_energy );

      }


    maximum_energy = ( ( first_mass / third_mass ) * production_frame_energy );


    // now we set up the coefficients of various terms, & use them to determine
    // the normalization.

    MINtoLK_lin
    = ( ( 4.0 * mlSq * mNSq * mq )
        / ( ( mNSq - mlSq ) * ( mNSq + mqSq ) * ( mlSq - mXSq ) ) );

    MINtoLK_log = ( ( 2.0 * ( mNSq * mNSq - mlSq * mqSq ) )
                    / ( ( mNSq - mlSq ) * ( mNSq + mqSq ) ) );

    MINtoLK_const
    = ( ( 2.0 * ( mNSq * ( 2.0 * mNSq - mqSq + mlSq )
                  + ( mlSq * mqSq - mNSq * mNSq )
                    * log( ( ( 2.0 * mq ) / ( mlSq - mXSq ) ) ) ) )
        / ( ( mlSq - mNSq ) * ( mNSq + mqSq ) ) );

    MINtoLK_inv = ( ( mNSq * ( ( 2.0 * mNSq - mqSq ) * ( mlSq - mXSq ) ) )
        / ( mq * ( mNSq - mlSq ) * ( mNSq + mqSq ) ) );

    // there are 2 kinematic cases for determining the kink energies in terms of the cascade masses.
    if( ( first_mass / second_mass ) < ( second_mass / third_mass ) )
      // if the assumption that the mass spectrum was SPS1a-like was
      // incorrect...
      {

        LKtoHK_const
        = ( ( 2.0 * ( ( mlSq + mNSq ) * ( mNSq - mqSq )
                      + ( mNSq * mNSq - mlSq * mqSq )
                        * log( ( mNSq / mqSq ) ) ) )
            / ( ( mlSq - mNSq ) * ( mNSq + mqSq ) ) );

        LKtoHK_inv = ( ( 2.0 * mNSq * ( mNSq - mqSq ) * ( mlSq - mXSq ) )
                       / ( mq * ( mNSq - mlSq ) * ( mNSq + mqSq ) ) );

      }
    else
      {

        LKtoHK_const = ( ( 2.0 * ( ( mqSq - mNSq ) * ( mlSq - mNSq )
                           + ( mNSq * mNSq - mlSq * mqSq )
                             * log( ( mlSq / mNSq ) ) ) )
                         / ( ( mlSq - mNSq ) * ( mNSq + mqSq ) ) );

        LKtoHK_inv = 0.0;

      }

    HKtoMAX_lin = -MINtoLK_lin;

    HKtoMAX_log = -MINtoLK_log;

    HKtoMAX_const
    = ( ( 2.0 * ( ( mNSq * mNSq - mlSq * mqSq )
                  * log( ( ( 2.0 * mlSq ) / ( ( mlSq - mXSq ) * mq ) ) )
                  - mNSq * ( mqSq + mlSq ) ) )
        / ( ( mlSq - mNSq ) * ( mNSq + mqSq ) ) );

    HKtoMAX_inv = ( ( mNSq * mq * ( mlSq - mXSq ) )
                    / ( ( mlSq - mNSq ) * ( mNSq + mqSq ) ) );


    normalization
    = ( MINtoLK_lin * 0.5 * ( Elk * Elk - minimum_energy * minimum_energy )
        + MINtoLK_log * ( Elk * ( log( Elk ) - 1.0 )
                          - minimum_energy * ( log( minimum_energy ) - 1.0 ) )
        + MINtoLK_const * ( Elk - minimum_energy )
        + MINtoLK_inv * log( ( Elk / minimum_energy ) )
        + LKtoHK_const * ( Ehk - Elk )
        + LKtoHK_inv * log( ( Ehk / Elk ) )
        + HKtoMAX_lin * 0.5 * ( maximum_energy * maximum_energy - Ehk * Ehk )
        + HKtoMAX_log * ( maximum_energy * ( log( maximum_energy ) - 1.0 )
                          - Ehk * ( log( Ehk ) - 1.0 ) )
        + HKtoMAX_const * ( maximum_energy - Ehk )
        + HKtoMAX_inv * log( ( maximum_energy / Ehk ) ) );


    // debugging:
    /**std::cout
    << std::endl
    << "debugging: lepton_distribution_opposite_chirality_far_muon:";
    std::cout << std::endl << "normalization = " << normalization;
    std::cout << std::endl << "minimum_energy = " << minimum_energy;
    std::cout << std::endl << "Elk = " << Elk;
    std::cout << std::endl << "Ehk = " << Ehk;
    std::cout << std::endl << "maximum_energy = " << maximum_energy;
    std::cout << std::endl << "LKtoHK_const = " << LKtoHK_const;
    std::cout << std::endl
    << "log( ( mlSq / mNSq ) ) = " << log( ( mlSq / mNSq ) );
    std::cout << std::endl
    << "( 2.0 / ( ( mlSq - mNSq ) * ( mNSq + mqSq ) ) ) = "
    << ( 2.0 / ( ( mlSq - mNSq ) * ( mNSq + mqSq ) ) );
    std::cout << std::endl
    << "( ( mqSq - mNSq ) * ( mlSq - mNSq ) "
    << "+ ( mNSq * mNSq - mlSq * mqSq ) * log( ( mlSq / mNSq ) ) ) = "
    << ( ( mqSq - mNSq ) * ( mlSq - mNSq )
         + ( mNSq * mNSq - mlSq * mqSq ) * log( ( mlSq / mNSq ) ) );
    std::cout << std::endl;**/


    // finally we fill the sets of terms, segment by segment:

    // MIN to LK segment:
    segment_term_set* segment_filler = new segment_term_set( minimum_energy,
                                                             Elk );

    // linear term:
    lepton_distribution_expansion_term*
    term_filler = new lepton_distribution_expansion_term( 1,
                                                          0,
                                             ( MINtoLK_lin / normalization ) );
    segment_filler->add_term( term_filler );

    // logarithm term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          1,
                                             ( MINtoLK_log / normalization ) );
    segment_filler->add_term( term_filler );

    // constant term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          0,
                                           ( MINtoLK_const / normalization ) );
    segment_filler->add_term( term_filler );

    // inverse term:
    term_filler = new lepton_distribution_expansion_term( -1,
                                                          0,
                                             ( MINtoLK_inv / normalization ) );
    segment_filler->add_term( term_filler );


    // record the segment:
    segments.push_back( segment_filler );


    // LK to HK segment:
    segment_filler = new segment_term_set( Elk,
                                           Ehk );

    // constant term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          0,
                                            ( LKtoHK_const / normalization ) );
    segment_filler->add_term( term_filler );

    // inverse term:
    term_filler = new lepton_distribution_expansion_term( -1,
                                                          0,
                                              ( LKtoHK_inv / normalization ) );
    segment_filler->add_term( term_filler );


    // record the segment
    segments.push_back( segment_filler );


    // HK to MAX segment:
    segment_filler = new segment_term_set( Ehk,
                                           maximum_energy );

    // linear term:
    term_filler = new lepton_distribution_expansion_term( 1,
                                                          0,
                                             ( HKtoMAX_lin / normalization ) );
    segment_filler->add_term( term_filler );

    // logarithm term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          1,
                                             ( HKtoMAX_log / normalization ) );
    segment_filler->add_term( term_filler );

    // constant term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          0,
                                           ( HKtoMAX_const / normalization ) );
    segment_filler->add_term( term_filler );

    // inverse term:
    term_filler = new lepton_distribution_expansion_term( -1,
                                                          0,
                                             ( HKtoMAX_inv / normalization ) );
    segment_filler->add_term( term_filler );


    // record the segment:
    segments.push_back( segment_filler );

  }

  opposite_chirality_far_muon::~opposite_chirality_far_muon()
  {

    // does nothing.

  }


  Higgs_muon_plus_antimuon::Higgs_muon_plus_antimuon(
                                 CppSLHA::CppSLHA0 const* const given_spectrum,
                    CppSLHA::particle_property_set const* const first_particle,
                                             double const effective_first_mass,
                   CppSLHA::particle_property_set const* const second_particle,
                    CppSLHA::particle_property_set const* const third_particle,
                CppSLHA::particle_property_set const* const fourth_particle ) :
     lepton_energy_distribution( given_spectrum,
                                 effective_first_mass,
                                 second_particle->get_absolute_mass(),
                                 third_particle->get_absolute_mass(),
                                 fourth_particle->get_absolute_mass() )
  {

    double mq = first_mass;
    double mN = second_mass;
    double mNSq = ( mN * mN );
    double mH = third_mass;
    double mHSq = ( mH * mH );
    double mX = fourth_mass;
    double mXSq = ( mX * mX );

    production_frame_energy = ( 0.5 * mH );

    double EHN = ( ( mNSq + mHSq - mXSq ) / ( 2.0 * mN ) );
    double gammaNH = ( EHN / mH );
    double betaNH = sqrt( ( 1.0 - ( 1.0 / ( gammaNH * gammaNH ) ) ) );
    double EmaxN = ( gammaNH * ( 1.0 + betaNH ) * production_frame_energy );
    double EminN = ( mHSq / ( 4.0 * EmaxN ) );
    // using ( EmaxN * EminN ) = ( mHSq / 4 )

    minimum_energy = ( ( mN / mq ) * EminN );

    double Elk;
    double Ehk;


    // there are 2 kinematic cases for determining the kink energies in terms
    // of the cascade masses:

    // 1st make an assumption:
    Elk = ( ( mN / mq ) * EmaxN );
    Ehk = ( ( mq / mN ) * EminN );

    // then check:
    if( Elk > Ehk )
      {

        Elk = Ehk;

        Ehk = ( ( mN / mq ) * EmaxN );

      }

    maximum_energy = ( ( mq / mN ) * EmaxN );


    // now we set up the coefficients of various terms, & use them to determine
    // the normalization:

    MINtoLK_const = -log( minimum_energy );
    MINtoLK_log = 1.0;

    LKtoHK_const = log( ( maximum_energy / Ehk ) );

    HKtoMAX_const = log( maximum_energy );
    HKtoMAX_log = -1.0;

    normalization
    = ( MINtoLK_const * ( Elk - minimum_energy )
        + MINtoLK_log * ( Elk * ( log( Elk ) - 1.0 )
                          - minimum_energy * ( log( minimum_energy ) - 1.0 ) )
        + LKtoHK_const * ( Ehk - Elk )
        + HKtoMAX_const * ( maximum_energy - Ehk )
        + HKtoMAX_log * ( maximum_energy * ( log( maximum_energy ) - 1.0 )
                          - Ehk * ( log( Ehk ) - 1.0 ) ) );

    // debugging:
    /**std::cout
    << std::endl
    << "debugging: lepton_distribution_Higgs_muon_plus_antimuon_distribution:";
    std::cout << std::endl << "normalization = " << normalization;
    std::cout << std::endl << "minimum_energy = " << minimum_energy;
    std::cout << std::endl << "Elk = " << Elk;
    std::cout << std::endl << "Ehk = " << Ehk;
    std::cout << std::endl << "maximum_energy = " << maximum_energy;
    std::cout << std::endl << "MINtoLK_log = " << MINtoLK_log;
    std::cout << std::endl << "MINtoLK_const = " << MINtoLK_const;
    std::cout << std::endl << "LKtoHK_const = " << LKtoHK_const;
    std::cout << std::endl;**/


    // finally we fill the sets of terms, segment by segment:

    // MIN to LK segment:
    segment_term_set* segment_filler = new segment_term_set( minimum_energy,
                                                             Elk );

    // logarithm term:
    lepton_distribution_expansion_term*
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          1,
                                             ( MINtoLK_log / normalization ) );
    segment_filler->add_term( term_filler );

    // constant term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          0,
                                           ( MINtoLK_const / normalization ) );
    segment_filler->add_term( term_filler );


    // record the segment:
    segments.push_back( segment_filler );


    // LK to HK segment:
    segment_filler = new segment_term_set( Elk,
                                           Ehk );

    // constant term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          0,
                                            ( LKtoHK_const / normalization ) );
    segment_filler->add_term( term_filler );


    // record the segment:
    segments.push_back( segment_filler );


    // HK to MAX segment:
    segment_filler = new segment_term_set( Ehk,
                                           maximum_energy );

    // logarithm term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          1,
                                             ( HKtoMAX_log / normalization ) );
    segment_filler->add_term( term_filler );

    // constant term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          0,
                                           ( HKtoMAX_const / normalization ) );
    segment_filler->add_term( term_filler );


    // record the segment:
    segments.push_back( segment_filler );

  }

  Higgs_muon_plus_antimuon::~Higgs_muon_plus_antimuon()
  {

    // does nothing.

  }


  Z_muon_plus_antimuon::Z_muon_plus_antimuon(
                                 CppSLHA::CppSLHA0 const* const given_spectrum,
                    CppSLHA::particle_property_set const* const first_particle,
                                             double const effective_first_mass,
                   CppSLHA::particle_property_set const* const second_particle,
                    CppSLHA::particle_property_set const* const third_particle,
                CppSLHA::particle_property_set const* const fourth_particle ) :
    lepton_energy_distribution( given_spectrum,
                                effective_first_mass,
                                second_particle->get_absolute_mass(),
                                third_particle->get_absolute_mass(),
                                fourth_particle->get_absolute_mass() )
  {

    /* it doesn't matter if the neutralino mass is negative, since only the
     * absolute square appears, & the couplings are only affected by it as an
     * overall phase.  I (BOL) assume no CP violation, so the neutralino mixing
     * matrices are strictly real.
     */
    double real_part_of_square_coupling;

    if( ( ( 0.0 < second_particle->get_mass() )
          &&
          ( 0.0 > fourth_particle->get_mass() ) )
        ||
        ( ( 0.0 < second_particle->get_mass() )
          &&
          ( 0.0 > fourth_particle->get_mass() ) ) )
      // if the relative phases end up such that the product of couplings is
      // purely imaginary...
      {

        real_part_of_square_coupling = 0.0;

      }
    else
      {

        real_part_of_square_coupling = 1.0;
        // this is relative to the strength of the square of the absolute
        // value of the coupling.

      }

    double mq = first_mass;
    double mqSq = ( mq * mq );
    double mN = second_mass;
    double mNSq = ( mN * mN );
    double mZ = third_mass;
    double mZSq = ( mZ * mZ );
    double mX = fourth_mass;
    double mXSq = ( mX * mX );

    production_frame_energy = ( 0.5 * mZ );

    double EZN = ( ( mNSq + mZSq - mXSq ) / ( 2.0 * mN ) );
    double gammaNZ = ( EZN / mZ );
    double betaNZ = sqrt( ( 1.0 - ( 1.0 / ( gammaNZ * gammaNZ ) ) ) );
    double EmaxN = ( gammaNZ * ( 1.0 + betaNZ ) * production_frame_energy );
    double EminN = ( mZSq / ( 4.0 * EmaxN ) );
    // using ( EmaxN * EminN ) = ( mZSq / 4 )

    minimum_energy = ( ( mN / mq ) * EminN );

    double Elk;
    double Ehk;

    // there are 2 kinematic cases for determining the kink energies in terms
    // of the cascade masses:

    // 1st assume that boost_angle_energy_limited_between_kinks == true for
    // this spectrum:
    bool boost_angle_energy_limited_between_kinks = true;
    Elk = ( ( mN / mq ) * EmaxN );
    Ehk = ( ( mq / mN ) * EminN );

    // then check:
    if( Elk > Ehk )
      {

        boost_angle_energy_limited_between_kinks = false;

        Elk = Ehk;

        Ehk = ( ( mN / mq ) * EmaxN );

      }

    maximum_energy = ( ( mq / mN ) * EmaxN );


    // now we set up the coefficients of various terms, & use them to determine
    // the normalization:

    MINtoLK_sq = ( ( -4.0 * mqSq ) / mN );

    MINtoLK_lin = ( 8.0 * EZN * mq );

    MINtoLK_log = ( 2.0 * mZSq * ( real_part_of_square_coupling * mX - EZN ) );

    MINtoLK_const
    = ( 2.0 * ( 2.0 * mN * EminN * ( EminN - 2.0 * EZN )
        + mZSq * ( real_part_of_square_coupling * mX - EZN )
          * log( ( mq / ( EminN * mN ) ) ) ) );

    // there are 2 kinematic cases for determining the kink energies in terms
    // of the cascade masses:
    if( boost_angle_energy_limited_between_kinks )
      /* if the assumption that the mass spectrum was such that the boost from
       * the squark frame to the neutralino frame is greater than that from the
       * neutralino frame to the Z frame was correct...
       */
      {

        LKtoHK_sq = 0.0;

        LKtoHK_lin = 0.0;

        LKtoHK_const
        = ( 2.0 * ( 2.0 * mN * ( 2.0 * EZN - EmaxN - EminN )
                             * ( EmaxN - EminN )
            + mZSq * ( real_part_of_square_coupling * mX - EZN )
              * log( ( EmaxN / EminN ) ) ) );

      }
    else
      {

        LKtoHK_sq
        = ( ( 4.0 * ( mNSq * mNSq - mqSq * mqSq ) ) / ( mN * mqSq ) );

        LKtoHK_lin = ( ( 8.0 * EZN * ( mqSq - mNSq ) ) / mq );

        LKtoHK_const
        = ( 4.0 * mZSq * ( real_part_of_square_coupling * mX - EZN )
                       * log( ( mq / mN ) ) );

      }

    HKtoMAX_sq = ( ( 4.0 * mN * mNSq ) / mqSq );

    HKtoMAX_lin = ( ( -8.0 * EZN * mNSq ) / mq );

    HKtoMAX_log = -MINtoLK_log;

    HKtoMAX_const
    = ( 2.0 * ( 2.0 * mN * EmaxN * ( 2.0 * EZN - EmaxN )
                + mZSq * ( real_part_of_square_coupling * mX - EZN )
                       * log( ( ( mq * EmaxN ) / mN ) ) ) );


    normalization
    = ( MINtoLK_sq
        * ( ( Elk * Elk * Elk
              - minimum_energy * minimum_energy * minimum_energy ) / 3.0 )
        + MINtoLK_lin * 0.5 * ( Elk * Elk - minimum_energy * minimum_energy )
        + MINtoLK_log * ( Elk * ( log( Elk ) - 1.0 )
                          - minimum_energy * ( log( minimum_energy ) - 1.0 ) )
        + MINtoLK_const * ( Elk - minimum_energy )
        + LKtoHK_sq * ( ( Ehk * Ehk * Ehk - Elk * Elk * Elk ) / 3.0 )
        + LKtoHK_lin * 0.5 * ( Ehk * Ehk - Elk * Elk )
        + LKtoHK_const * ( Ehk - Elk )
        + HKtoMAX_sq * ( ( maximum_energy * maximum_energy * maximum_energy
                           - Ehk * Ehk * Ehk ) / 3.0 )
        + HKtoMAX_lin * 0.5 * ( maximum_energy * maximum_energy - Ehk * Ehk )
        + HKtoMAX_log * ( maximum_energy * ( log( maximum_energy ) - 1.0 )
                          - Ehk * ( log( Ehk ) - 1.0 ) )
        + HKtoMAX_const * ( maximum_energy - Ehk ) );


    // debugging:
    /**std::cout
    << std::endl
    << "debugging: lepton_distribution_same_chirality_far_muon:";
    std::cout << std::endl << "normalization = " << normalization;
    std::cout << std::endl << "minimum_energy = " << minimum_energy;
    std::cout << std::endl << "Elk = " << Elk;
    std::cout << std::endl << "Ehk = " << Ehk;
    std::cout << std::endl << "maximum_energy = " << maximum_energy;
    std::cout << std::endl << "MINtoLK_lin = " << MINtoLK_lin;
    std::cout << std::endl << "MINtoLK_log = " << MINtoLK_log;
    std::cout << std::endl << "MINtoLK_const = " << MINtoLK_const;
    std::cout << std::endl << "MINtoLK_inv = " << MINtoLK_inv;
    std::cout << std::endl << "LKtoHK_const = " << LKtoHK_const;
    std::cout << std::endl << "LKtoHK_inv = " << LKtoHK_inv;
    std::cout << std::endl;**/


    // finally we fill the sets of terms, segment by segment:

    // MIN to LK segment:
    segment_term_set* segment_filler = new segment_term_set( minimum_energy,
                                                             Elk );

    // square term:
    lepton_distribution_expansion_term*
    term_filler = new lepton_distribution_expansion_term( 2,
                                                          0,
                                              ( MINtoLK_sq / normalization ) );
    segment_filler->add_term( term_filler );

    // linear term:
    term_filler = new lepton_distribution_expansion_term( 1,
                                                          0,
                                             ( MINtoLK_lin / normalization ) );
    segment_filler->add_term( term_filler );

    // logarithm term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          1,
                                             ( MINtoLK_log / normalization ) );
    segment_filler->add_term( term_filler );

    // constant term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          0,
                                           ( MINtoLK_const / normalization ) );
    segment_filler->add_term( term_filler );


    // record the segment:
    segments.push_back( segment_filler );


    // LK to HK segment:
    segment_filler = new segment_term_set( Elk,
                                           Ehk );

    // square term:
    term_filler = new lepton_distribution_expansion_term( 2,
                                                          0,
                                               ( LKtoHK_sq / normalization ) );
    segment_filler->add_term( term_filler );

    // linear term:
    term_filler = new lepton_distribution_expansion_term( 1,
                                                          0,
                                              ( LKtoHK_lin / normalization ) );
    segment_filler->add_term( term_filler );

    // constant term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          0,
                                            ( LKtoHK_const / normalization ) );
    segment_filler->add_term( term_filler );


    // record the segment:
    segments.push_back( segment_filler );


    // HK to MAX segment:
    segment_filler = new segment_term_set( Ehk,
                                           maximum_energy );

    // square term:
    term_filler = new lepton_distribution_expansion_term( 2,
                                                          0,
                                              ( HKtoMAX_sq / normalization ) );
    segment_filler->add_term( term_filler );

    // linear term:
    term_filler = new lepton_distribution_expansion_term( 1,
                                                          0,
                                             ( HKtoMAX_lin / normalization ) );
    segment_filler->add_term( term_filler );

    // logarithm term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          1,
                                             ( HKtoMAX_log / normalization ) );
    segment_filler->add_term( term_filler );

    // constant term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          0,
                                           ( HKtoMAX_const / normalization ) );
    segment_filler->add_term( term_filler );


    // record the segment:
    segments.push_back( segment_filler );

  }

  Z_muon_plus_antimuon::~Z_muon_plus_antimuon()
  {

    // does nothing.

  }


  W_minus_plus_up_L_type_muon::W_minus_plus_up_L_type_muon(
                                 CppSLHA::CppSLHA0 const* const given_spectrum,
                    CppSLHA::particle_property_set const* const first_particle,
                                             double const effective_first_mass,
                   CppSLHA::particle_property_set const* const second_particle,
                    CppSLHA::particle_property_set const* const third_particle,
                CppSLHA::particle_property_set const* const fourth_particle ) :
    lepton_energy_distribution( given_spectrum,
                                effective_first_mass,
                                second_particle->get_absolute_mass(),
                                third_particle->get_absolute_mass(),
                                fourth_particle->get_absolute_mass() )
  {

    // debugging:
    /**std::cout
    << std::endl
    << "W_minus_plus_up_L_type_muon::W_minus_plus_up_L_type_muon( "
    << given_spectrum << ", " << *(first_particle->get_name()) << ", "
    << effective_first_mass << ", " << *(second_particle->get_name()) << ", "
    << *(third_particle->get_name()) << ", " << *(fourth_particle->get_name())
    << " ) called.";
    std::cout << std::endl;**/

    int which_chargino;
    int which_neutralino;

    if( CppSLHA::PDG_code::chargino_one == second_particle->get_PDG_code() )
      {

        which_chargino = 1;

      }
    else if( CppSLHA::PDG_code::chargino_two
             == second_particle->get_PDG_code() )
      {

        which_chargino = 2;

      }
    else
      {

        which_chargino = -1;
        // this will cause UMIX or VMIX to return NaN, which should show the
        // result up as obviously wrong.

        std::cout
        << std::endl
        << "LHC-FASER::error! W_minus_plus_up_L_type_muon expected to be given"
        << " a chargino as its 2nd particle, but did not receive a particle"
        << " with code +-" << CppSLHA::PDG_code::chargino_one << " or +-"
        << CppSLHA::PDG_code::chargino_two << ", rather, it received "
        << second_particle->get_name() << " (code: "
        << second_particle->get_PDG_code() << ")";
        std::cout << std::endl;

      }


    if( CppSLHA::PDG_code::neutralino_one == fourth_particle->get_PDG_code() )
      {

        which_neutralino = 1;

      }
    else if( CppSLHA::PDG_code::neutralino_two
             == fourth_particle->get_PDG_code() )
      {

        which_neutralino = 2;

      }
    else if( CppSLHA::PDG_code::neutralino_three
             == fourth_particle->get_PDG_code() )
      {

        which_neutralino = 3;

      }
    else if( CppSLHA::PDG_code::neutralino_four
             == fourth_particle->get_PDG_code() )
      {

        which_neutralino = 4;

      }
    else
      {

        which_neutralino = -1;
        // this will cause NMIX to return NaN, which should show the result up
        // as obviously wrong.

        std::cout
        << std::endl
        << "LHC-FASER::error! W_minus_plus_up_L_type_muon expected to be given"
        << " a neutralino as its 4th particle, but did not receive a particle"
        << " with code " << CppSLHA::PDG_code::neutralino_one << ", "
        << CppSLHA::PDG_code::neutralino_two << ", "
        << CppSLHA::PDG_code::neutralino_three << ", or "
        << CppSLHA::PDG_code::neutralino_four << ", rather, it received "
        << fourth_particle->get_name() << " (code: "
        << fourth_particle->get_PDG_code() << ")";
        std::cout << std::endl;

      }

    CppSLHA::SLHA_BLOCK const* NMIX = spectrum_data->inspect_BLOCK( "NMIX" );
    CppSLHA::SLHA_BLOCK const* UMIX = spectrum_data->inspect_BLOCK( "UMIX" );
    CppSLHA::SLHA_BLOCK const* VMIX = spectrum_data->inspect_BLOCK( "VMIX" );

    // debugging:
    /**std::cout
    << std::endl
    << "debugging:";
    std::cout
    << std::endl
    << "NMIX = " << NMIX
    << std::endl
    << "UMIX = " << UMIX
    << std::endl
    << "VMIX = " << VMIX;
    std::cout << std::endl;
    std::cout << std::endl
    << "Z2iN = " << NMIX->get_entry( which_neutralino,
                                     2 );
    std::cout << std::endl
    << "Z1jplus = " << VMIX->get_entry( which_chargino,
                                        1 );
    std::cout << std::endl
    << "Z4iN = " << NMIX->get_entry( which_neutralino,
                                     4 );
    std::cout << std::endl
    << "Z2jplus = " << VMIX->get_entry( which_chargino,
                                        2 );
    std::cout << std::endl
    << "Z1jminus = " << UMIX->get_entry( which_chargino,
                                         1 );
    std::cout << std::endl
    << "Z3iN = " << NMIX->get_entry( which_neutralino,
                                     3 );
    std::cout << std::endl
    << "Z2jminus = " << UMIX->get_entry( which_chargino,
                                         2 );
    std::cout << std::endl;**/


    /* it doesn't matter if the neutralino mass is negative, since only the
     * absolute square appears, & the couplings are only affected by it as an
     * overall phase.  I (BOL) assume no CP violation, so the chargino mixing
     * matrices are strictly real.
     */
    double
    temporary_unsquared_coupling
    = ( NMIX->get_entry( which_neutralino,
                         2 ) * VMIX->get_entry( which_chargino,
                                                1 )
        - M_SQRT1_2 * NMIX->get_entry( which_neutralino,
                                       4 ) * VMIX->get_entry( which_chargino,
                                                              2 ) );
    // by the way, M_SQRT1_2 is 1 over the square root of 2, defined in math.h.
    double
    aCWXSq = ( temporary_unsquared_coupling * temporary_unsquared_coupling );
    // Z2iN * Z1jplus - ( 1 / sqrt2 ) * Z4iN * Z2jplus.
    double twice_real_part_of_a_conjugate_times_b
    = temporary_unsquared_coupling;  // take the 1st part...
    temporary_unsquared_coupling
    = ( NMIX->get_entry( which_neutralino,
                         2 ) * UMIX->get_entry( which_chargino,
                                                1 )
        + M_SQRT1_2 * NMIX->get_entry( which_neutralino,
                                       3 ) * UMIX->get_entry( which_chargino,
                                                              2 ) );
    double
    bCWXSq = ( temporary_unsquared_coupling * temporary_unsquared_coupling );
    // Z2iN * Z1jminus + ( 1 / sqrt2 ) * Z3iN * Z2jminus
    twice_real_part_of_a_conjugate_times_b
    *= ( 2.0 * temporary_unsquared_coupling );
    // assume that the product of couplings is real, since we have calculated
    // it already, then check to see if it should be set to zero:
    if( ( ( 0.0 < second_particle->get_mass() )
        &&
        ( 0.0 > fourth_particle->get_mass() ) )
        ||
        ( ( 0.0 > second_particle->get_mass() )
            &&
            ( 0.0 < fourth_particle->get_mass() ) ) )
      // if the relative phases end up such that the product of couplings is
      // purely imaginary...
      {

        twice_real_part_of_a_conjugate_times_b = 0.0;

      }

    double mq = first_mass;
    double mqSq = ( mq * mq );
    double mC = second_mass;
    double mCSq = ( mC * mC );
    double mW = third_mass;
    double mWSq = ( mW * mW );
    double mX = fourth_mass;
    double mXSq = ( mX * mX );

    production_frame_energy = ( 0.5 * mW );

    double EWC = ( ( mCSq + mWSq - mXSq ) / ( 2.0 * mC ) );
    double gammaCW = ( EWC / mW );
    double betaCW = sqrt( ( 1.0 - ( 1.0 / ( gammaCW * gammaCW ) ) ) );
    double EmaxC = ( gammaCW * ( 1.0 + betaCW ) * production_frame_energy );
    double EmaxCSq = ( EmaxC * EmaxC );
    double EminC = ( mWSq / ( 4.0 * EmaxC ) );
    // using ( EmaxC * EminC ) = ( mWSq / 4 )
    double EminCSq = ( EminC * EminC );

    minimum_energy = ( ( mC / mq ) * EminC );

    double Elk;
    double Ehk;

    // there are 2 kinematic cases for determining the kink energies in terms
    // of the cascade masses:

    // 1st assume that boost_angle_energy_limited_between_kinks == true for
    // this spectrum:
    bool boost_angle_energy_limited_between_kinks = true;
    Elk = ( ( mC / mq ) * EmaxC );
    Ehk = ( ( mq / mC ) * EminC );

    // then check:
    if( Elk > Ehk )
      {

        boost_angle_energy_limited_between_kinks = false;

        Elk = Ehk;

        Ehk = ( ( mC / mq ) * EmaxC );

      }

    maximum_energy = ( ( mq / mC ) * EmaxC );



    // now we set up the coefficients of various terms, & use them to determine
    // the normalization:

    double log_EminC_mC_over_mq = log( ( ( EminC * mC ) / mq ) );

    MINtoLK_sq
    = ( ( 2.0 * mqSq * ( ( aCWXSq - 2.0 * bCWXSq ) * mCSq
                           + bCWXSq * mqSq ) ) / ( mC * ( mCSq - mqSq ) ) );

    MINtoLK_linlog
    = ( ( 2.0 * mC * mq * ( ( bCWXSq - aCWXSq ) * ( mCSq + mWSq - mXSq )
                            + ( aCWXSq + bCWXSq ) * mWSq ) )
        / ( mCSq - mqSq ) );

    MINtoLK_lin
    = ( ( mq * ( 4.0 * aCWXSq * EminCSq * ( 2.0 * ( EminC - EWC ) * mC * mCSq
                                            - ( mCSq - 2.0 * mqSq ) * mWSq )
                 + bCWXSq * ( 4.0 * EminCSq * mqSq * ( mCSq + 2.0 * mWSq
                                                            - mXSq )
                             - 8.0 * EminCSq * EminC * mC * mCSq
                             - mCSq * mWSq * mWSq
                             + 4.0 * EminC * mCSq
                               * ( EWC * ( 2.0 * mCSq + mWSq )
                                   + mC * ( mXSq - mCSq ) ) )
                 - 2.0 * EminC * mCSq * mX * mWSq
                   * twice_real_part_of_a_conjugate_times_b
                 - 4.0 * EminCSq * mCSq
                   * ( ( aCWXSq - bCWXSq ) * ( mCSq + mWSq - mXSq )
                 - ( aCWXSq + bCWXSq ) * mWSq ) * log_EminC_mC_over_mq ) )
        / ( 2.0 * EminCSq * mC * ( mqSq - mCSq ) ) );

    MINtoLK_log
    = ( ( bCWXSq * ( 2.0 * EWC * ( mCSq * ( mCSq + mqSq ) + mqSq * mWSq )
                     - mC * ( mCSq + mqSq ) * (mCSq - mXSq) )
          - mWSq * ( 2.0 * aCWXSq * EWC * ( mCSq - mqSq )
                     + mqSq * mX * twice_real_part_of_a_conjugate_times_b ) )
        / ( mCSq - mqSq ) );

    MINtoLK_const
    = ( ( 4.0 * aCWXSq * EminCSq
          * ( ( EminC - 2.0 * EWC ) * mC * mCSq
              - ( mCSq - 2.0 * mqSq ) * mWSq )
          + bCWXSq * ( 4.0 * EminCSq * mqSq * ( mCSq + 2.0 * mWSq - mXSq )
                      - 4.0 * EminCSq * EminC * mC * mqSq
                      - ( mCSq + mqSq ) * mWSq * mWSq
                      + 4.0 * EminC * mCSq
                        * ( EWC * ( 2.0 * mCSq + mWSq )
                            + mC * ( mXSq - mCSq ) ) )
          - 2.0 * twice_real_part_of_a_conjugate_times_b
            * EminC * mCSq * mX * mWSq
          - 2.0 * EminC * ( bCWXSq * ( 2.0 * EWC * ( mCSq * ( mCSq + mqSq )
                                                     + mqSq * mWSq )
                                       - mC * ( mCSq + mqSq )
                                            * ( mCSq - mXSq ) )
                            - mWSq * ( 2.0 * aCWXSq * EWC * ( mCSq - mqSq )
                            + mqSq * mX
                              * twice_real_part_of_a_conjugate_times_b ) )
                        * log_EminC_mC_over_mq )
        / ( 2.0 * EminC * ( mCSq - mqSq ) ) );

    MINtoLK_inv
    = ( ( bCWXSq * mC * mq * mWSq * mWSq ) / ( 2.0 * ( mCSq - mqSq ) ) );

    // there are 2 kinematic cases for determining the kink energies in terms
    // of the cascade masses:
    if( boost_angle_energy_limited_between_kinks )
      /* if the assumption that the mass spectrum was such that the boost from
       * the squark frame to the chargino frame is greater than that from the
       * chargino frame to the W frame was correct...
       */
      {

        double log_twice_EmaxC_over_mW = log( ( ( 2.0 * EmaxC ) / mW ) );

        LKtoHK_sq = 0.0;

        LKtoHK_lin
        = ( ( 2.0 * twice_real_part_of_a_conjugate_times_b
                  * EmaxC * mC * mq * ( 4.0 * EmaxCSq - mWSq ) * mX * mWSq
              + bCWXSq * ( mC * mq * ( 4.0 * EmaxCSq - mWSq )
                           * ( ( 4.0 * EmaxCSq + mWSq ) * mWSq
                               - 2.0 * EmaxC
                                 * ( 2.0 * EWC * ( 2.0 * mCSq + mWSq )
                                     + mC
                                       * ( mWSq - 2.0 * mCSq + 2.0 * mXSq ) ) )
                           + 2.0 * EmaxCSq * mWSq
                             * ( 4.0 * mC * mq * ( mCSq + 2.0 * mWSq - mXSq )
                                   * log_twice_EmaxC_over_mW ) )
              + aCWXSq * mC * mq * 2.0 * EmaxC * mWSq
                * ( mC * ( 4.0 * EmaxCSq - mWSq )
                    + 4.0 * EmaxC * ( mXSq - mCSq )
                      * log_twice_EmaxC_over_mW ) )
            / ( 2.0 * EmaxCSq * ( mCSq - mqSq ) * mWSq ) );

        LKtoHK_const
        = ( ( aCWXSq * ( ( mWSq - 4.0 * EmaxCSq )
                         * ( 4.0 * EmaxC * ( EmaxC - 2.0 * EWC ) * mC * mCSq
                             + ( mC * mCSq - 4.0 * EmaxC * mCSq
                                 + 8.0 * EmaxC * mqSq ) * mWSq )
                         + 32.0 * EmaxCSq * EWC * ( mqSq - mCSq ) * mWSq
                           * log_twice_EmaxC_over_mW )
            - 16.0 * twice_real_part_of_a_conjugate_times_b
              * EmaxCSq * mqSq * mWSq * mX * log_twice_EmaxC_over_mW
            + bCWXSq * ( ( ( 4.0 * EmaxCSq - mWSq )
                           * ( 4.0 * EmaxCSq * mC * mqSq + mC * mqSq * mWSq
                               - 4.0 * EmaxC
                                 * ( ( mCSq + mWSq - mXSq )
                                     * ( mCSq + 2.0 * mqSq )
                                     - mCSq * mCSq + mCSq * ( mXSq - mqSq )
                                     + mqSq * ( mWSq + mXSq ) ) ) )
                          + 16.0 * EmaxCSq
                            * ( 2.0 * EWC * ( mCSq * ( mCSq + mqSq )
                                              + mqSq * mWSq )
                                - mC * ( ( mCSq + mqSq) * ( mCSq - mXSq ) ) )
                            * log_twice_EmaxC_over_mW ) )
            / ( 8.0 * EmaxCSq * ( mCSq - mqSq ) ) );

      }
    else
      {

        double log_mC_over_mq = log( ( mC / mq ) );

        LKtoHK_sq
        = ( ( 2.0 * ( mCSq - mqSq ) * ( aCWXSq * mCSq + bCWXSq * mqSq ) )
            / ( mC * mqSq ) );

        LKtoHK_lin
        = ( ( 2.0
            * ( ( mCSq - mqSq )
                * ( aCWXSq * ( ( mCSq + mWSq - mXSq ) * mCSq
                               + ( mCSq - 2.0 * mqSq ) * mWSq )
                    - bCWXSq * mqSq * ( mCSq + 2.0 * mWSq - mXSq ) )
                - 2.0 * mCSq * mqSq
                  * ( ( aCWXSq - bCWXSq ) * ( mCSq + mWSq - mXSq )
                      - ( aCWXSq + bCWXSq ) * mWSq )
                  * log_mC_over_mq ) )
            / ( mC * mq * ( mqSq - mCSq ) ) );

        LKtoHK_const
        = ( ( ( mCSq - mqSq )
            * ( 2.0 * bCWXSq * ( EWC * ( 2.0 * mCSq + mWSq )
                                 + mC * ( mXSq - mCSq ) )
                - twice_real_part_of_a_conjugate_times_b * mX * mWSq )
                - 2.0
                  * ( bCWXSq * ( 2.0 * EWC * ( mCSq * ( mCSq + mqSq )
                                               + mqSq * mWSq )
                                 - mC * ( mCSq + mqSq ) * ( mCSq - mXSq ) )
                      - mWSq
                        * ( 2.0 * aCWXSq * EWC * ( mCSq - mqSq )
                            + mqSq * mX
                              * twice_real_part_of_a_conjugate_times_b ) )
                  * log_mC_over_mq )
            / ( mCSq - mqSq ) );

      }

    double log_EmaxC_mq_over_mC = log( ( ( EmaxC * mq ) / mC ) );

    HKtoMAX_sq
    = ( ( 2.0 * mC * mCSq
          * ( aCWXSq * mCSq + ( bCWXSq - 2.0 * aCWXSq ) * mqSq ) )
        / ( mqSq * ( mCSq - mqSq ) ) );

    HKtoMAX_linlog = -MINtoLK_linlog;

    HKtoMAX_lin
    = ( ( mC
          * ( 4.0 * aCWXSq * EmaxCSq
              * ( 2.0 * mC * ( EmaxC * mqSq - EWC * mCSq )
                  - ( mCSq - 2.0 * mqSq ) * mWSq )
              + mqSq
                * ( bCWXSq * ( 4.0 * EmaxCSq * ( mCSq + 2.0 * mWSq - mXSq )
                               - 8.0 * EmaxC * EmaxCSq * mC
                               - mWSq * mWSq
                               + 4.0 * EmaxC * ( EWC * ( 2.0 * mCSq + mWSq )
                                                 + mC * ( mXSq - mCSq ) ) )
                    - 2.0 * twice_real_part_of_a_conjugate_times_b
                      * EmaxC * mX * mWSq )
              - 4.0 * EmaxCSq * mqSq
                * ( ( aCWXSq - bCWXSq ) * ( mCSq + mWSq - mXSq )
                    - ( aCWXSq + bCWXSq ) * mWSq ) * log_EmaxC_mq_over_mC ) )
        / ( 2.0 * EmaxCSq * mq * ( mCSq - mqSq ) ) );

    HKtoMAX_log = -MINtoLK_log;

    HKtoMAX_const
    = ( ( 4.0 * aCWXSq * EmaxCSq
          * ( ( mCSq - 2.0 * mqSq ) * mWSq
              - ( EmaxC - 2.0 * EWC ) * mC * mCSq )
          + bCWXSq * ( 4.0 * EmaxC * EmaxCSq * mC * mqSq
                       - 4.0 * EmaxCSq * mqSq * ( mCSq + 2.0 * mWSq - mXSq )
                       + ( mCSq + mqSq ) * mWSq * mWSq
                       - 4.0 * EmaxC * mqSq
                         * ( EWC * ( 2.0 * mCSq + mWSq )
                             + mC * ( mXSq - mCSq ) ) )
            + 2.0 * twice_real_part_of_a_conjugate_times_b
              * EmaxC * mqSq * mX * mWSq
            + 2.0 * EmaxC
              * ( bCWXSq * ( 2.0 * EWC * ( mCSq * ( mCSq + mqSq )
                                           + mqSq * mWSq )
                             - mC * ( mCSq + mqSq ) * ( mCSq - mXSq ) )
                  - mWSq
                    * ( 2.0 * aCWXSq * EWC * ( mCSq - mqSq )
                        +  twice_real_part_of_a_conjugate_times_b
                           * mqSq * mX ) )
                    * log_EmaxC_mq_over_mC )
        / ( 2.0 * EmaxC * ( mCSq - mqSq ) ) );

    HKtoMAX_inv = -MINtoLK_inv;


    normalization
    = ( MINtoLK_sq * ( ( Elk * Elk * Elk
                         - minimum_energy * minimum_energy * minimum_energy )
                       / 3.0 )
        + MINtoLK_linlog * 0.5
          * ( Elk * Elk * ( log( Elk ) - 0.5 )
              - minimum_energy * minimum_energy * ( log( minimum_energy )
                                                    - 0.5 ) )
        + MINtoLK_lin * 0.5 * ( Elk * Elk
                                - minimum_energy * minimum_energy )
        + MINtoLK_log * ( Elk * ( log( Elk ) - 1.0 ) - minimum_energy * ( log( minimum_energy ) - 1.0 ) )
        + MINtoLK_const * ( Elk - minimum_energy )
        + MINtoLK_inv * log( ( Elk / minimum_energy ) )
        + LKtoHK_sq * ( ( Ehk * Ehk * Ehk - Elk * Elk * Elk ) / 3.0 )
        + LKtoHK_lin * 0.5 * ( Ehk * Ehk - Elk * Elk )
        + LKtoHK_const * ( Ehk - Elk )
        + HKtoMAX_sq * ( ( maximum_energy * maximum_energy * maximum_energy
                           - Ehk * Ehk * Ehk ) / 3.0 )
        + HKtoMAX_linlog
          * 0.5 * ( maximum_energy * maximum_energy
                    * ( log( maximum_energy ) - 0.5 )
                    - Ehk * Ehk * ( log( Ehk ) - 0.5 ) )
        + HKtoMAX_lin * 0.5 * ( maximum_energy * maximum_energy - Ehk * Ehk )
        + HKtoMAX_log
          * ( maximum_energy * ( log( maximum_energy ) - 1.0 )
              - Ehk * ( log( Ehk ) - 1.0 ) )
        + HKtoMAX_const * ( maximum_energy - Ehk )
        + HKtoMAX_inv * log( ( maximum_energy / Ehk ) ) );


    // debugging:
    /**std::cout
    << std::endl
    << "debugging: W_minus_plus_up_L_type_muon:";
    std::cout << std::endl << "normalization = " << normalization;
    // correct.
    std::cout << std::endl << "minimum_energy = " << minimum_energy;
    // correct.
    std::cout << std::endl << "Elk = " << Elk;
    // correct.
    std::cout << std::endl << "Ehk = " << Ehk;
    // correct.
    std::cout << std::endl << "maximum_energy = " << maximum_energy;
    // correct.
    std::cout << std::endl << "aCWXSq = " << aCWXSq;
    // used to define the Mathematica value.
    std::cout << std::endl << "twice_real_part_of_a_conjugate_times_b = "
    << twice_real_part_of_a_conjugate_times_b;
    // used to define the Mathematica value.
    std::cout << std::endl << "bCWXSq = " << bCWXSq;
    // used to define the Mathematica value.
    std::cout << std::endl << "MINtoLK_sq = " << MINtoLK_sq;
    // correct.
    std::cout << std::endl << "MINtoLK_linlog = " << MINtoLK_linlog;
    // correct.
    std::cout << std::endl << "MINtoLK_lin = " << MINtoLK_lin;
    // correct.
    std::cout << std::endl << "MINtoLK_log = " << MINtoLK_log;
    // correct.
    std::cout << std::endl << "MINtoLK_const = " << MINtoLK_const;
    // correct.
    std::cout << std::endl << "MINtoLK_inv = " << MINtoLK_inv;
    // correct.
    std::cout << std::endl << "LKtoHK_sq = " << LKtoHK_sq;
    // correct.
    std::cout << std::endl << "LKtoHK_lin = " << LKtoHK_lin;
    // about 0.00003 too small (should be 2.55104).
    std::cout << std::endl << "LKtoHK_const = " << LKtoHK_const;
    // correct.
    std::cout << std::endl << "HKtoMAX_sq = " << HKtoMAX_sq;
    // correct.
    std::cout << std::endl << "HKtoMAX_linlog = " << HKtoMAX_linlog;
    // correct.
    std::cout << std::endl << "HKtoMAX_lin = " << HKtoMAX_lin;
    // correct.
    std::cout << std::endl << "HKtoMAX_log = " << HKtoMAX_log;
    // correct.
    std::cout << std::endl << "HKtoMAX_const = " << HKtoMAX_const;
    // correct.
    std::cout << std::endl << "HKtoMAX_inv = " << HKtoMAX_inv;
    // correct.
    std::cout << std::endl << "EWC = " << EWC;
    // correct.
    std::cout << std::endl << "gammaCW = " << gammaCW;
    // correct.
    std::cout << std::endl << "betaCW = " << betaCW;
    // correct.
    std::cout << std::endl << "EminC = " << EminC;
    // correct.
    std::cout << std::endl << "EmaxC = " << EmaxC;
    // correct.
    std::cout << std::endl;
    std::cout << std::endl << "MINtoLK normalization = "
    << ( MINtoLK_sq * ( ( Elk * Elk * Elk
                          - minimum_energy * minimum_energy * minimum_energy )
                        / 3.0 )
         + MINtoLK_linlog * 0.5 * ( Elk * Elk * ( log( Elk ) - 0.5 )
                                    - minimum_energy * minimum_energy
                                      * ( log( minimum_energy ) - 0.5 ) )
         + MINtoLK_lin * 0.5 * ( Elk * Elk - minimum_energy * minimum_energy )
         + MINtoLK_log * ( Elk * ( log( Elk ) - 1.0 )
                           - minimum_energy * ( log( minimum_energy ) - 1.0 ) )
         + MINtoLK_const * ( Elk - minimum_energy )
         + MINtoLK_inv * log( ( Elk / minimum_energy ) ) );
    // correct.
    std::cout << std::endl << "LKtoHK normalization = "
    << ( LKtoHK_sq * ( ( Ehk * Ehk * Ehk - Elk * Elk * Elk ) / 3.0 )
         + LKtoHK_lin * 0.5 * ( Ehk * Ehk - Elk * Elk )
         + LKtoHK_const * ( Ehk - Elk ) );
    // correct.
    std::cout << std::endl << "HKtoMAX normalization = "
    << ( HKtoMAX_sq * ( ( maximum_energy * maximum_energy * maximum_energy
                          - Ehk * Ehk * Ehk ) / 3.0 )
         + HKtoMAX_linlog
           * 0.5 * ( maximum_energy * maximum_energy
                     * ( log( maximum_energy ) - 0.5 )
                     - Ehk * Ehk * ( log( Ehk ) - 0.5 ) )
         + HKtoMAX_lin * 0.5 * ( maximum_energy * maximum_energy - Ehk * Ehk )
         + HKtoMAX_log * ( maximum_energy * ( log( maximum_energy ) - 1.0 )
                           - Ehk * ( log( Ehk ) - 1.0 ) )
         + HKtoMAX_const * ( maximum_energy - Ehk )
         + HKtoMAX_inv * log( ( maximum_energy / Ehk ) ) );
    // correct.
    std::cout << std::endl;**/


    // finally we fill the sets of terms, segment by segment:

    // MIN to LK segment:
    segment_term_set* segment_filler = new segment_term_set( minimum_energy,
                                                             Elk );

    // square term:
    lepton_distribution_expansion_term*
    term_filler = new lepton_distribution_expansion_term( 2,
                                                          0,
                                              ( MINtoLK_sq / normalization ) );
    segment_filler->add_term( term_filler );

    // linear times logarithm term:
    term_filler = new lepton_distribution_expansion_term( 1,
                                                          1,
                                          ( MINtoLK_linlog / normalization ) );
    segment_filler->add_term( term_filler );

    // linear term:
    term_filler = new lepton_distribution_expansion_term( 1,
                                                          0,
                                             ( MINtoLK_lin / normalization ) );
    segment_filler->add_term( term_filler );

    // logarithm term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          1,
                                             ( MINtoLK_log / normalization ) );
    segment_filler->add_term( term_filler );

    // constant term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          0,
                                           ( MINtoLK_const / normalization ) );
    segment_filler->add_term( term_filler );

    // inverse term:
    term_filler = new lepton_distribution_expansion_term( -1,
                                                          0,
                                             ( MINtoLK_inv / normalization ) );
    segment_filler->add_term( term_filler );


    // record the segment:
    segments.push_back( segment_filler );


    // LK to HK segment:
    segment_filler = new segment_term_set( Elk,
                                           Ehk );

    // square term:
    term_filler = new lepton_distribution_expansion_term( 2,
                                                          0,
                                               ( LKtoHK_sq / normalization ) );
    segment_filler->add_term( term_filler );

    // linear term:
    term_filler = new lepton_distribution_expansion_term( 1,
                                                          0,
                                              ( LKtoHK_lin / normalization ) );
    segment_filler->add_term( term_filler );

    // constant term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          0,
                                            ( LKtoHK_const / normalization ) );
    segment_filler->add_term( term_filler );


    // record the segment:
    segments.push_back( segment_filler );


    // HK to MAX segment:
    segment_filler = new segment_term_set( Ehk,
                                           maximum_energy );

    // square term:
    term_filler = new lepton_distribution_expansion_term( 2,
                                                          0,
                                              ( HKtoMAX_sq / normalization ) );
    segment_filler->add_term( term_filler );

    // linear times logarithm term:
    term_filler = new lepton_distribution_expansion_term( 1,
                                                          1,
                                          ( HKtoMAX_linlog / normalization ) );
    segment_filler->add_term( term_filler );

    // linear term:
    term_filler = new lepton_distribution_expansion_term( 1,
                                                          0,
                                             ( HKtoMAX_lin / normalization ) );
    segment_filler->add_term( term_filler );

    // logarithm term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          1,
                                             ( HKtoMAX_log / normalization ) );
    segment_filler->add_term( term_filler );

    // constant term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          0,
                                           ( HKtoMAX_const / normalization ) );
    segment_filler->add_term( term_filler );

    // inverse term:
    term_filler = new lepton_distribution_expansion_term( -1,
                                                          0,
                                             ( HKtoMAX_inv / normalization ) );
    segment_filler->add_term( term_filler );


    // record the segment:
    segments.push_back( segment_filler );

  }

  W_minus_plus_up_L_type_muon::~W_minus_plus_up_L_type_muon()
  {

    // does nothing.

  }


  W_minus_plus_up_R_type_muon::W_minus_plus_up_R_type_muon(
                                 CppSLHA::CppSLHA0 const* const given_spectrum,
                    CppSLHA::particle_property_set const* const first_particle,
                                             double const effective_first_mass,
                   CppSLHA::particle_property_set const* const second_particle,
                    CppSLHA::particle_property_set const* const third_particle,
                CppSLHA::particle_property_set const* const fourth_particle ) :
    lepton_energy_distribution( given_spectrum,
                                effective_first_mass,
                                second_particle->get_absolute_mass(),
                                third_particle->get_absolute_mass(),
                                fourth_particle->get_absolute_mass() )
  {


    int which_chargino;
    int which_neutralino;

    if( CppSLHA::PDG_code::chargino_one == second_particle->get_PDG_code() )
      {

        which_chargino = 1;

      }
    else if( CppSLHA::PDG_code::chargino_two
             == second_particle->get_PDG_code() )
      {

        which_chargino = 2;

      }
    else
      {

        which_chargino = -1;
        // this will cause UMIX or VMIX to return NaN, which should show the
        // result up as obviously wrong.

        std::cout
        << std::endl
        << "LHC-FASER::error! W_minus_plus_up_R_type_muon expected to be given a"
        << " chargino as its 2nd particle, but did not receive a particle with"
        << " code +-" << CppSLHA::PDG_code::chargino_one << " or +-"
        << CppSLHA::PDG_code::chargino_two << ", rather, it received "
        << second_particle->get_name() << " (code: "
        << second_particle->get_PDG_code() << ")";
        std::cout << std::endl;

      }


    if( CppSLHA::PDG_code::neutralino_one == fourth_particle->get_PDG_code() )
      {

        which_neutralino = 1;

      }
    else if( CppSLHA::PDG_code::neutralino_two
             == fourth_particle->get_PDG_code() )
      {

        which_neutralino = 2;

      }
    else if( CppSLHA::PDG_code::neutralino_three
             == fourth_particle->get_PDG_code() )
      {

        which_neutralino = 3;

      }
    else if( CppSLHA::PDG_code::neutralino_four
             == fourth_particle->get_PDG_code() )
      {

        which_neutralino = 4;

      }
    else
      {

        which_neutralino = -1;
        // this will cause NMIX to return NaN, which should show the result up
        // as obviously wrong.

        std::cout
        << std::endl
        << "LHC-FASER::error! W_minus_plus_up_R_type_muon expected to be given a"
        << " neutralino as its 4th particle, but did not receive a particle"
        << " with code " << CppSLHA::PDG_code::neutralino_one << ", "
        << CppSLHA::PDG_code::neutralino_two << ", "
        << CppSLHA::PDG_code::neutralino_three << ", or "
        << CppSLHA::PDG_code::neutralino_four << ", rather, it received "
        << fourth_particle->get_name() << " (code: "
        << fourth_particle->get_PDG_code() << ")";
        std::cout << std::endl;

      }

    CppSLHA::SLHA_BLOCK const* NMIX = spectrum_data->inspect_BLOCK( "NMIX" );
    CppSLHA::SLHA_BLOCK const* UMIX = spectrum_data->inspect_BLOCK( "UMIX" );
    CppSLHA::SLHA_BLOCK const* VMIX = spectrum_data->inspect_BLOCK( "VMIX" );

    // debugging:
    /**std::cout
    << std::endl
    << "debugging:";
    std::cout << std::endl
    << "Z2iN = " << NMIX->get_entry( which_neutralino,
                                     2 );
    std::cout << std::endl
    << "Z1jplus = " << sVMIX->get_entry( which_chargino,
                                         1 );
    std::cout << std::endl
    << "Z4iN = " << NMIX->get_entry( which_neutralino,
                                     4 );
    std::cout << std::endl
    << "Z2jplus = " << VMIX->get_entry( which_chargino,
                                        2 );
    std::cout << std::endl
    << "Z1jminus = " << UMIX->get_entry( which_chargino,
                                         1 );
    std::cout << std::endl
    << "Z3iN = " << NMIX->get_entry( which_neutralino,
                                     3 );
    std::cout << std::endl
    << "Z2jminus = " << UMIX->get_entry( which_chargino,
                                         2 );
    std::cout << std::endl;**/


    /* it doesn't matter if the neutralino mass is negative, since only the
     * absolute square appears, & the couplings are only affected by it as an
     * overall phase.  I (BOL) assume no CP violation, so the chargino mixing
     * matrices are strictly real.
     */
    double
    temporary_unsquared_coupling
    = ( NMIX->get_entry( which_neutralino,
                         2 ) * VMIX->get_entry( which_chargino,
                                                1 )
        - M_SQRT1_2 * NMIX->get_entry( which_neutralino,
                                       4 ) * VMIX->get_entry( which_chargino,
                                                              2 ) );
    // by the way, M_SQRT1_2 is 1 over the square root of 2, defined in math.h.
    double
    aCWXSq = ( temporary_unsquared_coupling * temporary_unsquared_coupling );
    // Z2iN * Z1jplus - ( 1 / sqrt2 ) * Z4iN * Z2jplus.
    double twice_real_part_of_a_conjugate_times_b
    = temporary_unsquared_coupling;  // take the 1st part...
    temporary_unsquared_coupling
    = ( NMIX->get_entry( which_neutralino,
                         2 ) * UMIX->get_entry( which_chargino,
                                                1 )
        + M_SQRT1_2 * NMIX->get_entry( which_neutralino,
                                       3 ) * UMIX->get_entry( which_chargino,
                                                              2 ) );
    double
    bCWXSq = ( temporary_unsquared_coupling * temporary_unsquared_coupling );
    // Z2iN * Z1jminus + ( 1 / sqrt2 ) * Z3iN * Z2jminus
    twice_real_part_of_a_conjugate_times_b
    *= ( 2.0 * temporary_unsquared_coupling );
    // assume that the product of couplings is real, since we have calculated
    // it already, then check to see if it should be set to zero:
    if( ( ( 0.0 < second_particle->get_mass() )
        &&
        ( 0.0 > fourth_particle->get_mass() ) )
        ||
        ( ( 0.0 > second_particle->get_mass() )
            &&
            ( 0.0 < fourth_particle->get_mass() ) ) )
      // if the relative phases end up such that the product of couplings is
      // purely imaginary...
      {

        twice_real_part_of_a_conjugate_times_b = 0.0;

      }

    double mq = first_mass;
    double mqSq = ( mq * mq );
    double mC = second_mass;
    double mCSq = ( mC * mC );
    double mW = third_mass;
    double mWSq = ( mW * mW );
    double mX = fourth_mass;
    double mXSq = ( mX * mX );

    production_frame_energy = ( 0.5 * mW );

    double EWC = ( ( mCSq + mWSq - mXSq ) / ( 2.0 * mC ) );
    double gammaCW = ( EWC / mW );
    double betaCW = sqrt( ( 1.0 - ( 1.0 / ( gammaCW * gammaCW ) ) ) );
    double EmaxC = ( gammaCW * ( 1.0 + betaCW ) * production_frame_energy );
    double EmaxCSq = ( EmaxC * EmaxC );
    double EminC = ( mWSq / ( 4.0 * EmaxC ) );
    // using ( EmaxC * EminC ) = ( mWSq / 4 )
    double EminCSq = ( EminC * EminC );

    minimum_energy = ( ( mC / mq ) * EminC );

    double Elk;
    double Ehk;

    // there are 2 kinematic cases for determining the kink energies in terms
    // of the cascade masses:

    // 1st assume that boost_angle_energy_limited_between_kinks == true for
    // this spectrum:
    bool boost_angle_energy_limited_between_kinks = true;
    Elk = ( ( mC / mq ) * EmaxC );
    Ehk = ( ( mq / mC ) * EminC );

    // then check:
    if( Elk > Ehk )
      {

        boost_angle_energy_limited_between_kinks = false;

        Elk = Ehk;

        Ehk = ( ( mC / mq ) * EmaxC );

      }

    maximum_energy = ( ( mq / mC ) * EmaxC );



    // now we set up the coefficients of various terms, & use them to determine
    // the normalization:

    double log_EminC_mC_over_mq = log( ( ( EminC * mC ) / mq ) );

    MINtoLK_sq
    = ( ( 2.0 * mqSq * ( ( bCWXSq - 2.0 * aCWXSq ) * mCSq + aCWXSq * mqSq ) )
        / ( mC * ( mCSq - mqSq ) ) );

    MINtoLK_linlog
    = ( ( 2.0 * mC * mq * ( ( aCWXSq - bCWXSq ) * ( mCSq + mWSq - mXSq )
                            - ( aCWXSq + bCWXSq ) * mWSq ) )
        / ( mCSq - mqSq ) );

    MINtoLK_lin
    = ( ( mq
          * ( 4.0 * aCWXSq * EminCSq
              * ( 2.0 * ( EminC * mCSq - EWC * mqSq ) * mC + mqSq * mWSq )
              + bCWXSq
                * ( 4.0 * EminCSq * ( mCSq * ( mCSq - mXSq )
                                      + 2.0 * mqSq * mWSq )
                    - 8.0 * EminCSq * EminC * mC * mCSq
                    - mCSq * mWSq * mWSq
                    + 4.0 * EminC * mCSq * ( EWC * ( 2.0 * mCSq + mWSq )
                                             + mC * ( mXSq - mCSq ) ) )
              - 2.0 * EminC * mCSq * mX * mWSq
                * twice_real_part_of_a_conjugate_times_b
              - 4.0 * EminCSq * mCSq
                * ( ( aCWXSq - bCWXSq ) * ( mCSq + mWSq - mXSq )
                    - ( aCWXSq + bCWXSq ) * mWSq ) * log_EminC_mC_over_mq ) )
        / ( 2.0 * EminCSq * mC * ( mCSq - mqSq ) ) );

    MINtoLK_log
    = ( ( bCWXSq * ( 2.0 * EWC * ( mCSq * ( mCSq + mqSq ) + mqSq * mWSq )
                     - mC * ( mCSq + mqSq ) * (mCSq - mXSq) )
          - twice_real_part_of_a_conjugate_times_b * mX * mCSq * mWSq )
        / ( mqSq - mCSq ) );

    MINtoLK_const
    = ( ( 4.0 * aCWXSq * EminCSq * mqSq * mC * ( ( EminC - mC ) * mC + mXSq )
          + 2.0 * twice_real_part_of_a_conjugate_times_b
            * EminC * mX * mCSq * mC * mWSq * ( log_EminC_mC_over_mq - 1.0 )
          - bCWXSq * ( mC * ( 4.0 * EminCSq * EminC * mCSq * mC
                       + ( mCSq + mqSq ) * mWSq * mWSq
                       - 2.0 * EminC * mC * mWSq * ( 3.0 * mCSq + mWSq - mXSq )
                       - 4.0 * EminCSq * ( 2.0 * mqSq * mWSq
                                           + mCSq * ( mCSq -  mXSq ) ) )
            + 2.0 * EminC * mWSq
              * ( mCSq * mCSq + mqSq * ( 2.0 * mCSq + mWSq - mXSq ) )
            * log_EminC_mC_over_mq ) )
        / ( 2.0 * EminC * mC * ( mqSq - mCSq ) ) );

    MINtoLK_inv
    = ( ( bCWXSq * mC * mq * mWSq * mWSq ) / ( 2.0 * ( mqSq - mCSq ) ) );


    // there are 2 kinematic cases for determining the kink energies in terms
    // of the cascade masses:
    if( boost_angle_energy_limited_between_kinks )
      /* if the assumption that the mass spectrum was such that the boost from
       * the squark frame to the chargino frame is greater than that from the
       * chargino frame to the W frame was correct...
       */
      {

        double log_twice_EmaxC_over_mW = log( ( ( 2.0 * EmaxC ) / mW ) );

        LKtoHK_sq = 0.0;

        LKtoHK_lin
        = ( ( 2.0 * twice_real_part_of_a_conjugate_times_b
              * EmaxC * mC * mq * ( 4.0 * EmaxCSq - mWSq ) * mX * mWSq
              + bCWXSq
                * ( mC * mq * ( 4.0 * EmaxCSq - mWSq )
                    * ( ( 4.0 * EmaxCSq + mWSq ) * mWSq
                          - 2.0 * EmaxC
                            * ( 2.0 * EWC * ( 2.0 * mCSq + mWSq )
                                + mC * ( mWSq - 2.0 * mCSq + 2.0 * mXSq ) ) )
                    + 2.0 * EmaxCSq * mWSq
                      * ( 4.0 * mC * mq * ( mCSq + 2.0 * mWSq - mXSq )
                          * log_twice_EmaxC_over_mW ) )
              + aCWXSq * mC * mq * 2.0 * EmaxC * mWSq
                * ( mC * ( 4.0 * EmaxCSq - mWSq )
                    + 4.0 * EmaxC * ( mXSq - mCSq )
                      * log_twice_EmaxC_over_mW ) )
            / ( 2.0 * EmaxCSq * ( mqSq - mCSq ) * mWSq ) );

        LKtoHK_const
        = ( ( aCWXSq * mqSq
              * ( 4.0 * EmaxCSq - mWSq )
              * ( 4.0 * EmaxC * ( EmaxC - 2.0 * EWC ) * mC
                  + ( 4.0 * EmaxC + mC ) * mWSq )
              - bCWXSq * ( 4.0 * EmaxCSq - mWSq )
                * ( mC * mCSq * ( 4.0 * EmaxCSq + mWSq )
                    + 4.0 * EmaxC
                      * ( mCSq * ( mXSq - mWSq - mCSq ) - 3.0 * mqSq * mWSq ) )
              + 16.0
                * ( twice_real_part_of_a_conjugate_times_b
                    * mX * EmaxCSq * mCSq * mWSq
                    - bCWXSq * EmaxCSq
                      * ( 2.0 * EWC * ( mCSq * ( mCSq + mqSq ) + mqSq * mWSq )
                          - mC * ( mCSq + mqSq ) * ( mCSq - mXSq ) ) )
                * log_twice_EmaxC_over_mW )
            / ( 8.0 * EmaxCSq * ( mCSq - mqSq ) ) );

      }
    else
      {

        double log_mC_over_mq = log( ( mC / mq ) );

        LKtoHK_sq
        = ( ( 2.0 * ( mCSq - mqSq ) * ( aCWXSq * mqSq + bCWXSq * mCSq ) )
            / ( mC * mqSq ) );

        LKtoHK_lin
        = ( ( 2.0
              * ( ( mCSq - mqSq )
                  * ( aCWXSq * mqSq * ( mXSq - mCSq )
                      + bCWXSq * ( mCSq * ( mCSq - mXSq )
                                   + 2.0 * mqSq * mWSq ) )
                  + 2.0 * mCSq * mqSq
                    * ( ( aCWXSq - bCWXSq ) * ( mCSq + mWSq - mXSq )
                        - ( aCWXSq + bCWXSq ) * mWSq ) * log_mC_over_mq ) )
            / ( mC * mq * ( mqSq - mCSq ) ) );

        LKtoHK_const
        = ( ( 2.0 * bCWXSq * ( mqSq - mCSq )
              * ( EWC * ( 2.0 * mCSq + mWSq ) + mC * ( mXSq - mCSq ) )
              + twice_real_part_of_a_conjugate_times_b
                * mX * mWSq * ( mCSq - mqSq )
              + 2.0 * ( bCWXSq
                        * ( 2.0 * EWC
                            * ( mCSq * ( mCSq + mqSq ) + mqSq * mWSq )
                            - mC * ( mCSq + mqSq ) * ( mCSq - mXSq ) )
                        - twice_real_part_of_a_conjugate_times_b
                          * mX * mCSq * mWSq ) * log_mC_over_mq )
            / ( mCSq - mqSq ) );

      }

    double log_EmaxC_mq_over_mC = log( ( ( EmaxC * mq ) / mC ) );

    HKtoMAX_sq
    = ( ( 2.0 * mC * mCSq
          * ( aCWXSq * mqSq + bCWXSq * ( mCSq - 2.0 * mqSq ) ) )
        / ( mqSq * ( mCSq - mqSq ) ) );

    HKtoMAX_linlog = -MINtoLK_linlog;

    HKtoMAX_lin
    = ( ( 2.0 * twice_real_part_of_a_conjugate_times_b
          * EmaxC * mX * mC * mqSq * mWSq
          + 4.0 * aCWXSq * EmaxCSq * mC * mqSq
            * ( ( mCSq - mXSq ) * log_EmaxC_mq_over_mC
                - 2.0 * EmaxC * mC + mCSq - mXSq )
          + bCWXSq
            * ( 8.0 * EmaxCSq * EmaxC * mCSq * mqSq
                + mC * mqSq * mWSq * mWSq
                - 2.0 * EmaxC * mqSq * mWSq * ( 3.0 * mCSq + mWSq - mXSq )
                - 4.0 * EmaxCSq * mC
                  * ( 2.0 * mqSq * mWSq + mCSq * ( mCSq - mXSq ) )
                + 4.0 * EmaxCSq * mqSq * mC * ( mXSq - mCSq - 2.0 * mWSq )
                  * log_EmaxC_mq_over_mC ) )
        / ( 2.0 * EmaxCSq * mq * ( mCSq - mqSq ) ) );

    HKtoMAX_log = -MINtoLK_log;

    HKtoMAX_const
    = ( ( 4.0 * aCWXSq * EmaxCSq * mC * mqSq * ( ( EmaxC - mC ) * mC + mXSq )
          + 2.0 * twice_real_part_of_a_conjugate_times_b
            * mX * EmaxC * mC * mWSq * ( mCSq * log_EmaxC_mq_over_mC - mqSq )
          - bCWXSq
            * ( 4.0 * EmaxC * EmaxCSq * mCSq * mCSq
                + mC * ( mCSq + mqSq ) * mWSq * mWSq
                - 2.0 * EmaxC * mqSq * mWSq * ( 3.0 * mCSq + mWSq - mXSq )
                - 4.0 * EmaxCSq * mC
                  * ( 2.0 * mqSq * mWSq + mCSq * ( mCSq - mXSq ) )
                + 2.0 * EmaxC * mWSq
                  * ( mCSq * mCSq + mqSq * ( 2.0 * mCSq + mWSq - mXSq ) )
                  * log_EmaxC_mq_over_mC ) )
        / ( 2.0 * EmaxC * mC * ( mCSq - mqSq ) ) );

    HKtoMAX_inv = -MINtoLK_inv;


    normalization
    = ( MINtoLK_sq * ( ( Elk * Elk * Elk
                         - minimum_energy * minimum_energy * minimum_energy )
                       / 3.0 )
        + MINtoLK_linlog * 0.5
          * ( Elk * Elk * ( log( Elk ) - 0.5 )
              - minimum_energy * minimum_energy
                * ( log( minimum_energy ) - 0.5 ) )
        + MINtoLK_lin * 0.5 * ( Elk * Elk - minimum_energy * minimum_energy )
        + MINtoLK_log * ( Elk * ( log( Elk ) - 1.0 )
                          - minimum_energy * ( log( minimum_energy ) - 1.0 ) )
        + MINtoLK_const * ( Elk - minimum_energy )
        + MINtoLK_inv * log( ( Elk / minimum_energy ) )
        + LKtoHK_sq * ( ( Ehk * Ehk * Ehk - Elk * Elk * Elk ) / 3.0 )
        + LKtoHK_lin * 0.5 * ( Ehk * Ehk - Elk * Elk )
        + LKtoHK_const * ( Ehk - Elk )
        + HKtoMAX_sq * ( ( maximum_energy * maximum_energy * maximum_energy
                           - Ehk * Ehk * Ehk ) / 3.0 )
        + HKtoMAX_linlog * 0.5
          * ( maximum_energy * maximum_energy * ( log( maximum_energy ) - 0.5 )
              - Ehk * Ehk * ( log( Ehk ) - 0.5 ) )
        + HKtoMAX_lin * 0.5 * ( maximum_energy * maximum_energy - Ehk * Ehk )
        + HKtoMAX_log * ( maximum_energy * ( log( maximum_energy ) - 1.0 )
                          - Ehk * ( log( Ehk ) - 1.0 ) )
        + HKtoMAX_const * ( maximum_energy - Ehk )
        + HKtoMAX_inv * log( ( maximum_energy / Ehk ) ) );


    // finally we fill the sets of terms, segment by segment.

    // MIN to LK segment:
    segment_term_set* segment_filler = new segment_term_set( minimum_energy,
                                                             Elk );

    // square term:
    lepton_distribution_expansion_term*
    term_filler = new lepton_distribution_expansion_term( 2,
                                                          0,
                                              ( MINtoLK_sq / normalization ) );
    segment_filler->add_term( term_filler );

    // linear times logarithm term:
    term_filler = new lepton_distribution_expansion_term( 1,
                                                          1,
                                          ( MINtoLK_linlog / normalization ) );
    segment_filler->add_term( term_filler );

    // linear term:
    term_filler = new lepton_distribution_expansion_term( 1,
                                                          0,
                                             ( MINtoLK_lin / normalization ) );
    segment_filler->add_term( term_filler );

    // logarithm term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          1,
                                             ( MINtoLK_log / normalization ) );
    segment_filler->add_term( term_filler );

    // constant term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          0,
                                           ( MINtoLK_const / normalization ) );
    segment_filler->add_term( term_filler );

    // inverse term:
    term_filler = new lepton_distribution_expansion_term( -1,
                                                          0,
                                             ( MINtoLK_inv / normalization ) );
    segment_filler->add_term( term_filler );


    // record the segment:
    segments.push_back( segment_filler );


    // LK to HK segment:
    segment_filler = new segment_term_set( Elk,
                                           Ehk );

    // square term:
    term_filler = new lepton_distribution_expansion_term( 2,
                                                          0,
                                               ( LKtoHK_sq / normalization ) );
    segment_filler->add_term( term_filler );

    // linear term:
    term_filler = new lepton_distribution_expansion_term( 1,
                                                          0,
                                              ( LKtoHK_lin / normalization ) );
    segment_filler->add_term( term_filler );

    // constant term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          0,
                                            ( LKtoHK_const / normalization ) );
    segment_filler->add_term( term_filler );


    // record the segment:
    segments.push_back( segment_filler );


    // HK to MAX segment:
    segment_filler = new segment_term_set( Ehk,
                                           maximum_energy );

    // square term:
    term_filler = new lepton_distribution_expansion_term( 2,
                                                          0,
                                              ( HKtoMAX_sq / normalization ) );
    segment_filler->add_term( term_filler );

    // linear times logarithm term:
    term_filler = new lepton_distribution_expansion_term( 1,
                                                          1,
                                          ( HKtoMAX_linlog / normalization ) );
    segment_filler->add_term( term_filler );

    // linear term:
    term_filler = new lepton_distribution_expansion_term( 1,
                                                          0,
                                             ( HKtoMAX_lin / normalization ) );
    segment_filler->add_term( term_filler );

    // logarithm term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          1,
                                             ( HKtoMAX_log / normalization ) );
    segment_filler->add_term( term_filler );

    // constant term:
    term_filler = new lepton_distribution_expansion_term( 0,
                                                          0,
                                           ( HKtoMAX_const / normalization ) );
    segment_filler->add_term( term_filler );

    // inverse term:
    term_filler = new lepton_distribution_expansion_term( -1,
                                                          0,
                                             ( HKtoMAX_inv / normalization ) );
    segment_filler->add_term( term_filler );


    // record the segment:
    segments.push_back( segment_filler );

  }

  W_minus_plus_up_R_type_muon::~W_minus_plus_up_R_type_muon()
  {

    // does nothing.

  }


  visible_tau_decay_product::visible_tau_decay_product(
                      lepton_energy_distribution const* const tau_distribution,
                               tau_decay_coefficient const* const tau_decay ) :
    lepton_energy_distribution( tau_distribution->get_spectrum_data(),
                                tau_distribution->get_first_mass(),
                                tau_distribution->get_second_mass(),
                                tau_distribution->get_third_mass(),
                                tau_distribution->get_fourth_mass() )
  {

    // debugging:
    /**std::cout
    << std::endl
    << "debugging: "
    << "visible_tau_decay_product( "
    << tau_distribution << ", " << tau_decay << " )";
    std::cout
    << std::endl;**/

    minimum_energy = 0.0;

    maximum_energy = tau_distribution->get_maximum_energy();

    segment_term_set* low_segment;
    // this is for filling the segment from 0.0 to the tau lepton segment's
    // start.
    segment_term_set* high_segment;
    // this is for filling the segment from the tau lepton segment's start to
    // its end.

    lepton_distribution_expansion_term* term_filler;
    // this is for filling the terms of the segment.

    double coefficient_filler;
    // this is for filling the coefficients of the terms of the segment.

    for( std::vector< segment_term_set* >::const_iterator
           segment_iterator = tau_distribution->get_segments()->begin();
         tau_distribution->get_segments()->end() > segment_iterator;
         ++segment_iterator )
      {

        /* each tau lepton segment gives 2 segments for the light lepton:
         * 0.0 GeV to the tau lepton segment_start energy,
         * & the tau lepton segment_start energy to the tau lepton
         * segment_end energy:
         */

        low_segment
        = new segment_term_set( 0.0,
                                (*segment_iterator)->get_segment_start() );
        high_segment
        = new segment_term_set( (*segment_iterator)->get_segment_start(),
                                (*segment_iterator)->get_segment_end() );

        for( std::vector< lepton_distribution_expansion_term* >::const_iterator
               term_iterator = (*segment_iterator)->get_terms()->begin();
             (*segment_iterator)->get_terms()->end() > term_iterator;
             ++term_iterator )
          {

            for( int energy_power_counter = -1;
                 3 >= energy_power_counter;
                 ++energy_power_counter )
              {

                for( int log_power_counter = 0;
                     3 >= log_power_counter;
                     ++log_power_counter )
                  {

                    coefficient_filler
                    = ( (*term_iterator)->get_coefficient()
                        * (*tau_decay)( energy_power_counter,
                                        log_power_counter,
                                       (*term_iterator)->get_power_of_energy(),
                                    (*term_iterator)->get_power_of_logarithm(),
                                      (*segment_iterator)->get_segment_start(),
                                        (*segment_iterator)->get_segment_end(),
                                        false ) );

                    if( 0.0 != coefficient_filler )
                      {


                        term_filler
                        = new lepton_distribution_expansion_term(
                                                        energy_power_counter,
                                                           log_power_counter,
                                                        coefficient_filler );
                        low_segment->add_term( term_filler );

                      }

                    coefficient_filler
                    = ( (*term_iterator)->get_coefficient()
                        * (*tau_decay)( energy_power_counter,
                                        log_power_counter,
                                       (*term_iterator)->get_power_of_energy(),
                                    (*term_iterator)->get_power_of_logarithm(),
                                      (*segment_iterator)->get_segment_start(),
                                        (*segment_iterator)->get_segment_end(),
                                        true ) );

                    if( 0.0 != coefficient_filler )
                      {


                        term_filler
                        = new lepton_distribution_expansion_term(
                                                        energy_power_counter,
                                                           log_power_counter,
                                                        coefficient_filler );
                        high_segment->add_term( term_filler );

                      }

                  }  // end of loop over log powers

              }  // end of loop over energy powers

          }  // end of loop through terms.

        // record the segments
        if( 0 < low_segment->get_number_of_terms() )
          {

            segments.push_back( low_segment );

          }

        if( 0 < high_segment->get_number_of_terms() )
          {

            segments.push_back( high_segment );

          }

      }  // end of loop through segments.

  }

  visible_tau_decay_product::~visible_tau_decay_product()
  {

    // does nothing.

  }

}  // end of LHC_FASER namespace

