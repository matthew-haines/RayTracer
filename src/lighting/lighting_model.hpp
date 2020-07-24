#ifndef LIGHTING_MODEL_HPP
#define LIGHTING_MODEL_HPP
#include "../vector3.hpp"
#include "../ray.hpp"
#include "../intersector/intersector.hpp"
#include <vector>

class LightingModel {
    protected:
        Intersector& intersector;
        int maxDepth;
        Vector3 ambient;
    public:
        LightingModel(Intersector& intersector, int maxDepth, Vector3 ambient): intersector(intersector), maxDepth(maxDepth), ambient(ambient) {};
        virtual std::vector<Vector3> Render(std::vector<Ray> &rays, int threads, int samples)=0;
};

#endif