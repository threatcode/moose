/****************************************************************/
/*                  DO NOT MODIFY THIS HEADER                   */
/*                           Marmot                             */
/*                                                              */
/*            (c) 2017 Battelle Energy Alliance, LLC            */
/*                     ALL RIGHTS RESERVED                      */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*             Under Contract No. DE-AC07-05ID14517             */
/*             With the U. S. Department of Energy              */
/*                                                              */
/*             See COPYRIGHT for full restrictions              */
/****************************************************************/

#ifndef GRANDPOTENTIALSINTERINGMATERIAL_H
#define GRANDPOTENTIALSINTERINGMATERIAL_H

#include "Material.h"
#include "DerivativeMaterialInterface.h"

class GrandPotentialSinteringMaterial;

template <>
InputParameters validParams<GrandPotentialSinteringMaterial>();

/**
 * This material calculates necessary parameters for the grand potential sintering model.
 * Especially those related to switching functions and thermodynamics.
 */
class GrandPotentialSinteringMaterial : public DerivativeMaterialInterface<Material>
{
public:
  GrandPotentialSinteringMaterial(const InputParameters & parameters);

protected:
  virtual void computeQpProperties();

  /// number of solid phase order paramters
  const unsigned int _neta;

  /// solid phase order parameters
  std::vector<const VariableValue *> _eta;
  std::vector<VariableName> _eta_name;

  /// chemical potential
  const VariableValue & _w;
  const NonlinearVariableName _w_name;

  /// void phase order parameter
  const VariableValue & _phi;
  const NonlinearVariableName _phi_name;

  /// equilibrium vacancy concentration
  const MaterialPropertyName _cs_eq_name;
  const MaterialProperty<Real> & _cs_eq;
  std::vector<const MaterialProperty<Real> *> _dcs_eq;
  std::vector<std::vector<const MaterialProperty<Real> *>> _d2cs_eq;

  /// temperature
  const VariableValue & _T;

  /// void energy coefficient
  const MaterialProperty<Real> & _kv;
  /// solid energy coefficient
  const MaterialProperty<Real> & _ks;

  /// void phase switching function
  MaterialProperty<Real> & _hv;
  MaterialProperty<Real> & _dhv;
  MaterialProperty<Real> & _d2hv;

  /// solid phase switching function
  MaterialProperty<Real> & _hs;
  MaterialProperty<Real> & _dhs;
  MaterialProperty<Real> & _d2hs;

  /// susceptibility
  MaterialProperty<Real> & _chi;
  MaterialProperty<Real> & _dchidphi;
  MaterialProperty<Real> & _dchidw;
  MaterialProperty<Real> & _d2chidphi2;
  MaterialProperty<Real> & _d2chidw2;
  MaterialProperty<Real> & _d2chidphidw;

  /// void phase vacancy density
  MaterialProperty<Real> & _rhov;
  MaterialProperty<Real> & _drhovdw;

  /// solid phase vacancy density
  MaterialProperty<Real> & _rhos;
  MaterialProperty<Real> & _drhosdw;
  MaterialProperty<Real> & _d2rhosdw2;
  std::vector<MaterialProperty<Real> *> _drhos;
  std::vector<MaterialProperty<Real> *> _d2rhosdwdeta;
  std::vector<std::vector<MaterialProperty<Real> *>> _d2rhos;

  /// void phase potential density
  MaterialProperty<Real> & _omegav;
  MaterialProperty<Real> & _domegavdw;
  MaterialProperty<Real> & _d2omegavdw2;

  /// solid phase potential density
  MaterialProperty<Real> & _omegas;
  MaterialProperty<Real> & _domegasdw;
  MaterialProperty<Real> & _d2omegasdw2;
  std::vector<MaterialProperty<Real> *> _domegasdeta;
  std::vector<MaterialProperty<Real> *> _d2omegasdwdeta;
  std::vector<std::vector<MaterialProperty<Real> *>> _d2omegasdetadeta;

  /// energy barrier coefficient
  MaterialProperty<Real> & _mu;
  MaterialProperty<Real> & _dmu;
  MaterialProperty<Real> & _d2mu;

  /// gradient energy coefficient
  MaterialProperty<Real> & _kappa;
  MaterialProperty<Real> & _dkappa;
  MaterialProperty<Real> & _d2kappa;

  /// interface profile coefficient
  MaterialProperty<Real> & _gamma;

  /// surface energy
  const Real _sigma_s;

  /// grain boundary energy
  const Real _sigma_gb;

  /// interface width
  const Real _int_width;

  /// Parameter to determine accuracy of surface/GB phase switching function
  const Real _switch;

  /// Atomic volume of species
  const Real _Va;

  /// Type of energy function to use for the solid phase
  const MooseEnum _solid_energy;

  /// mu value on surfaces
  const Real _mu_s;

  /// mu value on grain boundaries
  const Real _mu_gb;

  /// kappa value on surfaces
  const Real _kappa_s;

  /// kappa value on grain boundaries
  const Real _kappa_gb;

  /// Boltzmann constant
  const Real _kB;
};

#endif // GRANDPOTENTIALSINTERINGMATERIAL_H
