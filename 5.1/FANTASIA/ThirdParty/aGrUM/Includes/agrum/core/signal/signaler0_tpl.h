
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
 * @brief Class of listener.
 *
 * @author Pierre-Henri WUILLEMIN and Christophe GONZALES
 *
 */

// To help IDE parsers
#include <agrum/core/signal/signaler0.h>

namespace gum {
  namespace __sig__ {

    template < class TargetClass >
    Connector0< TargetClass >::Connector0() {
      GUM_CONSTRUCTOR(Connector0);
      __target = nullptr;
      __action = nullptr;
    }

    template < class TargetClass >
    Connector0< TargetClass >::Connector0(
       TargetClass* target, void (TargetClass::*action)(const void*)) {
      GUM_CONSTRUCTOR(Connector0);
      __target = target;
      __action = action;
    }

    template < class TargetClass >
    Connector0< TargetClass >::Connector0(const Connector0< TargetClass >* src) :
        IConnector0(src) {
      GUM_CONS_CPY(Connector0);
    }

    template < class TargetClass >
    Connector0< TargetClass >::~Connector0() {
      GUM_DESTRUCTOR(Connector0);
    }

    template < class TargetClass >
    IConnector0* Connector0< TargetClass >::clone() {
      return new Connector0< TargetClass >(*this);
    }

    template < class TargetClass >
    IConnector0* Connector0< TargetClass >::duplicate(Listener* target) {
      return new Connector0< TargetClass >((TargetClass*)target, __action);
    }

    template < class TargetClass >
    void Connector0< TargetClass >::notify(const void* src) {
      (__target->*__action)(src);
    }

    template < class TargetClass >
    Listener* Connector0< TargetClass >::target() const {
      return __target;
    }

  }   // namespace __sig__

}   // namespace gum
