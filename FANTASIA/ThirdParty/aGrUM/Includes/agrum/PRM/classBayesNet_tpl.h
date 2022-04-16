
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
 * @brief Inline implementation of ClassBayesNet.
 *
 * @author Lionel TORTI and Pierre-Henri WUILLEMIN
 */
#include <agrum/PRM/classBayesNet.h>   // to ease IDE parser
#include <agrum/core/inline.h>

namespace gum {
  namespace prm {

    template < typename GUM_SCALAR >
    void ClassBayesNet< GUM_SCALAR >::__init(const PRMClass< GUM_SCALAR >& c) {
      for (const auto node : c.containerDag().nodes()) {
        try {
          // Adding the attribute
          if (PRMClassElement< GUM_SCALAR >::isAttribute(c.get(node))
              || PRMClassElement< GUM_SCALAR >::isAggregate(c.get(node))) {
            const PRMClassElement< GUM_SCALAR >& elt = c.get(node);
            this->_dag.addNodeWithId(elt.id());
            this->__varNodeMap.insert(&(elt.type().variable()), &elt);
          }
        } catch (NotFound&) {
          // Not an attribute
        }
      }

      for (const auto& arc : c.containerDag().arcs()) {
        try {
          this->_dag.addArc(arc.tail(), arc.head());
        } catch (InvalidNode&) {
          // Not added means not an attribute
        }
      }
    }

    template < typename GUM_SCALAR >
    INLINE ClassBayesNet< GUM_SCALAR >::ClassBayesNet(
       const PRMClass< GUM_SCALAR >& c) :
        IBayesNet< GUM_SCALAR >(),
        __class(&c) {
      GUM_CONSTRUCTOR(ClassBayesNet);
      __init(c);
    }

    template < typename GUM_SCALAR >
    INLINE ClassBayesNet< GUM_SCALAR >::ClassBayesNet(
       const ClassBayesNet< GUM_SCALAR >& from) :
        IBayesNet< GUM_SCALAR >(from),
        __class(from.__class) {
      GUM_CONS_CPY(ClassBayesNet);
    }

    template < typename GUM_SCALAR >
    INLINE ClassBayesNet< GUM_SCALAR >::~ClassBayesNet() {
      GUM_DESTRUCTOR(ClassBayesNet);
    }

    template < typename GUM_SCALAR >
    INLINE ClassBayesNet< GUM_SCALAR >& ClassBayesNet< GUM_SCALAR >::
                                        operator=(const ClassBayesNet< GUM_SCALAR >& from) {
      if (this != &from) {
        IBayesNet< GUM_SCALAR >::operator=(from);

        __class = from.__class;
      }

      return *this;
    }

    template < typename GUM_SCALAR >
    INLINE const Potential< GUM_SCALAR >&
                 ClassBayesNet< GUM_SCALAR >::cpt(NodeId varId) const {
      return __get(varId).cpf();
    }

    template < typename GUM_SCALAR >
    INLINE const VariableNodeMap&
                 ClassBayesNet< GUM_SCALAR >::variableNodeMap() const {
      GUM_ERROR(FatalError, "Sorry no VarMap in a ClassBayesNet.");
    }

    template < typename GUM_SCALAR >
    INLINE const DiscreteVariable&
                 ClassBayesNet< GUM_SCALAR >::variable(NodeId id) const {
      return __get(id).type().variable();
    }

    template < typename GUM_SCALAR >
    INLINE NodeId
           ClassBayesNet< GUM_SCALAR >::nodeId(const DiscreteVariable& var) const {
      return __varNodeMap[&var]->id();
    }

    template < typename GUM_SCALAR >
    INLINE NodeId
           ClassBayesNet< GUM_SCALAR >::idFromName(const std::string& name) const {
      return __get(name).id();
    }

    template < typename GUM_SCALAR >
    INLINE const DiscreteVariable& ClassBayesNet< GUM_SCALAR >::variableFromName(
       const std::string& name) const {
      return __get(name).type().variable();
    }

    template < typename GUM_SCALAR >
    INLINE const PRMClassElement< GUM_SCALAR >&
                 ClassBayesNet< GUM_SCALAR >::__get(NodeId id) const {
      if (this->_dag.exists(id)) {
        return __class->get(id);
      } else {
        GUM_ERROR(NotFound, "no element found with that id.");
      }
    }

    template < typename GUM_SCALAR >
    INLINE const PRMClassElement< GUM_SCALAR >&
                 ClassBayesNet< GUM_SCALAR >::__get(const std::string& name) const {
      try {
        return __class->get(name);
      } catch (NotFound&) {
        GUM_ERROR(NotFound, "no element found with that id.");
      }
    }

    template < typename GUM_SCALAR >
    INLINE const NodeProperty< Size >&
                 ClassBayesNet< GUM_SCALAR >::modalities() const {
      if (__modalities.empty()) {
        for (const auto node : this->nodes()) {
          __modalities.insert(node, (Size)variable(node).domainSize());
        }
      }

      return __modalities;
    }

    template < typename GUM_SCALAR >
    INLINE std::string ClassBayesNet< GUM_SCALAR >::toDot() const {
      std::string       tab = "  ";
      std::stringstream output;
      output << "digraph \"";
      output << __class->name() << "\" {" << std::endl;

      for (const auto node : this->nodes()) {
        if (this->children(node).size() > 0)
          for (const auto chi : this->children(node)) {
            output << tab << "\"" << variable(node).name() << "\" -> ";
            output << "\"" << variable(chi).name() << "\";" << std::endl;
          }
        else if (this->parents(node).size() == 0) {
          output << tab << "\"" << variable(node).name() << "\";" << std::endl;
        }
      }

      output << "}" << std::endl;
      return output.str();
    }

  } /* namespace prm */
} /* namespace gum */
