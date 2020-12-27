#include "primitive.hpp"
#include "material.hpp"

Primitive::Primitive(const Material material): material(material) {

};

Vector3 Primitive::color(const Vector3& point) const {
    return material.textureMap->mapPoint(getUVAtPoint(point));
}