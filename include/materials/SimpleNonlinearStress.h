#pragma once

#include "Material.h"
#include "RankTwoTensor.h"

class SimpleNonlinearStress : public Material{
    public:
        static InputParameters validParams();
        SimpleNonlinearStress(const InputParameters &);
    
    protected:
        virtual void computeQpProperties() override;
        const ADMaterialProperty<RankTwoTensor> & _e;
        const ADMaterialProperty<Real> & _aValue;
        const ADMaterialProperty<Real> & _bValue;
        const ADMaterialProperty<Real> & _cValue;
        ADMaterialProperty<RankTwoTensor> &_s;
};