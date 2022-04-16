
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
 * @brief median aggregator
 *
 * @author Pierre-Henri WUILLEMIN et Christophe GONZALES
 */

#ifndef GUM_MEDIAN_AGGREGATOR_H
#define GUM_MEDIAN_AGGREGATOR_H

#include <agrum/multidim/aggregators/multiDimAggregator.h>

namespace gum {

  namespace aggregator {
    // =========================================================================
    // ===                     GUM_MEDIAN_AGGREGATOR                         ===
    // =========================================================================

    /**
     * @class Median
     * @headerfile median.h <agrum/multidim/aggregators/median.h>
     * @ingroup multidim_agg_group
     *
     * @brief median aggregator
     *
     * @see MultiDimAggregator for more details of implementations
     *
     * Median needs to have the same domain than its parent.
     *
     * @warning if the number of parent is even, the median (with the same type
     * as its parents) is not well defined : the median of [1,1,3,3] is 2. But
     * what is the median of [1,1,2,2] ?  The mathematical response is 1.5
     * which is not in the range of the variables. In that case, we choose
     * (arbitrarilly by excess) the value 2.
     */
    template < typename GUM_SCALAR >
    class Median : public MultiDimAggregator< GUM_SCALAR > {
      public:
      Median();
      Median(const Median< GUM_SCALAR >& from);
      virtual ~Median();

      virtual std::string aggregatorName() const;

      /**
       * This method creates a clone of this object, withouth its content
       * (including variable), you must use this method if you want to ensure
       * that the generated object has the same type than the object containing
       * the called newFactory()
       *
       * For example :
       * @code
       *   MultiDimArray<double> y;
       *   MultiDimContainer<double>* x = y.newFactory();
       * @endcode
       *
       * Then x is a MultiDimArray<double>*
       *
       * @warning you must desallocate by yourself the memory
       * @return an empty clone of this object with the same type
       */
      virtual MultiDimContainer< GUM_SCALAR >* newFactory() const;

      protected:
      virtual Idx _buildValue(const gum::Instantiation& i) const;

      // fold scheme is not used, these methods are neutralized
      virtual Idx _neutralElt() const { return 0; };
      virtual Idx _fold(const DiscreteVariable& v,
                        Idx                     i1,
                        Idx                     i2,
                        bool&                   stop_iteration) const;

      private:
      Idx __value;
    };


#ifndef GUM_NO_EXTERN_TEMPLATE_CLASS
    extern template class Median< double >;
#endif


  }   // namespace aggregator
}   // namespace gum

#include <agrum/multidim/aggregators/median_tpl.h>

#endif   // GUM_MEDIAN_AGGREGATOR_H
