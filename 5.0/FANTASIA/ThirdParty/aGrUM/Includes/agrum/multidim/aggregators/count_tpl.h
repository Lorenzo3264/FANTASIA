
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
 * @brief count aggregator
 *
 * @author Pierre-Henri WUILLEMIN et Christophe GONZALES
 */

#include <agrum/multidim/aggregators/count.h>
#include <sstream>

namespace gum {

  namespace aggregator {
    template < typename GUM_SCALAR >
    INLINE Count< GUM_SCALAR >::Count(Idx value) :
        MultiDimAggregator< GUM_SCALAR >(), __value(value) {
      GUM_CONSTRUCTOR(Count);
    }

    template < typename GUM_SCALAR >
    INLINE Count< GUM_SCALAR >::Count(const Count< GUM_SCALAR >& from) :
        MultiDimAggregator< GUM_SCALAR >(from) {
      __value = from.__value;
      GUM_CONS_CPY(Count);
    }

    template < typename GUM_SCALAR >
    INLINE Count< GUM_SCALAR >::~Count() {
      GUM_DESTRUCTOR(Count);
    }

    template < typename GUM_SCALAR >
    INLINE Idx Count< GUM_SCALAR >::_neutralElt() const {
      return (Idx)0;
    }

    template < typename GUM_SCALAR >
    INLINE Idx Count< GUM_SCALAR >::_fold(const DiscreteVariable& v,
                                          Idx                     i1,
                                          Idx                     i2,
                                          bool& stop_iteration) const {
      return (i1 == __value) ? 1 + i2 : i2;
    }

    template < typename GUM_SCALAR >
    INLINE std::string Count< GUM_SCALAR >::aggregatorName() const {
      std::stringstream ss;
      ss << "count[" << __value << "]";
      return ss.str();
    }

    template < typename GUM_SCALAR >
    INLINE MultiDimContainer< GUM_SCALAR >*
           Count< GUM_SCALAR >::newFactory() const {
      return new Count< GUM_SCALAR >(__value);
    }

  }   // namespace aggregator
}   // namespace gum
