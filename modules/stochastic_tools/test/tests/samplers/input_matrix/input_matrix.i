[StochasticTools]
[]

[Samplers]
  [sample]
    type = InputMatrix
    matrix = '1   2   3   4   5   6;
              10  20  30  40  50  60;
              0.1 0.2 0.3 0.4 0.5 0.6;
              2   4   6   8   10  12;
              1   4   9   16  25  36'
  []
[]

[VectorPostprocessors]
  [data]
    type = SamplerData
    sampler = sample
  []
[]

[Outputs]
  execute_on = timestep_end
  csv = true
[]
