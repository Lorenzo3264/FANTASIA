
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


/** @file
 * @brief Inline implementation of classes for directed edge sets
 *
 * @author Pierre-Henri WUILLEMIN and Christophe GONZALES
 *
 */

// to ease parsing by IDE
#include <agrum/graphs/parts/arcGraphPart.h>

namespace gum {

  INLINE bool ArcGraphPart::emptyArcs() const { return __arcs.empty(); }

  INLINE Size ArcGraphPart::sizeArcs() const { return __arcs.size(); }

  INLINE const ArcSet& ArcGraphPart::arcs() const { return __arcs; }

  INLINE bool ArcGraphPart::existsArc(const Arc& arc) const {
    return __arcs.contains(arc);
  }

  INLINE bool ArcGraphPart::existsArc(const NodeId tail, const NodeId head) const {
    return __parents.exists(head) && __parents[head]->exists(tail);
  }

  INLINE void ArcGraphPart::__checkParents(const NodeId id) const {
    if (!__parents.exists(id)) { __parents.insert(id, new NodeSet); }
  }

  INLINE void ArcGraphPart::__checkChildren(const NodeId id) const {
    if (!__children.exists(id)) { __children.insert(id, new NodeSet); }
  }

  INLINE const NodeSet& ArcGraphPart::parents(const NodeId id) const {
    __checkParents(id);
    return *(__parents[id]);
  }

  INLINE const NodeSet& ArcGraphPart::children(const NodeId id) const {
    __checkChildren(id);
    return *(__children[id]);
  }

  INLINE void ArcGraphPart::addArc(const NodeId tail, const NodeId head) {
    Arc arc(tail, head);

    __arcs.insert(arc);
    __checkParents(head);
    __checkChildren(tail);
    __parents[head]->insert(tail);
    __children[tail]->insert(head);

    GUM_EMIT2(onArcAdded, tail, head);
  }

  INLINE void ArcGraphPart::eraseArc(const Arc& arc) {
    // ASSUMING tail and head exists in __parents anf __children
    // (if not, it is an error)
    if (existsArc(arc)) {
      NodeId tail = arc.tail(), head = arc.head();
      __parents[head]->erase(tail);
      __children[tail]->erase(head);
      __arcs.erase(arc);
      GUM_EMIT2(onArcDeleted, tail, head);
    }
  }

  INLINE void ArcGraphPart::_eraseSetOfArcs(const ArcSet& set) {
    for (const auto arc : set)
      eraseArc(arc);
  }

  INLINE void ArcGraphPart::eraseParents(const NodeId id) {
    if (__parents.exists(id)) {
      NodeSet& parents = *(__parents[id]);

      for (auto iter = parents.beginSafe();   // safe iterator needed here
           iter != parents.endSafe();
           ++iter) {
        // warning: use this erase so that you actually use the virtualized
        // arc removal function
        eraseArc(Arc(*iter, id));
      }
    }
  }

  INLINE void ArcGraphPart::eraseChildren(const NodeId id) {
    if (__children.exists(id)) {
      NodeSet& children = *(__children[id]);

      for (auto iter = children.beginSafe();   // safe iterator needed here
           iter != children.endSafe();
           ++iter) {
        // warning: use this erase so that you actually use the vritualized
        // arc removal function
        eraseArc(Arc(id, *iter));
      }
    }
  }

  INLINE void ArcGraphPart::_unvirtualizedEraseSetOfArcs(const ArcSet& set) {
    for (const auto& arc : set)
      ArcGraphPart::eraseArc(arc);
  }

  INLINE void ArcGraphPart::unvirtualizedEraseParents(const NodeId id) {
    if (__parents.exists(id)) {
      NodeSet& parents = *(__parents[id]);

      for (auto iter = parents.beginSafe();   // safe iterator needed here
           iter != parents.endSafe();
           ++iter) {
        ArcGraphPart::eraseArc(Arc(*iter, id));
      }
    }
  }

  INLINE void ArcGraphPart::unvirtualizedEraseChildren(const NodeId id) {
    if (__children.exists(id)) {
      NodeSet& children = *(__children[id]);

      for (auto iter = children.beginSafe();   // safe iterator needed here
           iter != children.endSafe();
           ++iter) {
        ArcGraphPart::eraseArc(Arc(id, *iter));
      }
    }
  }

  INLINE bool ArcGraphPart::operator==(const ArcGraphPart& p) const {
    return __arcs == p.__arcs;
  }

  INLINE bool ArcGraphPart::operator!=(const ArcGraphPart& p) const {
    return __arcs != p.__arcs;
  }

} /* namespace gum */