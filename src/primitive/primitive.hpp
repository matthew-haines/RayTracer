#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include "material.hpp"
#include "texture.hpp"
#include "bound.hpp"
#include "vector2.hpp"

// Base class for any primitive implemented.
class Primitive {
    public:
        const Material material;
        Primitive(const Material material);
        // Intersection test. Takes ray and returns distance (-1 if no intersect). 
        // Updates intersect/normal with information when required.
        virtual double intersect(const Ray ray, Vector3* const intersect, Vector3* const normal) const =0; // Must return -1 if no intersect
        // Uniformly samples a point on the primitive given two random uniform variables in [0, 1).
        virtual Vector3 sample(const double u1, const double u2) const =0;
        // Returns the PDF of a given sampled point/direction.
        virtual double samplePdf(const Vector3 point, const Vector3 direction) const =0;
        // Samples a direction to a point on the primitive given two random 
        // uniform variables in [0, 1) and an origin.
        virtual Vector3 directionalSample(const double u1, const double u2, const Vector3 point) const =0;
        // Returns the PDF of a given sampled point/direction, accounting for solid angle.
        virtual double directionalSamplePdf(const Vector3 point, const Vector3 direction) const =0;
        // Returns the minimum bound for the given primitive.
        virtual Bound getBound() const =0;
        // Returns some projection of a 3D point on the primitive into 2D space.
        virtual Vector2 getUVAtPoint(const Vector3& point) const =0;
        // Returns color at a given point, using the material and its TextureMap.
        Vector3 color(const Vector3& point) const;
};

#endif