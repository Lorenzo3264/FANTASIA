
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


/**
 * @file
 * @brief A generic class to project efficiently a MultiDim table over all
 * of its variables
 *
 * @author Christophe GONZALES and Pierre-Henri WUILLEMIN
 */

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#  include <agrum/agrum.h>
#  include <limits>

namespace gum {

  // constructor
  template < typename GUM_SCALAR, template < typename > class TABLE >
  MultiDimCompleteProjection< GUM_SCALAR, TABLE >::MultiDimCompleteProjection(
     GUM_SCALAR (*proj)(const TABLE< GUM_SCALAR >&, Instantiation*)) :
      _proj(proj) {
    // for debugging purposes
    GUM_CONSTRUCTOR(MultiDimCompleteProjection);
  }

  // copy constructor
  template < typename GUM_SCALAR, template < typename > class TABLE >
  MultiDimCompleteProjection< GUM_SCALAR, TABLE >::MultiDimCompleteProjection(
     const MultiDimCompleteProjection< GUM_SCALAR, TABLE >& from) :
      _proj(from._proj) {
    // for debugging purposes
    GUM_CONS_CPY(MultiDimCompleteProjection);
  }

  // destructor
  template < typename GUM_SCALAR, template < typename > class TABLE >
  MultiDimCompleteProjection< GUM_SCALAR, TABLE >::~MultiDimCompleteProjection() {
    // for debugging purposes
    GUM_DESTRUCTOR(MultiDimCompleteProjection);
  }

  // virtual constructor
  template < typename GUM_SCALAR, template < typename > class TABLE >
  MultiDimCompleteProjection< GUM_SCALAR, TABLE >*
     MultiDimCompleteProjection< GUM_SCALAR, TABLE >::newFactory() const {
    return new MultiDimCompleteProjection< GUM_SCALAR, TABLE >(*this);
  }

  // creates and returns the projection of the table over a subset of its vars
  template < typename GUM_SCALAR, template < typename > class TABLE >
  INLINE GUM_SCALAR MultiDimCompleteProjection< GUM_SCALAR, TABLE >::project(
     const TABLE< GUM_SCALAR >& table, Instantiation* inst) {
    return _proj(table, inst);
  }

  // changes the function used for projecting TABLES
  template < typename GUM_SCALAR, template < typename > class TABLE >
  void MultiDimCompleteProjection< GUM_SCALAR, TABLE >::setProjectFunction(
     GUM_SCALAR (*proj)(const TABLE< GUM_SCALAR >&, Instantiation*)) {
    _proj = proj;
  }

  // returns the projection function currently used by the projector
  template < typename GUM_SCALAR, template < typename > class TABLE >
  INLINE GUM_SCALAR (
     *MultiDimCompleteProjection< GUM_SCALAR, TABLE >::projectFunction())(
     const TABLE< GUM_SCALAR >&, Instantiation*) {
    return _proj;
  }

} /* namespace gum */

#endif /* DOXYGEN_SHOULD_SKIP_THIS */
