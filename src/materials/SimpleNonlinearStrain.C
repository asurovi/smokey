#include "SimpleNonlinearStrain.h"

registerMooseObject("smokeyApp", SimpleNonlinearStrain);

InputParameters SimpleNonlinearStrain::validParams(){
    auto params = Material::validParams();
    params.addClassDescription("Calculate small strain as function of displacement gradient");
    params.addRequiredCoupledVar("displacements", "Displacement variables");
    params.addParam<MaterialPropertyName>("strain", "strain", "Name of the strain");
    return params;
}

SimpleNonlinearStrain::SimpleNonlinearStrain(const InputParameters & params)
    : Material(params),
     _grad_u(adCoupledGradients("displacements")),
     _e(declareADProperty<RankTwoTensor>("strain"))
    {
        _grad_u.resize(3, &_ad_grad_zero);
    }

// to calculate strain at quadrature points
void SimpleNonlinearStrain::computeQpProperties(){
    using R2 = ADRankTwoTensor;
    auto G = R2::initializeFromRows((*_grad_u[0])[_qp],(*_grad_u[1])[_qp],(*_grad_u[2])[_qp]);
    //strains at integration points
    _e[_qp] = (G.transpose() + G) / 2;

}