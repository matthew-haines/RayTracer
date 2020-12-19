#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include "../vector3.hpp"
#include "../vector2.hpp"
#include <vector>

class Texture {
    public:
        Texture();
        virtual Vector3 getColorAtUV(const Vector2& point) const =0;
};

class ImageTexture: public Texture {
    private:
        std::vector<Vector3>* const color;
        const std::size_t width, height;
    public:
        ImageTexture(std::vector<Vector3>* const color, const std::size_t width, const std::size_t height)
        Vector3 getColorAtUV(const Vector2& point) const;
};

class CheckerboardTexture: public Texture {
    private:
        const Vector3 colorA, colorB;
    public:
        CheckerboardTexture(const Vector3 colorA, const Vector3 colorB);
        Vector3 getColorAtUV(const Vector2& point) const;
};

class ConstantTexture: public Texture {
    private:
        const Vector3 color;
    public:
        ConstantTexture(const Vector3 color);
        Vector3 getColorAtUV(const Vector2& point) const;
};

class TextureMap {
    private:
        Texture* const texture;
    public:
        TextureMap(Texture* const texture);
        virtual Vector2 mapPoint(const Vector2& point) const =0;
};

class SimpleTextureMap: public TextureMap {
    private:
        const Vector2 scale, offset;
    public:
        SimpleTextureMap(const Vector2 scale, const Vector2 offset, Texture* const texture);
        Vector2 mapPoint(const Vector2& point) const;
};

#endif