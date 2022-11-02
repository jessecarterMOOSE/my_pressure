[GlobalParams]
  displacements = 'disp_x disp_y'
[]

[Mesh]
  [gmg]
    type = GeneratedMeshGenerator
    dim = 2
    nx = 1
    ny = 1
  []
[]

[Functions]
  [linear_ramp]
    type = ParsedFunction
    value = 1000.0*t
  []
[]

[MyPressure]
  pressure_file = foo.txt
  verbose = true
[]

[Postprocessors]
  [./react_x]
    type = SidesetReaction
    direction = '0 1 0'
    stress_tensor = stress
    boundary = top
  [../]
[]

[Modules/TensorMechanics/Master]
  [plane_strain]
    strain = FINITE
    add_variables = true
  []
[]


  
[BCs]
  [leftx]
    type = DirichletBC
    boundary = left
    variable = disp_x
    value = 0.0
  []
  [bottomy]
    type = DirichletBC
    boundary = bottom
    variable = disp_y
    value = 0.0
  []
[]

[Materials]
  [elasticity_tensor]
    type = ComputeIsotropicElasticityTensor
    poissons_ratio = 0.3
    youngs_modulus = 1e6
  []
  [stress]
    type = ComputeFiniteStrainElasticStress
  []
[]

[Debug]
  show_actions = true
  show_parser = true
[]

[Executioner]
  type = Transient
  line_search = none

  nl_rel_tol = 1e-8
  nl_abs_tol = 1e-8

  # time control
  start_time = 0.0
  dt = 0.01
  dtmin = 0.01
  end_time = 0.1
[]

[Outputs]
  csv = true
[]
