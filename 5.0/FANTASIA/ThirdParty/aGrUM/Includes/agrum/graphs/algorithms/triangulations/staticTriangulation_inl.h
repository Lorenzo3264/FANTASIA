
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
 * @brief Inline implementations for computing default triangulations of graphs
 *
 * @author Christophe GONZALES and Pierre-Henri WUILLEMIN
 */

#ifndef DOXYGEN_SHOULD_SKIP_THIS


namespace gum {


  /// returns an elimination ordering compatible with the triangulated graph
  INLINE
  const std::vector< NodeId >& StaticTriangulation::eliminationOrder() {
    if (!__has_triangulation) __triangulate();

    return __elim_order;
  }


  /** @brief returns the index of a given node in the elimination order
   * (0 = first node eliminated) */
  INLINE
  Idx StaticTriangulation::eliminationOrder(const NodeId id) {
    if (!__has_triangulation) __triangulate();

    return __reverse_elim_order[id];
  }


  /** @brief returns the number of a given node in the elimination order
   * (0 = first node eliminated) */
  INLINE
  const NodeProperty< NodeId >& StaticTriangulation::reverseEliminationOrder() {
    if (!__has_triangulation) __triangulate();

    return __reverse_elim_order;
  }


  /// returns the elimination tree of a compatible ordering
  INLINE
  const CliqueGraph& StaticTriangulation::eliminationTree() {
    if (!__has_elimination_tree) __computeEliminationTree();

    return __elim_tree;
  }


  /// returns a compatible junction tree
  INLINE
  const CliqueGraph& StaticTriangulation::junctionTree() {
    // checks if junctionTree already exists
    if (!__has_junction_tree) {
      __junction_tree = &(_junction_tree_strategy->junctionTree());
      __has_junction_tree = true;
    }

    return *__junction_tree;
  }


  /// returns a junction tree of maximal prime subgraphs
  INLINE
  const CliqueGraph& StaticTriangulation::maxPrimeSubgraphTree() {
    if (!__has_max_prime_junction_tree) __computeMaxPrimeJunctionTree();

    return __max_prime_junction_tree;
  }


  /** @brief returns the Id of the maximal prime subgraph created by the
   * elimination of a given node during the triangulation process */
  INLINE
  NodeId StaticTriangulation::createdMaxPrimeSubgraph(const NodeId id) {
    if (!__has_max_prime_junction_tree) __computeMaxPrimeJunctionTree();

    return __node_2_max_prime_clique[id];
  }


  /** @brief returns the Id of the clique created by the
   * elimination of a given node during the triangulation process */
  INLINE
  NodeId StaticTriangulation::createdJunctionTreeClique(const NodeId id) {
    return _junction_tree_strategy->createdClique(id);
  }


  /** @brief returns the Ids of the cliques of the junction tree created by the
   * elimination of the nodes */
  INLINE
  const NodeProperty< NodeId >& StaticTriangulation::createdJunctionTreeCliques() {
    return _junction_tree_strategy->createdCliques();
  }


  /// sets/unset the fill-ins storage in the standard triangulation procedure
  INLINE
  void StaticTriangulation::setFillIns(bool b) {
    __we_want_fill_ins = b;
    _elimination_sequence_strategy->askFillIns(b);
  }


  /// returns the graph to be triangulated
  INLINE
  const UndiGraph* StaticTriangulation::originalGraph() const {
    return __original_graph;
  }


  /// returns the elimination sequence strategy used by the triangulation
  INLINE EliminationSequenceStrategy&
         StaticTriangulation::eliminationSequenceStrategy() const {
    return *_elimination_sequence_strategy;
  }


  /// returns the junction tree strategy used by the triangulation
  INLINE JunctionTreeStrategy& StaticTriangulation::junctionTreeStrategy() const {
    return *_junction_tree_strategy;
  }


  /// indicates wether minimality is required
  INLINE bool StaticTriangulation::isMinimalityRequired() const {
    return __minimality_required;
  }


} /* namespace gum */


#endif /* DOXYGEN_SHOULD_SKIP_THIS */
