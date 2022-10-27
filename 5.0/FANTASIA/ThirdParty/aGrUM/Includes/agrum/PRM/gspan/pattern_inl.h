
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
 * @brief Inline implementation of the Pattern class.
 *
 * @author Lionel TORTI and Pierre-Henri WUILLEMIN
 */

namespace gum {
  namespace prm {
    namespace gspan {

      INLINE
      Pattern::Pattern() : DiGraph(), __last(0) { GUM_CONSTRUCTOR(Pattern); }

      INLINE
      Pattern::~Pattern() { GUM_DESTRUCTOR(Pattern); }

      INLINE
      NodeId Pattern::addNodeWithLabel(LabelData& l) {
        NodeId n = NodeId(size() + 1);
        DiGraph::addNodeWithId(n);
        __node_map.insert(n, &l);
        __last = &l;
        return n;
      }

      INLINE
      LabelData& Pattern::label(NodeId node) {
        try {
          return *(__node_map[node]);
        } catch (NotFound&) {
          GUM_ERROR(NotFound, "node not found in this Pattern");
        }
      }

      INLINE
      const LabelData& Pattern::label(NodeId node) const {
        try {
          return *(__node_map[node]);
        } catch (NotFound&) {
          GUM_ERROR(NotFound, "node not found in this Pattern");
        }
      }

      INLINE
      LabelData& Pattern::lastAdded() {
        if (__last) return *__last;

        GUM_ERROR(OperationNotAllowed, "there are no LabelData yet");
      }

      INLINE
      const LabelData& Pattern::lastAdded() const {
        if (__last) return *__last;

        GUM_ERROR(OperationNotAllowed, "there are no LabelData yet");
      }

      INLINE
      LabelData& Pattern::label(NodeId i, NodeId j) {
        try {
          return *(__arc_map[Arc(i, j)].first);
        } catch (NotFound&) {
          GUM_ERROR(NotFound, "arc not found in this Pattern");
        }
      }

      INLINE
      const LabelData& Pattern::label(NodeId i, NodeId j) const {
        try {
          return *(__arc_map[Arc(i, j)].first);
        } catch (NotFound&) {
          GUM_ERROR(NotFound, "arc not found in this Pattern");
        }
      }

      INLINE
      LabelData& Pattern::label(const Arc& arc) {
        try {
          return *(__arc_map[arc].first);
        } catch (NotFound&) {
          GUM_ERROR(NotFound, "arc not found in this Pattern");
        }
      }

      INLINE
      const LabelData& Pattern::label(const Arc& arc) const {
        try {
          return *(__arc_map[arc].first);
        } catch (NotFound&) {
          GUM_ERROR(NotFound, "arc not found in this Pattern");
        }
      }

      INLINE
      void Pattern::addArc(NodeId i, NodeId j, LabelData& l) {
        if (!(DiGraph::exists(i) && DiGraph::exists(j))) {
          GUM_ERROR(NotFound, "node not found in this pattern");
        }

        EdgeCode* edge =
           new EdgeCode(i, j, __node_map[i]->id, l.id, __node_map[j]->id);

        if ((code().codes.size() == 0)
            || (DFSCode::validNeighbors(code().codes.back(), edge))) {
          DiGraph::addArc(i, j);
          __arc_map.insert(Arc(i, j), std::make_pair(&l, edge));
          code().codes.push_back(edge);
        } else {
          delete edge;
          GUM_ERROR(OperationNotAllowed,
                    "illegal arc considering neighborhood restriction");
        }
      }

      INLINE
      bool Pattern::exists(NodeId id) const { return DiGraph::exists(id); }

      INLINE
      bool Pattern::exists(NodeId tail, NodeId head) const {
        return DiGraph::existsArc(tail, head);
      }

      INLINE
      Size Pattern::size() const { return DiGraph::size(); }

      INLINE
      Size Pattern::sizeArcs() const { return DiGraph::sizeArcs(); }

      INLINE
      void Pattern::rightmostPath(std::list< NodeId >& r_path) const {
        r_path.push_back(NodeId(size()));

        while (r_path.front() != 1) {
          for (const auto par : parents(r_path.front())) {
            if (par < r_path.front()) {
              r_path.push_front(par);
              break;
            }
          }
        }
      }

      INLINE const NodeGraphPart& Pattern::nodes() const {
        return DiGraph::nodes();
      }

      INLINE const ArcSet& Pattern::arcs() const { return DiGraph::arcs(); }

      INLINE
      DFSCode& Pattern::code() { return __code; }

      INLINE
      const DFSCode& Pattern::code() const { return __code; }

      INLINE
      EdgeCode& Pattern::edgeCode(NodeId tail, NodeId head) {
        try {
          return *(__arc_map[Arc(tail, head)].second);
        } catch (NotFound&) { GUM_ERROR(NotFound, "arc not found in Pattern"); }
      }

      INLINE
      EdgeCode& Pattern::edgeCode(const Arc& arc) {
        try {
          return *(__arc_map[arc].second);
        } catch (NotFound&) { GUM_ERROR(NotFound, "arc not found in Pattern"); }
      }

      INLINE
      const EdgeCode& Pattern::edgeCode(NodeId tail, NodeId head) const {
        try {
          return *(__arc_map[Arc(tail, head)].second);
        } catch (NotFound&) { GUM_ERROR(NotFound, "arc not found in Pattern"); }
      }

      INLINE
      const EdgeCode& Pattern::edgeCode(const Arc& arc) const {
        try {
          return *(__arc_map[arc].second);
        } catch (NotFound&) { GUM_ERROR(NotFound, "arc not found in Pattern"); }
      }

      INLINE
      void Pattern::pop_back() {
        EdgeCode* edge = __code.codes.back();
        __code.codes.pop_back();

        if (edge->isForward()) {
          __node_map.erase(edge->j);
          __arc_map.erase(Arc(edge->i, edge->j));
          DiGraph::eraseArc(Arc(edge->i, edge->j));
          DiGraph::eraseNode(edge->j);
        } else {
          __arc_map.erase(Arc(edge->i, edge->j));
          DiGraph::eraseArc(Arc(edge->i, edge->j));
        }

        delete edge;
      }

      INLINE
      void Pattern::remove(NodeId node) {
        if (DiGraph::parents(node).empty() && DiGraph::children(node).empty()) {
          DiGraph::eraseNode(node);
          __node_map.erase(node);
        } else {
          GUM_ERROR(OperationNotAllowed, "the given node has neighbors");
        }
      }
    } /* namespace gspan */
  }   /* namespace prm */
} /* namespace gum */
