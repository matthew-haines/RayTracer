# RayTracer
(Actually a path tracer)

### Features
- Modular
- BxDFs:
  - Phong
  - Mirror
  - Dielectric Transmissive
  - Microfacet models (GGX, Beckmann, Phong)
  - Anistrophic Phong (Not implemented yet)
  - Disney (Not implemented yet)
- Integrators (All multithreaded)
  - Naive path tracer
  - Multiple importance sampling based path tracer
  - Bidirectional path tracer (Not implemented yet)
- Multithreaded Bounding Volume Hierarchy Acceleration Structure (Surface Area Heuristic)
- OBJ File Parser
- Simple to use JSON scene specification
