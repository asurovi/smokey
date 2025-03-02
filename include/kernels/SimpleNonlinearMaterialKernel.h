#pragma once

#include "ADKernel.h"
#include "RankTwoTensor.h"

class SimpleNonlinearMaterialKernel : public ADKernel{
    public:
        static InputParameters validParams();
        SimpleNonlinearMaterialKernel(const InputParameters &);

    protected:
        virtual ADReal computeQpResidual() override;
        std::vector<const ADVariableGradient *> _grad_u;
        const ADMaterialProperty<Real> & _aValue;
        const ADMaterialProperty<Real> & _bValue;
        const ADMaterialProperty<Real> & _cValue;
        const unsigned int _component;
        
};