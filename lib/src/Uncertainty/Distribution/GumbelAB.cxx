//                                               -*- C++ -*-
/**
 *  @brief Gumbel distribution with a and b as parameters
 *
 *  Copyright 2005-2017 Airbus-EDF-IMACS-Phimeca
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
 *  You should have received a copy of the GNU Lesser General Public
 *  along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "openturns/GumbelFactory.hxx"
#include "openturns/SquareMatrix.hxx"
#include "openturns/GumbelAB.hxx"

BEGIN_NAMESPACE_OPENTURNS

CLASSNAMEINIT(GumbelAB)

/* Default constructor */
GumbelAB::GumbelAB()
  : DistributionParametersImplementation()
  , a_(0.0)
  , b_(1.0)
{
  // Nothing to do
}

GumbelAB::GumbelAB(const Scalar a, const Scalar b)
  : DistributionParametersImplementation()
  , a_(a)
  , b_(b)
{
  if (!(b > 0.0)) throw InvalidArgumentException(HERE) << "b must be > 0, here b=" << b;
}

/* Virtual constructor */
GumbelAB * GumbelAB::clone() const
{
  return new GumbelAB(*this);
}

/* Comparison operator */
Bool GumbelAB::operator ==(const GumbelAB & other) const
{
  return (this == &other);
}


/* Build a distribution based on a set of native parameters */
Distribution GumbelAB::getDistribution() const
{
  Point newParameters(2);
  newParameters[0] = a_;
  newParameters[1] = b_;

  Point nativeParameters(operator()(newParameters));
  return GumbelFactory().build(nativeParameters);
}


/* Compute jacobian / native parameters */
Matrix GumbelAB::gradient() const
{
  const Scalar dalphada = 0.0;
  const Scalar dalphadb = -1 / (b_ * b_);
  const Scalar dbetada = 1.0;
  const Scalar dbetadb = 0.0;

  SquareMatrix nativeParametersGradient(IdentityMatrix(2));
  nativeParametersGradient(0, 0) = dalphada;
  nativeParametersGradient(1, 0) = dalphadb;

  nativeParametersGradient(0, 1) = dbetada;
  nativeParametersGradient(1, 1) = dbetadb;

  return nativeParametersGradient;
}


/* Conversion operator */
Point GumbelAB::operator () (const Point & inP) const
{
  if (inP.getDimension() != 2) throw InvalidArgumentException(HERE) << "the given point must have dimension=2, here dimension=" << inP.getDimension();
  const Scalar a = inP[0];
  const Scalar b = inP[1];

  if (!(b > 0.0)) throw InvalidArgumentException(HERE) << "b must be > 0, here b=" << b;

  const Scalar alpha = 1 / b;
  const Scalar beta = a;

  Point nativeParameters(inP);
  nativeParameters[0] = alpha;
  nativeParameters[1] = beta;

  return nativeParameters;
}


Point GumbelAB::inverse(const Point & inP) const
{
  if (inP.getDimension() != 2) throw InvalidArgumentException(HERE) << "the given point must have dimension=2, here dimension=" << inP.getDimension();
  const Scalar alpha = inP[0];
  const Scalar beta = inP[1];

  if (!(alpha > 0.0)) throw InvalidArgumentException(HERE) << "alpha must be > 0, here alpha=" << alpha;

  const Scalar a = beta;
  const Scalar b = 1.0 / alpha;

  Point abParameters(inP);
  abParameters[0] = a;
  abParameters[1] = b;

  return abParameters;
}

/* Parameters value and description accessor */
void GumbelAB::setValues(const Point & inP)
{
  if (inP.getDimension() != 2) throw InvalidArgumentException(HERE) << "the given point must have dimension=2, here dimension=" << inP.getDimension();
  a_ = inP[0];
  b_ = inP[1];
}

Point GumbelAB::getValues() const
{
  Point point(2);
  point[0] = a_;
  point[1] = b_;
  return point;
}

Description GumbelAB::getDescription() const
{
  Description description(2);
  description[0] = "a";
  description[1] = "b";
  return description;
}

/* String converter */
String GumbelAB::__repr__() const
{
  OSS oss(true);
  oss << "class=" << GetClassName()
      << " name=" << getName()
      << " a=" << a_
      << " b=" << b_;
  return oss;
}


String GumbelAB::__str__(const String & offset) const
{
  OSS oss(false);
  oss << offset << getClassName() << "(a = " << a_ << ", b = " << b_ << ")";
  return oss;
}

END_NAMESPACE_OPENTURNS