#include "texture.hpp"

Texture::Texture() {

}

ImageTexture::ImageTexture(std::vector<Vector3>* const color, const std::size_t width, const std::size_t height): Texture(), color(color), width(width), height(height) {

}

Vector3 ImageTexture::getColorAtUV(const Vector2& point) const {
    std::size_t column = (double)width * (point.x - std::floor(point.x));
    std::size_t row = (double)height * (point.y - std::floor(point.y));
    return color->at(row * width + column);
}

CheckerboardTexture::CheckerboardTexture(const Vector3 colorA, const Vector3 colorB): Texture(), colorA(colorA), colorB(colorB) {

}

Vector3 CheckerboardTexture::getColorAtUV(const Vector2& point) const {
    int u = std::floor(std::fmod(point.x, 2));
    int v = std::floor(std::fmod(point.y, 2));
    return Vector3(u == v ? colorA : colorB);
}

ConstantTexture::ConstantTexture(const Vector3 color): Texture(), color(color) {}

Vector3 ConstantTexture::getColorAtUV(const Vector2& point) const {
    return color;
}

TextureMap::TextureMap(Texture* const texture): texture(texture) {
    
}

SimpleTextureMap::SimpleTextureMap(const Vector2 scale, const Vector2 offset, Texture* const texture): TextureMap(texture), scale(scale), offset(offset) {

};

Vector3 SimpleTextureMap::mapPoint(const Vector2& point) const {
    return texture->getColorAtUV(point * scale + offset);
}
