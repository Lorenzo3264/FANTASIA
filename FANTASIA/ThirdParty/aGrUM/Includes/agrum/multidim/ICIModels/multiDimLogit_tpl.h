
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
 * @brief class for LOGIT implementation as multiDim
 * @author Pierre-Henri WUILLEMIN et Christophe GONZALES
 */

#include <agrum/core/exceptions.h>
#include <agrum/multidim/ICIModels/multiDimLogit.h>
#include <agrum/multidim/implementations/multiDimImplementation.h>

namespace gum {

  // Default constructor
  template < typename GUM_SCALAR >
  INLINE MultiDimLogit< GUM_SCALAR >::MultiDimLogit(GUM_SCALAR external_weight,
                                                    GUM_SCALAR default_weight) :
      MultiDimICIModel< GUM_SCALAR >(external_weight, default_weight) {
    GUM_CONSTRUCTOR(MultiDimLogit);
  }

  // Default constructor
  template < typename GUM_SCALAR >
  INLINE MultiDimLogit< GUM_SCALAR >::MultiDimLogit(
     const MultiDimLogit< GUM_SCALAR >& from) :
      MultiDimICIModel< GUM_SCALAR >(from) {
    GUM_CONS_CPY(MultiDimLogit);
  }

  // Copy constructor using a bijection to replace variables from source.
  template < typename GUM_SCALAR >
  INLINE MultiDimLogit< GUM_SCALAR >::MultiDimLogit(
     const Bijection< const DiscreteVariable*, const DiscreteVariable* >& bij,
     const MultiDimLogit< GUM_SCALAR >&                                   from) :
      MultiDimICIModel< GUM_SCALAR >(bij, from) {
    GUM_CONSTRUCTOR(MultiDimLogit);
  }

  // destructor
  template < typename GUM_SCALAR >
  INLINE MultiDimLogit< GUM_SCALAR >::~MultiDimLogit() {
    GUM_DESTRUCTOR(MultiDimLogit);
  }

  template < typename GUM_SCALAR >
  GUM_SCALAR MultiDimLogit< GUM_SCALAR >::get(const Instantiation& i) const {
    if (this->nbrDim() < 1) {
      GUM_ERROR(OperationNotAllowed, "Not enough variable for a Logit");
    }

    const DiscreteVariable& C = this->variable((Idx)0);

    if (i.val(C) > 1) return (GUM_SCALAR)0.0;

    GUM_SCALAR fact = this->externalWeight();

    for (Idx j = 1; j < this->nbrDim(); j++) {
      const DiscreteVariable& v = this->variable(j);
      fact +=
         GUM_SCALAR(this->causalWeight(v) * this->variable(j).numerical(i.val(v)));
    }

    fact = 1 / (1 + std::exp(-fact));   // or std::exp(fact)/(1+std::exp(fact))
    auto res = (i.val(C) == 1) ? fact : (GUM_SCALAR)1.0 - fact;

    return res;
  }

  template < typename GUM_SCALAR >
  const std::string MultiDimLogit< GUM_SCALAR >::toString() const {
    std::stringstream s;
    s << this->variable(0) << "=logit(" << this->externalWeight();

    for (Idx i = 1; i < this->nbrDim(); i++) {
      GUM_SCALAR c = this->causalWeight(this->variable(i));

      if (c != GUM_SCALAR(0)) {
        s << " ";

        if (c > 0) s << "+";

        s << this->causalWeight(this->variable(i)) << "*" << this->variable(i);
      }
    }

    s << ")";

    return s.str();
  }

  // For friendly displaying the content of the variable.
  template < typename GUM_SCALAR >
  INLINE std::ostream& operator<<(std::ostream&                      s,
                                  const MultiDimLogit< GUM_SCALAR >& ag) {
    return s << ag.toString();
  }

  template < typename GUM_SCALAR >
  INLINE MultiDimContainer< GUM_SCALAR >*
         MultiDimLogit< GUM_SCALAR >::newFactory() const {
    return new MultiDimLogit< GUM_SCALAR >(this->__external_weight,
                                           this->__default_weight);
  }

  // returns the name of the implementation
  template < typename GUM_SCALAR >
  INLINE const std::string& MultiDimLogit< GUM_SCALAR >::name() const {
    static const std::string str = "MultiDimLogit";
    return str;
  }

} /* namespace gum */
