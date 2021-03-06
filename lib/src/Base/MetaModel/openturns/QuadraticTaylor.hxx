//                                               -*- C++ -*-
/**
 *  @brief Second order polynomial response surface by Taylor expansion
 *
 *  Copyright 2005-2019 Airbus-EDF-IMACS-Phimeca
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
#ifndef OPENTURNS_QUADRATICTAYLOR_HXX
#define OPENTURNS_QUADRATICTAYLOR_HXX

#include "openturns/OTprivate.hxx"
#include "openturns/PersistentObject.hxx"
#include "openturns/Point.hxx"
#include "openturns/Matrix.hxx"
#include "openturns/SymmetricTensor.hxx"
#include "openturns/Function.hxx"

BEGIN_NAMESPACE_OPENTURNS



/**
 * @class QuadraticTaylor
 *
 * The class describes the concept of quadratic taylor response surface
 */
class OT_API QuadraticTaylor
  : public PersistentObject
{
  CLASSNAME
public:


  /** Default constructor */
  QuadraticTaylor();

  /** Constructor with parameters */
  QuadraticTaylor(const Point & center,
                  const Function & inputFunction);


  /** Virtual constructor */
  virtual QuadraticTaylor * clone() const;

  /** String converter */
  String __repr__() const;

  /** Response surface computation */
  void run();

  /** Center accessor */
  Point getCenter() const;

  /** Constant accessor */
  Point getConstant() const;

  /** Linear accessor */
  Matrix getLinear() const;

  /** Quadratic accessor */
  SymmetricTensor getQuadratic() const;

  /** Input function accessor */
  Function getInputFunction() const;

  /** Metamodel accessor */
  Function getMetaModel() const;

  /** @deprecated Response surface accessor */
  Function getResponseSurface() const;

  /** Method save() stores the object through the StorageManager */
  virtual void save(Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
  virtual void load(Advocate & adv);
protected:

private:

  Point center_;
  Function inputFunction_;
  Function responseSurface_;
  Point constant_;
  Matrix linear_;
  SymmetricTensor quadratic_;

}; /* class QuadraticTaylor */

END_NAMESPACE_OPENTURNS

#endif /* OPENTURNS_QUADRATICTAYLOR_HXX */
