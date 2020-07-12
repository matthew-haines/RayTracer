#ifndef IMPORTANCE_SAMPLING_MODEL_HPP
#define IMPORTANCE_SAMPLING_MODEL_HPP
#include "lighting_model.hpp"

class ImportanceSamplingModel: public LightingModel {
    ImportanceSamplingModel();
    Vector3 Evaluate(Ray ray, int depth);
};

#endif