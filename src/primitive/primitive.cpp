#include "primitive.hpp"

Primitive::Primitive(Material* const material): material(material) {

};

Vector3 Primitive::color(const Vector3& point) const {
    return material->textureMap->mapPoint(getUVAtPoint(point));
}