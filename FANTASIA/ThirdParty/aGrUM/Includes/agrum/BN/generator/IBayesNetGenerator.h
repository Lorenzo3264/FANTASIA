
/**
 *
 *  Copyright 2005-2019 Pierre-Henri WUILLEMIN et Christophe GONZALES (LIP6)
 *   {prenom.nom}_at_lip6.fr
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


/** @file
 * @brief Interface-like class for generating bayesian networks.
 *
 * @author Christophe GONZALES, Pierre-Henri WUILLEMIN, Lionel TORTI and
 * Ariele-Paolo MAESANO
 */
#ifndef GUM_I_BAYES_NET_GENERATOR_H
#define GUM_I_BAYES_NET_GENERATOR_H

#include <climits>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

#include <agrum/BN/BayesNet.h>
#include <agrum/BN/generator/simpleCPTGenerator.h>
#include <agrum/agrum.h>

#include <agrum/variables/labelizedVariable.h>

#include <agrum/BN/algorithms/divergence/BNdistance.h>

namespace gum {

  /**
   * @class IBayesNetGenerator
   * @headerfile IBayesNetGenerator.h <agrum/BN/generator/IBayesNetGenerator.h>
   * @brief Class for generating bayesian networks.
   * @ingroup bn_generator
   *
   * This class is the abstract class for randomly generating a bayesian
   * network given three parameters: the number of nodes the wanted maximum
   * number of arcs and the maximum number of modality for each node.
   *
   * @warning  Be Careful when entering the parameters, high Values may cause
   * the density of the Bayesian Network to be too high resulting in the
   * failure of most of the inference Methods.
   */
  template < typename GUM_SCALAR, template < typename > class ICPTGenerator >
  class IBayesNetGenerator : public ICPTGenerator< GUM_SCALAR > {
    public:
    // ############################################################################
    /// @name Constructors / Destructor
    // ############################################################################
    /// @{
    /**
     * constructor.
     * Use by default the SimpleCPTGenerator for generating the BNs CPT.
     * @param nbrNodes The number of nodes in the generated BN.
     * @param maxArcs The number of maximum number of arcs imposed on the
     * generator
     * @param maxModality Each DRV has from 2 to maxModality modalities
     * @throws OperationNotAllowed if the number of maximum arcs does not allow
     * the
     * generation of a connexe graph maxArcs < nbrNodes -1, is too big maxArcs >
     * nbrNodes *(nbrNodes -1) /2 and if the maximum of modality is lower than
     * 2.
     */
    IBayesNetGenerator(Size nbrNodes, Size maxArcs, Size maxModality);

    /**
     * Destructor.
     */

    virtual ~IBayesNetGenerator();
    /// @}

    // ############################################################################
    /// @name BN generation methods
    // ############################################################################
    /// @{

    /**
     * Virtual function that Generates a bayesian networks.
     * @param bayesNet Bayesian Network to be completed after initialisation
     * @return null but modify inputed empty Bayesian Network
     */

    virtual void generateBN(BayesNet< GUM_SCALAR >& bayesNet) = 0;

    /**
     * function that insert random values in the CPT of each nodes according to
     * the
     * @a CPTGenerator.
     * @return null but modify inputed empty Bayesian Network
     */

    void fillCPT();

    /// @}
    // ===========================================================================
    /// @name Variable manipulation methods.
    // ===========================================================================
    /// @{
    /**
     * @name Getters
     **/

    /**
     * Return a constant reference to the number of nodes imposed on the
     * IBayesNetGenerator.
     */
    Size nbrNodes() const;

    /**
     * Return a constant reference to the maximum number of arcs imposed on the
     * IBayesNetGenerator
     */
    Size maxArcs() const;

    /**
     * Return a constant reference to the maximum modality imposed on the
     * IBayesNetGenerator
     */
    Size maxModality() const;

    /**
     * @name Setters
     **/

    //      void setcptGenerator(CPTGenerator * cptGenerator);
    /**
     * Modifies the value of the number of nodes imposed on the BayesGenerator
     */
    void setNbrNodes(Size nbrNodes);

    /**
     * Modifies the value of the number of nodes imposed on the BayesGenerator
     */
    void setMaxArcs(Size maxArcs);

    /**
     * Modifies the value of the number of nodes imposed on the BayesGenerator
     */
    void setMaxModality(Size maxModality);

    /// @}
    protected:
    // The Conditional Probability Table generator
    //  CPTGenerator * _cptGenerator;
    Size                   _nbrNodes;
    Size                   _maxArcs;
    Size                   _maxModality;
    BayesNet< GUM_SCALAR > _bayesNet;
  };

} /* namespace gum */

#include <agrum/BN/generator/IBayesNetGenerator_tpl.h>

#endif /* GUM_I_BAYES_NET_GENERATOR_H */
