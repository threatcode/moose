#ifndef VECTORCOEFFFIELD_H
#define VECTORCOEFFFIELD_H

#include "VectorKernel.h"

class VectorCoeffField;

template <>
InputParameters validParams<VectorCoeffField>();

class VectorCoeffField : public VectorKernel
{
public:
  VectorCoeffField(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  Real _coefficient;

  Function & _func;
};

#endif // VECTORCOEFFFIELD_H
