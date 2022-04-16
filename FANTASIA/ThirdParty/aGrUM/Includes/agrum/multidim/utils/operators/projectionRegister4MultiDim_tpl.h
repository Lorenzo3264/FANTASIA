
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
 * @brief A container for registering projection functions on
 * multiDimImplementations
 *
 * @author Christophe GONZALES and Pierre-Henri WUILLEMIN
 */

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#  include <agrum/agrum.h>

#  include <agrum/multidim/utils/operators/projectionRegister4MultiDim.h>

namespace gum {

  // adds a new entry into the register
  template < typename GUM_SCALAR >
  void ProjectionRegister4MultiDim< GUM_SCALAR >::insert(
     const std::string& projection_name,
     const std::string& type_multidim,
     typename ProjectionRegister4MultiDim< GUM_SCALAR >::ProjectionPtr
        newFunction) {
    // insert the new entry
    ProjectionSet* theset;

    if (!__set.exists(projection_name)) {
      theset = __set.insert(projection_name, new ProjectionSet).second;
#  ifdef GUM_DEBUG_MODE
      // for debugging purposes, we should inform the aGrUM's debugger that
      // the hashtable contained within the ProjectionRegister4MultiDim will be
      // removed at the end of the program's execution.
      __debug__::__inc_deletion(
         "HashTable", __FILE__, __LINE__, "destructor of", (void*)theset);
#  endif /* GUM_DEBUG_MODE */
    } else {
      theset = __set[projection_name];
    }

    theset->insert(type_multidim, newFunction);
  }

  // removes a given entry from the register
  template < typename GUM_SCALAR >
  void ProjectionRegister4MultiDim< GUM_SCALAR >::erase(
     const std::string& projection_name, const std::string& type_multidim) {
    if (!__set.exists(projection_name)) return;

    ProjectionSet* theset = __set[projection_name];

    theset->erase(type_multidim);
  }

  // indicates whether a given entry exists in the register
  template < typename GUM_SCALAR >
  INLINE bool ProjectionRegister4MultiDim< GUM_SCALAR >::exists(
     const std::string& projection_name, const std::string& type_multidim) const {
    if (!__set.exists(projection_name)) return false;

    return __set[projection_name].exists(type_multidim);
  }

  /** @brief returns the specialized operator assigned to a given subtype of
   * MultiDimImplementation */
  template < typename GUM_SCALAR >
  INLINE typename ProjectionRegister4MultiDim< GUM_SCALAR >::ProjectionPtr
     ProjectionRegister4MultiDim< GUM_SCALAR >::get(
        const std::string& projection_name,
        const std::string& type_multidim) const {
    ProjectionSet* theset = __set[projection_name];
    return theset->operator[](type_multidim);
  }

  // a named constructor that constructs one and only one Register per data
  // type
  template < typename GUM_SCALAR >
  ProjectionRegister4MultiDim< GUM_SCALAR >&
     ProjectionRegister4MultiDim< GUM_SCALAR >::Register() {
    static ProjectionRegister4MultiDim container;

#  ifdef GUM_DEBUG_MODE
    static bool first = true;

    if (first) {
      first = false;
      // for debugging purposes, we should inform the aGrUM's debugger that
      // the hashtable contained within the ProjectionRegister4MultiDim will be
      // removed at the end of the program's execution.
      __debug__::__inc_deletion("HashTable",
                                __FILE__,
                                __LINE__,
                                "destructor of",
                                (void*)&container.__set);
    }

#  endif /* GUM_DEBUG_MODE */

    return container;
  }

  // Default constructor: creates an empty register
  template < typename GUM_SCALAR >
  ProjectionRegister4MultiDim< GUM_SCALAR >::ProjectionRegister4MultiDim() {}

  // destructor
  template < typename GUM_SCALAR >
  ProjectionRegister4MultiDim< GUM_SCALAR >::~ProjectionRegister4MultiDim() {
    // remove all the sets
    for (typename HashTable< std::string, ProjectionSet* >::iterator_safe iter =
            __set.beginSafe();
         iter != __set.endSafe();
         ++iter)
      delete iter.val();
  }

  // a function to more easily register new projection functions in MultiDims
  template < typename GUM_SCALAR >
  void registerProjection(
     const std::string& projection_name,
     const std::string& type_multidim,
     typename ProjectionRegister4MultiDim< GUM_SCALAR >::ProjectionPtr function) {
    ProjectionRegister4MultiDim< GUM_SCALAR >::Register().insert(
       projection_name, type_multidim, function);
  }

} /* namespace gum */

#endif /* DOXYGEN_SHOULD_SKIP_THIS */
