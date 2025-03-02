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
    [u_1x]
      type = PointValue
      variable = disp_x
      point = '0.0 0.0 0.0'
    []
    [u_1y]
      type = PointValue
      variable = disp_y
      point = '0.0 0.0 0.0'
    []
    [u_2x]
      type = PointValue
      variable = disp_x
      point = '1.0 0.0 0.0'
    []
    [u_2y]
      type = PointValue
      variable = disp_y
      point = '1.0 0.0 0.0'
    []
    [u_3x]
      type = PointValue
      variable = disp_x
      point = '1.0 1.0 0.0'
    []
    [u_3y]
      type = PointValue
      variable = disp_y
      point = '1.0 1.0 0.0'
    []
    [u_4x]
      type = PointValue
      variable = disp_x
      point = '0.0 1.0 0.0'
    []
    [u_4y]
      type = PointValue
      variable = disp_y
      point = '0.0 1.0 0.0'
    []
  []
  
  [Outputs]
    exodus = true
    csv = true
  []