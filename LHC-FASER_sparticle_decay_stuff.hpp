/*
 * LHC-FASER_sparticle_decay_stuff.hpp
 *
 *  Created on: Mar 21, 2011
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

#ifndef LHC_FASER_SPARTICLE_DECAY_STUFF_HPP_
#define LHC_FASER_SPARTICLE_DECAY_STUFF_HPP_

#include "CppSLHA/CppSLHA.hpp"
#include "LHC-FASER_global_stuff.hpp"

namespace LHC_FASER
{

  // this class holds a pair of particle_property_set along with a bool which
  // is true for particles, false for antiparticles.
  class signed_particle_shortcut_pair
  {

  public:

    signed_particle_shortcut_pair(
               CppSLHA::particle_property_set const* const given_first_pointer,
                               bool const given_first_is_not_antiparticle_flag,
              CppSLHA::particle_property_set const* const given_second_pointer,
                             bool const given_second_is_not_antiparticle_flag )
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    signed_particle_shortcut_pair(
                       signed_particle_shortcut_pair const* const copy_source )
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    ~signed_particle_shortcut_pair()
    /* code after the classes in this .hpp file, or in the .cpp file. */;


    CppSLHA::particle_property_set const*
    get_first_pointer()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    CppSLHA::particle_property_set const*
    get_second_pointer()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;


    bool
    first_is_not_antiparticle()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    bool
    second_is_not_antiparticle()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;


  protected:

    CppSLHA::particle_property_set const* first_particle_pointer;
    bool first_is_not_antiparticle_flag;
    CppSLHA::particle_property_set const* second_particle_pointer;
    bool second_is_not_antiparticle_flag;

  };  // end of signed_particle_shortcut_pair class.


  // this class just checks whether the given particle can decay directly to
  // any of the particles in the given vector, or their antiparticles.
  class direct_decay_checker : public interface_readied_for_new_point
  {

  public:

    direct_decay_checker(
                     CppSLHA::particle_property_set const* const given_decayer,
              std::vector< CppSLHA::particle_property_set const* > const* const
                          given_products,
                          readier_for_new_point* const given_readier )
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    ~direct_decay_checker()
    /* code after the classes in this .hpp file, or in the .cpp file. */;


    CppSLHA::particle_property_set const*
    get_decayer()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    std::vector< CppSLHA::particle_property_set const* > const*
    get_products()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;


    bool
    has_direct_decay()
    /* code after the classes in this .hpp file, or in the .cpp file. */;


  protected:

    CppSLHA::particle_property_set const* decayer;
    std::vector< CppSLHA::particle_property_set const* > const* products;
    bool decayer_does_decay_to_at_least_one_product;

    bool
    check_for_decay()
    // this checks the particles to see if the decay exists for this point.
    /* code after the classes in this .hpp file, or in the .cpp file. */;

  };  // end of direct_decay_checker class.

  // this class holds a set of direct_decay_checkers & passes out pointers
  // to them.
  class decay_checker_handler
  {

  public:

    decay_checker_handler( readier_for_new_point* const given_readier )
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    ~decay_checker_handler()
    /* code after the classes in this .hpp file, or in the .cpp file. */;


    direct_decay_checker*
    get_decay_checker(
                     CppSLHA::particle_property_set const* const given_decayer,
              std::vector< CppSLHA::particle_property_set const* > const* const
                       given_products )
    /* code after the classes in this .hpp file, or in the .cpp file. */;


  protected:

    std::vector< direct_decay_checker* > decay_checkers;
    readier_for_new_point* readier;

    direct_decay_checker*
    add( CppSLHA::particle_property_set const* const given_decayer,
              std::vector< CppSLHA::particle_property_set const* > const* const
         given_products  )
    /* code after the classes in this .hpp file, or in the .cpp file. */;

  };  // end of decay_checker_handler class.


  /* this class calculates the branching ratio for the given decayer into the
   * given product for all channels *excluding* those which also have any of
   * the particles in the exclusion list.
   */
  class exclusive_BR_calculator : public interface_readied_for_new_point
  {

  public:

    exclusive_BR_calculator(
                     CppSLHA::particle_property_set const* const given_decayer,
                     CppSLHA::particle_property_set const* const given_product,
                             bool const product_is_not_antiparticle_flag,
                             std::list< int > const* const given_excluded,
                             readier_for_new_point* const given_readier )
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    ~exclusive_BR_calculator()
    /* code after the classes in this .hpp file, or in the .cpp file. */;


    CppSLHA::particle_property_set const*
    get_decayer()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    CppSLHA::particle_property_set const*
    get_product()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    std::list< int > const*
    get_excluded()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;


    double
    get_BR()
    /* code after the classes in this .hpp file, or in the .cpp file. */;


    protected:

    CppSLHA::particle_property_set const* decayer;
    CppSLHA::particle_property_set const* product;
    std::list< int >* product_code;
    std::list< int > const* const exclusion_list;
    double BR_value;


    double
    calculate_BR()
    const
    // this calculates the branching ratio for this point.
    /* code after the classes in this .hpp file, or in the .cpp file. */;

  };  // end of exclusive_BR_calculator class.

  // this class holds a set of exclusive_BR_calculators & passes out pointers
  // to them.
  class exclusive_BR_handler
  {

  public:

    exclusive_BR_handler(
      std::vector< CppSLHA::particle_property_set const* > const* const sdowns,
        std::vector< CppSLHA::particle_property_set const* > const* const sups,
                          readier_for_new_point* const given_readier )
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    ~exclusive_BR_handler()
    /* code after the classes in this .hpp file, or in the .cpp file. */;


    exclusive_BR_calculator*
    get_BR_calculator(
                     CppSLHA::particle_property_set const* const given_decayer,
                     CppSLHA::particle_property_set const* const given_product,
                       bool const product_is_not_antiparticle_flag,
                       std::list< int > const* const given_excluded )
    /* code after the classes in this .hpp file, or in the .cpp file. */;


  protected:

    std::vector< exclusive_BR_calculator* > exclusive_BRs;
    readier_for_new_point* readier;

    std::vector< std::pair< int,
                            int >* > always_neglected_decays;

    exclusive_BR_calculator*
    add( CppSLHA::particle_property_set const* const given_decayer,
         CppSLHA::particle_property_set const* const given_product,
         bool const product_is_not_antiparticle_flag,
         std::list< int > const* const given_excluded )
    /* code after the classes in this .hpp file, or in the .cpp file. */;

  };  // end of exclusive_BR_handler class.


  /* this class is for keeping track of a particular cascade decay of a colored
   * sparticle down to the 1st electroweak decay, such that it keeps track of
   * all the colored sparticles of a cascade decay. some of its utility is very
   * format-*dependent*: it holds integers for direct look-up of the colored
   * decay product sparticle in shortcut->get_colored_sparticles() & of the
   * electroweakino in shortcut->get_electroweakinos().
   */
  class colored_cascade
  {

  public:

    colored_cascade( CppSLHA::particle_property_set const* const given_decayer,
                     CppSLHA::particle_property_set const* const given_product,
                     int const given_product_position,
                     CppSLHA::particle_property_set const* const given_EWino,
                     int const given_EWino_position )
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    ~colored_cascade()
    /* code after the classes in this .hpp file, or in the .cpp file. */;


    CppSLHA::particle_property_set const*
    get_decayer()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    CppSLHA::particle_property_set const*
    get_product()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    int
    get_product_position()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    CppSLHA::particle_property_set const*
    get_EWino()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    int
    get_EWino_position()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    bool
    is_sx()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    bool
    is_gx()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    bool
    is_sgx()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    bool
    is_gsx()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    bool
    is_sgsx()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;


    enum cascade_type
    {

      sx,
      gx,
      sgx,
      gsx,
      sgsx

    };


  protected:

    cascade_type cascade_code;

    CppSLHA::particle_property_set const* decayer;
    CppSLHA::particle_property_set const* product;
    int const product_position;
    CppSLHA::particle_property_set const* EWino;
    int const EWino_position;

  };  // end of colored_cascade class.

  // this class holds a set of colored_cascades & passes out a vector of
  // pointers to those which are kinematically allowed.
  class colored_cascade_set : public interface_readied_for_new_point
  {

  public:

    colored_cascade_set(
                     CppSLHA::particle_property_set const* const given_decayer,
                      CppSLHA::particle_property_set const* const given_gluino,
              std::vector< CppSLHA::particle_property_set const* > const* const
                         given_scoloreds,
              std::vector< CppSLHA::particle_property_set const* > const* const
                         given_EWinos,
                         readier_for_new_point* const given_readier )
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    ~colored_cascade_set()
    /* code after the classes in this .hpp file, or in the .cpp file. */;


    CppSLHA::particle_property_set const*
    get_decayer()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;


    std::vector< colored_cascade* > const*
    get_colored_cascades()
    /* code after the classes in this .hpp file, or in the .cpp file. */;


  protected:

    CppSLHA::particle_property_set const* const decayer;
    CppSLHA::particle_property_set const* const gluino_pointer;
    std::vector< CppSLHA::particle_property_set const* > const* const
    scoloreds;
    std::vector< CppSLHA::particle_property_set const* > const* const EWinos;
    std::vector< colored_cascade* > colored_cascades;
    readier_for_new_point* readier;


    void
    prepare_open_channels()
    /* code after the classes in this .hpp file, or in the .cpp file. */;

  };  // end of colored_cascade_set class.

  // this class holds a set of colored_cascade_sets & passes out pointers to
  // them.
  class colored_cascade_handler
  {

  public:

    colored_cascade_handler(
                      CppSLHA::particle_property_set const* const given_gluino,
              std::vector< CppSLHA::particle_property_set const* > const* const
                             given_scoloreds,
              std::vector< CppSLHA::particle_property_set const* > const* const
                             given_EWinos,
                             readier_for_new_point* const given_readier )
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    ~colored_cascade_handler()
    /* code after the classes in this .hpp file, or in the .cpp file. */;


    colored_cascade_set*
    get_colored_cascade_set(
                    CppSLHA::particle_property_set const* const given_decayer )
    /* code after the classes in this .hpp file, or in the .cpp file. */;


  protected:

    CppSLHA::particle_property_set const* const gluino_pointer;
    std::vector< CppSLHA::particle_property_set const* > const* const
    scoloreds;
    std::vector< CppSLHA::particle_property_set const* > const* const EWinos;
    std::vector< colored_cascade_set* > colored_cascade_sets;
    readier_for_new_point* readier;

  };  // end of colored_cascade_handler class.


  /* this holds a set of pointers to describe a full
   * sQCD-to-electroweakino-pair "subchannel" of colored sparticle pair
   * production & subsequent SUSY-QCD decay to a pair of final colored
   * sparticles which then decay to a pair of electroweakinos. hence it holds
   * - a pointer to a signed_particle_shortcut_pair for the directly-produced
   *   colored sparticles
   * - 2 pointers to colored_cascades, for each of the directly-produced
   *   sparticles decaying to the electroweakino for each
   * - 4 bools, for holding whether the final colored sparticles & the
   *   electroweakinos are particles or antiparticles.
   * it also holds a total branching ratio for the total pair of cascades.
   * it is intended to be used only for a single point - each is made by a
   * sQCD_to_EWino, which deletes all the scoloreds_to_EWinos it made when told
   * to update for a new point.
   */
  class scoloreds_to_EWinos
  {

  public:

    scoloreds_to_EWinos(
                signed_particle_shortcut_pair const* const given_scolored_pair,
                              colored_cascade const* const given_first_cascade,
                       bool const given_first_end_scolored_is_not_antiparticle,
                              bool const given_first_EWino_is_not_antiparticle,
                             colored_cascade const* const given_second_cascade,
                      bool const given_second_end_scolored_is_not_antiparticle,
                             bool const given_second_EWino_is_not_antiparticle,
                         double given_BR_product )
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    ~scoloreds_to_EWinos()
    /* code after the classes in this .hpp file, or in the .cpp file. */;


    signed_particle_shortcut_pair const*
    get_scoloreds()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    colored_cascade const*
    get_first_cascade()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    bool
    first_end_scolored_is_not_antiparticle()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    bool
    first_EWino_is_not_antiparticle()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;


    colored_cascade const*
    get_second_cascade()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    bool
    second_end_scolored_is_not_antiparticle()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    bool
    second_EWino_is_not_antiparticle()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;


    double
    get_BR_product()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;


  protected:

    signed_particle_shortcut_pair const* const scolored_pair;
    colored_cascade const* const first_cascade;
    bool const first_end_scolored_is_not_antiparticle_flag;
    bool const first_EWino_is_not_antiparticle_flag;
    colored_cascade const* const second_cascade;
    bool const second_end_scolored_is_not_antiparticle_flag;
    bool const second_EWino_is_not_antiparticle_flag;
    double BR_product;

  };  // end of scoloreds_to_EWinos class.





  // inline functions:


  inline CppSLHA::particle_property_set const*
  signed_particle_shortcut_pair::get_first_pointer()
  const
  {

    return first_particle_pointer;

  }

  inline CppSLHA::particle_property_set const*
  signed_particle_shortcut_pair::get_second_pointer()
  const
  {

    return second_particle_pointer;

  }


  inline bool
  signed_particle_shortcut_pair::first_is_not_antiparticle()
  const
  {

    return first_is_not_antiparticle_flag;

  }

  inline bool
  signed_particle_shortcut_pair::second_is_not_antiparticle()
  const
  {

    return second_is_not_antiparticle_flag;

  }



  inline CppSLHA::particle_property_set const*
  direct_decay_checker::get_decayer()
  const
  {

    return decayer;

  }

  inline std::vector< CppSLHA::particle_property_set const* > const*
  direct_decay_checker::get_products()
  const
  {

    return products;

  }


  inline bool
  direct_decay_checker::has_direct_decay()
  {

    if( needs_to_prepare_for_this_point() )
      {

        decayer_does_decay_to_at_least_one_product = check_for_decay();
        finish_preparing_for_this_point();

      }

    return decayer_does_decay_to_at_least_one_product;

  }



  inline direct_decay_checker*
  decay_checker_handler::add(
                     CppSLHA::particle_property_set const* const given_decayer,
              std::vector< CppSLHA::particle_property_set const* > const* const
                              given_products  )
  {

    direct_decay_checker*
    added_decay_checker = new direct_decay_checker( given_decayer,
                                                    given_products,
                                                    readier );

    decay_checkers.push_back( added_decay_checker );

    return added_decay_checker;

  }



  inline CppSLHA::particle_property_set const*
  exclusive_BR_calculator::get_decayer()
  const
  {

    return decayer;

  }

  inline CppSLHA::particle_property_set const*
  exclusive_BR_calculator::get_product()
  const
  {

    return product;

  }

  inline std::list< int > const*
  exclusive_BR_calculator::get_excluded()
  const
  {

    return exclusion_list;

  }


  inline double
  exclusive_BR_calculator::get_BR()
  {

    if( needs_to_prepare_for_this_point() )
      {

        if( decayer->get_absolute_mass() > product->get_absolute_mass() )
          // we check 1st to see if the BR can be non-zero.
          {

            BR_value = calculate_BR();

          }
        else
          {

            BR_value = 0.0;

          }

        finish_preparing_for_this_point();

      }

    return BR_value;

  }

  inline double
  exclusive_BR_calculator::calculate_BR()
  const
  // this calculates the branching ratio for this point.
  {

    return decayer->inspect_direct_decay_handler(
                             )->get_branching_ratio_for_subset( product_code,
                                                            exclusion_list );

  }



  inline exclusive_BR_calculator*
  exclusive_BR_handler::add(
                     CppSLHA::particle_property_set const* const given_decayer,
                     CppSLHA::particle_property_set const* const given_product,
                             bool const product_is_not_antiparticle_flag,
                             std::list< int > const* const given_excluded )
  {

    exclusive_BR_calculator*
    added_BR_calculator = new exclusive_BR_calculator( given_decayer,
                                                       given_product,
                                              product_is_not_antiparticle_flag,
                                                       given_excluded,
                                                       readier );

    exclusive_BRs.push_back( added_BR_calculator );

    return added_BR_calculator;

  }



  inline CppSLHA::particle_property_set const*
  colored_cascade::get_decayer()
  const
  {

    return decayer;

  }

  inline CppSLHA::particle_property_set const*
  colored_cascade::get_product()
  const
  {

    return product;

  }

  inline int
  colored_cascade::get_product_position()
  const
  {

    return product_position;

  }

  inline CppSLHA::particle_property_set const*
  colored_cascade::get_EWino()
  const
  {

    return EWino;

  }

  inline int
  colored_cascade::get_EWino_position()
  const
  {

    return EWino_position;

  }

  inline bool
  colored_cascade::is_sx()
  const
  {

    if( sx == cascade_code )
      {

        return true;

      }
    else
      {

        return false;

      }

  }

  inline bool
  colored_cascade::is_gx()
  const
  {

    if( gx == cascade_code )
      {

        return true;

      }
    else
      {

        return false;

      }

  }

  inline bool
  colored_cascade::is_sgx()
  const
  {

    if( sgx == cascade_code )
      {

        return true;

      }
    else
      {

        return false;

      }

  }

  inline bool
  colored_cascade::is_gsx()
  const
  {

    if( gsx == cascade_code )
      {

        return true;

      }
    else
      {

        return false;

      }

  }

  inline bool
  colored_cascade::is_sgsx()
  const
  {

    if( sgsx == cascade_code )
      {

        return true;

      }
    else
      {

        return false;

      }

  }



  inline CppSLHA::particle_property_set const*
  colored_cascade_set::get_decayer()
  const
  {

    return decayer;

  }


  inline std::vector< colored_cascade* > const*
  colored_cascade_set::get_colored_cascades()
  {

    if( needs_to_prepare_for_this_point() )
      {

        prepare_open_channels();
        finish_preparing_for_this_point();

      }

    return &colored_cascades;

  }



  inline signed_particle_shortcut_pair const*
  scoloreds_to_EWinos::get_scoloreds()
  const
  {

    return scolored_pair;

  }


  inline colored_cascade const*
  scoloreds_to_EWinos::get_first_cascade()
  const
  {

    return first_cascade;

  }

  inline bool
  scoloreds_to_EWinos::first_end_scolored_is_not_antiparticle()
  const
  {

    return first_end_scolored_is_not_antiparticle_flag;

  }

  inline bool
  scoloreds_to_EWinos::first_EWino_is_not_antiparticle()
  const
  {

    return first_EWino_is_not_antiparticle_flag;

  }


  inline colored_cascade const*
  scoloreds_to_EWinos::get_second_cascade()
  const
  {

    return second_cascade;

  }

  inline bool
  scoloreds_to_EWinos::second_end_scolored_is_not_antiparticle()
  const
  {

    return second_end_scolored_is_not_antiparticle_flag;

  }

  inline bool
  scoloreds_to_EWinos::second_EWino_is_not_antiparticle()
  const
  {

    return second_EWino_is_not_antiparticle_flag;

  }


  inline double
  scoloreds_to_EWinos::get_BR_product()
  const
  {

    return BR_product;

  }

}  // end of LHC_FASER namespace


#endif /* LHC_FASER_SPARTICLE_DECAY_STUFF_HPP_ */
