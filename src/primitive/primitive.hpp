#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP
#include "../material/material.hpp"
#include "../vector3.hpp"
#include "../ray.hpp"
#include "../intersector/bound.hpp"

class Primitive {
    public:
        Material *material;
        Primitive(Material *material): material(material) {};
        virtual double Intersect(Ray ray, Vector3 *intersect, Vector3 *normal)=0; // Must return -1 if no intersect
        virtual Vector3 Sample(double u1, double u2)=0;
        virtual double SamplePDF(Vector3 point, Vector3 direction)=0;
        virtual Vector3 DirectionalSample(double u1, double u2, Vector3 point)=0;
        virtual double DirectionalSamplePDF(Vector3 point, Vector3 direction)=0;
        virtual Bound GetBound()=0;
};

#endif