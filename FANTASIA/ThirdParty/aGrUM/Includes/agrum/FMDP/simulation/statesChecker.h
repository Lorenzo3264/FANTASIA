
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
 * @brief Headers of the States Checker class.
 *
 * @author Jean-Christophe MAGNAN and Pierre-Henri WUILLEMIN
 */

// =========================================================================
#ifndef GUM_STATES_CHECKER_H
#define GUM_STATES_CHECKER_H
// =========================================================================
// =========================================================================
#include <agrum/core/sequence.h>
#include <agrum/multidim/implementations/multiDimFunctionGraph.h>
// =========================================================================

namespace gum {


  /**
   * @class StatesChecker statesChecker.h
   * <agrum/FMDP/simulation/statesChecker.h>
   * @brief Provides the necessary to check whether or not states have been
   * already visited.
   * @ingroup fmdp_group
   */
  class StatesChecker {
    public:
    // ==========================================================================
    /// @name Constructor & destructor.
    // ==========================================================================
    /// @{

    /**
     * Default constructor
     */
    StatesChecker();

    /**
     * Default destructor
     */
    ~StatesChecker();

    /// @}

    // ==========================================================================
    /// @name Miscelleanous methods
    // ==========================================================================
    /// @{

    bool checkState(const Instantiation& state) { return __checker->get(state); }

    void addState(const Instantiation&);

    Idx nbVisitedStates() { return __nbVisitedStates; }

    void reset(const Instantiation&);

    /// @}

    private:
    void __insertState(const Instantiation&, NodeId, Idx);

    Idx __nbVisitedStates;

    MultiDimFunctionGraph< bool >* __checker;
    NodeId                         __checkerTrueId, __checkerFalseId;

    Set< Instantiation* > __visitedStates;
  };
} /* namespace gum */

#endif   // GUM_STATES_CHECKER_H
