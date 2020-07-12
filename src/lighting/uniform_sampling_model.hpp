#ifndef UNIFORM_SAMPLING_MODEL_HPP
#define UNIFORM_SAMPLING_MODEL_HPP
#include "lighting_model.hpp"

class UniformSamplingModel: public LightingModel {
    public:
        UniformSamplingModel(Vector3 ambient, Intersector *intersector, int maxDepth);
        Vector3 Evaluate(Ray ray, int depth);
};


#endif