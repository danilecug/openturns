//                                               -*- C++ -*-
/**
 *  @brief Field to point function allowing to perform the lifting of a
 *         point into a field using a Karhunen-Loeve basis
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
#include "openturns/KarhunenLoeveLifting.hxx"
#include "openturns/Exception.hxx"
#include "openturns/OSS.hxx"
#include "openturns/PersistentObjectFactory.hxx"

BEGIN_NAMESPACE_OPENTURNS

CLASSNAMEINIT(KarhunenLoeveLifting)

static const Factory<KarhunenLoeveLifting> Factory_KarhunenLoeveLifting;

/* Default constructor */
KarhunenLoeveLifting::KarhunenLoeveLifting()
  : PointToFieldFunctionImplementation()
  , result_()
{
  // Nothing to do
}

/* Parameter constructor */
KarhunenLoeveLifting::KarhunenLoeveLifting(const KarhunenLoeveResult & result)
  : PointToFieldFunctionImplementation(result.getEigenValues().getSize(), result.getModesAsProcessSample().getDimension())
  , result_(result)
{
  // Set the description
  const UnsignedInteger size = result_.getModesAsProcessSample().getSize();
  if (size == 0) setOutputDescription(Description::BuildDefault(getOutputDimension(), "x"));
  else setOutputDescription(result_.getModesAsProcessSample()[0].getDescription());
  setInputDescription(Description::BuildDefault(getInputDimension(), "xi"));
}

/* Virtual constructor */
KarhunenLoeveLifting * KarhunenLoeveLifting::clone() const
{
  return new KarhunenLoeveLifting(*this);
}

/* Comparison operator */
Bool KarhunenLoeveLifting::operator ==(const KarhunenLoeveLifting & other) const
{
  return true;
}

/* String converter */
String KarhunenLoeveLifting::__repr__() const
{
  OSS oss(true);
  oss << "class=" << KarhunenLoeveLifting::GetClassName()
      << " name=" << getName()
      << " input description=" << inputDescription_
      << " output description=" << outputDescription_
      << " number of calls=" << callsNumber_;
  return oss;
}

/* String converter */
String KarhunenLoeveLifting::__str__(const String & offset) const
{
  return OSS(false) << offset << __repr__();
}

/* Get the i-th marginal function */
KarhunenLoeveLifting::Implementation KarhunenLoeveLifting::getMarginal(const UnsignedInteger i) const
{
  if (i >= getOutputDimension()) throw InvalidArgumentException(HERE) << "Error: the index of a marginal function must be in the range [0, outputDimension-1]";
  return getMarginal(Indices(1, i));
}

/* Get the function corresponding to indices components */
KarhunenLoeveLifting::Implementation KarhunenLoeveLifting::getMarginal(const Indices & indices) const
{
  if (!indices.check(getOutputDimension())) throw InvalidArgumentException(HERE) << "Error: the indices of a marginal function must be in the range [0, outputDimension-1] and must be different";
  throw NotYetImplementedException(HERE) << "In KarhunenLoeveLifting::getMarginal(const Indices & indices) const";
}

/* Operator () */
Field KarhunenLoeveLifting::operator() (const Point & inP) const
{
  const Field outField(result_.liftAsField(inP));
  ++callsNumber_;
  return outField;
}

/* Accessor for the output mesh */
Mesh KarhunenLoeveLifting::getOutputMesh() const
{
  return result_.getModesAsProcessSample().getMesh();
}

/* Method save() stores the object through the StorageManager */
void KarhunenLoeveLifting::save(Advocate & adv) const
{
  PointToFieldFunctionImplementation::save(adv);
  adv.saveAttribute( "result_", result_ );
}

/* Method load() reloads the object from the StorageManager */
void KarhunenLoeveLifting::load(Advocate & adv)
{
  PointToFieldFunctionImplementation::load(adv);
  adv.loadAttribute( "result_", result_ );
}

END_NAMESPACE_OPENTURNS
