#include "primitive.hpp"

Primitive::Primitive(Material* const material, TextureMap* const textureMap): material(material), textureMap(textureMap) {

};

Vector3 Primitive::color(const Vector3& point) const {
    return material->texture->getColorAtUV(textureMap->mapPoint(getUVAtPoint(point)));
}