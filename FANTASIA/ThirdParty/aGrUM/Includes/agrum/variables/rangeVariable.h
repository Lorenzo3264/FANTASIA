
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
 * @brief Header of gumRangeVariable.
 *
 * @author Pierre-Henri WUILLEMIN et Christophe GONZALES
 */

#ifndef GUM_RANGE_VARIABLE_H
#define GUM_RANGE_VARIABLE_H

#include <ostream>
#include <sstream>
#include <string>

#include <agrum/agrum.h>

#include <agrum/core/hashFunc.h>
#include <agrum/variables/discreteVariable.h>

namespace gum {

  /**
   * @class RangeVariable
   * @brief Defines a discrete random variable over an integer interval.
   *
   * It is technically possible to create RangeVariable with minVal > maxVal
   * (or modify in that way an already created RangeVariable). The result is
   * an empty variable (i.e. empty() returns true).
   * If maxVal - minVal < 0, then domainsize() = 0.
   */

  class RangeVariable : public DiscreteVariable {
    public:
    /// @name Constructors / Destructors

    /// @{
    ///  constructors
    RangeVariable(const std::string& aName,
                  const std::string& aDesc,
                  long               minVal,
                  long               maxVal);

    /// by de default min=0, max=1
    RangeVariable(const std::string& aName, const std::string& aDesc);

    /** Copy Constructor.
     *
     * If aDRV haves any listener, it will not be copied.
     *
     * @param aDRV the variable we copy
     */
    RangeVariable(const RangeVariable& aDRV);

    /// destructor
    virtual ~RangeVariable();

    /// Copy Factory.
    /// @return Returns a pointer on a new copy of this.
    virtual DiscreteVariable* clone() const;

    /// @}

    /// @name Accessors / Modifiers

    /// @{
    /// returns the size of the random discrete variable domain
    /// @warning :  It is technically possible to create RangeVariable with minVal
    /// > maxVal
    ///   (or modify in that way an already created RangeVariable). The result is
    ///   an empty variable (i.e. empty() returns true).
    ///   If maxVal - minVal < 0, then domainsize() = 0.
    virtual Size domainSize() const;

    /// returns the type of variable

    virtual VarType varType() const;

    ///
    /**
     * Get the indice-th label.
     * @param indice the index of the label we wish to return
     * @throw OutOfBound
     */
    virtual std::string label(Idx indice) const;

    /// get a numerical representation of he indice-the value.
    virtual double numerical(Idx indice) const;

    /**
     * Returns the lower bound.
     */
    long minVal() const;

    /**
     * Set a new value for the lower bound.
     */
    void setMinVal(long minVal);

    /**
     * Returns the upper bound.
     */
    long maxVal() const;

    /**
     * Set a new value of the upper bound.
     */
    void setMaxVal(long maxVal);

    /**
     * Returns true if the param belongs to the variable's interval.
     */
    bool belongs(long val) const;

    /**
     * @return the modality index from the label
     * @throw NotFound
     */
    virtual Idx index(const std::string&) const;

    /// @}

    /// @name Operators
    /// @{
    /**
     * Copy operator
     * @param aRV to be copied
     * @return a ref to *this */
    RangeVariable& operator=(const RangeVariable& aRV);

    /// @}

    virtual const std::string domain() const;

    private:
    /// @name Private Members.

    /// @{
    /// The lower bound.
    long __minBound;

    /// The upper bound.
    long __maxBound;

    /// @}
  };

} /* namespace gum */

#ifndef GUM_NO_INLINE
#  include <agrum/variables/rangeVariable_inl.h>
#endif /* GUM_NO_INLINE */

#endif /* GUM_RANGE_VARIABLE_H */
