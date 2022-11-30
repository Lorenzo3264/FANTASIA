
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
 * @brief Implementation of the MultiDimBijArray class.
 *
 * @author Pierre-Henri WUILLEMIN et Christophe GONZALES
 * @author Lionel TORTI
 */

#include <agrum/multidim/implementations/multiDimBijArray.h>

namespace gum {

  template < typename GUM_SCALAR >
  MultiDimBijArray< GUM_SCALAR >::MultiDimBijArray(
     const MultiDimBijArray< GUM_SCALAR >& from) :
      MultiDimWithOffset< GUM_SCALAR >(),
      __array(from.__array), __name(from.__name) {
    GUM_CONS_CPY(MultiDimBijArray);

    for (auto var : from.variablesSequence()) {
      MultiDimWithOffset< GUM_SCALAR >::add(*var);
    }
  }

  template < typename GUM_SCALAR >
  MultiDimBijArray< GUM_SCALAR >::MultiDimBijArray(
     const VarBijection& bijection, const MultiDimArray< GUM_SCALAR >& array) :
      MultiDimWithOffset< GUM_SCALAR >(),
      __array(array), __name("MultiDimBijArray") {
    GUM_CONSTRUCTOR(MultiDimBijArray);

    for (auto var : array.variablesSequence()) {
      MultiDimWithOffset< GUM_SCALAR >::add(*(bijection.second(var)));
    }
  }

  template < typename GUM_SCALAR >
  MultiDimBijArray< GUM_SCALAR >::MultiDimBijArray(
     const VarBijection& bijection, const MultiDimBijArray< GUM_SCALAR >& array) :
      MultiDimWithOffset< GUM_SCALAR >(),
      __array(array.__array), __name("MultiDimBijArray") {
    GUM_CONSTRUCTOR(MultiDimBijArray);

    for (auto var : array.variablesSequence()) {
      MultiDimWithOffset< GUM_SCALAR >::add(*(bijection.second(var)));
    }
  }

  template < typename GUM_SCALAR >
  INLINE MultiDimBijArray< GUM_SCALAR >::~MultiDimBijArray() {
    GUM_DESTRUCTOR(MultiDimBijArray);
  }

  template < typename GUM_SCALAR >
  MultiDimBijArray< GUM_SCALAR >& MultiDimBijArray< GUM_SCALAR >::
                                  operator=(const MultiDimBijArray< GUM_SCALAR >& from) {
    GUM_ERROR(OperationNotAllowed, "MultiDimBijArray are readonly.");
  }

  template < typename GUM_SCALAR >
  INLINE MultiDimBijArray< GUM_SCALAR >*
         MultiDimBijArray< GUM_SCALAR >::newFactory() const {
    return new MultiDimBijArray< GUM_SCALAR >(*this);
  }

  template < typename GUM_SCALAR >
  INLINE const std::string& MultiDimBijArray< GUM_SCALAR >::name() const {
    return __name;
  }

  template < typename GUM_SCALAR >
  INLINE void MultiDimBijArray< GUM_SCALAR >::add(const DiscreteVariable& v) {
    GUM_ERROR(OperationNotAllowed, "MultiDimBijArray<GUM_SCALAR> are read only.");
  }

  template < typename GUM_SCALAR >
  INLINE void MultiDimBijArray< GUM_SCALAR >::erase(const DiscreteVariable& v) {
    GUM_ERROR(OperationNotAllowed, "MultiDimBijArray<GUM_SCALAR> are read only.");
  }

  template < typename GUM_SCALAR >
  INLINE Size MultiDimBijArray< GUM_SCALAR >::realSize() const {
    return (Size)0;
  }

  template < typename GUM_SCALAR >
  INLINE void MultiDimBijArray< GUM_SCALAR >::fill(const GUM_SCALAR& d) const {
    GUM_ERROR(OperationNotAllowed, "MultiDimBijArray<GUM_SCALAR> are read only.");
  }

  template < typename GUM_SCALAR >
  INLINE void MultiDimBijArray< GUM_SCALAR >::_commitMultipleChanges() {
    // Do nothing
  }

  template < typename GUM_SCALAR >
  INLINE GUM_SCALAR
         MultiDimBijArray< GUM_SCALAR >::get(const Instantiation& i) const {
    if (i.isMaster(this)) {
      return __array._values[this->_offsets[&i]];
    } else {
      return __array._values[this->_getOffs(i)];
    }
  }

  template < typename GUM_SCALAR >
  INLINE void MultiDimBijArray< GUM_SCALAR >::set(const Instantiation& i,
                                                  const GUM_SCALAR& value) const {
    GUM_ERROR(OperationNotAllowed, "MultiDimBijArray<GUM_SCALAR> are read only.");
  }

  template < typename GUM_SCALAR >
  INLINE void MultiDimBijArray< GUM_SCALAR >::populate(
     const std::vector< GUM_SCALAR >& v) const {
    GUM_ERROR(OperationNotAllowed, "MultiDimBijArray<GUM_SCALAR> are read only.");
  }

  template < typename GUM_SCALAR >
  INLINE void MultiDimBijArray< GUM_SCALAR >::populate(
     std::initializer_list< GUM_SCALAR > l) const {
    GUM_ERROR(OperationNotAllowed, "MultiDimBijArray<GUM_SCALAR> are read only.");
  }

  template < typename GUM_SCALAR >
  INLINE GUM_SCALAR&
         MultiDimBijArray< GUM_SCALAR >::_get(const Instantiation& i) const {
    GUM_ERROR(OperationNotAllowed, "MultiDimBijArray<GUM_SCALAR> are read only.");
  }

  template < typename GUM_SCALAR >
  INLINE void MultiDimBijArray< GUM_SCALAR >::_replace(const DiscreteVariable* x,
                                                       const DiscreteVariable* y) {
    MultiDimImplementation< GUM_SCALAR >::_replace(x, y);
  }

}   // namespace gum
