
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
 * @brief gum::ApproximationSchemeListener header file.
 *
 * @author Christophe GONZALES and Pierre-Henri WUILLEMIN
 */

#ifndef APPROXIMATIONSCHEMELISTENER_H
#define APPROXIMATIONSCHEMELISTENER_H

#include <agrum/agrum.h>
#include <agrum/core/signal/listener.h>

#include <agrum/core/approximations/IApproximationSchemeConfiguration.h>

namespace gum {

  /**
   * @class ApproximationSchemeListener
   * @brief The ApproximationSchemeListener class.
   *
   * @warning Doxygen does not like spanning command on multiple line, so we
   * could not configure it with the correct include directive. Use the
   * following code snippet to include this file.
   * @code
   * #include <agrum/core/approximations/approximationSchemeListener.h>
   * @endcode
   */
  class ApproximationSchemeListener : public Listener {
    public:
    /**
     * @brief Class constructor.
     * @param sch The scheme configuration.
     */
    ApproximationSchemeListener(IApproximationSchemeConfiguration& sch);

    /**
     * @brief Class destructor.
     */
    virtual ~ApproximationSchemeListener();

    /**
     * @brief When progress was made.
     * @param src The signal source.
     * @param pourcent The advancement in percent.
     * @param error The number of errors.
     * @param time The time.
     */
    virtual void whenProgress(const void*  src,
                              const Size   step,
                              const double error,
                              const double time) = 0;

    /**
     * @brief When it stops.
     * @param src The signal source.
     * @param message A message.
     */
    virtual void whenStop(const void* src, const std::string message) = 0;

    protected:
    /**
     * Copy constructor.
     */
    ApproximationSchemeListener(const ApproximationSchemeListener& other);

    /**
     * Copy operator.
     */
    ApproximationSchemeListener&
       operator=(const ApproximationSchemeListener& other);

    private:
    /// The scheme configuration.
    IApproximationSchemeConfiguration& __sch;
  };
}   // namespace gum

#endif   // APPROXIMATIONSCHEMELISTENER_H
