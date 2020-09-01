#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP
#include "../material/material.hpp"
#include "../intersector/bound.hpp"

class Primitive {
    public:
        Material *material;
        Primitive(Material *material): material(material) {};
        virtual double intersect(Ray ray, Vector3 *intersect, Vector3 *normal)=0; // Must return -1 if no intersect
        virtual Vector3 sample(double u1, double u2)=0;
        virtual double samplePdf(Vector3 point, Vector3 direction)=0;
        virtual Vector3 directionalSample(double u1, double u2, Vector3 point)=0;
        virtual double directionalSamplePdf(Vector3 point, Vector3 direction)=0;
        virtual Bound getBound()=0;
};

#endif