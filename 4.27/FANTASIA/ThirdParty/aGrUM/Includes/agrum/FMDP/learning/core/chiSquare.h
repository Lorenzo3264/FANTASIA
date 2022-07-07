
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
 * @brief Headers of the ChiSquare class.
 *
 * @author Jean-Christophe MAGNAN and Pierre-Henri WUILLEMIN
 */


#ifndef GUM_CHI_SQUARE_H
#  define GUM_CHI_SQUARE_H

#  include <agrum/core/math/math.h>
#  include <agrum/core/hashTable.h>


namespace gum {

  /**
   * @class ChiSquare chiSquare.h
   * <agrum/FMDP/learning/core/testPolicy/chiSquare.h>
   * @brief
   * @ingroup fmdp_group
   *
   */

  class ChiSquare {
    public:
    static double probaChi2(double x, Size df);

    private:
    /// Required constant to compute the cdf
    /// @{

    /// maximum meaningful z value
    static constexpr double __Z_MAX = 6.0;

    /// accuracy of critchi approximation
    static constexpr double __CHI_EPSILON = 0.000001;

    /// maximum chi square value
    static constexpr double __CHI_MAX = 99999.0;

    /// log (sqrt (pi))
    static constexpr double __LOG_SQRT_PI = 0.5723649429247000870717135;

    /// 1 / sqrt (pi)
    static constexpr double __I_SQRT_PI = 0.5641895835477562869480795;

    /// max value to represent exp (x)
    static constexpr double __BIGX = 20.0;

    /// @}


    /// Required constant to compute the cdf
    /// @{

    static double __exp(double x) { return (((x) < -__BIGX) ? 0.0 : exp(x)); }

    static double __probaZValue(double z);
    /// @}
  };

} /* namespace gum */

#endif   // GUM_CHI_SQUARE_H


// static HashTable<std::pair<double, unsigned long>, double> __chi2Cache;
// static HashTable<double, double> __ZCache;
// static Idx nbZ;
// static Idx nbChi;
// static Idx nbZt;
// static Idx nbChit;