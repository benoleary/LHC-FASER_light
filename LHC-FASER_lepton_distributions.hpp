/*
 * LHC-FASER_lepton_distributions.hpp
 *
 *  Created on: 16 Mar 2011
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


/* this is a set of classes used for the calculation of the fraction of leptons
 * that pass various cuts at the moment. it also includes jets by pretending
 * that they're basically leptons.
 */

/* all the initialize() functions used by constructors are there because an
 * earlier version had several different constructors & it was the easiest way
 * to accomodate them.  then I changed my mind & now there is only 1
 * constructor per class, but I don't think that it'd be worthwhile undoing
 * separating out the code to initalize().
 */

#ifndef LHC_FASER_LEPTON_DISTRIBUTIONS_HPP
#define LHC_FASER_LEPTON_DISTRIBUTIONS_HPP

#include "CppSLHA/CppSLHA.hpp"

namespace LHC_FASER
{

  // this class is for emulating doing minor symbolic algebra.
  class lepton_distribution_expansion_term
  {

  public:

    lepton_distribution_expansion_term( int const given_power_of_energy,
                                        int const given_power_of_logarithm,
                                        double const given_coefficient )
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    virtual
    ~lepton_distribution_expansion_term()
    /* code after the classes in this .hpp file, or in the .cpp file. */;


    int
    get_power_of_energy()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    int
    get_power_of_logarithm()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    double
    get_coefficient()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    inline double
    evaluate( double const given_energy )
    const
    // this evaluates this term for the given input energy.
    /* code after the classes in this .hpp file, or in the .cpp file. */;


  protected:

    int power_of_energy;
    int power_of_logarithm;
    double coefficient;

  };

  inline int
  lepton_distribution_expansion_term::get_power_of_energy()
  const
  {

    return power_of_energy;

  }

  inline int
  lepton_distribution_expansion_term::get_power_of_logarithm()
  const
  {

    return power_of_logarithm;

  }

  inline double
  lepton_distribution_expansion_term::get_coefficient()
  const
  {

    return coefficient;

  }


  // this is a class to hold a set of lepton_distribution_expansion_term
  // objects relevant for an energy range for the distribution.
  class segment_term_set
  {

  public:

    segment_term_set( double const given_start,
                      double const given_end )
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    virtual
    ~segment_term_set()
    /* code after the classes in this .hpp file, or in the .cpp file. */;


    double
    get_segment_start()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    double
    get_segment_end()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    std::vector< lepton_distribution_expansion_term* > const*
    get_terms()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    int
    get_number_of_terms()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;


    lepton_distribution_expansion_term*
    add_term( lepton_distribution_expansion_term* const given_term )
    /* code after the classes in this .hpp file, or in the .cpp file. */;


    double
    evaluate( double const given_energy )
    const
    // this evaluates the sum of the set of terms for the given input energy.
    /* code after the classes in this .hpp file, or in the .cpp file. */;


  protected:

    std::vector< lepton_distribution_expansion_term* > segment_terms;
    double segment_start;
    double segment_end;

  };

  inline double
  segment_term_set::get_segment_start()
  const
  {

    return segment_start;

  }

  inline double
  segment_term_set::get_segment_end()
  const
  {

    return segment_end;

  }

  inline std::vector< lepton_distribution_expansion_term* > const*
  segment_term_set::get_terms()
  const
  {

    return &segment_terms;

  }

  inline int
  segment_term_set::get_number_of_terms()
  const
  {

    return segment_terms.size();

  }

  inline lepton_distribution_expansion_term*
  segment_term_set::add_term(
                         lepton_distribution_expansion_term* const given_term )
  {

    segment_terms.push_back( given_term );

    return given_term;

  }


  /* this class is the base abstract class for the functors for obtaining
   * energy distributions for the visible decay products of tau leptons with
   * given energy distributions.
   * (yes, left-handed tau leptons / right-handed tau antileptons give harder
   * muons / electrons but softer pions than the other helicity.)
   */
  class tau_decay_coefficient
  {

  public:

    tau_decay_coefficient()
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    virtual
    ~tau_decay_coefficient()
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    virtual double
    operator()( int const visible_product_energy_power
                /* the power of the visible product's energy for the term. */,
                int const visible_product_log_power
/* the power of the logarithm of the visible product's energy for the term. */,
                int const tau_lepton_energy_power
                /* the power of the tau lepton's energy for the term. */,
                int const tau_lepton_log_power
     /* the power of the logarithm of the tau lepton's energy for the term. */,
                double const Emin
         /* the minimum of the range of the tau lepton energies considered. */,
                double const Emax
         /* the maximum of the range of the tau lepton energies considered. */,
                bool const is_inside_range )
    const
    = 0;


    //protected:

      // nothing.

  };

  /* this functor returns the coefficient for the muon distribution which would
   * come from a left-handed tau lepton distribution of the given power of the
   * tau lepton's energy & power of logarithm thereof, for requested integer
   * powers of the muon's energy or logarithm thereof, which also depends on
   * whether the muon's energy is inside the range of the tau lepton's energy
   * for this segment.
   */
  class hard_muon_from_tau : public tau_decay_coefficient
  {

  public:

    hard_muon_from_tau()
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    virtual
    ~hard_muon_from_tau()
    /* code after the classes in this .hpp file, or in the .cpp file. */;


    virtual double
    operator()( int const muon_energy_power
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
    /* code after the classes in this .hpp file, or in the .cpp file. */;


    //protected:

      // nothing.

  };

  /* this functor returns the coefficient for the muon distribution which would
   * come from a right-handed tau lepton distribution of the given power of the
   * tau lepton's energy & power of logarithm thereof, for requested integer
   * powers of the muon's energy or logarithm thereof, which also depends on
   * whether the muon's energy is inside the range of the tau lepton's energy
   * for this segment.
   */
  class soft_muon_from_tau : public tau_decay_coefficient
  {

  public:

    soft_muon_from_tau()
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    virtual
    ~soft_muon_from_tau()
    /* code after the classes in this .hpp file, or in the .cpp file. */;


    virtual double
    operator()( int const muon_energy_power
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
    /* code after the classes in this .hpp file, or in the .cpp file. */;


    //protected:

      // nothing.

  };

  /* this functor returns the coefficient for the pion distribution which would
   * come from a right-handed tau lepton distribution of the given power of the
   * tau lepton's energy & power of logarithm thereof, for requested integer
   * powers of the pion's energy or logarithm thereof, which also depends on
   * whether the pion's energy is inside the range of the tau lepton's energy
   * for this segment.
   */
  class hard_pion_from_tau : public tau_decay_coefficient
  {

  public:

    hard_pion_from_tau()
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    virtual
    ~hard_pion_from_tau()
    /* code after the classes in this .hpp file, or in the .cpp file. */;


    virtual double
    operator()( int const pion_energy_power
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
    /* code after the classes in this .hpp file, or in the .cpp file. */;


  //protected:

    // nothing.

  };

  /* this functor returns the coefficient for the pion distribution which would
   * come from a left-handed tau lepton distribution of the given power of the
   * tau lepton's energy & power of logarithm thereof, for requested integer
   * powers of the pion's energy or logarithm thereof, which also depends on
   * whether the pion's energy is inside the range of the tau lepton's energy
   * for this segment.
   */
  class soft_pion_from_tau : public tau_decay_coefficient
  {

  public:

    soft_pion_from_tau()
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    virtual
    ~soft_pion_from_tau()
    /* code after the classes in this .hpp file, or in the .cpp file. */;


    virtual double
    operator()( int const pion_energy_power
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
    /* code after the classes in this .hpp file, or in the .cpp file. */;


    //protected:

      // nothing.

  };


  /* this class is just an abstract base class for some polymorphic derived
   * classes. However, it does do most of the work, the derived classes just
   * set up the lepton_distribution_expansion_term objects properly.
   */
  class lepton_energy_distribution
  {

  public:

    lepton_energy_distribution( CppSLHA::CppSLHA0 const* const given_spectrum,
                                double const given_first_mass,
                                double const given_second_mass,
                                double const given_third_mass,
                                double const given_fourth_mass )
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    virtual
    ~lepton_energy_distribution()
    /* code after the classes in this .hpp file, or in the .cpp file. */;


    CppSLHA::CppSLHA0 const*
    get_spectrum_data()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    double
    get_minimum_energy()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    double
    get_maximum_energy()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    std::vector< segment_term_set* > const*
    get_segments()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    double
    get_first_mass()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    double
    get_second_mass()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    double
    get_third_mass()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    double
    get_fourth_mass()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    double
    get_normalization()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    double
    get_production_frame_energy()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;


    double
    value_at( double const given_energy )
    const
    // this returns the value of the distribution at the given value, with
    // arbitrary normalization (different for each distribution).
    /* code after the classes in this .hpp file, or in the .cpp file. */;


  protected:

    CppSLHA::CppSLHA0 const* spectrum_data;
    // this holds all the information about the MSSM point. care must be taken
    // to ensure that it has the appropriate BLOCKs for the distribution.

    double minimum_energy;
    double maximum_energy;

    std::vector< segment_term_set* > segments;

    /* these masses could be pulled out of spectrum_data every time they are
     * needed, but it's probably worthwhile to have them as quickly-accessible
     * doubles:
     */
    double const first_mass;
    // the squark mass in a standard decay, but let's pretend that I'm being
    // general.
    double const second_mass;
    // the intermediate neutralino mass in the standard decay, but could be
    // e.g. the chargino mass in a certain decay.
    double const third_mass;
    // the slepton mass in the standard decay, but could be e.g.
    // the Z boson mass or sneutrino mass.
    double const fourth_mass;
    // the lightest neutralino mass in the standard decay, but could be
    // something else in some crazy cascade.

    double normalization;
    // this is *an overall denominator*, rather than multiplicative
    // normalization.

    // this is not strictly necessary, but is handy for distributions from
    // on-shell cascades:
    double production_frame_energy;

  };

  inline CppSLHA::CppSLHA0 const*
  lepton_energy_distribution::get_spectrum_data()
  const
  {

    return spectrum_data;

  }

  inline double
  lepton_energy_distribution::get_minimum_energy()
  const
  {

    return minimum_energy;

  }

  inline double
  lepton_energy_distribution::get_maximum_energy()
  const
  {

    return maximum_energy;

  }

  inline std::vector< segment_term_set* > const*
  lepton_energy_distribution::get_segments()
  const
  {

    return &segments;

  }

  inline double
  lepton_energy_distribution::get_first_mass()
  const
  {

    return first_mass;

  }

  inline double
  lepton_energy_distribution::get_second_mass()
  const
  {

    return second_mass;

  }

  inline double
  lepton_energy_distribution::get_third_mass()
  const
  {

    return third_mass;

  }

  inline double
  lepton_energy_distribution::get_fourth_mass()
  const
  {

    return fourth_mass;

  }

  inline double
  lepton_energy_distribution::get_normalization()
  const
  {

    return normalization;

  }

  inline double
  lepton_energy_distribution::get_production_frame_energy()
  const
  {

    return production_frame_energy;

  }

  /* this derived class sets up the energy distribution for a light lepton
   * which is the "near" lepton in a cascade decay, summing over charges, which
   * averages over the chirality effects & thus produces a flat distribution.
   */
  class flat_near_muon_plus_antimuon : public lepton_energy_distribution
  {

  public:

    flat_near_muon_plus_antimuon(
                                 CppSLHA::CppSLHA0 const* const given_spectrum,
                    CppSLHA::particle_property_set const* const first_particle,
                                             double const effective_first_mass,
                   CppSLHA::particle_property_set const* const second_particle,
                   CppSLHA::particle_property_set const* const third_particle )
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    virtual
    ~flat_near_muon_plus_antimuon()
    /* code after the classes in this .hpp file, or in the .cpp file. */;


  //protected:

    //double MINtoMAX_const;
    // the coefficient constant with respect to input_energy between
    // minimum_energy & Elk

  };

  /* this derived class sets up the energy distribution for a light lepton
   * which is the "near" lepton in a cascade decay from a squark to a slepton,
   * where the near lepton or antilepton has the same helicity to the jet (thus
   * the distibution peaks at higher energies, hence "hard" ).  Actually, in
   * practice, this is from a cascade decay of a squark to a chargino & then
   * the chargino to a light lepton plus sneutrino.
   */
  class same_chirality_near_muon : public lepton_energy_distribution
  {

  public:

    same_chirality_near_muon( CppSLHA::CppSLHA0 const* const given_spectrum,
                    CppSLHA::particle_property_set const* const first_particle,
                              double const effective_first_mass,
                   CppSLHA::particle_property_set const* const second_particle,
                   CppSLHA::particle_property_set const* const third_particle )
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    virtual
    ~same_chirality_near_muon()
    /* code after the classes in this .hpp file, or in the .cpp file. */;


  protected:

    double MINtoMAX_lin;
    // the coefficient of the logarithm of input_energy between minimum_energy
    // & maximum_energy.
    double MINtoMAX_const;
    // the coefficient constant with respect to input_energy between
    // minimum_energy & maximum_energy.

  };

  /* this derived class sets up the energy distribution for a light lepton
   * which is the "near" lepton in a cascade decay from a squark to a slepton,
   * where the near lepton or antilepton has the opposite helicity to the jet
   * (thus the distibution peaks at lower energies, hence "soft" ).  Actually,
   * in practice, this is from a cascade decay of a squark to a chargino & then
   * the chargino to a light lepton plus sneutrino.
   */
  class opposite_chirality_near_muon : public lepton_energy_distribution
  {


  public:

    opposite_chirality_near_muon(
                                 CppSLHA::CppSLHA0 const* const given_spectrum,
                    CppSLHA::particle_property_set const* const first_particle,
                                             double const effective_first_mass,
                   CppSLHA::particle_property_set const* const second_particle,
                   CppSLHA::particle_property_set const* const third_particle )
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    virtual
    ~opposite_chirality_near_muon()
    /* code after the classes in this .hpp file, or in the .cpp file. */;


  protected:

    double MINtoMAX_lin;
    // the coefficient of the logarithm of input_energy between minimum_energy
    // & maximum_energy.
    double MINtoMAX_const;
    // the coefficient constant with respect to input_energy between
    // minimum_energy & maximum_energy.

  };

  /* this derived class sets up the energy distribution for a light lepton
   * which is the "far" lepton in a cascade decay, summing over charges, which
   * averages over the chirality effects & thus produces a relatively simple
   * distribution.
   */
  class flat_far_muon_plus_antimuon : public lepton_energy_distribution
  {

  public:

    flat_far_muon_plus_antimuon( CppSLHA::CppSLHA0 const* const given_spectrum,
                    CppSLHA::particle_property_set const* const first_particle,
                                 double const effective_first_mass,
                   CppSLHA::particle_property_set const* const second_particle,
                    CppSLHA::particle_property_set const* const third_particle,
                  CppSLHA::particle_property_set const* const fourth_particle )
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    virtual
    ~flat_far_muon_plus_antimuon()
    /* code after the classes in this .hpp file, or in the .cpp file. */;


  protected:

    // the various coefficients for each case are given their own variables:

    double MINtoLK_log;
    // the coefficient of the logarithm of input_energy between minimum_energy
    // & Elk.
    double MINtoLK_const;
    // the coefficient constant with respect to input_energy between
    // minimum_energy & Elk.

    double LKtoHK_const;
    // the coefficient constant with respect to input_energy between Elk & Ehk.

    double HKtoMAX_log;
    // the coefficient of the logarithm of input_energy between Ehk &
    // maximum_energy.
    double HKtoMAX_const;
    // the coefficient constant with respect to input_energy between Ehk &
    // maximum_energy.

  };

  /* this derived class sets up the energy distribution for a light lepton
   * which is the "far" lepton in a cascade decay from a squark to a slepton,
   * where the near lepton or antilepton has the same helicity to the jet (thus
   * the distibution peaks at lower energies, hence "soft" ).  Actually, in
   * practice, this is from a cascade decay of a squark to a chargino & then
   * the chargino to a neutrino plus slepton which then decays to the light
   * lepton.
   */
  class same_chirality_far_muon : public lepton_energy_distribution
  {

  public:

    same_chirality_far_muon( CppSLHA::CppSLHA0 const* const given_spectrum,
                    CppSLHA::particle_property_set const* const first_particle,
                             double const effective_first_mass,
                   CppSLHA::particle_property_set const* const second_particle,
                    CppSLHA::particle_property_set const* const third_particle,
                  CppSLHA::particle_property_set const* const fourth_particle )
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    virtual
    ~same_chirality_far_muon()
    /* code after the classes in this .hpp file, or in the .cpp file. */;


  protected:

    // the various coefficients for each case are given their own variables:

    double MINtoLK_lin;
    // the coefficient of the linear power of input_energy between
    // minimum_energy & Elk.
    double MINtoLK_log;
    // the coefficient of the logarithm of input_energy between minimum_energy
    // & Elk.
    double MINtoLK_const;
    // the coefficient constant with respect to input_energy between
    // minimum_energy & Elk.
    double MINtoLK_inv;
    // the coefficient of the linear inverse power of input_energy between
    // minimum_energy & Elk.

    double LKtoHK_const;
    // the coefficient constant with respect to input_energy between Elk & Ehk.
    double LKtoHK_inv;
    // the coefficient of the linear inverse power of input_energy between Elk
    // & Ehk.

    double HKtoMAX_lin;
    // the coefficient of the linear power of input_energy between Ehk &
    // maximum_energy.
    double HKtoMAX_log;
    // the coefficient of the logarithm of input_energy between Ehk &
    // maximum_energy.
    double HKtoMAX_const;
    // the coefficient constant with respect to input_energy between Ehk &
    // maximum_energy.
    double HKtoMAX_inv;
    // the coefficient of the linear inverse power of input_energy between Ehk
    // & maximum_energy.

  };

  /* this derived class sets up the energy distribution for a light lepton
   * which is the "far" lepton in a cascade decay from a squark to a slepton,
   * where the near lepton or antilepton has the opposite helicity to the jet
   * (thus the distibution peaks at higher energies, hence "hard" ).  Actually,
   * in practice, this is from a cascade decay of a squark to a chargino & then
   * the chargino to a neutrino plus slepton which then decays to the light
   * lepton.
   */
  class opposite_chirality_far_muon : public lepton_energy_distribution
  {

  public:

    opposite_chirality_far_muon( CppSLHA::CppSLHA0 const* const given_spectrum,
                    CppSLHA::particle_property_set const* const first_particle,
                                 double const effective_first_mass,
                   CppSLHA::particle_property_set const* const second_particle,
                    CppSLHA::particle_property_set const* const third_particle,
                  CppSLHA::particle_property_set const* const fourth_particle )
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    virtual
    ~opposite_chirality_far_muon()
    /* code after the classes in this .hpp file, or in the .cpp file. */;


  protected:

    // the various coefficients for each case are given their own variables:

    double MINtoLK_lin;
    // the coefficient of the linear power of input_energy between
    // minimum_energy & Elk.
    double MINtoLK_log;
    // the coefficient of the logarithm of input_energy between minimum_energy
    // & Elk.
    double MINtoLK_const;
    // the coefficient constant with respect to input_energy between
    // minimum_energy & Elk.
    double MINtoLK_inv;
    // the coefficient of the linear inverse power of input_energy between
    // minimum_energy & Elk.

    double LKtoHK_const;
    // the coefficient constant with respect to input_energy between Elk & Ehk.
    double LKtoHK_inv;
    // the coefficient of the linear inverse power of input_energy between Elk
    // & Ehk.

    double HKtoMAX_lin;
    // the coefficient of the linear power of input_energy between Ehk &
    // maximum_energy.
    double HKtoMAX_log;
    // the coefficient of the logarithm of input_energy between Ehk &
    // maximum_energy.
    double HKtoMAX_const;
    // the coefficient constant with respect to input_energy between Ehk &
    // maximum_energy.
    double HKtoMAX_inv;
    // the coefficient of the linear inverse power of input_energy between Ehk
    // & maximum_energy.

  };

  /* specific lepton or antilepton versions of the Higgs-channel distribution
   * could be done, but at the moment there is no need for them.
   */
  /* this derived class sets up the energy distribution for a light lepton
   * which is from the decay of an on-shell Higgs boson from the cascade decay
   * of a squark to a jet of either chirality plus a light lepton-antilepton
   * pair plus a lightest neutralino, summing over charges, which averages over
   * the chirality effects & thus produces a relatively simple distribution.
   */
  class Higgs_muon_plus_antimuon : public lepton_energy_distribution
  {

  public:

      Higgs_muon_plus_antimuon( CppSLHA::CppSLHA0 const* const given_spectrum,
                    CppSLHA::particle_property_set const* const first_particle,
                                double const effective_first_mass,
                   CppSLHA::particle_property_set const* const second_particle,
                    CppSLHA::particle_property_set const* const third_particle,
                  CppSLHA::particle_property_set const* const fourth_particle )
      /* code after the classes in this .hpp file, or in the .cpp file. */;

      virtual
      ~Higgs_muon_plus_antimuon()
      /* code after the classes in this .hpp file, or in the .cpp file. */;


  protected:

    // the various coefficients for each case are given their own variables:

    double MINtoLK_log;
    // the coefficient of the logarithm of input_energy between minimum_energy
    // & Elk.
    double MINtoLK_const;
    // the coefficient constant with respect to input_energy between
    // minimum_energy & Elk.

    double LKtoHK_const;
    // the coefficient constant with respect to input_energy between Elk & Ehk.

    double HKtoMAX_log;
    // the coefficient of the logarithm of input_energy between Ehk &
    // maximum_energy.
    double HKtoMAX_const;
    // the coefficient constant with respect to input_energy between Ehk &
    // maximum_energy.

  };

  /* specific lepton or antilepton versions of the Z-channel distribution could
   * be done, but at the moment there is no need for them.
   */
  /* this derived class sets up the energy distribution for a light lepton
   * which is from the decay of an on-shell Z boson from the cascade decay of a
   * squark to a jet of either chirality plus a light lepton-antilepton pair
   * plus a lightest neutralino, summing over charges, which averages over the
   * chirality effects & thus produces a relatively simple distribution.
   */
  class Z_muon_plus_antimuon : public lepton_energy_distribution
  {

  public:

    Z_muon_plus_antimuon( CppSLHA::CppSLHA0 const* const given_spectrum,
                    CppSLHA::particle_property_set const* const first_particle,
                          double const effective_first_mass,
                   CppSLHA::particle_property_set const* const second_particle,
                    CppSLHA::particle_property_set const* const third_particle,
                  CppSLHA::particle_property_set const* const fourth_particle )
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    virtual
    ~Z_muon_plus_antimuon()
    /* code after the classes in this .hpp file, or in the .cpp file. */;


  protected:

    // the various coefficients for each case are given their own variables:

    double MINtoLK_sq;
    // the coefficient of the square of input_energy between minimum_energy &
    // Elk.
    double MINtoLK_lin;
    // the coefficient of the linear power of input_energy between
    // minimum_energy & Elk.
    double MINtoLK_log;
    // the coefficient of the logarithm of input_energy between minimum_energy
    // & Elk.
    double MINtoLK_const;
    // the coefficient constant with respect to input_energy between
    // minimum_energy & Elk.

    double LKtoHK_sq;
    // the coefficient of the square of input_energy between Elk & Ehk.
    double LKtoHK_lin;
    // the coefficient of the linear power of input_energy between Elk & Ehk.
    double LKtoHK_const;
    // the coefficient constant with respect to input_energy between Elk & Ehk.

    double HKtoMAX_sq;
    // the coefficient of the square of input_energy between Ehk &
    // maximum_energy.
    double HKtoMAX_lin;
    // the coefficient of the linear power of input_energy between Ehk &
    // maximum_energy.
    double HKtoMAX_log;
    // the coefficient of the logarithm of input_energy between Ehk &
    // maximum_energy.
    double HKtoMAX_const;
    // the coefficient constant with respect to input_energy between Ehk &
    // maximum_energy.

  };

  /* this derived class sets up the energy distribution for a light lepton
   * which is from the decay of an on-shell negatively-charged W boson from the
   * cascade decay of a down-type squark to a left-handed jet plus a
   * negatively-charged light lepton plus an antineutrino plus a lightest
   * neutralino.  it also seems to be the same for an up-type squark decaying
   * into a right-handed jet plus a positively-charged light antilepton plus a
   * neutrino plus a lightest neutralino.
   */
  class W_minus_plus_up_L_type_muon : public lepton_energy_distribution
  {

  public:

    W_minus_plus_up_L_type_muon( CppSLHA::CppSLHA0 const* const given_spectrum,
                    CppSLHA::particle_property_set const* const first_particle,
                                 double const effective_first_mass,
                   CppSLHA::particle_property_set const* const second_particle,
                    CppSLHA::particle_property_set const* const third_particle,
                  CppSLHA::particle_property_set const* const fourth_particle )
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    virtual
    ~W_minus_plus_up_L_type_muon()
    /* code after the classes in this .hpp file, or in the .cpp file. */;


  protected:

    // the various coefficients for each case are given their own variables:

    double MINtoLK_sq;
    // the coefficient of the square of input_energy between minimum_energy &
    // Elk.
    double MINtoLK_linlog;
    // the coefficient of the linear power of input_energy times its logarithm
    // between minimum_energy & Elk.
    double MINtoLK_lin;
    // the coefficient of the linear power of input_energy between
    // minimum_energy & Elk.
    double MINtoLK_log;
    // the coefficient of the logarithm of input_energy between minimum_energy
    // & Elk.
    double MINtoLK_const;
    // the coefficient constant with respect to input_energy between
    // minimum_energy & Elk.
    double MINtoLK_inv;
    // the coefficient of the linear inverse power of input_energy between
    // minimum_energy & Elk.

    double LKtoHK_sq;
    // the coefficient of the square of input_energy between Elk & Ehk.
    double LKtoHK_lin;
    // the coefficient of the linear power of input_energy between Elk & Ehk.
    double LKtoHK_const;
    // the coefficient constant with respect to input_energy between Elk & Ehk.

    double HKtoMAX_sq;
    // the coefficient of the square of input_energy between Ehk &
    // maximum_energy.
    double HKtoMAX_linlog;
    // the coefficient of the linear power of input_energy times its logarithm
    // between Ehk & maximum_energy.
    double HKtoMAX_lin;
    // the coefficient of the linear power of input_energy between Ehk &
    // maximum_energy.
    double HKtoMAX_log;
    // the coefficient of the logarithm of input_energy between Ehk &
    // maximum_energy.
    double HKtoMAX_const;
    // the coefficient constant with respect to input_energy between Ehk &
    // maximum_energy.
    double HKtoMAX_inv;
    // the coefficient of the linear inverse power of input_energy between Ehk
    // & maximum_energy.


  };

  /* this derived class sets up the energy distribution for a light lepton
   * which is from the decay of an on-shell negatively-charged W boson from the
   * cascade decay of a down-type squark to a right-handed jet plus a
   * negatively-charged light lepton plus an antineutrino plus a lightest
   * neutralino.  it also seems to be the same for an up-type squark decaying
   * into a left-handed jet plus a positively-charged light antilepton plus a
   * neutrino plus a lightest neutralino.
   */
  class W_minus_plus_up_R_type_muon : public lepton_energy_distribution
  {

  public:

    W_minus_plus_up_R_type_muon( CppSLHA::CppSLHA0 const* const given_spectrum,
                    CppSLHA::particle_property_set const* const first_particle,
                                 double const effective_first_mass,
                   CppSLHA::particle_property_set const* const second_particle,
                    CppSLHA::particle_property_set const* const third_particle,
                  CppSLHA::particle_property_set const* const fourth_particle )
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    virtual
    ~W_minus_plus_up_R_type_muon()
    /* code after the classes in this .hpp file, or in the .cpp file. */;


  protected:

    // the various coefficients for each case are given their own variables:

    double MINtoLK_sq;
    // the coefficient of the square of input_energy between minimum_energy &
    // Elk.
    double MINtoLK_linlog;
    // the coefficient of the linear power of input_energy times its logarithm
    // between minimum_energy & Elk.
    double MINtoLK_lin;
    // the coefficient of the linear power of input_energy between
    // minimum_energy & Elk.
    double MINtoLK_log;
    // the coefficient of the logarithm of input_energy between minimum_energy
    // & Elk.
    double MINtoLK_const;
    // the coefficient constant with respect to input_energy between
    // minimum_energy & Elk.
    double MINtoLK_inv;
    // the coefficient of the linear inverse power of input_energy between
    // minimum_energy & Elk.

    double LKtoHK_sq;
    // the coefficient of the square of input_energy between Elk & Ehk.
    double LKtoHK_lin;
    // the coefficient of the linear power of input_energy between Elk & Ehk.
    double LKtoHK_const;
    // the coefficient constant with respect to input_energy between Elk & Ehk.

    double HKtoMAX_sq;
    // the coefficient of the square of input_energy between Ehk &
    // maximum_energy.
    double HKtoMAX_linlog;
    // the coefficient of the linear power of input_energy times its logarithm
    // between Ehk & maximum_energy.
    double HKtoMAX_lin;
    // the coefficient of the linear power of input_energy between Ehk &
    // maximum_energy.
    double HKtoMAX_log;
    // the coefficient of the logarithm of input_energy between Ehk &
    // maximum_energy.
    double HKtoMAX_const;
    // the coefficient constant with respect to input_energy between Ehk &
    // maximum_energy.
    double HKtoMAX_inv;
    // the coefficient of the linear inverse power of input_energy between Ehk
    // & maximum_energy.

  };

  // averaging over both jets from the Z boson produces the same distribution
  // as directly-produced light leptons.
  class Z_direct_jet : public Z_muon_plus_antimuon
  {

  public:

    Z_direct_jet( CppSLHA::CppSLHA0 const* const given_spectrum,
                    CppSLHA::particle_property_set const* const first_particle,
                               double const effective_first_mass,
                   CppSLHA::particle_property_set const* const second_particle,
                    CppSLHA::particle_property_set const* const third_particle,
                CppSLHA::particle_property_set const* const fourth_particle ) :
      Z_muon_plus_antimuon( given_spectrum,
                            first_particle,
                            effective_first_mass,
                            second_particle,
                            third_particle,
                            fourth_particle )
    {

      // just an initialization of the base class object.

    }

    virtual
    ~Z_direct_jet()
    {

      // does nothing.

    }

  };

  // averaging over both jets from the W boson produces the same distribution
  // which Z bosons produce.
  class W_minus_direct_jet : public Z_muon_plus_antimuon

  {

  public:

    W_minus_direct_jet( CppSLHA::CppSLHA0 const* const given_spectrum,
                    CppSLHA::particle_property_set const* const first_particle,
                        double const effective_first_mass,
                   CppSLHA::particle_property_set const* const second_particle,
                    CppSLHA::particle_property_set const* const third_particle,
                CppSLHA::particle_property_set const* const fourth_particle ) :
      Z_muon_plus_antimuon( given_spectrum,
                            first_particle,
                            effective_first_mass,
                            second_particle,
                            third_particle,
                            fourth_particle )
    {

      // just an initialization of the base class object.

    }

    virtual
    ~W_minus_direct_jet()
    {

      // does nothing.

    }

  };

  /* this is a derived class which sets up the energy distribution for a muon
   * or pion which is from the decay of a left- or right-handed tau lepton or
   * antilepton with the provided energy distribution.
   */
  class visible_tau_decay_product : public lepton_energy_distribution
  {

  public:

    visible_tau_decay_product(
                      lepton_energy_distribution const* const tau_distribution,
                               tau_decay_coefficient const* const tau_decay )
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    virtual
    ~visible_tau_decay_product()
    /* code after the classes in this .hpp file, or in the .cpp file. */;


  //protected:

    // nothing.

  };


  /* FROM THIS POINT ON ARE DERIVED CLASSES WHICH STILL NEED WORK!
   * ALL ARE CURRENTLY ROUGH GUESSES!
   * direct light leptons: charged EWSB scalar decay
   *   - equations in progress...
   * direct light leptons: 3-body neutralino decay
   *   - equations in progress...
   * direct light leptons: 3-body chargino decay
   *   - equations in progress...
   * direct jets: charged EWSB scalar decay
   *   - should be a quick modification of the light lepton case.
   * direct jets: 3-body neutralino decay
   *   - should be a quick modification of the light lepton case.
   * direct jets: 3-body chargino decay
   *   - should be a quick modification of the light lepton case.
   */

  /* placeholder of neutral Higgs distribution. it's different, because the
   * chiral couplings of the charged Higgs with the chargino & neutralino make
   * the neutralino prefer to be aligned or anti-aligned (depending on the
   * couplings) with the jet, & thus the charged Higgs is preferentially
   * boosted more or less compared to the neutral Higgs case, & thus the
   * muon distribution is different.
   */
  class negatively_charged_Higgs_muon : public Higgs_muon_plus_antimuon
  {

  public:

    negatively_charged_Higgs_muon(
                                 CppSLHA::CppSLHA0 const* const given_spectrum,
                    CppSLHA::particle_property_set const* const first_particle,
                                   double const effective_first_mass,
                   CppSLHA::particle_property_set const* const second_particle,
                    CppSLHA::particle_property_set const* const third_particle,
                CppSLHA::particle_property_set const* const fourth_particle ) :
      Higgs_muon_plus_antimuon( given_spectrum,
                                first_particle,
                                effective_first_mass,
                                second_particle,
                                third_particle,
                                fourth_particle )
    {

      // just an initialization of the base class object.

    }

    virtual
    ~negatively_charged_Higgs_muon()
    {

      // does nothing.

    }

  };

  /* placeholder of neutral Higgs distribution. it's different, because the
   * chiral couplings of the charged Higgs with the chargino & neutralino make
   * the neutralino prefer to be aligned or anti-aligned (depending on the
   * couplings) with the jet, & thus the charged Higgs is preferentially
   * boosted more or less compared to the neutral Higgs case, & thus the
   * jet distribution is different.
   */
  class negatively_charged_Higgs_jet : public Higgs_muon_plus_antimuon
  {

  public:

    negatively_charged_Higgs_jet(
                                 CppSLHA::CppSLHA0 const* const given_spectrum,
                    CppSLHA::particle_property_set const* const first_particle,
                                   double const effective_first_mass,
                   CppSLHA::particle_property_set const* const second_particle,
                    CppSLHA::particle_property_set const* const third_particle,
                CppSLHA::particle_property_set const* const fourth_particle ) :
      Higgs_muon_plus_antimuon( given_spectrum,
                                first_particle,
                                effective_first_mass,
                                second_particle,
                                third_particle,
                                fourth_particle )
    {

      // just an initialization of the base class object.

    }

    virtual
    ~negatively_charged_Higgs_jet()
    {

      // does nothing.

    }

  };


  /* this needs to know the 2 sfermions which appear off-shell in the process.
   * they are given as "left" & "right", but the code checks for 3rd-generation
   * sfermions & treats them accordingly.
   * currently this is a placeholder guess of a flat distribution from 0.0 GeV
   * to the neutralino mass difference.
   */
  class neutralino_three_body_decay : public lepton_energy_distribution
  {

  public:

    neutralino_three_body_decay( CppSLHA::CppSLHA0 const* const given_spectrum,
                    CppSLHA::particle_property_set const* const first_particle,
                                 double const effective_first_mass,
                   CppSLHA::particle_property_set const* const second_particle,
                    CppSLHA::particle_property_set const* const third_particle,
                     CppSLHA::particle_property_set const* const left_sfermion,
                 CppSLHA::particle_property_set const* const right_sfermion ) :
      lepton_energy_distribution( given_spectrum,
                                  effective_first_mass,
                                  second_particle->get_absolute_mass(),
                                  third_particle->get_absolute_mass(),
                                  0.0 )
    {

      minimum_energy = 0.0;

      maximum_energy = ( second_mass - third_mass );


      // now we set up the coefficients of various terms, & use them to
      // determine the normalization:

      normalization = maximum_energy;


      // finally we fill the sets of terms, segment by segment.

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

    virtual
    ~neutralino_three_body_decay()
    {

      // does nothing.

    }


  //protected:

    // nothing.

  };

  /* this needs to know the 2 sfermions which appear off-shell in the process.
   * they are given as "left" & "right", but the code checks for 3rd-generation
   * sfermions & treats them accordingly.
   * currently this is a placeholder guess of a flat distribution from 0.0 GeV
   * to the mass difference between the chargino & the neutralino.
   */
  class chargino_three_body_decay : public lepton_energy_distribution
  {

  public:

    chargino_three_body_decay( CppSLHA::CppSLHA0 const* const given_spectrum,
                    CppSLHA::particle_property_set const* const first_particle,
                               double const effective_first_mass,
                   CppSLHA::particle_property_set const* const second_particle,
                    CppSLHA::particle_property_set const* const third_particle,
               CppSLHA::particle_property_set const* const first_left_sfermion,
              CppSLHA::particle_property_set const* const first_right_sfermion,
              CppSLHA::particle_property_set const* const second_left_sfermion,
          CppSLHA::particle_property_set const* const second_right_sfermion ) :
      lepton_energy_distribution( given_spectrum,
                                  effective_first_mass,
                                  second_particle->get_absolute_mass(),
                                  third_particle->get_absolute_mass(),
                                  0.0 )
    {

      minimum_energy = 0.0;

      maximum_energy = ( second_mass - third_mass );


      // now we set up the coefficients of various terms, & use them to
      // determine the normalization:

      normalization = maximum_energy;


      // finally we fill the sets of terms, segment by segment.

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

    virtual
    ~chargino_three_body_decay()
    {

      // does nothing.

    }


  //protected:

    // nothing.

  };

}  // end of LHC_FASER namespace.

#endif  // LHC_FASER_LEPTON_DISTRIBUTIONS_HPP
