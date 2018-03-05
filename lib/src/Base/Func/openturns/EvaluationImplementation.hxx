//                                               -*- C++ -*-
/**
 * @brief Abstract top-level class for all numerical math function implementations
 *
 *  Copyright 2005-2018 Airbus-EDF-IMACS-Phimeca
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

#ifndef OPENTURNS_EVALUATIONIMPLEMENTATION_HXX
#define OPENTURNS_EVALUATIONIMPLEMENTATION_HXX

#include "openturns/PersistentObject.hxx"
#include "openturns/Point.hxx"
#include "openturns/PointWithDescription.hxx"
#include "openturns/Sample.hxx"
#include "openturns/Field.hxx"
#include "openturns/HistoryStrategy.hxx"
#include "openturns/Description.hxx"
#include "openturns/Indices.hxx"
#include "openturns/Matrix.hxx"
#include "openturns/Collection.hxx"
#include "openturns/Pointer.hxx"
#include "openturns/StorageManager.hxx"
#include "openturns/Cache.hxx"
#include "openturns/Graph.hxx"

BEGIN_NAMESPACE_OPENTURNS

/**
 * @class EvaluationImplementation
 *
 * This class offers an abstract interface for the implementation
 * of an real numerical mathematical function into the platform.
 */
class OT_API EvaluationImplementation
  : public PersistentObject
{
  CLASSNAME
public:

  typedef Pointer<EvaluationImplementation>      Implementation;
  typedef PersistentCollection<Scalar>               CacheKeyType;
  typedef PersistentCollection<Scalar>               CacheValueType;
  typedef Cache<CacheKeyType, CacheValueType>                 CacheType;
  typedef Pointer<CacheType>                                  CacheImplementation;

  /** Default constructor */
  EvaluationImplementation();

  /** Virtual constructor */
  virtual EvaluationImplementation * clone() const;

  /** Comparison operator */
  Bool operator ==(const EvaluationImplementation & other) const;

  /** String converter */
  virtual String __repr__() const;
  virtual String __str__(const String & offset = "") const;


  /** Description Accessor, i.e. the names of the input and output parameters */
  virtual void setDescription(const Description & description);
  Description getDescription() const;

  /** Input description Accessor, i.e. the names of the input parameters */
  Description getInputDescription() const;
  void setInputDescription(const Description & inputDescription);

  /** Output description Accessor, i.e. the names of the Output parameters */
  Description getOutputDescription() const;
  void setOutputDescription(const Description & outputDescription);

  /** Enable or disable the input/output history */
  virtual void enableHistory() const;
  void disableHistory() const;

  /** @brief Test the history mechanism activity
   * @see enableHistory()
   */
  Bool isHistoryEnabled() const;

  /** @brief Clear the history mechanism
   * @see enableHistory()
   */
  void clearHistory() const;

  /** @brief Retrieve the history of the input values
   * @see enableHistory()
   */
  HistoryStrategy getHistoryInput() const;

  /** @brief Retrieve the history of the output values
   * @see enableHistory()
   */
  HistoryStrategy getHistoryOutput() const;

  /** Input point / parameter history accessor */
  virtual Sample getInputPointHistory() const;
  virtual Sample getInputParameterHistory() const;

  /** Enable or disable the internal cache */
  void enableCache() const;
  void disableCache() const;

  /** @brief Test the internal cache activity
   * @see enableCache()
   */
  Bool isCacheEnabled() const;

  /** @brief Returns the number of successful hits in the cache
   */
  UnsignedInteger getCacheHits() const;

  /** @brief Add some content to the cache
   */
  void addCacheContent(const Sample & inSample, const Sample & outSample);

  /** @brief Returns the cache input
   */
  Sample getCacheInput() const;

  /** @brief Returns the cache output
   */
  Sample getCacheOutput() const;

  /** @brief Empty the cache
   */
  void clearCache() const;

  /* Here is the interface that all derived class must implement */

  /** Test for actual implementation */
  virtual Bool isActualImplementation() const;

  /** Operator () */
  virtual Point operator() (const Point & inP) const;
  virtual Point operator() (const Point & inP,
                            const Point & parameters);
  virtual Sample operator() (const Point & point,
                             const Sample & parameters);

  /** Operator () on a sample, not pure virtual because a generic implementation is given */
  virtual Sample operator() (const Sample & inSample) const;

  /** Operator () on a time series, not pure virtual because a generic implementation is given */
  virtual Field operator() (const Field & inField) const;

  /** Accessor for input point dimension */
  virtual UnsignedInteger getInputDimension() const;

  /** Accessor for output point dimension */
  virtual UnsignedInteger getOutputDimension() const;

  /** Accessor for parameters dimension */
  virtual UnsignedInteger getParameterDimension() const;

  /** Get the i-th marginal evaluation */
  virtual Implementation getMarginal(const UnsignedInteger i) const;

  /** Get the evaluation corresponding to indices components */
  virtual Implementation getMarginal(const Indices & indices) const;

  /** Gradient according to the marginal parameters */
  virtual Matrix parameterGradient(const Point & inP) const;

  /** Parameters value accessor */
  virtual Point getParameter() const;
  virtual void setParameter(const Point & parameters);

  /** Parameters description accessor */
  virtual Description getParameterDescription() const;
  virtual void setParameterDescription(const Description & description);

  /** Get the number of calls to operator() */
  UnsignedInteger getCallsNumber() const;

  /** Draw the given 1D marginal output as a function of the given 1D marginal input around the given central point */
  virtual Graph draw(const UnsignedInteger inputMarginal,
                     const UnsignedInteger outputMarginal,
                     const Point & centralPoint,
                     const Scalar xMin,
                     const Scalar xMax,
                     const UnsignedInteger pointNumber = ResourceMap::GetAsUnsignedInteger("NumericalMathEvaluation-DefaultPointNumber"),
                     const GraphImplementation::LogScale scale = GraphImplementation::NONE) const;

  /** Draw the given 1D marginal output as a function of the given 2D marginal input around the given central point */
  virtual Graph draw(const UnsignedInteger firstInputMarginal,
                     const UnsignedInteger secondInputMarginal,
                     const UnsignedInteger outputMarginal,
                     const Point & centralPoint,
                     const Point & xMin,
                     const Point & xMax,
                     const Indices & pointNumber = Indices(2, ResourceMap::GetAsUnsignedInteger("NumericalMathEvaluation-DefaultPointNumber")),
                     const GraphImplementation::LogScale scale = GraphImplementation::NONE) const;

  /** Draw the output of the function with respect to its input when the input and output dimensions are 1 */
  virtual Graph draw(const Scalar xMin,
                     const Scalar xMax,
                     const UnsignedInteger pointNumber = ResourceMap::GetAsUnsignedInteger("NumericalMathEvaluation-DefaultPointNumber"),
                     const GraphImplementation::LogScale scale = GraphImplementation::NONE) const;

  /** Draw the output of the function with respect to its input when the input dimension is 2 and the output dimension is 1 */
  virtual Graph draw(const Point & xMin,
                     const Point & xMax,
                     const Indices & pointNumber = Indices(2, ResourceMap::GetAsUnsignedInteger("NumericalMathEvaluation-DefaultPointNumber")),
                     const GraphImplementation::LogScale scale = GraphImplementation::NONE) const;

  /** Method save() stores the object through the StorageManager */
  void save(Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
  void load(Advocate & adv);


protected:

  /** Number of calls since the construction */
  mutable UnsignedInteger callsNumber_;

  /** A cache to store already computed points */
  mutable CacheImplementation p_cache_;

  /** An history mechanism that allows to remember all the input/output associations including duplicate calls */
  mutable HistoryStrategy inputStrategy_;

  mutable HistoryStrategy outputStrategy_;

  /** Flag to activate or deactivate the history mechanism */
  mutable Bool isHistoryEnabled_;

  /** The value of the parameters */
  Point parameter_;

  /** The description of the parameters */
  Description parameterDescription_;

private:

  /** The description of the input components */
  Description inputDescription_;

  /** The description of the input components */
  Description outputDescription_;

}; /* class EvaluationImplementation */


END_NAMESPACE_OPENTURNS

#endif /* OPENTURNS_EVALUATIONIMPLEMENTATION_HXX */
