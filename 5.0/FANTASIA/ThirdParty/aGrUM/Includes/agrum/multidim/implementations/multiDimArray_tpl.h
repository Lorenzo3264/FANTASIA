
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
 * @brief Implementation of the MultiDimArray class.
 *
 * @author Pierre-Henri WUILLEMIN et Christophe GONZALES
 */

#include <agrum/multidim/implementations/multiDimArray.h>
#include <agrum/multidim/implementations/multiDimWithOffset.h>

namespace gum {

  // Default constructor: creates an empty null dimensional matrix
  template < typename GUM_SCALAR >
  MultiDimArray< GUM_SCALAR >::MultiDimArray() :
      MultiDimWithOffset< GUM_SCALAR >() {
    // for debugging purposes
    GUM_CONSTRUCTOR(MultiDimArray);
  }

  // copy constructor
  template < typename GUM_SCALAR >
  MultiDimArray< GUM_SCALAR >::MultiDimArray(
     const MultiDimArray< GUM_SCALAR >& src) :
      MultiDimWithOffset< GUM_SCALAR >(src),
      _values(src._values) {
    // for debugging purposes
    GUM_CONS_CPY(MultiDimArray);
  }

  // destructor
  template < typename GUM_SCALAR >
  MultiDimArray< GUM_SCALAR >::~MultiDimArray() {
    // for debugging purposes
    GUM_DESTRUCTOR(MultiDimArray);
    // no need to unregister all slaves as it will be done by MultiDimWithOffset
  }

  template < typename GUM_SCALAR >
  void MultiDimArray< GUM_SCALAR >::copyFrom(
     const MultiDimContainer< GUM_SCALAR >& src) const {
    auto mda = dynamic_cast< const MultiDimArray< GUM_SCALAR >* >(&src);

    if (mda == nullptr) {
      MultiDimContainer< GUM_SCALAR >::copyFrom(src);
    } else {
      _values = mda->_values;
    }
  }

  template < typename GUM_SCALAR >
  void MultiDimArray< GUM_SCALAR >::apply(
     std::function< GUM_SCALAR(GUM_SCALAR) > f) const {
    std::transform(_values.begin(), _values.end(), _values.begin(), f);
  }

  template < typename GUM_SCALAR >
  GUM_SCALAR MultiDimArray< GUM_SCALAR >::reduce(
     std::function< GUM_SCALAR(GUM_SCALAR, GUM_SCALAR) > f,
     GUM_SCALAR                                          base) const {
    return std::accumulate(_values.begin(), _values.end(), base, f);
  }


  // data access operator
  template < typename GUM_SCALAR >
  INLINE GUM_SCALAR&
         MultiDimArray< GUM_SCALAR >::_get(const Instantiation& i) const {
    if (i.isMaster(this)) {
      return _values[this->_offsets[&i]];
    } else {
      return _values[this->_getOffs(i)];
    }
  }

  // add a new dimension, needed for updating the _offsets & _gaps
  template < typename GUM_SCALAR >
  INLINE void MultiDimArray< GUM_SCALAR >::add(const DiscreteVariable& v) {
    Size lg = MultiDimWithOffset< GUM_SCALAR >::domainSize();
    MultiDimWithOffset< GUM_SCALAR >::add(v);

    if (!this->_isInMultipleChangeMethod()) {
      _values.resize(lg * v.domainSize());
    }
  }

  // removes a dimension, needed for updating the _offsets & _gaps
  template < typename GUM_SCALAR >
  INLINE void MultiDimArray< GUM_SCALAR >::erase(const DiscreteVariable& v) {
    Sequence< const DiscreteVariable* > variables = this->variablesSequence();
    Idx pos = variables.pos(&v);   // throw a NotFound if necessary

    if (variables.size() == 1) {
      if (!this->_isInMultipleChangeMethod()) _values.clear();
    } else {
      Size v_size = v.domainSize();
      Size size = this->domainSize();
      // here, the variable does belong to the array.
      // => if pos = variables.size() - 1 then we just have to extract the
      // beginning of the array (actually the first gap of variable v)
      // if pos = 0, then copy every element whose index is a multiple of |v|
      // Assume now that pos != 0 and pos != variables.size() - 1, then
      // let w be the next variable in the set of variables of the array.
      // Then we must copy |gap(v)| elements every |gap(w)| elements

      if (!this->_isInMultipleChangeMethod()) {
        if (pos != variables.size() - 1) {
          Size gap_v = this->_gaps[variables[pos]];
          Size gap_w = this->_gaps[variables[pos + 1]];

          for (Idx i = 0, j = 0; i < size; i += gap_w) {
            Idx last = i + gap_v;

            for (Idx k = i; k < last; ++k, ++j)
              _values[j] = _values[k];
          }
        }

        // shrink _values
        _values.resize(size / v_size);
      }
    }

    MultiDimWithOffset< GUM_SCALAR >::erase(v);
  }

  template < typename GUM_SCALAR >
  INLINE Size MultiDimArray< GUM_SCALAR >::realSize() const {
    return this->domainSize();
  }

  // synchronise content after MultipleChanges
  template < typename GUM_SCALAR >
  INLINE void MultiDimArray< GUM_SCALAR >::_commitMultipleChanges() {
    if (MultiDimWithOffset< GUM_SCALAR >::domainSize() != _values.size()) {
      _values.resize(MultiDimWithOffset< GUM_SCALAR >::domainSize());
    }
  }

  // synchronise content after MultipleChanges
  template < typename GUM_SCALAR >
  INLINE void
     MultiDimArray< GUM_SCALAR >::_commitMultipleChanges(const GUM_SCALAR& x) {
    if (MultiDimWithOffset< GUM_SCALAR >::domainSize() != _values.size()) {
      _values.resize(MultiDimWithOffset< GUM_SCALAR >::domainSize(), x);
    }
  }

  // fill the array with the arg
  template < typename GUM_SCALAR >
  INLINE void MultiDimArray< GUM_SCALAR >::fill(const GUM_SCALAR& d) const {
    if (!this->empty()) std::fill(_values.begin(), _values.end(), d);
  }

  // virtual constructor
  template < typename GUM_SCALAR >
  INLINE MultiDimContainer< GUM_SCALAR >*
         MultiDimArray< GUM_SCALAR >::newFactory() const {
    return new MultiDimArray< GUM_SCALAR >;
  }

  // returns the element stored in the multidimArray at a given offset
  template < typename GUM_SCALAR >
  INLINE const GUM_SCALAR&
               MultiDimArray< GUM_SCALAR >::unsafeGet(Idx offset) const {
    return _values[offset];
  }

  template < typename GUM_SCALAR >
  INLINE void MultiDimArray< GUM_SCALAR >::unsafeSet(Idx               offset,
                                                     const GUM_SCALAR& data) {
    _values[offset] = data;
  }

  // returns the element stored in the multidimArray at a given offset
  template < typename GUM_SCALAR >
  INLINE const GUM_SCALAR&
               MultiDimArray< GUM_SCALAR >::getByOffset(Idx offset) const {
    if (offset >= _values.size()) { GUM_ERROR(OutOfBounds, "offset too large"); }

    return _values[offset];
  }

  template < typename GUM_SCALAR >
  INLINE void MultiDimArray< GUM_SCALAR >::setByOffset(Idx               offset,
                                                       const GUM_SCALAR& data) {
    if (offset >= _values.size()) { GUM_ERROR(OutOfBounds, "offset too large"); }

    _values[offset] = data;
  }

  // returns the name of the implementation
  template < typename GUM_SCALAR >
  INLINE const std::string& MultiDimArray< GUM_SCALAR >::name() const {
    static const std::string str = "MultiDimArray";
    return str;
  }

  template < typename GUM_SCALAR >
  INLINE void MultiDimArray< GUM_SCALAR >::_replace(const DiscreteVariable* x,
                                                    const DiscreteVariable* y) {
    MultiDimImplementation< GUM_SCALAR >::_replace(x, y);
  }
} /* namespace gum */
