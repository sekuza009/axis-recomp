# dmath-check (CI only)

Checks that the GDScript rewrite's `AxisDMath` (fdlibm's sine, cosine and arctangent in plain IEEE arithmetic,
`axis/sim/dmath.gd`) gives bit-identical results on macOS (Apple Silicon and Intel), Linux (x86_64 and arm64) and
Windows. This branch holds only that file, its test and the workflow.
