
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
 * @brief Definition of templatized reader of BIF files for Bayesian Networks.
 *
 * @author Pierre-Henri WUILLEMIN
 */


#include <agrum/BN/io/BIF/BIFReader.h>
#include <agrum/BN/io/BNReader.h>
#ifndef DOXYGEN_SHOULD_SKIP_THIS

namespace gum {

  template < typename GUM_SCALAR >
  BIFReader< GUM_SCALAR >::BIFReader(BayesNet< GUM_SCALAR >* bn,
                                     const std::string&      filename) :
      BNReader< GUM_SCALAR >(bn, filename) {
    GUM_CONSTRUCTOR(BIFReader);
    __bn = bn;
    __streamName = filename;
    __parseDone = false;

    __factory = new BayesNetFactory< GUM_SCALAR >(__bn);

    __ioerror = false;

    try {
      __scanner = new BIF::Scanner(__streamName.c_str());
      __parser = new BIF::Parser(__scanner);
      __parser->setFactory((IBayesNetFactory*)__factory);
    } catch (IOError&) { __ioerror = true; }
  }

  template < typename GUM_SCALAR >
  BIFReader< GUM_SCALAR >::~BIFReader() {
    GUM_DESTRUCTOR(BIFReader);

    if (!__ioerror) {
      // this could lead to memory leak !!
      if (__parser) delete (__parser);

      if (__scanner) delete (__scanner);
    }

    if (__factory) delete (__factory);
  }

  template < typename GUM_SCALAR >
  INLINE BIF::Scanner& BIFReader< GUM_SCALAR >::scanner() {
    if (__ioerror) { GUM_ERROR(gum::IOError, "No such file " + streamName()); }

    return *__scanner;
  }

  template < typename GUM_SCALAR >
  INLINE const std::string& BIFReader< GUM_SCALAR >::streamName() const {
    return __streamName;
  }

  template < typename GUM_SCALAR >
  INLINE bool BIFReader< GUM_SCALAR >::trace() const {
    return __traceScanning;
  }

  template < typename GUM_SCALAR >
  INLINE void BIFReader< GUM_SCALAR >::trace(bool b) {
    __traceScanning = b;
    scanner().setTrace(b);
  }

  template < typename GUM_SCALAR >
  Size BIFReader< GUM_SCALAR >::proceed() {
    if (__ioerror) { GUM_ERROR(gum::IOError, "No such file " + streamName()); }

    if (!__parseDone) {
      try {
        __parser->Parse();
        __parseDone = true;
      } catch (gum::Exception& e) {
        GUM_SHOWERROR(e);
        return 1 + __parser->errors().error_count;
      }
    }

    return (__parser->errors().error_count);
  }

  /// @{
  /// publishing Errors API
  template < typename GUM_SCALAR >
  INLINE Idx BIFReader< GUM_SCALAR >::errLine(Idx i) {
    if (__parseDone)
      return __parser->errors().error(i).line;
    else {
      GUM_ERROR(OperationNotAllowed, "BIF file not parsed yet");
    }
  }

  template < typename GUM_SCALAR >
  INLINE Idx BIFReader< GUM_SCALAR >::errCol(Idx i) {
    if (__parseDone)
      return __parser->errors().error(i).column;
    else {
      GUM_ERROR(OperationNotAllowed, "BIF file not parsed yet");
    }
  }

  template < typename GUM_SCALAR >
  INLINE bool BIFReader< GUM_SCALAR >::errIsError(Idx i) {
    if (__parseDone)
      return __parser->errors().error(i).is_error;
    else {
      GUM_ERROR(OperationNotAllowed, "BIF file not parsed yet");
    }
  }

  template < typename GUM_SCALAR >
  INLINE std::string BIFReader< GUM_SCALAR >::errMsg(Idx i) {
    if (__parseDone)
      return __parser->errors().error(i).msg;
    else {
      GUM_ERROR(OperationNotAllowed, "BIF file not parsed yet");
    }
  }

  template < typename GUM_SCALAR >
  INLINE void BIFReader< GUM_SCALAR >::showElegantErrors(std::ostream& o) {
    if (__parseDone)
      __parser->errors().elegantErrors(o);
    else {
      GUM_ERROR(OperationNotAllowed, "BIF file not parsed yet");
    }
  }

  template < typename GUM_SCALAR >
  INLINE void
     BIFReader< GUM_SCALAR >::showElegantErrorsAndWarnings(std::ostream& o) {
    if (__parseDone)
      __parser->errors().elegantErrorsAndWarnings(o);
    else {
      GUM_ERROR(OperationNotAllowed, "BIF file not parsed yet");
    }
  }

  template < typename GUM_SCALAR >
  INLINE void BIFReader< GUM_SCALAR >::showErrorCounts(std::ostream& o) {
    if (__parseDone)
      __parser->errors().syntheticResults(o);
    else {
      GUM_ERROR(OperationNotAllowed, "BIF file not parsed yet");
    }
  }

  template < typename GUM_SCALAR >
  INLINE Size BIFReader< GUM_SCALAR >::errors() {
    return (!__parseDone) ? (Size)0 : __parser->errors().error_count;
  }

  template < typename GUM_SCALAR >
  INLINE Size BIFReader< GUM_SCALAR >::warnings() {
    return (!__parseDone) ? (Size)0 : __parser->errors().warning_count;
  }

  /// @}
}   // namespace gum

#endif   // DOXYGEN_SHOULD_SKIP_THIS
