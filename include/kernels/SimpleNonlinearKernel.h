#pragma once

#include "ADKernel.h"
#include "RankTwoTensor.h"

class SimpleNonlinearKernel : public ADKernel{
    public:
        static InputParameters validParams();
        SimpleNonlinearKernel(const InputParameters &);

    protected:
        virtual ADReal computeQpResidual() override;
        const ADMaterialProperty <RankTwoTensor> & _s;
        const unsigned int _component;
        
};