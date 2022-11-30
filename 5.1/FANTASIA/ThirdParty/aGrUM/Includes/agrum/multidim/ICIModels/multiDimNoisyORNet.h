
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
 * @brief class for NoisyOR-net implementation as multiDim
 *
 * @author Pierre-Henri WUILLEMIN et Christophe GONZALES
 */
#ifndef GUM_MULTI_DIM_NOISY_OR_NET_H
#define GUM_MULTI_DIM_NOISY_OR_NET_H

#include <agrum/multidim/ICIModels/multiDimICIModel.h>

namespace gum {

  // clang-format off
  /**
   * @class MultiDimNoisyORNet
   * @headerfile multiDimNoisyORNet.h <agrum/multidim/ICIModels/multiDimNoisyORNet.h>
   * @ingroup multidim_group
   *
   * @brief Noisy OR representation
   *
   * Noisy-OR as described by Henrion (UAI-3, 1989, pp161-173)
   *
   * @warning
   *   - The first variable is assumed to be the NOISY-OR. The latter are
   *     the causes.
   *   - This code give probabilities for BINARY VARIABLES (other values are
   *     assumed to be of probability 0). But for optimization reason, we will
   *     never check if it is the case.
   */
  // clang-format on
  template < typename GUM_SCALAR >
  class MultiDimNoisyORNet : public MultiDimICIModel< GUM_SCALAR > {
    public:
    // ============================================================================
    /// @name Constructors / Destructors
    // ============================================================================
    /// @{

    /// Default constructor.
    MultiDimNoisyORNet(GUM_SCALAR external_weight,
                       GUM_SCALAR default_weight = (GUM_SCALAR)1.0);

    MultiDimNoisyORNet(const MultiDimNoisyORNet< GUM_SCALAR >& from);

    /**
     * Copy constructor using a bijection to swap variables from source.
     *
     * @param bij First variables are new variables, seconds are in from.
     * @param from the copied instance
     */
    MultiDimNoisyORNet(
       const Bijection< const DiscreteVariable*, const DiscreteVariable* >& bij,
       const MultiDimNoisyORNet< GUM_SCALAR >&                              from);

    /// Destructor.
    virtual ~MultiDimNoisyORNet();

    /// @}

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

    // ============================================================================
    /// @name Accessors / Modifiers
    // ============================================================================
    /// @{

    public:
    virtual GUM_SCALAR get(const Instantiation& i) const;

    const std::string toString() const;

    ///
    /**
     * @brief Returns the real name of the multiDimArray.
     *
     * In aGrUM, all the types of multi-dimensional arrays/functionals have a
     * name that describes what they are in reality. For instance, a table
     * stored in extension is a "MultiDimArray", one that stores only non zero
     * elements is a "MultiDimSparseArray", and so on. These names are unique
     * for each type of implementation and is used by the system to determine
     * which is the best functions to use, say, when we wish to use operators
     * such as operator+ on two MultiDimImplementations.
     */
    virtual const std::string& name() const;

    /// @}
  };


#ifndef GUM_NO_EXTERN_TEMPLATE_CLASS
  extern template class MultiDimNoisyORNet< double >;
#endif

  /// For friendly displaying the content of the array.
  template < typename GUM_SCALAR >
  std::ostream& operator<<(std::ostream&                           s,
                           const MultiDimNoisyORNet< GUM_SCALAR >& ag);

} /* namespace gum */

#include <agrum/multidim/ICIModels/multiDimNoisyORNet_tpl.h>

#endif /* GUM_MULTI_DIM_NOISY_OR_NET_H */
