[Mesh]
  [generate]
    type = GeneratedMeshGenerator
    dim = 2
    nx = 10
    ny = 10
  []
  add_subdomain_ids = 999
[]

[Variables]
  [u]
  []
[]

[Kernels]
  [diff]
    type = Diffusion
    variable = u
  []
  [diff2]
    type = MatDiffusion
    diffusivity = 2
    variable = u
    block = 999
  []
[]

[BCs]
  [left]
    type = DirichletBC
    variable = u
    boundary = left
    value = 0
  []
  [right]
    type = DirichletBC
    variable = u
    boundary = right
    value = 1
  []
[]

[Executioner]
  type = Steady
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  exodus = true
[]
