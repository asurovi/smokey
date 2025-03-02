#include "SimpleNonlinearKernel.h"

registerMooseObject("smokeyApp", SimpleNonlinearKernel);

InputParameters SimpleNonlinearKernel::validParams(){
    auto params = ADKernel::validParams();
    params.addClassDescription("Solve the linear momentum balance");
    params.addParam<MaterialPropertyName>("stress", "stress", "The stress of weak form");
    params.addRequiredParam<unsigned int>("component","The residual component");
    return params;
}

SimpleNonlinearKernel::SimpleNonlinearKernel(const InputParameters & params)
    : ADKernel(params),
    _s(getADMaterialProperty<RankTwoTensor> ("stress")),
    _component(getParam<unsigned int>("component"))
{
    
} 

ADReal SimpleNonlinearKernel::computeQpResidual()
{
    
    auto r = _grad_test[_i][_qp] * _s[_qp].row(_component);
    return r;
}
