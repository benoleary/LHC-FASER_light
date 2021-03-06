/*
 * LHC-FASER_base_lepton_distribution_stuff.hpp
 *
 *  Created on: 17 Mar 2010
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

/* this is a set of classes used for the calculation of the fraction of leptons
 * that pass various cuts at the moment. it also includes jets by pretending
 * that they're basically leptons.
 */


#ifndef LHC_FASER_BASE_LEPTON_DISTRIBUTION_STUFF_HPP
#define LHC_FASER_BASE_LEPTON_DISTRIBUTION_STUFF_HPP

#include "CppSLHA/CppSLHA.hpp"
#include "LHC-FASER_global_stuff.hpp"

namespace LHC_FASER
{
  // this class is to make it easier to update the effective squark mass.
  class effectiveSquarkMassHolder
  {
  public:
    effectiveSquarkMassHolder()
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    virtual
    ~effectiveSquarkMassHolder()
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    virtual double
    getEffectiveSquarkMass()
    = 0;

  //protected:
    // nothing
  };

  // this derived class is for the case of on-shell squarks:
  class onshellSquarkMassHolder : public effectiveSquarkMassHolder
  {
  public:
    onshellSquarkMassHolder(
                    CppSLHA::particle_property_set const* const onshellSquark )
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    virtual
    ~onshellSquarkMassHolder()
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    virtual double
    getEffectiveSquarkMass()
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    CppSLHA::particle_property_set const*
    getOnshellSquark()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

  protected:
    CppSLHA::particle_property_set const* onshellSquark;
  };


  // this class is for emulating doing minor symbolic algebra.
  class leptonDistributionExpansionTerm
  {
  public:
    static double const minimumInputEnergy;
    // this is used to prevent trying to take logarithms of 0.0 or less.

    leptonDistributionExpansionTerm( int const powerOfEnergy,
                                     int const powerOfLogarithm,
                                     double const coefficientValue,
                  leptonDistributionExpansionTerm* const referenceTerm = NULL )
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    virtual
    ~leptonDistributionExpansionTerm()
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    leptonDistributionExpansionTerm const*
    getReferenceTerm()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    int
    getPowerOfEnergy()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    int
    getPowerOfLogarithm()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    double
    getCoefficient()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    void
    setCoefficient( double const coefficientValue )
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    void
    addToCoefficient( double const coefficientValue )
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    void
    normalizeCoefficient( double const normalizingFactor )
    // this just multiplies coefficientValue by normalizingFactor.
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    virtual double
    evaluate( double const inputEnergy )
    const
    // this evaluates this term for the given input energy.
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    virtual double
    getArea( double startEnergy,
             double endEnergy )
    const
    // this gives the definite integral of the term from startEnergy to
    // endEnergy.
    /* code after the classes in this .hpp file, or in the .cpp file. */;

  protected:
    int powerOfEnergy;
    int powerOfLogarithm;
    double coefficientValue;
    leptonDistributionExpansionTerm* const referenceTerm;
    // this is for ease of updating coefficients in tauon-decay distributions.
  };

  class leptonDistributionInverseTerm : public leptonDistributionExpansionTerm
  {
  public:
    leptonDistributionInverseTerm( double const coefficientValue,
                  leptonDistributionExpansionTerm* const referenceTerm = NULL )
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    virtual
    ~leptonDistributionInverseTerm()
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    virtual double
    evaluate( double const inputEnergy )
    const
    // this evaluates this term for the given input energy.
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    virtual double
    getArea( double startEnergy,
             double endEnergy )
    const
    // this gives the definite integral of the term from startEnergy to
    // endEnergy.
    /* code after the classes in this .hpp file, or in the .cpp file. */;

  protected:
    // nothing.
  };

  class leptonDistributionConstantTerm : public leptonDistributionExpansionTerm
  {
  public:
    leptonDistributionConstantTerm( double const coefficientValue,
                  leptonDistributionExpansionTerm* const referenceTerm = NULL )
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    virtual
    ~leptonDistributionConstantTerm()
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    virtual double
    evaluate( double const inputEnergy )
    const
    // this evaluates this term for the given input energy.
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    virtual double
    getArea( double startEnergy,
             double endEnergy )
    const
    // this gives the definite integral of the term from startEnergy to
    // endEnergy.
    /* code after the classes in this .hpp file, or in the .cpp file. */;

  protected:
    // nothing.
  };

  class leptonDistributionPowerTerm : public leptonDistributionExpansionTerm
  {
  public:
    leptonDistributionPowerTerm( int const powerOfEnergy,
                                 double const coefficientValue,
                  leptonDistributionExpansionTerm* const referenceTerm = NULL )
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    virtual
    ~leptonDistributionPowerTerm()
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    virtual double
    evaluate( double const inputEnergy )
    const
    // this evaluates this term for the given input energy.
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    virtual double
    getArea( double startEnergy,
             double endEnergy )
    const
    // this gives the definite integral of the term from startEnergy to
    // endEnergy.
    /* code after the classes in this .hpp file, or in the .cpp file. */;

  protected:
    // nothing.
  };


  // this is a class to hold a set of leptonDistributionExpansionTerm
  // objects relevant for an energy range for the distribution.
  class segmentTermSet
  {
  public:
    segmentTermSet()
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    ~segmentTermSet()
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    double
    getSegmentStart()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    void
    setSegmentStart( double const inputValue )
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    double
    getSegmentEnd()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    void
    setSegmentEnd( double const inputValue )
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    void
    setSegmentRange( double const rangeStart,
                     double const rangeEnd )
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    std::vector< leptonDistributionExpansionTerm* > const*
    getTerms()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    int
    getNumberOfTerms()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    leptonDistributionExpansionTerm*
    addTerm( int const powerOfEnergy,
             int const powerOfLogarithm,
             leptonDistributionExpansionTerm* const referenceTerm = NULL,
             double const
             coefficientValue = CppSLHA::CppSLHA_global::really_wrong_value )
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    void
    normalizeCoefficients( double const normalizingFactor )
    // this goes through each term & gets it to multiply its coefficient
    // by normalizingFactor.
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    double
    getCoefficient( int const powerOfEnergy,
                    int const powerOfLogarithm )
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    double
    evaluate( double const inputEnergy )
    const
    // this evaluates the sum of the set of terms for the given input energy.
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    double
    getArea()
    const
    // this evaluates the sum of the areas of the set of terms for the
    // segment's range.
    /* code after the classes in this .hpp file, or in the .cpp file. */;

  protected:
    std::vector< leptonDistributionExpansionTerm* > segmentTerms;
    // the segmentTermSet is responsible for calling the destructors of the
    // leptonDistributionExpansionTerms held in segmentTerms.
    leptonDistributionExpansionTerm* termAdder;
    double segmentStart;
    double segmentEnd;
  };



  /* this class is the base abstract class for the functors for obtaining
   * energy distributions for the visible decay productSet of tau leptons with
   * given energy distributions.
   * (yes, left-handed tau leptons / right-handed tau antileptons give harder
   * muons / electrons but softer pions than the other helicity.)
   */
  class tauDecayCoefficient
  {
  public:
    tauDecayCoefficient()
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    virtual
    ~tauDecayCoefficient()
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    virtual double
    operator()( int const visibleProductEnergyPower
                 /* the power of the visible product's energy for the term. */,
                int const visibleProductLogPower
/* the power of the logarithm of the visible product's energy for the term. */,
                int const tauLeptonEnergyPower
                /* the power of the tau lepton's energy for the term. */,
                int const tauLeptonLogPower
     /* the power of the logarithm of the tau lepton's energy for the term. */,
                double tauMinEnergy
         /* the minimum of the range of the tau lepton energies considered. */,
                double const tauMaxEnergy
         /* the maximum of the range of the tau lepton energies considered. */,
                bool const isInsideRange )
    const
    = 0;
    /* this is overridden by functions which return the value of the
     * coefficient for the specified term for the tauon decay product from the
     * specified term for the tauon.
     */

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
  class hardMuonFromTau : public tauDecayCoefficient
  {
  public:
    hardMuonFromTau()
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    virtual
    ~hardMuonFromTau()
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    virtual double
    operator()( int const visibleProductEnergyPower
                /* the power of the visible product's energy for the term. */,
                int const visibleProductLogPower
/* the power of the logarithm of the visible product's energy for the term. */,
                int const tauLeptonEnergyPower
                /* the power of the tau lepton's energy for the term. */,
                int const tauLeptonLogPower
    /* the power of the logarithm of the tau lepton's energy for the term. */,
                double tauMinEnergy
         /* the minimum of the range of the tau lepton energies considered. */,
                double const tauMaxEnergy
         /* the maximum of the range of the tau lepton energies considered. */,
                bool const isInsideRange )
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

  //protected:
    // nothing.
  };

  /* this functor returns the coefficientValue for the muon distribution which would
   * come from a right-handed tau lepton distribution of the given power of the
   * tau lepton's energy & power of logarithm thereof, for requested integer
   * powers of the muon's energy or logarithm thereof, which also depends on
   * whether the muon's energy is inside the range of the tau lepton's energy
   * for this segment.
   */
  class softMuonFromTau : public tauDecayCoefficient
  {
  public:
    softMuonFromTau()
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    virtual
    ~softMuonFromTau()
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    virtual double
    operator()( int const visibleProductEnergyPower
                /* the power of the visible product's energy for the term. */,
                int const visibleProductLogPower
/* the power of the logarithm of the visible product's energy for the term. */,
                int const tauLeptonEnergyPower
                /* the power of the tau lepton's energy for the term. */,
                int const tauLeptonLogPower
     /* the power of the logarithm of the tau lepton's energy for the term. */,
                double tauMinEnergy
         /* the minimum of the range of the tau lepton energies considered. */,
                double const tauMaxEnergy
         /* the maximum of the range of the tau lepton energies considered. */,
                bool const isInsideRange )
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

  //protected:
    // nothing.
  };

  /* this functor returns the coefficientValue for the pion distribution which would
   * come from a right-handed tau lepton distribution of the given power of the
   * tau lepton's energy & power of logarithm thereof, for requested integer
   * powers of the pion's energy or logarithm thereof, which also depends on
   * whether the pion's energy is inside the range of the tau lepton's energy
   * for this segment.
   */
  class hardPionFromTau : public tauDecayCoefficient
  {
  public:
    hardPionFromTau()
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    virtual
    ~hardPionFromTau()
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    virtual double
    operator()( int const visibleProductEnergyPower
                /* the power of the visible product's energy for the term. */,
                int const visibleProductLogPower
/* the power of the logarithm of the visible product's energy for the term. */,
                int const tauLeptonEnergyPower
                /* the power of the tau lepton's energy for the term. */,
                int const tauLeptonLogPower
     /* the power of the logarithm of the tau lepton's energy for the term. */,
                double tauMinEnergy
         /* the minimum of the range of the tau lepton energies considered. */,
                double const tauMaxEnergy
         /* the maximum of the range of the tau lepton energies considered. */,
                bool const isInsideRange )
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

  //protected:
    // nothing.
  };

  /* this functor returns the coefficientValue for the pion distribution which would
   * come from a left-handed tau lepton distribution of the given power of the
   * tau lepton's energy & power of logarithm thereof, for requested integer
   * powers of the pion's energy or logarithm thereof, which also depends on
   * whether the pion's energy is inside the range of the tau lepton's energy
   * for this segment.
   */
  class softPionFromTau : public tauDecayCoefficient
  {
  public:
    softPionFromTau()
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    virtual
    ~softPionFromTau()
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    virtual double
    operator()( int const visibleProductEnergyPower
                /* the power of the visible product's energy for the term. */,
                int const visibleProductLogPower
/* the power of the logarithm of the visible product's energy for the term. */,
                int const tauLeptonEnergyPower
                /* the power of the tau lepton's energy for the term. */,
                int const tauLeptonLogPower
     /* the power of the logarithm of the tau lepton's energy for the term. */,
                double tauMinEnergy
         /* the minimum of the range of the tau lepton energies considered. */,
                double const tauMaxEnergy
         /* the maximum of the range of the tau lepton energies considered. */,
                bool const isInsideRange )
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;

  //protected:
    // nothing.
  };


  /* this holds together a pair of segmentTermSet pointers for the 2 parts of
   * of the distribution for the visible decay product of a tau lepton with
   * distribution given by the 3rd segmentTermSet pointer the
   * tauSegmentTriple has. it performs the role of updating the visible decay
   * product terms based on the reference terms.
   */
  class tauSegmentTriple
  {
  public:
    tauSegmentTriple( std::vector< segmentTermSet* >* segmentSetToPopulate,
                      segmentTermSet* referenceSegment,
                      tauDecayCoefficient const* const tauDecay )
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    ~tauSegmentTriple()
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    void
    updateSegments()
    /* code after the classes in this .hpp file, or in the .cpp file. */;

  protected:
    segmentTermSet* referenceSegment;
    segmentTermSet* lowSegment;
    segmentTermSet* highSegment;
    tauDecayCoefficient const* const tauDecay;
  };

  /* this class is just an abstract base class for some polymorphic derived
   * classes. However, it does do most of the work, the derived classes just
   * set up the leptonDistributionExpansionTerm objects properly.
   */
  class leptonEnergyDistribution : public getsReadiedForNewPoint
  {
  public:
    leptonEnergyDistribution( readierForNewPoint* const readier,
                              CppSLHA::CppSLHA0 const* const spectrum,
                     CppSLHA::particle_property_set const* const firstParticle,
                          effectiveSquarkMassHolder* const effectiveSquarkMass,
                    CppSLHA::particle_property_set const* const secondParticle,
                     CppSLHA::particle_property_set const* const thirdParticle,
                   CppSLHA::particle_property_set const* const fourthParticle )
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    virtual
    ~leptonEnergyDistribution()
    /* code after the classes in this .hpp file, or in the .cpp file. */;

    double
    getMinimumEnergy()
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    double
    getMaximumEnergy()
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    std::vector< segmentTermSet* >*
    getSegments()
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    std::vector< segmentTermSet* > const*
    inspectSegments()
    const
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    double
    valueAt( double const inputEnergy )
    // this returns the value of the distribution at the given value, with
    // arbitrary normalization (different for each distribution).
    /* code after the classes in this .hpp file, or in the .cpp file. */;

  protected:
    CppSLHA::CppSLHA0 const* spectrum;
    // this holds all the information about the MSSM point. care must be taken
    // to ensure that it has the appropriate BLOCKs for the distribution.
    double minimumEnergy;
    double maximumEnergy;

    std::vector< segmentTermSet* > segments;

    CppSLHA::particle_property_set const* const firstParticle;
    effectiveSquarkMassHolder* const effectiveSquarkMass;
    CppSLHA::particle_property_set const* const secondParticle;
    CppSLHA::particle_property_set const* const thirdParticle;
    CppSLHA::particle_property_set const* const fourthParticle;
    /* these masses could be pulled out of spectrumData every time they are
     * needed, but it's probably worthwhile to have them as quickly-accessible
     * doubles:
     */
    double firstMass;
    // the squark mass in a standard decay, but let's pretend that I'm being
    // general.
    double secondMass;
    // the intermediate neutralino mass in the standard decay, but could be
    // e.g. the chargino mass in a certain decay.
    double thirdMass;
    // the slepton mass in the standard decay, but could be e.g.
    // the Z boson mass or sneutrino mass.
    double fourthMass;
    // the lightest neutralino mass in the standard decay, but could be
    // something else in some crazy cascade.
    double normalizingDivisor;
    // this is *an overall denominator*, rather than a multiplicative
    // normalization.
    double normalizingFactor;
    // this *is* an overall multiplicative normalization
    // (= 1.0 / normalizingDivisor ).
    // this is not strictly necessary, but is handy for distributions from
    // on-shell cascades:
    double productionFrameEnergy;

    void
    reset()
    // this updates the masses then calls calculate_coefficients().
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    virtual void
    calculateCoefficients()
    = 0;
    // this is overridden by functions which calculate & set the coefficients
    // of all the terms of the distribution.
    void
    normalizeCoefficients()
    // this goes through each segment & gets it to divide its terms'
    // coefficients by normalization.
    /* code after the classes in this .hpp file, or in the .cpp file. */;
  };


  /* this is a derived class which sets up the energy distribution for a muon
   * or pion which is from the decay of a left- or right-handed tau lepton or
   * antilepton with the provided energy distribution.
   */
  class visibleTauDecayProduct : public leptonEnergyDistribution
  {
  public:
    visibleTauDecayProduct( readierForNewPoint* const readier,
                            leptonEnergyDistribution* const tauDistribution,
                            tauDecayCoefficient const* const tauDecay )
    /* code after the classes in this .hpp file, or in the .cpp file. */;
    virtual
    ~visibleTauDecayProduct()
    /* code after the classes in this .hpp file, or in the .cpp file. */;

  protected:
    leptonEnergyDistribution* const tauDistribution;
    std::vector< tauSegmentTriple* > tauTriples;

    virtual void
    calculateCoefficients()
    // this is overridden by functions which calculate & set the coefficients
    // of all the terms of the distribution.
    /* code after the classes in this .hpp file, or in the .cpp file. */;
  };




  // inline functions


  inline double
  onshellSquarkMassHolder::getEffectiveSquarkMass()
  {
    return onshellSquark->get_absolute_mass();
  }

  inline CppSLHA::particle_property_set const*
  onshellSquarkMassHolder::getOnshellSquark()
  const
  {
    return onshellSquark;
  }



  inline leptonDistributionExpansionTerm const*
  leptonDistributionExpansionTerm::getReferenceTerm()
  const
  {
    return referenceTerm;
  }

  inline int
  leptonDistributionExpansionTerm::getPowerOfEnergy()
  const
  {
    return powerOfEnergy;
  }

  inline int
  leptonDistributionExpansionTerm::getPowerOfLogarithm()
  const
  {
    return powerOfLogarithm;
  }

  inline double
  leptonDistributionExpansionTerm::getCoefficient()
  const
  {
    return coefficientValue;
  }

  inline void
  leptonDistributionExpansionTerm::setCoefficient(
                                                double const coefficientValue )
  {
     this->coefficientValue = coefficientValue;
  }

  inline void
  leptonDistributionExpansionTerm::addToCoefficient(
                                                double const coefficientValue )
  {
     this->coefficientValue += coefficientValue;
  }

  inline void
  leptonDistributionExpansionTerm::normalizeCoefficient(
                                               double const normalizingFactor )
  // this just multiplies coefficientValue by normalizingFactor.
  {
    coefficientValue *= normalizingFactor;
  }



  inline double
  leptonDistributionInverseTerm::evaluate( double const inputEnergy )
  const
  // this evaluates this term for the given input energy.
  {
    return ( coefficientValue / inputEnergy );
  }

  inline double
  leptonDistributionInverseTerm::getArea( double startEnergy,
                                          double endEnergy )
  const
  // this gives the definite integral of the term from startEnergy to
  // endEnergy.
  {
    double returnValue( 0.0 );
    if( 0.0 != coefficientValue )
    {
      if( minimumInputEnergy > startEnergy )
      {
        startEnergy = minimumInputEnergy;
      }

      if( endEnergy > startEnergy )
      {
        returnValue
        = ( coefficientValue * log( ( endEnergy / startEnergy ) ) );
      }
    }
    return returnValue;
  }



  inline double
  leptonDistributionConstantTerm::evaluate( double const inputEnergy )
  const
  // this evaluates this term for the given input energy.
  {
    return coefficientValue;
  }

  inline double
  leptonDistributionConstantTerm::getArea( double startEnergy,
                                           double endEnergy )
  const
  // this gives the definite integral of the term from startEnergy to
  // endEnergy.
  {
    double returnValue( 0.0 );
    if( 0.0 != coefficientValue )
    {
      if( minimumInputEnergy > startEnergy )
      {
        startEnergy = minimumInputEnergy;
      }

      if( endEnergy > startEnergy )
      {
        returnValue
        = ( coefficientValue * ( endEnergy - startEnergy ) );
      }
    }
    return returnValue;
  }



  inline double
  leptonDistributionPowerTerm::evaluate( double const inputEnergy )
  const
  // this evaluates this term for the given input energy.
  {
    if( 0.0 != coefficientValue )
    {
      double returnValue( coefficientValue );

      for( int powerCount( powerOfEnergy );
           0 < powerCount;
           --powerCount )
      {
        returnValue *= inputEnergy;
      }
      return returnValue;
    }
    else
    {
      return 0.0;
    }
  }



  inline double
  segmentTermSet::getSegmentStart()
  const
  {
    return segmentStart;
  }

  inline void
  segmentTermSet::setSegmentStart( double const inputValue )
  {
    segmentStart = inputValue;
  }

  inline double
  segmentTermSet::getSegmentEnd()
  const
  {
    return segmentEnd;
  }

  inline void
  segmentTermSet::setSegmentEnd( double const inputValue )
  {
    segmentEnd = inputValue;
  }

  inline void
  segmentTermSet::setSegmentRange( double const rangeStart,
                                   double const rangeEnd )
  {
    segmentStart = rangeStart;
    segmentEnd = rangeEnd;
  }

  inline std::vector< leptonDistributionExpansionTerm* > const*
  segmentTermSet::getTerms()
  const
  {
    return &segmentTerms;
  }

  inline int
  segmentTermSet::getNumberOfTerms()
  const
  {
    return (int)segmentTerms.size();
  }

  inline void
  segmentTermSet::normalizeCoefficients( double const normalizingFactor )
  // this goes through each term & gets it to multiply its coefficientValue by
  // normalizingFactor.
  {
    for( std::vector< leptonDistributionExpansionTerm* >::iterator
         termIterator( segmentTerms.begin() );
         segmentTerms.end() > termIterator;
         ++termIterator )
    {
      (*termIterator)->normalizeCoefficient( normalizingFactor );
    }
  }

  inline double
  segmentTermSet::getCoefficient( int const powerOfEnergy,
                                  int const powerOfLogarithm )
  const
  {
    double returnValue( 0.0 );
    // start by assuming that the coefficientValue is zero.
    for( std::vector< leptonDistributionExpansionTerm* >::const_iterator
         termIterator( segmentTerms.begin() );
         segmentTerms.end() > termIterator;
         ++termIterator )
      // go through all the terms...
      {
        if( ( powerOfEnergy == (*termIterator)->getPowerOfEnergy() )
            &&
            ( powerOfLogarithm == (*termIterator)->getPowerOfLogarithm() ) )
          // if we find the requested term with a non-zero coefficientValue...
        {
          returnValue = (*termIterator)->getCoefficient();
          // note the coefficientValue to return.
          termIterator = segmentTerms.end();
          // stop looking.
        }
      }
    return returnValue;
  }

  inline double
  segmentTermSet::getArea()
  const
  // this evaluates the sum of the areas of the set of terms for the segment's
  // range.
  {
    double returnValue( 0.0 );
    for( std::vector< leptonDistributionExpansionTerm* >::const_iterator
        summationIterator( segmentTerms.begin() );
        summationIterator < segmentTerms.end();
        ++summationIterator )
    {
      returnValue += (*summationIterator)->getArea( segmentStart,
                                                    segmentEnd );
    }
    return returnValue;
  }



  inline double
  leptonEnergyDistribution::valueAt( double const inputEnergy )
  // this returns the value of the distribution at the given value, with
  // arbitrary normalization (different for each distribution).
  {
    if( needsToPrepareForThisPoint() )
    {
      reset();
      finishPreparingForThisPoint();
    }
    double returnValue( 0.0 );
    for( std::vector< segmentTermSet* >::const_iterator
         summationIterator( segments.begin() );
         segments.end() > summationIterator;
         ++summationIterator )
    {
      returnValue += (*summationIterator)->evaluate( inputEnergy );
    }
    return returnValue;
  }

  inline double
  leptonEnergyDistribution::getMinimumEnergy()
  {
    if( needsToPrepareForThisPoint() )
    {
      reset();
      finishPreparingForThisPoint();
    }
    return minimumEnergy;
  }

  inline double
  leptonEnergyDistribution::getMaximumEnergy()
  {
    if( needsToPrepareForThisPoint() )
    {
      reset();
      finishPreparingForThisPoint();
    }
    return maximumEnergy;
  }

  inline std::vector< segmentTermSet* >*
  leptonEnergyDistribution::getSegments()
  {
    return &segments;
  }

  inline std::vector< segmentTermSet* > const*
  leptonEnergyDistribution::inspectSegments()
  const
  {
    return &segments;
  }

  inline void
  leptonEnergyDistribution::normalizeCoefficients()
  // this goes through each segment & gets it to divide its terms' coefficients
  // by normalization.
  {
    normalizingDivisor = 0.0;
    for( std::vector< segmentTermSet* >::iterator
         segmentIterator( segments.begin() );
         segments.end() > segmentIterator;
         ++segmentIterator )
    {
      normalizingDivisor += (*segmentIterator)->getArea();
    }
    normalizingFactor = ( 1.0 / normalizingDivisor );
    for( std::vector< segmentTermSet* >::iterator
         segmentIterator( segments.begin() );
         segments.end() > segmentIterator;
         ++segmentIterator )
    {
      (*segmentIterator)->normalizeCoefficients( normalizingFactor );
    }
  }

}  // end of LHC_FASER namespace.

#endif  // LHC_FASER_BASE_LEPTON_DISTRIBUTION_STUFF_HPP
