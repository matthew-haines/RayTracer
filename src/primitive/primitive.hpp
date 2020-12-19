#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include "../material/material.hpp"
#include "../intersector/bound.hpp"
#include "../vector2.hpp"

class Primitive {
    private:
        TextureMap* const textureMap;
    public:
        Material* const material;
        Primitive(Material* const material, TextureMap* const textureMap);
        virtual double intersect(const Ray ray, Vector3* const intersect, Vector3* const normal) const =0; // Must return -1 if no intersect
        virtual Vector3 sample(const double u1, const double u2) const =0;
        virtual double samplePdf(const Vector3 point, const Vector3 direction) const =0;
        virtual Vector3 directionalSample(const double u1, const double u2, const Vector3 point) const =0;
        virtual double directionalSamplePdf(const Vector3 point, const Vector3 direction) const =0;
        virtual Bound getBound() const =0;
        virtual Vector2 getUVAtPoint(const Vector3& point) const =0;
        Vector3 color(const Vector3& point) const;
};

#endif