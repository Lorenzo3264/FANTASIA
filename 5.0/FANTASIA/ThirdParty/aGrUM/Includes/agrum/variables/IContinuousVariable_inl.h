
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
 * @brief Inline implementations of IContinuousVariable.
 *
 * @author Christophe GONZALES and Pierre-Henri WUILLEMIN
 */
#ifndef DOXYGEN_SHOULD_SKIP_THIS

#  include <agrum/variables/IContinuousVariable.h>

namespace gum {


  /// Default constructor
  INLINE
  IContinuousVariable::IContinuousVariable(const std::string& aName,
                                           const std::string& aDesc) :
      Variable(aName, aDesc) {}


  /// Copy Constructor
  INLINE
  IContinuousVariable::IContinuousVariable(const IContinuousVariable& from) :
      Variable(from) {}


  /// move constructor
  INLINE
  IContinuousVariable::IContinuousVariable(IContinuousVariable&& from) :
      Variable(std::move(from)) {}


  /// destructor
  INLINE
  IContinuousVariable::~IContinuousVariable() {}


  /// copy operator
  INLINE IContinuousVariable& IContinuousVariable::
                              operator=(const IContinuousVariable& from) {
    Variable::operator=(from);
    return *this;
  }


  /// move operator
  INLINE IContinuousVariable& IContinuousVariable::
                              operator=(IContinuousVariable&& from) {
    Variable::operator=(std::move(from));
    return *this;
  }


} /* namespace gum */


#endif /* DOXYGEN_SHOULD_SKIP_THIS */
