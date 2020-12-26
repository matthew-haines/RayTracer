cmake_minimum_required(VERSION 3.10)

project(RayTracer CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
add_compile_options(-Wall)
if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_options(-g)
else()
    add_compile_options(-O)
endif()

add_library(
    lodepng
    lib/lodepng/lodepng.h
    lib/lodepng/lodepng.cpp
    )

set(
    SOURCES
    src/lighting/pathtracer.cpp
    src/lighting/lighting_model.cpp
    src/lighting/pathtracermis.cpp
    src/primitive/primitive.cpp
    src/primitive/plane.cpp
    src/primitive/polygon.cpp
    src/primitive/triangle.cpp
    src/primitive/sphere.cpp
    src/primitive/quad.cpp
    src/reader/texture_reader.cpp
    src/reader/camera_reader.cpp
    src/reader/obj_reader.cpp
    src/reader/scene_reader.cpp
    src/intersector/bvh_intersector.cpp
    src/intersector/intersector.cpp
    src/intersector/bound.cpp
    src/intersector/naive_intersector.cpp
    src/scene.cpp
    src/matrix3.cpp
    src/camera/orthographic_camera.cpp
    src/camera/camera.cpp
    src/camera/perspective_camera.cpp
    src/helpers.cpp
    src/vector2.cpp
    src/material/microfacet_bsdf.cpp
    src/material/fresnel_specular_bsdf.cpp
    src/material/anistropic_phong_brdf.cpp
    src/material/bxdf.cpp
    src/material/phong_brdf.cpp
    src/material/lambertian_brdf.cpp
    src/material/fresnel.cpp
    src/material/specular_refract_btdf.cpp
    src/material/texture.cpp
    src/material/microfacet.cpp
    src/material/specular_reflect_brdf.cpp
    src/vector3.cpp
    )

set(
    HEADERS
    src/lighting/pathtracermis.hpp
    src/lighting/pathtracer.hpp
    src/lighting/lighting_model.hpp
    src/vector2.hpp
    src/primitive/quad.hpp
    src/primitive/triangle.hpp
    src/primitive/polygon.hpp
    src/primitive/sphere.hpp
    src/primitive/plane.hpp
    src/primitive/primitive.hpp
    src/primitive/complex_primitive.hpp
    src/constants.hpp
    src/matrix3.hpp
    src/reader/camera_reader.hpp
    src/reader/obj_reader.hpp
    src/reader/texture_reader.hpp
    src/reader/scene_reader.hpp
    src/helpers.hpp
    src/intersector/bound.hpp
    src/intersector/intersector.hpp
    src/intersector/bvh_intersector.hpp
    src/intersector/thread_safe_queue.hpp
    src/intersector/naive_intersector.hpp
    src/vector3.hpp
    src/camera/orthographic_camera.hpp
    src/camera/camera.hpp
    src/camera/perspective_camera.hpp
    src/intersection.hpp
    src/material/specular_refract_btdf.hpp
    src/material/anistropic_phong_brdf.hpp
    src/material/phong_brdf.hpp
    src/material/lambertian_brdf.hpp
    src/material/material.hpp
    src/material/microfacet.hpp
    src/material/fresnel_specular_bsdf.hpp
    src/material/specular_reflect_brdf.hpp
    src/material/bxdf.hpp
    src/material/fresnel.hpp
    src/material/texture.hpp
    src/material/microfacet_bsdf.hpp
    src/ray.hpp
    src/scene.hpp
    )

add_executable(tracer src/tracer.cpp ${SOURCES} ${HEADERS})

target_include_directories(tracer PUBLIC src src/camera src/intersector src/lighting src/material src/primitive src/reader lib/json)
target_link_libraries(tracer PUBLIC lodepng pthread m)
