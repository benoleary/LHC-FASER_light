/*
 * LHC-FASER_global_stuff.hpp
 *
 *  Created on: 15 Dec 2010
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


#ifndef LHC_FASER_GLOBAL_STUFF_HPP_
#define LHC_FASER_GLOBAL_STUFF_HPP_

#include <stdlib.h>
#include <math.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <list>
#include <map>


namespace LHC_FASER
{

  // this class has static methods for miscellaneous useful functions.
  class LHC_FASER_global
  {

  public:

    static double
    unit_linear_interpolation( double const x_fraction,
                               double const left_value,
                               double const right_value )
    /* this does a linear interpolation from the values at the given 2
     * ends of a unit line segment for the given point in the segment.
     */
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    static double
    square_bilinear_interpolation( double const x_fraction,
                                   double const y_fraction,
                                   double const lower_left_value,
                                   double const lower_right_value,
                                   double const upper_right_value,
                                   double const upper_left_value )
    /* this does a bilinear interpolation from the values at the given 4
     * corners of a unit square for the given point in the unit square.
     */
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    static double const negligible_BR;
    // this is what we use to decide when we throw away cascades because the
    // acceptance times branching ratio dropped too low.

    static double const negligible_sigma;
    // this is what we use to decide when we throw away channels because the
    // cross-section times acceptance times branching ratio dropped too low.

  };  // end of LHC_FASER_global class.



  /* this class does the job of a subject, observed by
   * interface_readied_for_new_point objects. the
   * interface_readied_for_new_point objects are responsible for registering &
   * de-registering themselves with their constructors & destructors.
   * this class sets the 1st bools of the pairs observed by its observers to
   * true when requested. it sets the 2nd bools to false when the
   * readier_for_new_point instance's destructor is called.
   */
  class readier_for_new_point
  {

  public:

    readier_for_new_point()
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    ~readier_for_new_point()
    /* code after the classes in this .hpp file, or in the .cpp file. */;


    void
    include_me( bool* observer_bool_for_readier_existence )
    // this registers the observer so that the readier's destructor can let
    // the observer know that the readier is retiring.
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    void
    remove_me( bool* observer_bool_for_readier_existence,
               bool* observer_bool_for_readying )
    /* this removes the observer from the readier's list of observers which is
     * used when the readier's destructor is called to let the observers know
     * to stop asking to be reset.
     */
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    void
    reset_me_on_next_update( bool* observer_bool_for_readying )
    // this adds a pointer from the observer to the list of bools to be set to
    // true with the next call of ready_for_new_point().
    /* code after the classes in this .hpp file, or in the .cpp file. */;


    void
    ready_for_new_point()
    // this goes through the list of pointers to bools created by observers
    // calling reset_me() & sets all the bools to true.
    /* code after the classes in this .hpp file, or in the .cpp file. */;


  protected:

    std::list< bool* > observer_bools_for_readying;

    std::list< bool* > observer_bools_for_readier_existence;

  };  // end of readier_for_new_point class.


  /* this class does the job of being an interface for objects which need to
   * observe a readier_for_new_point subject. it's not mimicking a Java-style
   * interface properly, since it is not an abstract class (no abstract
   * functions), so there is the possibility of the deadly diamond of death if
   * any class which inherits from this class also inherits from another class
   * which also defines ready_for_new_point(). however, you have been warned.
   * I am not going to write any class like that, & if you write such a class,
   * it is entirely your own silly fault.  ;]
   * the constructor registers the object with the readier_for_new_point & the
   * destructor de-registers itself from the readier_for_new_point.
   */
  class interface_readied_for_new_point
  {

  public:

    interface_readied_for_new_point( readier_for_new_point* given_readier )
    /* the constructor gives a pointer to a bool to given_readier which
     * has a value that given_readier's destructor changes. this object keeps
     * a pointer to given_readier so that it can de-register when its
     * destructor is called.
     */
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    ~interface_readied_for_new_point()
    // the destructor tells readier, if it still exists, to stop modifying its
    // bool pointers.
    /* code after the classes in this .hpp file, or in the .cpp file. */;


  protected:

    bool needs_to_prepare_flag;
    bool readier_exists_flag;
    readier_for_new_point* const readier;


    bool
    needs_to_prepare_for_this_point()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    void
    finish_preparing_for_this_point()
    /* code after the classes in this .hpp file, or in the .cpp file. */;

  };  // end of interface_readied_for_new_point class.





  // inline functions:


  inline void
  readier_for_new_point::include_me(
                                    bool* observer_bool_for_readier_existence )
  // this registers the observer so that the readier's destructor can let
  // the observer know that the readier is retiring.
  {

    observer_bools_for_readier_existence.push_back(
                                         observer_bool_for_readier_existence );

  }


  inline void
  readier_for_new_point::reset_me_on_next_update(
                                             bool* observer_bool_for_readying )
  // this adds a pointer from the observer to the list of bools to be set to
  // true with the next call of ready_for_new_point().
  {

    observer_bools_for_readying.push_back( observer_bool_for_readying );

  }



  inline bool
  interface_readied_for_new_point::needs_to_prepare_for_this_point()
  const
  {

    return needs_to_prepare_flag;

  }

  inline void
  interface_readied_for_new_point::finish_preparing_for_this_point()
  {

    needs_to_prepare_flag = false;
    readier->reset_me_on_next_update( &needs_to_prepare_flag );

  }

}  // end of LHC_FASER namespace.

#endif /* LHC_FASER_GLOBAL_STUFF_HPP_ */
