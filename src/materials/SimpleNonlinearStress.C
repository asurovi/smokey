#include "SimpleNonlinearStress.h"

registerMooseObject("smokeyApp", SimpleNonlinearStress);

InputParameters SimpleNonlinearStress::validParams(){
    auto params = Material::validParams();
    params.addClassDescription("Calculate stress for a linear elastic material");
    params.addRequiredParam<MaterialPropertyName>("aValue", "aValue = 40");
    params.addRequiredParam<MaterialPropertyName>("bValue", "bValue = -50");
    params.addRequiredParam<MaterialPropertyName>("cValue", "cValue = -30");
    params.addParam<MaterialPropertyName>("strain", "strain","Name of the small strain");
    params.addParam<MaterialPropertyName>("stress", "stress", "Name of the stress");
    return params;
}

SimpleNonlinearStress::SimpleNonlinearStress(const InputParameters & params)
: Material(params),
_e(getADMaterialProperty<RankTwoTensor>("strain")),
_aValue(getADMaterialProperty<Real>("aValue")),
_bValue(getADMaterialProperty<Real>("bValue")),
_cValue(getADMaterialProperty<Real>("cValue")),
_s(declareADProperty<RankTwoTensor>("stress")){

}

void SimpleNonlinearStress::computeQpProperties(){
    using R2 = ADRankTwoTensor;
    //strain is an input from SimpleNonlinearStrain that strain is written as _e
    //if strain would be declared here then strain would need to be written as e
    _s[_qp] = 2*_aValue[_qp]*_e[_qp] + 3*_bValue[_qp]*_e[_qp].trace()*_e[_qp].trace()*R2::Identity() + 3*_cValue[_qp]*_e[_qp]*_e[_qp];
}