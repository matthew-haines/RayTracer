# RayTracer
(Actually a path tracer)

This is a path tracer written completely from scratch, only libraries used are [lodepng](https://github.com/lvandeve/lodepng) for image writing and [json](https://github.com/nlohmann/json) for parsing scene files. (And STL of course)

### Features
- Highly Modular with base classes defined for most features
- BxDFs:
  - Phong
  - Mirror
  - Lambertian
  - Dielectric Transmissive
  - Microfacet models (GGX, Beckmann, Phong)
  - Anistrophic Phong (Not implemented yet)
  - Disney (Not implemented yet)
- Primitives:
  - Plane
  - Quad
  - Triangle
  - Sphere
  - Polygon
  - Quadric (Not implemented yet)
- Integrators (All multithreaded):
  - Naive path tracer
  - Multiple importance sampling based path tracer
  - Bidirectional path tracer (Not implemented yet)
- Cameras:
  - Perspective Camera with Simulated Depth of Field
  - Orthographic Camera
- Intersectors:
  - Multithreaded Bounding Volume Hierarchy Acceleration Structure (Surface Area Heuristic)
  - Naive intersector
- OBJ File Parser
- Simple to use JSON scene specification

### Building
- Tested on macOS and Linux using latest clang/apple clang.
- Builds to bin/tracer
- Debugging support for VSCode using LLDB with [CodeLLDB extension](https://marketplace.visualstudio.com/items?itemName=vadimcn.vscode-lldb)

### Syntax
```
bin/tracer [OPTION]... [IMAGE]
Arguments:
  -i, --input       path to json scene file
  -t, --threads     number of threads used by tracer
  -w, --width       width of output image
  -h, --height      height of output image
  -s, --size        can be used instead of width/height to specify square size of output image
  -c, --count       number of samples taken per pixel
```
### Pretty Pictures
Gallery coming soon but check out images/
