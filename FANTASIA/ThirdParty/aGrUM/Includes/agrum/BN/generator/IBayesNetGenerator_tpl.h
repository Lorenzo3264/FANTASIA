
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
 * @brief Source implementation of IBayesNetGenerator
 *
 * @author Christophe GONZALES, Pierre-Henri WUILLEMIN, Lionel TORTI and
 *Ariele-Paolo
 *MAESANO
 *
 */

#include <agrum/BN/generator/IBayesNetGenerator.h>

namespace gum {

  // Default constructor.
  // Use the SimpleCPTGenerator for generating the BNs CPT.
  template < typename GUM_SCALAR, template < typename > class ICPTGenerator >
  INLINE IBayesNetGenerator< GUM_SCALAR, ICPTGenerator >::IBayesNetGenerator(
     Size nbrNodes, Size maxArcs, Size maxModality) :
      _bayesNet() {
    GUM_CONSTRUCTOR(IBayesNetGenerator);
    _nbrNodes = nbrNodes;

    if (maxArcs < nbrNodes - 1 || maxArcs > (nbrNodes * (nbrNodes - 1)) / 2)
      GUM_ERROR(OperationNotAllowed, " maxArcs value not possible ");

    if (maxModality < 2)
      GUM_ERROR(OperationNotAllowed,
                " maxModality must be at least equal to two ");

    _maxArcs = maxArcs;
    _maxModality = maxModality;
  }

  // Destructor.
  template < typename GUM_SCALAR, template < typename > class ICPTGenerator >
  INLINE IBayesNetGenerator< GUM_SCALAR, ICPTGenerator >::~IBayesNetGenerator() {
    GUM_DESTRUCTOR(IBayesNetGenerator);
    //    delete _cptGenerator;
  }

  template < typename GUM_SCALAR, template < typename > class ICPTGenerator >
  void IBayesNetGenerator< GUM_SCALAR, ICPTGenerator >::fillCPT() {
    for (auto node : _bayesNet.nodes())
      this->generateCPT(_bayesNet.cpt(node).pos(_bayesNet.variable(node)),
                        _bayesNet.cpt(node));   // TODO ASSERT THE LINE
  }

  template < typename GUM_SCALAR, template < typename > class ICPTGenerator >
  INLINE Size
         IBayesNetGenerator< GUM_SCALAR, ICPTGenerator >::maxModality() const {
    return _maxModality;
  }

  template < typename GUM_SCALAR, template < typename > class ICPTGenerator >
  INLINE Size IBayesNetGenerator< GUM_SCALAR, ICPTGenerator >::nbrNodes() const {
    return _nbrNodes;
  }

  template < typename GUM_SCALAR, template < typename > class ICPTGenerator >
  INLINE Size IBayesNetGenerator< GUM_SCALAR, ICPTGenerator >::maxArcs() const {
    return _maxArcs;
  }

  template < typename GUM_SCALAR, template < typename > class ICPTGenerator >
  INLINE void IBayesNetGenerator< GUM_SCALAR, ICPTGenerator >::setMaxModality(
     Size maxModality) {
    if (maxModality < 2)
      GUM_ERROR(OperationNotAllowed,
                " maxModality must be at least equal to two ");

    _maxModality = maxModality;
  }
  template < typename GUM_SCALAR, template < typename > class ICPTGenerator >
  INLINE void
     IBayesNetGenerator< GUM_SCALAR, ICPTGenerator >::setNbrNodes(Size nbrNodes) {
    if ((_maxArcs < nbrNodes - 1) || (_maxArcs > (nbrNodes * (nbrNodes - 1)) / 2))
      GUM_ERROR(OperationNotAllowed, " nbrNodes value not possible ");

    _nbrNodes = nbrNodes;
  }

  template < typename GUM_SCALAR, template < typename > class ICPTGenerator >
  INLINE void
     IBayesNetGenerator< GUM_SCALAR, ICPTGenerator >::setMaxArcs(Size maxArcs) {
    if (maxArcs < _nbrNodes - 1 || maxArcs > (_nbrNodes * (_nbrNodes - 1)) / 2)
      GUM_ERROR(OperationNotAllowed, " maxArcs value not possible ");

    _maxArcs = maxArcs;
  }

  // Generates a bayesian network using floats.
  // @param nbrNodes The number of nodes in the generated BN.
  // @param density The probability of adding an arc between two nodes.
  // @return A BNs randomly generated.

} /* namespace gum */
