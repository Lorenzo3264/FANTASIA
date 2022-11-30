
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
 * @brief Implementation of gum::MultiDimImplementation.
 *
 * @author Pierre-Henri WUILLEMIN et Christophe GONZALES
 */

// to ease IDE parser
#include <agrum/multidim/implementations/multiDimImplementation.h>

namespace gum {

  // Default constructor

  template < typename GUM_SCALAR >
  INLINE MultiDimImplementation< GUM_SCALAR >::MultiDimImplementation() :
      MultiDimContainer< GUM_SCALAR >(), __vars(), __slaveInstantiations() {
    GUM_CONSTRUCTOR(MultiDimImplementation);
    __internalChangeMethod = __InternalChangeMethod::DIRECT_CHANGE;
    __internalChangeState = __InternalChangeState::NO_CHANGE;
    __domainSize = 1;
  }

  // Copy constructor

  template < typename GUM_SCALAR >
  INLINE MultiDimImplementation< GUM_SCALAR >::MultiDimImplementation(
     const MultiDimImplementation< GUM_SCALAR >& from) :
      MultiDimContainer< GUM_SCALAR >(from),
      __vars(from.__vars), __internalChangeMethod(from.__internalChangeMethod),
      __internalChangeState(from.__internalChangeState),
      __domainSize(from.__domainSize) {
    GUM_CONS_CPY(MultiDimImplementation);
    GUM_ASSERT(!this->_isCommitNeeded());
  }

  // destructor

  template < typename GUM_SCALAR >
  INLINE MultiDimImplementation< GUM_SCALAR >::~MultiDimImplementation() {
    GUM_DESTRUCTOR(MultiDimImplementation);
    // unregister all remaining slave instantiations

    for (List< Instantiation* >::iterator_safe iter =
            __slaveInstantiations.beginSafe();
         iter != __slaveInstantiations.endSafe();
         ++iter)
      (*iter)->forgetMaster();
  }

  // add a new var to the sequence of __vars.

  template < typename GUM_SCALAR >
  INLINE void
     MultiDimImplementation< GUM_SCALAR >::add(const DiscreteVariable& v) {
    // check if the variable already belongs to the tuple of variables
    // of the Instantiation
    if (__vars.exists(&v)) {
      GUM_ERROR(DuplicateElement,
                "Var " << v.name() << " already exists in this instantiation");
    }
    for (const auto& w : __vars) {
      if (w->name() == v.name())
        GUM_ERROR(DuplicateElement,
                  "A var with name '" << v.name()
                                      << "' already exists in this instantiation");
    }

    __domainSize *= v.domainSize();

    __vars.insert(&v);

    // informs all the slaves that they have to update themselves
    for (List< Instantiation* >::iterator_safe iter =
            __slaveInstantiations.beginSafe();
         iter != __slaveInstantiations.endSafe();
         ++iter) {
      (*iter)->addWithMaster(this, v);
    }

    if (_isInMultipleChangeMethod()) __setNotCommitedChange();
  }

  // removes a var from the variables of the multidimensional matrix

  template < typename GUM_SCALAR >
  INLINE void
     MultiDimImplementation< GUM_SCALAR >::erase(const DiscreteVariable& v) {
    // check that the variable does actually belong to the
    // MultiDimImplementation
    if (!__vars.exists(&v)) {
      GUM_ERROR(NotFound, "Var does not exist in this implementation");
    }

    __domainSize /= v.domainSize();

    __vars.erase(&v);

    // informs all the slaves that they have to update themselves
    for (List< Instantiation* >::iterator_safe iter =
            __slaveInstantiations.beginSafe();
         iter != __slaveInstantiations.endSafe();
         ++iter) {
      (*iter)->eraseWithMaster(this, v);
    }

    if (_isInMultipleChangeMethod()) __setNotCommitedChange();
  }

  // adds a new var to the sequence of __vars
  // @todo this function should be declared somewhere?

  template < typename GUM_SCALAR >
  INLINE MultiDimImplementation< GUM_SCALAR >&
         operator<<(MultiDimImplementation< GUM_SCALAR >& array,
                const DiscreteVariable&               v) {
    array.add(v);
    return array;
  }

  // add a Instantiation to the list of slave instantiations

  template < typename GUM_SCALAR >
  INLINE bool
     MultiDimImplementation< GUM_SCALAR >::registerSlave(Instantiation& slave) {
    // check that the Instantiation has the same variables as this
    if (slave.nbrDim() != __vars.size()) return false;

    for (Sequence< const DiscreteVariable* >::iterator_safe iter =
            __vars.beginSafe();
         iter != __vars.endSafe();
         ++iter)
      if (!slave.contains(*iter)) return false;

    slave.synchronizeWithMaster(this);

    __slaveInstantiations += (&slave);

    return true;
  }

  // removes a Instantiation from the list of slave instantiations

  template < typename GUM_SCALAR >
  INLINE bool
     MultiDimImplementation< GUM_SCALAR >::unregisterSlave(Instantiation& slave) {
    __slaveInstantiations.eraseByVal(&slave);
    // TODO This method should return true? Why not use a void instead?
    return true;
  }

  template < typename GUM_SCALAR >
  INLINE Idx MultiDimImplementation< GUM_SCALAR >::nbrDim() const {
    return __vars.size();
  }

  template < typename GUM_SCALAR >
  INLINE Size MultiDimImplementation< GUM_SCALAR >::domainSize() const {
    return __domainSize;
  }

  template < typename GUM_SCALAR >
  INLINE const DiscreteVariable&
               MultiDimImplementation< GUM_SCALAR >::variable(Idx i) const {
    return *(__vars.atPos(i));
  }

  template < typename GUM_SCALAR >
  INLINE const DiscreteVariable& MultiDimImplementation< GUM_SCALAR >::variable(
     const std::string& name) const {
    for (const auto& v : __vars) {
      if (v->name() == name) return *v;
    }

    GUM_ERROR(NotFound,
              "'" << name << "' can not be found in the multidim structure.")
  }

  template < typename GUM_SCALAR >
  INLINE Idx
         MultiDimImplementation< GUM_SCALAR >::pos(const DiscreteVariable& v) const {
    return __vars.pos(&v);
  }

  template < typename GUM_SCALAR >
  INLINE bool MultiDimImplementation< GUM_SCALAR >::contains(
     const DiscreteVariable& v) const {
    return __vars.exists(&v);
  }

  // returns a const ref to the sequence of DiscreteVariable*

  template < typename GUM_SCALAR >
  INLINE const Sequence< const DiscreteVariable* >&
               MultiDimImplementation< GUM_SCALAR >::variablesSequence() const {
    return __vars;
  }

  // is this empty ?
  template < typename GUM_SCALAR >
  INLINE bool MultiDimImplementation< GUM_SCALAR >::empty() const {
    GUM_ASSERT(!this->_isCommitNeeded());
    return __vars.empty();
  }

  template < typename GUM_SCALAR >
  INLINE void MultiDimImplementation< GUM_SCALAR >::beginMultipleChanges() {
    __internalChangeMethod = __InternalChangeMethod::MULTIPLE_CHANGE;
  }

  template < typename GUM_SCALAR >
  INLINE void MultiDimImplementation< GUM_SCALAR >::endMultipleChanges() {
    if (__internalChangeState == __InternalChangeState::NOT_COMMITTED_CHANGE) {
      _commitMultipleChanges();
      __internalChangeState = __InternalChangeState::NO_CHANGE;
    }

    __internalChangeMethod = __InternalChangeMethod::DIRECT_CHANGE;
  }

  template < typename GUM_SCALAR >
  INLINE void MultiDimImplementation< GUM_SCALAR >::endMultipleChanges(
     const GUM_SCALAR& x) {
    if (__internalChangeState == __InternalChangeState::NOT_COMMITTED_CHANGE) {
      _commitMultipleChanges(x);
      __internalChangeState = __InternalChangeState::NO_CHANGE;
    }

    __internalChangeMethod = __InternalChangeMethod::DIRECT_CHANGE;
  }

  template < typename GUM_SCALAR >
  INLINE void MultiDimImplementation< GUM_SCALAR >::_commitMultipleChanges() {
    // empty!
  }

  template < typename GUM_SCALAR >
  INLINE void MultiDimImplementation< GUM_SCALAR >::_commitMultipleChanges(
     const GUM_SCALAR&) {
    // empty!
  }

  // get the actual change method of *this
  template < typename GUM_SCALAR >
  INLINE bool
     MultiDimImplementation< GUM_SCALAR >::_isInMultipleChangeMethod() const {
    return (__internalChangeMethod == __InternalChangeMethod::MULTIPLE_CHANGE);
  }

  // get the actual state of *this
  template < typename GUM_SCALAR >
  INLINE bool MultiDimImplementation< GUM_SCALAR >::_isCommitNeeded() const {
    return (__internalChangeState == __InternalChangeState::NOT_COMMITTED_CHANGE);
  }

  // Returns a constant reference over the list of slaved instantiations.
  template < typename GUM_SCALAR >
  INLINE const List< Instantiation* >&
               MultiDimImplementation< GUM_SCALAR >::_slaves() const {
    return __slaveInstantiations;
  }

  // get the actual state of *this
  template < typename GUM_SCALAR >
  INLINE void MultiDimImplementation< GUM_SCALAR >::__setNotCommitedChange() {
    __internalChangeState = __InternalChangeState::NOT_COMMITTED_CHANGE;
  }

  // get the actual state of *this
  template < typename GUM_SCALAR >
  INLINE float MultiDimImplementation< GUM_SCALAR >::compressionRate() const {
    return ((float)1) - (float)realSize() / (float)domainSize();
  }

  // returns a basename to be used for default operators
  template < typename GUM_SCALAR >
  const std::string& MultiDimImplementation< GUM_SCALAR >::basename() const {
    static const std::string str = "MultiDimImplementation";
    return str;
  }

  template < typename GUM_SCALAR >
  INLINE void
     MultiDimImplementation< GUM_SCALAR >::_replace(const DiscreteVariable* x,
                                                    const DiscreteVariable* y) {
    __vars.setAtPos(__vars.pos(x), y);

    for (List< Instantiation* >::iterator_safe iter =
            __slaveInstantiations.beginSafe();
         iter != __slaveInstantiations.endSafe();
         ++iter) {
      (**iter).replace(*x, *y);
    }
  }

  template < typename GUM_SCALAR >
  INLINE void MultiDimImplementation< GUM_SCALAR >::_invert(Idx p1, Idx p2) {
    __vars.swap(p1, p2);
  }

  // for friendly displaying the content of the array
  template < typename GUM_SCALAR >
  INLINE std::ostream&
         operator<<(std::ostream&                               out,
                const MultiDimImplementation< GUM_SCALAR >& array) {
    return out << static_cast< const MultiDimContainer< GUM_SCALAR >& >(array);
  }


  // protected access to _content
  template < typename GUM_SCALAR >
  INLINE MultiDimImplementation< GUM_SCALAR >*
         MultiDimImplementation< GUM_SCALAR >::content() {
    return this;
  }

  // protected access to _content
  template < typename GUM_SCALAR >
  INLINE const MultiDimImplementation< GUM_SCALAR >*
               MultiDimImplementation< GUM_SCALAR >::content() const {
    return this;
  }
} /* namespace gum */
