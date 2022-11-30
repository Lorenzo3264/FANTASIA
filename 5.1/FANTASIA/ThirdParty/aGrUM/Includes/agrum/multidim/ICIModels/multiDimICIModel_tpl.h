
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
 * @brief A Interface to all Causal Independence models
 *
 * Causal Independence (CI) is a method of defining a discrete distribution
 * that can dramatically reduce the number of prior probabilities necessary to
 * define a distribution.
 *
 * @author Pierre-Henri WUILLEMIN et Christophe GONZALES
 */
#include <agrum/core/bijection.h>
#include <agrum/multidim/ICIModels/multiDimICIModel.h>
#include <agrum/multidim/implementations/multiDimReadOnly.h>

namespace gum {

  // Default constructor
  template < typename GUM_SCALAR >
  INLINE
     MultiDimICIModel< GUM_SCALAR >::MultiDimICIModel(GUM_SCALAR external_weight,
                                                      GUM_SCALAR default_weight) :
      MultiDimReadOnly< GUM_SCALAR >(),
      __external_weight(external_weight), __default_weight(default_weight) {
    GUM_CONSTRUCTOR(MultiDimICIModel);
  }

  // Default constructor
  template < typename GUM_SCALAR >
  INLINE MultiDimICIModel< GUM_SCALAR >::MultiDimICIModel(
     const MultiDimICIModel< GUM_SCALAR >& from) :
      MultiDimReadOnly< GUM_SCALAR >(from) {
    GUM_CONS_CPY(MultiDimICIModel);
    __default_weight = from.__default_weight;
    __external_weight = from.__external_weight;
    __causal_weights = from.__causal_weights;
  }

  // Copy constructor using a bijection to replace variables from source.
  template < typename GUM_SCALAR >
  INLINE MultiDimICIModel< GUM_SCALAR >::MultiDimICIModel(
     const Bijection< const DiscreteVariable*, const DiscreteVariable* >& bij,
     const MultiDimICIModel< GUM_SCALAR >&                                from) :
      MultiDimReadOnly< GUM_SCALAR >() {
    GUM_CONSTRUCTOR(MultiDimICIModel);
    __default_weight = from.__default_weight;
    __external_weight = from.__external_weight;

    for (HashTableConstIteratorSafe< const DiscreteVariable*, GUM_SCALAR > iter =
            from.__causal_weights.beginSafe();
         iter != from.__causal_weights.endSafe();
         ++iter) {
      try {
        causalWeight(*(bij.first(iter.key())), iter.val());
      } catch (NotFound&) { causalWeight(*(iter.key()), iter.val()); }
    }
  }

  // destructor
  template < typename GUM_SCALAR >
  INLINE MultiDimICIModel< GUM_SCALAR >::~MultiDimICIModel() {
    GUM_DESTRUCTOR(MultiDimICIModel);
  }

  template < typename GUM_SCALAR >
  INLINE GUM_SCALAR MultiDimICIModel< GUM_SCALAR >::causalWeight(
     const DiscreteVariable& v) const {
    return (__causal_weights.exists(&v)) ? __causal_weights[&v] : __default_weight;
  }

  template < typename GUM_SCALAR >
  INLINE void
     MultiDimICIModel< GUM_SCALAR >::causalWeight(const DiscreteVariable& v,
                                                  GUM_SCALAR w) const {
    if (!this->contains(v)) {
      GUM_ERROR(InvalidArgument, v.name() << " is not a cause for this CI Model");
    }

    if (w == (GUM_SCALAR)0) {
      GUM_ERROR(gum::OutOfBounds, "causal weight in CI Model>0");
    }

    __causal_weights.set(&v, w);
  }

  template < typename GUM_SCALAR >
  INLINE GUM_SCALAR MultiDimICIModel< GUM_SCALAR >::externalWeight() const {
    return __external_weight;
  }

  template < typename GUM_SCALAR >
  INLINE void MultiDimICIModel< GUM_SCALAR >::externalWeight(GUM_SCALAR w) const {
    __external_weight = w;
  }

  template < typename GUM_SCALAR >
  const std::string MultiDimICIModel< GUM_SCALAR >::toString() const {
    std::stringstream s;
    s << this->variable(0) << "=CIModel([" << externalWeight() << "],";

    for (Idx i = 1; i < this->nbrDim(); i++) {
      s << this->variable(i) << "[" << causalWeight(this->variable(i)) << "]";
    }

    s << ")";

    std::string res;
    s >> res;
    return res;
  }
  template < typename GUM_SCALAR >
  void MultiDimICIModel< GUM_SCALAR >::copyFrom(
     const MultiDimContainer< GUM_SCALAR >& src) const {
    auto p = dynamic_cast< const MultiDimICIModel< GUM_SCALAR >* >(&src);
    if (p == nullptr)
      MultiDimReadOnly< GUM_SCALAR >::copyFrom(src);
    else {
      if (src.domainSize() != this->domainSize()) {
        GUM_ERROR(OperationNotAllowed, "Domain sizes do not fit");
      }
      __external_weight = p->__external_weight;
      __default_weight = p->__default_weight;
      for (Idx i = 1; i < this->nbrDim(); i++) {
        __causal_weights.set(
           const_cast< const DiscreteVariable* >(&this->variable(i)),
           p->causalWeight(this->variable(i)));
      }
    }
  }

  // returns the name of the implementation
  template < typename GUM_SCALAR >
  INLINE const std::string& MultiDimICIModel< GUM_SCALAR >::name() const {
    static const std::string str = "MultiDimICIModel";
    return str;
  }

  template < typename GUM_SCALAR >
  INLINE void MultiDimICIModel< GUM_SCALAR >::_replace(const DiscreteVariable* x,
                                                       const DiscreteVariable* y) {
    MultiDimReadOnly< GUM_SCALAR >::_replace(x, y);
    __causal_weights.insert(y, __causal_weights[x]);
    __causal_weights.erase(x);
  }

} /* namespace gum */
