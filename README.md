smokey
=====
# Custom Kernel for Small Strain Nonlinear Material Model in MOOSE

This repository contains a custom kernel implementation for a small strain nonlinear material model in MOOSE (Multiphysics Object Oriented Simulation Environment). The project structure follows the standard MOOSE framework.
Fork "smokey" to create a new MOOSE-based application.

## Features

* Custom kernel for small strain nonlinear material modeling

* Compatible with the MOOSE framework

* Maintains the MOOSE project structure

## Prerequisites

* Ensure that you have the following installed:

* MOOSE (properly built and configured)

* C++ compiler supporting C++11 or newer

* PETSc, libMesh, and other dependencies required by MOOSE

# Installation

* Clone the repository:

  git clone https://github.com/asurovi/smokey.git
  
  cd smokey

# Usage

* Run the simulation using the MOOSE executable:
  
./smokey-opt -i ./test/tests/stress_strain_output/simpleNonlinearWithMaterialStressStrain.i 




