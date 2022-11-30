
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


#include "CNMonteCarloSampling.h"
#include <agrum/core/exceptions.h>

namespace gum {
  namespace credal {

    template < typename GUM_SCALAR, class BNInferenceEngine >
    CNMonteCarloSampling< GUM_SCALAR, BNInferenceEngine >::CNMonteCarloSampling(
       const CredalNet< GUM_SCALAR >& credalNet) :
        MultipleInferenceEngine< GUM_SCALAR, BNInferenceEngine >::
           MultipleInferenceEngine(credalNet) {
      __infEs::_repetitiveInd = false;
      //__infEs::_iterStop = 1000;
      __infEs::_storeVertices = false;
      __infEs::_storeBNOpt = false;

      this->setMaxTime(60);
      this->enableMaxTime();

      /// this->setBurnIn ( 1000 );
      this->setPeriodSize(1000);

      GUM_CONSTRUCTOR(CNMonteCarloSampling);
    }

    template < typename GUM_SCALAR, class BNInferenceEngine >
    CNMonteCarloSampling< GUM_SCALAR,
                          BNInferenceEngine >::~CNMonteCarloSampling() {
      GUM_DESTRUCTOR(CNMonteCarloSampling);
    }

    template < typename GUM_SCALAR, class BNInferenceEngine >
    void CNMonteCarloSampling< GUM_SCALAR, BNInferenceEngine >::makeInference() {
      if (__infEs::_repetitiveInd) {
        try {
          this->_repetitiveInit();
        } catch (InvalidArgument& err) {
          GUM_SHOWERROR(err);
          __infEs::_repetitiveInd = false;
        }
      }

      // debug
      /// notOptDelete = 0;

      __mcInitApproximationScheme();

      __mcThreadDataCopy();

      // don't put it after burnIn, it could stop with timeout : we want at
      // least one
      // burnIn and one periodSize
      GUM_SCALAR eps = 1.;   // to validate testSuite ?

      /// auto bsize = this->burnIn();
      auto psize = this->periodSize();
      /*

            auto remaining = this->remainingBurnIn();

            /// this->burnIn() should be 0 therefor the first do ... while should
      be
            /// skipped
            if ( remaining != 0 ) {
              /// instead of doing the whole burnIn in one pass, we do it period by
              /// period
              /// so we can test the timer ( done by continueApproximationScheme )
      and
              /// exit
              /// during burnIn
              /// no error is thrown if we exit during burnIn ( although one should
      )
              do {
                eps = 0;

                int iters = int( ( remaining < psize ) ? remaining : psize );

      #pragma omp parallel for

                for ( int iter = 0; iter < iters; iter++ ) {
                  __threadInference();
                  __threadUpdate();
                }  // end of : parallel periodSize

                this->updateApproximationScheme( iters );

                /// this->_updateMarginals(); // fusion threads + update margi

                /// eps = this->_computeEpsilon(); // also updates oldMargi

                remaining = this->remainingBurnIn();

              } while ( ( remaining > 0 ) && this->continueApproximationScheme( eps
      ) );
            }
      */

      if (this->continueApproximationScheme(eps)) {
        do {
          eps = 0;

// less overheads with high periodSize
#pragma omp parallel for

          for (int iter = 0; iter < int(psize); iter++) {
            __threadInference();
            __threadUpdate();
          }   // end of : parallel periodSize

          this->updateApproximationScheme(int(psize));

          this->_updateMarginals();   // fusion threads + update margi

          eps = this->_computeEpsilon();   // also updates oldMargi

        } while (this->continueApproximationScheme(eps));
      }

      if (!this->_modal.empty()) { this->_expFusion(); }

      if (__infEs::_storeBNOpt) { this->_optFusion(); }

      if (__infEs::_storeVertices) { this->_verticesFusion(); }

      if (!this->_modal.empty()) {
        this->_dynamicExpectations();   // work with any network
      }

      /// GUM_TRACE ( this->messageApproximationScheme() );
    }

    template < typename GUM_SCALAR, class BNInferenceEngine >
    inline void
       CNMonteCarloSampling< GUM_SCALAR, BNInferenceEngine >::__threadUpdate() {
      int tId = getThreadNumber();
      // bool keepSample = false;

      if (this->_l_inferenceEngine[tId]->evidenceProbability() > 0) {
        const DAG& tDag = this->_workingSet[tId]->dag();

        for (auto node : tDag.nodes()) {
          const Potential< GUM_SCALAR >& potential(
             this->_l_inferenceEngine[tId]->posterior(node));
          Instantiation             ins(potential);
          std::vector< GUM_SCALAR > vertex;

          for (ins.setFirst(); !ins.end(); ++ins) {
            vertex.push_back(potential[ins]);
          }

          // true for redundancy elimination of node it credal set
          // but since global marginals are only updated at the end of each
          // period of
          // approximationScheme, it is "useless" ( and expensive ) to check now
          this->_updateThread(node, vertex, false);

        }   // end of : for all nodes
      }     // end of : if ( p(e) > 0 )
    }

    template < typename GUM_SCALAR, class BNInferenceEngine >
    inline void
       CNMonteCarloSampling< GUM_SCALAR, BNInferenceEngine >::__threadInference() {
      int tId = getThreadNumber();
      __verticesSampling();

      this->_l_inferenceEngine[tId]->eraseAllEvidence();
      __insertEvidence();
      this->_l_inferenceEngine[tId]->makeInference();
    }

    template < typename GUM_SCALAR, class BNInferenceEngine >
    void CNMonteCarloSampling< GUM_SCALAR,
                               BNInferenceEngine >::__mcInitApproximationScheme() {
      // this->setEpsilon ( std::numeric_limits< GUM_SCALAR >::min() );
      /**
       * VERIFIER d/dt(e(t+1)-e(t))
       */
      this->setEpsilon(0.);
      this->enableEpsilon();   // to be sure

      this->disableMinEpsilonRate();
      this->disableMaxIter();

      this->initApproximationScheme();
    }

    template < typename GUM_SCALAR, class BNInferenceEngine >
    void CNMonteCarloSampling< GUM_SCALAR,
                               BNInferenceEngine >::__mcThreadDataCopy() {
      int num_threads;
#pragma omp parallel
      {
        int this_thread = getThreadNumber();

// implicit wait clause (don't put nowait)
#pragma omp single
        {
          // should we ask for max threads instead ( no differences here in
          // practice
          // )
          num_threads = getNumberOfRunningThreads();

          this->_initThreadsData(
             num_threads, __infEs::_storeVertices, __infEs::_storeBNOpt);
          this->_l_inferenceEngine.resize(num_threads, nullptr);

          // if ( __infEs::_storeBNOpt )
          // this->_l_sampledNet.resize ( num_threads );
        }   // end of : single region

        // we could put those below in a function in InferenceEngine, but let's
        // keep
        // this parallel region instead of breaking it and making another one to
        // do
        // the same stuff in 2 places since :
        // !!! BNInferenceEngine still needs to be initialized here anyway !!!

        BayesNet< GUM_SCALAR >* thread_bn = new BayesNet< GUM_SCALAR >();
#pragma omp critical(Init)
        {
          // IBayesNet< GUM_SCALAR > * thread_bn = new IBayesNet< GUM_SCALAR
          // >();//(this->_credalNet->current_bn());
          *thread_bn = this->_credalNet->current_bn();
        }
        this->_workingSet[this_thread] = thread_bn;

        this->_l_marginalMin[this_thread] = this->_marginalMin;
        this->_l_marginalMax[this_thread] = this->_marginalMax;
        this->_l_expectationMin[this_thread] = this->_expectationMin;
        this->_l_expectationMax[this_thread] = this->_expectationMax;
        this->_l_modal[this_thread] = this->_modal;

        __infEs::_l_clusters[this_thread].resize(2);
        __infEs::_l_clusters[this_thread][0] = __infEs::_t0;
        __infEs::_l_clusters[this_thread][1] = __infEs::_t1;

        if (__infEs::_storeVertices) {
          this->_l_marginalSets[this_thread] = this->_marginalSets;
        }

        List< const Potential< GUM_SCALAR >* >* evi_list =
           new List< const Potential< GUM_SCALAR >* >();
        this->_workingSetE[this_thread] = evi_list;

        // #TODO: the next instruction works only for lazy propagation.
        //        => find a way to remove the second argument
        BNInferenceEngine* inference_engine =
           new BNInferenceEngine((this->_workingSet[this_thread]),
                                 RelevantPotentialsFinderType::FIND_ALL);

        this->_l_inferenceEngine[this_thread] = inference_engine;

        if (__infEs::_storeBNOpt) {
          VarMod2BNsMap< GUM_SCALAR >* threadOpt =
             new VarMod2BNsMap< GUM_SCALAR >(*this->_credalNet);
          this->_l_optimalNet[this_thread] = threadOpt;
        }
      }
    }

    template < typename GUM_SCALAR, class BNInferenceEngine >
    inline void CNMonteCarloSampling< GUM_SCALAR, BNInferenceEngine >::__binaryRep(
       std::vector< bool >& toFill, const Idx value) const {
      Idx  n = value;
      auto tfsize = toFill.size();

      // get bits of choosen_vertex
      for (decltype(tfsize) i = 0; i < tfsize; i++) {
        toFill[i] = n & 1;
        n /= 2;
      }
    }

    template < typename GUM_SCALAR, class BNInferenceEngine >
    inline void CNMonteCarloSampling< GUM_SCALAR,
                                      BNInferenceEngine >::__verticesSampling() {
      int                      this_thread = getThreadNumber();
      IBayesNet< GUM_SCALAR >* working_bn = this->_workingSet[this_thread];

      const auto cpt = &this->_credalNet->credalNet_currentCpt();

      using dBN = std::vector< std::vector< std::vector< bool > > >;

      dBN sample;

      if (__infEs::_storeBNOpt) {
        sample = dBN(this->_l_optimalNet[this_thread]->getSampleDef());
      }

      if (__infEs::_repetitiveInd) {
        const auto& t0 = __infEs::_l_clusters[this_thread][0];
        const auto& t1 = __infEs::_l_clusters[this_thread][1];

        for (const auto& elt : t0) {
          auto dSize = working_bn->variable(elt.first).domainSize();
          Potential< GUM_SCALAR >* potential(
             const_cast< Potential< GUM_SCALAR >* >(&working_bn->cpt(elt.first)));
          std::vector< GUM_SCALAR > var_cpt(potential->domainSize());

          Size pconfs = Size((*cpt)[elt.first].size());

          for (Size pconf = 0; pconf < pconfs; pconf++) {
            Size choosen_vertex = rand() % (*cpt)[elt.first][pconf].size();

            if (__infEs::_storeBNOpt) {
              __binaryRep(sample[elt.first][pconf], choosen_vertex);
            }

            for (Size mod = 0; mod < dSize; mod++) {
              var_cpt[pconf * dSize + mod] =
                 (*cpt)[elt.first][pconf][choosen_vertex][mod];
            }
          }   // end of : pconf

          potential->fillWith(var_cpt);

          Size t0esize = Size(elt.second.size());

          for (Size pos = 0; pos < t0esize; pos++) {
            if (__infEs::_storeBNOpt) {
              sample[elt.second[pos]] = sample[elt.first];
            }

            Potential< GUM_SCALAR >* potential2(
               const_cast< Potential< GUM_SCALAR >* >(
                  &working_bn->cpt(elt.second[pos])));
            potential2->fillWith(var_cpt);
          }
        }

        for (const auto& elt : t1) {
          auto dSize = working_bn->variable(elt.first).domainSize();
          Potential< GUM_SCALAR >* potential(
             const_cast< Potential< GUM_SCALAR >* >(&working_bn->cpt(elt.first)));
          std::vector< GUM_SCALAR > var_cpt(potential->domainSize());

          for (Size pconf = 0; pconf < (*cpt)[elt.first].size(); pconf++) {
            Idx choosen_vertex = Idx(rand() % (*cpt)[elt.first][pconf].size());

            if (__infEs::_storeBNOpt) {
              __binaryRep(sample[elt.first][pconf], choosen_vertex);
            }

            for (decltype(dSize) mod = 0; mod < dSize; mod++) {
              var_cpt[pconf * dSize + mod] =
                 (*cpt)[elt.first][pconf][choosen_vertex][mod];
            }
          }   // end of : pconf

          potential->fillWith(var_cpt);

          auto t1esize = elt.second.size();

          for (decltype(t1esize) pos = 0; pos < t1esize; pos++) {
            if (__infEs::_storeBNOpt) {
              sample[elt.second[pos]] = sample[elt.first];
            }

            Potential< GUM_SCALAR >* potential2(
               const_cast< Potential< GUM_SCALAR >* >(
                  &working_bn->cpt(elt.second[pos])));
            potential2->fillWith(var_cpt);
          }
        }

        if (__infEs::_storeBNOpt) {
          this->_l_optimalNet[this_thread]->setCurrentSample(sample);
        }
      } else {
        for (auto node : working_bn->nodes()) {
          auto                     dSize = working_bn->variable(node).domainSize();
          Potential< GUM_SCALAR >* potential(
             const_cast< Potential< GUM_SCALAR >* >(&working_bn->cpt(node)));
          std::vector< GUM_SCALAR > var_cpt(potential->domainSize());

          auto pConfs = (*cpt)[node].size();

          for (decltype(pConfs) pconf = 0; pconf < pConfs; pconf++) {
            Size nVertices = Size((*cpt)[node][pconf].size());
            Idx  choosen_vertex = Idx(rand() % nVertices);

            if (__infEs::_storeBNOpt) {
              __binaryRep(sample[node][pconf], choosen_vertex);
            }

            for (decltype(dSize) mod = 0; mod < dSize; mod++) {
              var_cpt[pconf * dSize + mod] =
                 (*cpt)[node][pconf][choosen_vertex][mod];
            }
          }   // end of : pconf

          potential->fillWith(var_cpt);
        }

        if (__infEs::_storeBNOpt) {
          this->_l_optimalNet[this_thread]->setCurrentSample(sample);
        }
      }
    }

    template < typename GUM_SCALAR, class BNInferenceEngine >
    inline void
       CNMonteCarloSampling< GUM_SCALAR, BNInferenceEngine >::__insertEvidence() {
      if (this->_evidence.size() == 0) { return; }

      int this_thread = getThreadNumber();

      BNInferenceEngine* inference_engine = this->_l_inferenceEngine[this_thread];

      IBayesNet< GUM_SCALAR >* working_bn = this->_workingSet[this_thread];

      List< const Potential< GUM_SCALAR >* >* evi_list =
         this->_workingSetE[this_thread];

      if (evi_list->size() > 0) {
        for (const auto pot : *evi_list)
          inference_engine->addEvidence(*pot);
        return;
      }

      for (const auto& elt : this->_evidence) {
        Potential< GUM_SCALAR >* p = new Potential< GUM_SCALAR >;
        (*p) << working_bn->variable(elt.first);

        try {
          p->fillWith(elt.second);
        } catch (Exception& err) {
          GUM_SHOWERROR(err);
          throw(err);
        }

        evi_list->insert(p);
      }

      if (evi_list->size() > 0) {
        for (const auto pot : *evi_list)
          inference_engine->addEvidence(*pot);
      }
    }

  }   // namespace credal
}   // namespace gum
