
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
 * @brief Inline implementation of ClassDependencyGraph.
 *
 * @author Lionel TORTI and Pierre-Henri WUILLEMIN
 */
#include <agrum/PRM/classDependencyGraph.h>

namespace gum {
  namespace prm {

    // Destructor.
    template < typename GUM_SCALAR >
    ClassDependencyGraph< GUM_SCALAR >::~ClassDependencyGraph() {
      GUM_DESTRUCTOR(ClassDependencyGraph);

      for (const auto& elt : __node_map)
        delete elt.second;

      for (const auto& elt : __elt_map)
        delete elt.second;
    }

    // Build the class dependency graph.
    template < typename GUM_SCALAR >
    void ClassDependencyGraph< GUM_SCALAR >::__buildGraph(
       const PRM< GUM_SCALAR >& prm) {
      // First we add all nodes
      for (const auto ci : prm.classes()) {
        __node_map.insert(
           ci, new HashTable< const PRMClassElement< GUM_SCALAR >*, NodeId >());

        for (const auto node : ci->containerDag().nodes())
          __addNode(ci, ci->get(node));
      }

      for (const auto ii : prm.interfaces()) {
        __node_map.insert(
           ii, new HashTable< const PRMClassElement< GUM_SCALAR >*, NodeId >());

        for (const auto node : ii->containerDag().nodes()) {
          __addNode(ii, ii->get(node));
        }
      }

      // Then we add the arcs
      for (const auto cc : prm.classes())
        for (const auto node : cc->containerDag().nodes())
          __addArcs(*cc, node, *(__node_map[cc]));
    }

    // Add arcs in __graph.
    template < typename GUM_SCALAR >
    void ClassDependencyGraph< GUM_SCALAR >::__addArcs(
       const PRMClassElementContainer< GUM_SCALAR >&              c,
       NodeId                                                     node,
       HashTable< const PRMClassElement< GUM_SCALAR >*, NodeId >& map) {
      switch (c.get(node).elt_type()) {
        case PRMClassElement< GUM_SCALAR >::prm_slotchain: {
          const PRMSlotChain< GUM_SCALAR >& sc =
             static_cast< const PRMSlotChain< GUM_SCALAR >& >(c.get(node));

          for (const auto chi : c.containerDag().children(node))
            __graph.addArc((*(__node_map[&(sc.end())]))[&(
                              sc.end().get(sc.lastElt().safeName()))],
                           map[&(c.get(chi))]);

          break;
        }

        case PRMClassElement< GUM_SCALAR >::prm_aggregate:
        case PRMClassElement< GUM_SCALAR >::prm_attribute: {
          for (const auto chi : c.containerDag().children(node))
            __graph.addArc(map[&(c.get(node))], map[&(c.get(chi))]);

          break;
        }

        default: { /* do nothing */ break;
        }
      }
    }

    template < typename GUM_SCALAR >
    INLINE ClassDependencyGraph< GUM_SCALAR >::ClassDependencyGraph(
       const PRM< GUM_SCALAR >& prm) {
      GUM_CONSTRUCTOR(ClassDependencyGraph);
      __buildGraph(prm);
    }

    template < typename GUM_SCALAR >
    INLINE ClassDependencyGraph< GUM_SCALAR >::ClassDependencyGraph(
       const ClassDependencyGraph< GUM_SCALAR >& source) :
        __graph(source.__graph),
        __modalitites(source.__modalitites), __elt_map(source.__elt_map) {
      GUM_CONS_CPY(ClassDependencyGraph);

      for (const auto elt : source.__node_map) {
        __node_map.insert(
           elt.first,
           new HashTable< const PRMClassElement< GUM_SCALAR >*, NodeId >(
              *elt.second));
      }
    }

    template < typename GUM_SCALAR >
    INLINE const DAG& ClassDependencyGraph< GUM_SCALAR >::dag() const {
      return __graph;
    }

    template < typename GUM_SCALAR >
    INLINE const typename ClassDependencyGraph< GUM_SCALAR >::EltPair&
       ClassDependencyGraph< GUM_SCALAR >::get(NodeId id) const {
      return *(__elt_map[id]);
    }

    template < typename GUM_SCALAR >
    INLINE NodeId ClassDependencyGraph< GUM_SCALAR >::get(
       const PRMClassElementContainer< GUM_SCALAR >& c,
       const PRMClassElement< GUM_SCALAR >&          elt) const {
      return (*(__node_map[&c]))[&elt];
    }

    template < typename GUM_SCALAR >
    INLINE const NodeProperty< Size >&
                 ClassDependencyGraph< GUM_SCALAR >::modalities() const {
      return __modalitites;
    }

    template < typename GUM_SCALAR >
    INLINE void ClassDependencyGraph< GUM_SCALAR >::__addNode(
       const PRMClassElementContainer< GUM_SCALAR >* c,
       const PRMClassElement< GUM_SCALAR >&          elt) {
      switch (elt.elt_type()) {
        case PRMClassElement< GUM_SCALAR >::prm_attribute:
        case PRMClassElement< GUM_SCALAR >::prm_aggregate: {
          NodeId id = __graph.addNode();
          __elt_map.insert(
             id, new ClassDependencyGraph< GUM_SCALAR >::EltPair(c, &elt));
          __node_map[c]->insert(&elt, id);
          __modalitites.insert(id, elt.type().variable().domainSize());
          break;
        }

        default: { /* do nothing */ break;
        }
      }
    }

  } /* namespace prm */
} /* namespace gum */
