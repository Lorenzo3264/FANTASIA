
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
 * @brief Head of abstract classe for export of influence diagram
 *
 * All classes used to export ID must inherit from IDWriter
 *
 * @author Jean-Christophe MAGNAN and Pierre-Henri WUILLEMIN
 */
#ifndef GUM_ID_WRITER_H
#define GUM_ID_WRITER_H

#include <agrum/ID/influenceDiagram.h>
#include <agrum/agrum.h>
#include <iostream>
#include <string>

namespace gum {

  /**
   * @class IDWriter
   * @brief Pure virtual class for exporting an ID.
   * @ingroup id_group
   *
   * All classes used to write an influence diagram in a stream or
   * a file must inherit from this class
   */
  template < typename GUM_SCALAR >

  class IDWriter {
    public:
    /**
     * Default constructor.
     */
    IDWriter();

    /**
     * Default destructor.
     */
    virtual ~IDWriter();

    /**
     * Writes an influence diagram in the given ouput stream.
     *
     * @param output The output stream.
     * @param infdiag The influence diagram writen in the stream.
     * @throws IOError Raised if an I/O error occurs.
     */
    virtual void write(std::ostream&                         output,
                       const InfluenceDiagram< GUM_SCALAR >& infdiag) = 0;

    /**
     * Writes an Influence Diagram in the file referenced by filePath.
     * If the file doesn't exists, it is created.
     * If the file exists, it's content will be erased.
     *
     * @param filePath The path to the file used to write the Influence Diagram.
     * @param infdiag The Influence Diagram writen in the file.
     * @throw IOError Raised if an I/O error occurs.
     */
    virtual void write(std::string                           filePath,
                       const InfluenceDiagram< GUM_SCALAR >& infdiag) = 0;
  };
} /* namespace gum */

#include "IDWriter_tpl.h"

#endif   // GUM_ID_WRITER_H
