#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP
#include "../material/material.hpp"
#include "../vector3.hpp"
#include "../ray.hpp"

class Primitive {
    public:
        Material *material;
        Primitive(Material *material): material(material) {};
        virtual double Intersect(Ray ray, Vector3 *intersect, Vector3 *normal)=0; // Must return -1 if no intersect
        virtual Vector3 Sample(double u1, double u2, double& probability)=0;
        virtual Vector3 
        virtual Vector3 DirectionalSample(double u1, double u2, Vector3 point, double& probability)=0;
};

#endif