#include "SimpleNonlinearMaterialKernel.h"

registerMooseObject("smokeyApp", SimpleNonlinearMaterialKernel);

InputParameters SimpleNonlinearMaterialKernel::validParams(){
    auto params = ADKernel::validParams();
    params.addClassDescription("Solve a custom simple nonlinear material");
    params.addRequiredCoupledVar("displacements", "Displacement varibles");
    params.addRequiredParam<MaterialPropertyName>("aValue","aValue = 40");
    params.addRequiredParam<MaterialPropertyName>("bValue","bValue = -50");
    params.addRequiredParam<MaterialPropertyName>("cValue","cValue = -30");
    params.addRequiredParam<unsigned int>("component","The residual component");
    return params;
}

SimpleNonlinearMaterialKernel::SimpleNonlinearMaterialKernel(const InputParameters & params)
    : ADKernel(params),_grad_u(adCoupledGradients("displacements")),
                       _aValue(getADMaterialProperty<Real>("aValue")),
                       _bValue(getADMaterialProperty<Real>("bValue")),
                       _cValue(getADMaterialProperty<Real>("cValue")),
                       _component(getParam<unsigned int>("component"))
{
    _grad_u.resize(3, &_ad_grad_zero);
} 

ADReal SimpleNonlinearMaterialKernel::computeQpResidual()
{
    using R2 = ADRankTwoTensor;
    auto G = R2::initializeFromRows((*_grad_u[0])[_qp], (*_grad_u[1])[_qp], (*_grad_u[2])[_qp]);
    auto e = (G.transpose() + G) / 2;
    auto s = 2*_aValue[_qp]*e + 3*_bValue[_qp]*e.trace()*e.trace()*R2::Identity() + 3*_cValue[_qp]*e*e;
    auto r = _grad_test[_i][_qp] * s.row(_component);
    return r;
}
