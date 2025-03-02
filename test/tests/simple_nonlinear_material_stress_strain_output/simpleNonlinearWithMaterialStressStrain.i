  [GlobalParams]
    displacements = 'disp_x disp_y'
  []
  
  [Mesh]
    [square]
      type = GeneratedMeshGenerator
      nx = 1
      ny = 1
      xmin = 0
      xmax = 1
      ymin = 0
      ymax = 1
      dim = 2
    []
    [node1]
      type = ExtraNodesetGenerator
      new_boundary = 101
      coord = '0 0'
      input = square
    []
    [node2]
      type = ExtraNodesetGenerator
      new_boundary = 102
      coord = '1 0'
      input = node1
    []
    [node3]
      type = ExtraNodesetGenerator
      new_boundary = 103
      coord = '1 1'
      input = node2
    []
    [node4]
      type = ExtraNodesetGenerator
      new_boundary = 104
      coord = '0 1'
      input = node3
    []
  []
  
  [Variables]
    [disp_x]
    []
    [disp_y]
    []
  []

  [AuxVariables]
    [stress_xx]
      order = CONSTANT
      family = MONOMIAL
    []
    [stress_yy]
      order = CONSTANT
      family = MONOMIAL
    []
    [stress_xy]
      order = CONSTANT
      family = MONOMIAL
    []
    [strain_xx]
      order = CONSTANT
      family = MONOMIAL
    []
    [strain_yy]
      order = CONSTANT
      family = MONOMIAL
    []
    [strain_xy]
      order = CONSTANT
      family = MONOMIAL
    []
  []

  [AuxKernels]
    [stress_xx]
      type = ADRankTwoAux
      variable = stress_xx
      rank_two_tensor = stress
      index_j = 0
      index_i = 0
      execute_on = timestep_end
    []
    [strain_xx]
      type = ADRankTwoAux
      variable = strain_xx
      rank_two_tensor = strain
      index_j = 0
      index_i = 0
      execute_on = timestep_end
    []
    [stress_yy]
      type = ADRankTwoAux
      variable = stress_yy
      rank_two_tensor = stress
      index_j = 1
      index_i = 1
      execute_on = timestep_end
    []
    [strain_yy]
      type = ADRankTwoAux
      variable = strain_yy
      rank_two_tensor = strain
      index_j = 1
      index_i = 1
      execute_on = timestep_end
    []
    [stress_xy]
      type = ADRankTwoAux
      variable = stress_xy
      rank_two_tensor = stress
      index_j = 0
      index_i = 1
      execute_on = timestep_end
    []
    [strain_xy]
      type = ADRankTwoAux
      variable = strain_xy
      rank_two_tensor = strain
      index_j = 0
      index_i = 1
      execute_on = timestep_end
    []
  []
  

  [Kernels]
    [momentum_balance_x]
      type = SimpleNonlinearKernel
      variable = disp_x
      component = 0
    []
    [momentum_balance_y]
      type = SimpleNonlinearKernel
      variable = disp_y
      component = 1
    []
  []

  [Materials]
    [strain]
      type = SimpleNonlinearStrain
    []
    [stress]
      type = SimpleNonlinearStress
      aValue = 40
      bValue = -50
      cValue = -30  
    []
  []
  
  [BCs]
    [fix_x]
      type = DirichletBC
      variable = disp_x
      value = 0
      boundary = '101 104'
    []
    [bottom_fix_y]
      type = DirichletBC
      variable = disp_y
      value = 0
      boundary = '101'
    []
    [pull_x]
      type = FunctionDirichletBC
      variable = disp_x
      function = '0.05*t'
      boundary = '102 103'
    []
  []
  
  [Executioner]
    type = Transient
    solve_type = NEWTON
    petsc_options_iname = '-pc_type'
    petsc_options_value = 'lu'
    automatic_scaling = true
    end_time = 1
    dt = 0.1
  []

  [Postprocessors]
    [avg_stress_xx]
      type = ElementAverageValue
      variable = stress_xx
    []
    [avg_strain_xx]
      type = ElementAverageValue
      variable = strain_xx
    []
    [avg_stress_yy]
      type = ElementAverageValue
      variable = stress_yy
    []
    [avg_strain_yy]
      type = ElementAverageValue
      variable = strain_yy
    []
    [avg_stress_xy]
      type = ElementAverageValue
      variable = stress_xy
    []
    [avg_strain_xy]
      type = ElementAverageValue
      variable = strain_xy
    []
  []
  
  [Outputs]
    exodus = true
    csv = true
  []