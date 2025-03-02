# pragma once

#include "Material.h"
#include "RankTwoTensor.h"

class SimpleNonlinearStrain : public Material{
    public:
        static InputParameters validParams();
        SimpleNonlinearStrain(const InputParameters &);

    protected:
        virtual void computeQpProperties() override;
        // Calcutation for gradient of u that will be used to calculate small strain
        std::vector<const ADVariableGradient *> _grad_u;
        ADMaterialProperty<RankTwoTensor> & _e;

};