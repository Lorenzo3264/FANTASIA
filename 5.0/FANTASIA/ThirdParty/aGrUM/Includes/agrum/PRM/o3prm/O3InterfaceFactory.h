
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
 * @brief Headers for the O3InterfaceFactory class.
 *
 * @author Christophe GONZALES and Pierre-Henri WUILLEMIN
 * @author Lionel TORTI
 */

#include <memory>
#include <string>

#include <agrum/PRM/PRM.h>
#include <agrum/PRM/PRMFactory.h>
#include <agrum/PRM/o3prm/O3NameSolver.h>
#include <agrum/PRM/o3prm/O3prm.h>
#include <agrum/PRM/o3prm/errors.h>
#include <agrum/core/hashTable.h>
#include <agrum/core/set.h>

#ifndef GUM_PRM_O3PRM_O3INTERFACE_FACTORY_H
#  define GUM_PRM_O3PRM_O3INTERFACE_FACTORY_H

namespace gum {
  namespace prm {
    namespace o3prm {

      /**
       * @class O3InterfaceFactory
       * @headerfile O3InterfaceFactory.h <agrum/PRM/o3prm/O3InterfaceFactory.h>
       * @ingroup o3prm_group
       *
       * @brief Bulds gum::prm:PRMInterface from gum::prm::o3prm::O3Interface.
       *
       * @tparam GUM_SCALAR The scalar type used by the gum::prm::PRM.
       */
      template < typename GUM_SCALAR >
      class O3InterfaceFactory {
        public:
        O3InterfaceFactory(PRM< GUM_SCALAR >&          prm,
                           O3PRM&                      o3_prm,
                           O3NameSolver< GUM_SCALAR >& solver,
                           ErrorsContainer&            errors);
        O3InterfaceFactory(const O3InterfaceFactory< GUM_SCALAR >& src);
        O3InterfaceFactory(O3InterfaceFactory< GUM_SCALAR >&& src);
        ~O3InterfaceFactory();
        O3InterfaceFactory< GUM_SCALAR >&
           operator=(const O3InterfaceFactory< GUM_SCALAR >& src);
        O3InterfaceFactory< GUM_SCALAR >&
           operator=(O3InterfaceFactory< GUM_SCALAR >&& src);

        void buildInterfaces();

        void buildElements();

        private:
        PRM< GUM_SCALAR >*          __prm;
        O3PRM*                      __o3_prm;
        O3NameSolver< GUM_SCALAR >* __solver;
        ErrorsContainer*            __errors;

        HashTable< std::string, std::string >  __eltName;
        HashTable< std::string, gum::NodeId >  __nameMap;
        HashTable< std::string, O3Interface* > __interfaceMap;
        HashTable< NodeId, O3Interface* >      __nodeMap;
        DAG                                    __dag;
        std::vector< O3Interface* >            __o3Interface;

        bool __addInterface2Dag();

        bool __addArcs2Dag();

        void __setO3InterfaceCreationOrder();

        bool __checkO3Interfaces();

        bool __checkInterfaceElement(O3Interface& i, O3InterfaceElement& elt);

        bool __checkOverloadLegality(O3Interface& i, O3InterfaceElement& elt);

        bool __checkAttributeOverloadLegality(O3Interface&        i,
                                              O3InterfaceElement& elt);

        bool __checkReferenceOverloadLegality(O3Interface&        i,
                                              O3InterfaceElement& elt);

        bool __checkCyclicReference(O3Interface& i, O3InterfaceElement& elt);
      };

    }   // namespace o3prm
  }     // namespace prm
}   // namespace gum

// always include the implementation of the templates
#  include <agrum/PRM/o3prm/O3InterfaceFactory_tpl.h>


#  ifndef GUM_NO_EXTERN_TEMPLATE_CLASS
extern template class gum::prm::o3prm::O3InterfaceFactory< double >;
#  endif


#endif   // GUM_PRM_O3PRM_O3INTERFACE_FACTORY_H
