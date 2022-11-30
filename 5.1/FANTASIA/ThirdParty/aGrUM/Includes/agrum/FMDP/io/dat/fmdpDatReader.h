
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
 * @brief Definition of templatized reader of dat files for Factored Markov
 Decision Process.
 *
 * how to use it :
 * @code
  // OPTIONAL LISTENER CLASS
  class aSimpleListener : public gum::Listener {
  public:
    void whenLoading(const void *buffer,int percent) {
      // percent goes from 0 to 100 (whenLoading is called at most once for each
 integer between 0 and 100
      // percent=200 recieved when End Of File.
    }
  };
  // END OF OPTIONAL LISTENER

  gum::FMDP<double> fmdp;

  try {
    gum::FMDPDatReader<double> reader( &fmdp, std::string( args[1] ) );

    // OPTIONAL SECTION
    aSimpleListener l;
    GUM_CONNECT( reader.scanner(), onLoad, l, aSimpleListener::whenLoading );
    // END OF OPTIONNAL SECTION

    if ( reader.proceed() == 0 ) {
      std::cerr << "Well done !" << std::endl;
    } else {
      reader.showElegantErrorsAndWarnings();
      reader.showErrorCounts();
    }
  } catch ( gum::IOError& e ) { GUM_SHOWERROR( e ); }

  return 0;

 * @endcode
 *
 * @author Pierre-Henri WUILLEMIN
 */

// ======================================================================================================
#ifndef FMDP_DAT_READER_H
#define FMDP_DAT_READER_H
// ======================================================================================================
#include <fstream>
#include <iostream>
#include <string>
// ======================================================================================================
#include <agrum/FMDP/fmdp.h>
#include <agrum/FMDP/fmdpFactory.h>
#include <agrum/FMDP/io/fmdpReader.h>
// ======================================================================================================
#include <agrum/multidim/implementations/multiDimFunctionGraph.h>
// ======================================================================================================

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// including coco-generated PARSER and SCANNER
#  include <agrum/FMDP/io/dat/cocoR/Parser.h>
#endif   // DOXYGEN_SHOULD_SKIP_THIS

namespace gum {
  /**
   * @class FMDPDatReader
   * @brief Definition of templatized reader of FMDPDat files for Factored
   * Markov Decision Processes.
   * @author Jean-Christophe MAGNAN and Pierre-Henri WUILLEMIN
   */
  template < typename GUM_SCALAR >
  class FMDPDatReader : public FMDPReader< GUM_SCALAR > {
    public:
    FMDPDatReader(FMDP< GUM_SCALAR >* fmdp, const std::string& filename);
    ~FMDPDatReader();

    /// Direct access to FMDPDat scanner (mandatory for listener connection)
    /// @throws IOError if file not exists
    MDPDAT::Scanner& scanner();

    /// name of readen file
    const std::string& streamName() const;

    /// accessor to trace function (just write the number of parser line)
    bool trace() const;
    void trace(bool b);

    /// parse.
    /// @return the number of detected errors
    /// @throws IOError if file not exists
    Size proceed();

    /// @{
    /// publishing Errors API

    /// # of errors
    Size errors();
    /// # of errors
    Size warnings();

    /// line of ith error or warning
    Idx errLine(Idx i);
    /// col of ith error or warning
    Idx errCol(Idx i);
    /// type of ith error or warning
    bool errIsError(Idx i);
    /// message of ith error or warning
    std::string errMsg(Idx i);

    /// send on std::cerr the list of errors
    void showElegantErrors(std::ostream& o = std::cerr);

    /// send on std::cerr the list of errors or warnings
    void showElegantErrorsAndWarnings(std::ostream& o = std::cerr);

    /// send on std::cerr the number of errors and the number of warnings
    void showErrorCounts(std::ostream& o = std::cerr);
    /// @}

    protected:
    FMDP< GUM_SCALAR >*        __fmdp;
    FMDPFactory< GUM_SCALAR >* __factory;
    MDPDAT::Scanner*           __scanner;
    MDPDAT::Parser*            __parser;

    std::string __streamName;
    bool        __traceScanning;
    bool        __parseDone;

    // a boolean to throw the ioerror not in the constructor but in the
    // proceed()
    bool __ioerror;
  };


#ifndef GUM_NO_EXTERN_TEMPLATE_CLASS
  extern template class FMDPDatReader< double >;
#endif

}   // namespace gum

#include <agrum/FMDP/io/dat/fmdpDatReader_tpl.h>

#endif   // FMDP_DAT_READER_H
