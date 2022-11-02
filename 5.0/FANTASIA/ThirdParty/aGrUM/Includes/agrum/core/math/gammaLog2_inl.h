
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
 * @brief The class for computing Log2 (Gamma(x)).
 *
 * @author Christophe GONZALES and Pierre-Henri WUILLEMIN
 */

namespace gum {

  ALWAYS_INLINE double GammaLog2::gammaLog2(double x) const {
    if (x <= 0)
      GUM_ERROR(OutOfBounds,
                "log2(gamma()) should be called with a positive argument");

    // if x is small, use precomputed values
    if (x < 50) {
      if (__requires_precision) {
        Idx index = int(x * 100);
        return __small_values[index]
               + (__small_values[index + 1] - __small_values[index])
                    * double(x * 100 - index);
      } else {
        Idx index = int(x * 100 + 0.5);
        return __small_values[index];
      }
    }

    // returns the approximation by the stirling formula
    return (__log_sqrt_2pi + (x - 0.5f) * log(x) - x + log(1.0 + 1.0 / (12 * x)))
           * __1log2;
  }

  ALWAYS_INLINE double GammaLog2::operator()(double x) const {
    return gammaLog2(x);
  }

  INLINE void GammaLog2::setPrecision(bool prec) { __requires_precision = prec; }

} /* namespace gum */