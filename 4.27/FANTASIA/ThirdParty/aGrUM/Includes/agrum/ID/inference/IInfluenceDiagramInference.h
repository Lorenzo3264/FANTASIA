
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
 * @brief This file contains abstract class definitions influence diagrams
 *        inference classes.
 *
 * @author Jean-Christophe MAGNAN and Pierre-Henri WUILLEMIN
 */

#ifndef GUM_IINFLUENCE_DIAGRAM_INFERENCE_H
#define GUM_IINFLUENCE_DIAGRAM_INFERENCE_H

#include <agrum/ID/influenceDiagram.h>
#include <agrum/agrum.h>

namespace gum {
  /**
   * @class IInfluenceDiagramInference IInfluenceDiagramInference.h
   *<agrum/ID/inference/IInfluenceDiagramInference.h>
   * @brief Abstract base class for inference engines in influence diagrams.
   * @ingroup id_group
   *
   */
  template < typename GUM_SCALAR >
  class IInfluenceDiagramInference {
    public:
    /**
     * Default constructor
     */
    explicit IInfluenceDiagramInference(
       const InfluenceDiagram< GUM_SCALAR >& infDiag);

    /**
     * Destructor.
     */
    virtual ~IInfluenceDiagramInference();

    /**
     * Makes the inference
     */
    virtual void makeInference() = 0;

    /**
     * Insert new evidence in the graph.
     * @warning if an evidence already w.r.t. a given node and a new
     * evidence w.r.t. this node is onserted, the old evidence is removed.
     * @throw OperationNotAllowed Raised if an evidence is over more than one
     * variable.
     */
    virtual void insertEvidence(
       const List< const Potential< GUM_SCALAR >* >& evidenceList) = 0;

    /**
     * Remove a given evidence from the graph.
     */
    virtual void eraseEvidence(const Potential< GUM_SCALAR >* evidence) = 0;

    /**
     * Remove all evidence from the graph.
     */
    virtual void eraseAllEvidence() = 0;

    /**
     * Returns a constant reference over the InfluenceDiagram on which this
     * class
     * work.
     */
    const InfluenceDiagram< GUM_SCALAR >& influenceDiagram() const;

    /**
     * Returns maximum expected utility obtained from inference
     * @throw OperationNotAllowed if no inference have yet been made
     */
    virtual GUM_SCALAR getMEU() = 0;

    /**
     * Returns best choice for decision variable given in parameter ( based upon
     * MEU
     * criteria )
     * @param decisionId the id of the decision variable
     * @throw OperationNotAllowed if no inference have yet been made
     * @throw InvalidNode if node given in parmaeter is not a decision node
     */
    virtual Idx getBestDecisionChoice(NodeId decisionId) = 0;

    protected:
    /**
     * The Bayes net we wish to perform inference on.
     */
    const InfluenceDiagram< GUM_SCALAR >& __infDiag;
  };

} /* namespace gum */

#include <agrum/ID/inference/IInfluenceDiagramInference_tpl.h>

#endif /* GUM_IINFLUENCE_DIAGRAM_INFERENCE_H */