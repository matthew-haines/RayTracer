#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include "vector3.hpp"
#include "vector2.hpp"
#include <vector>

// Texture base class.
class Texture {
    public:
        Texture();
        // Needs to return a colour for a given point in real^2.
        virtual Vector3 getColorAtUV(const Vector2& point) const =0;
};

class ImageTexture: public Texture {
    private:
        std::vector<Vector3>* const color;
        const std::size_t width, height;
    public:
        ImageTexture(std::vector<Vector3>* const color, const std::size_t width, const std::size_t height);
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

// TextureMap base class, abstracts some of the more advanced mapping 
// away from the texture it wraps.
class TextureMap {
    protected:
        Texture* const texture;
    public:
        TextureMap(Texture* const texture);
        virtual Vector3 mapPoint(const Vector2& point) const =0;
};

// TextureMap, scales a given point by given factors in both directions 
// and then adds an offset.
class SimpleTextureMap: public TextureMap {
    private:
        const Vector2 scale, offset;
    public:
        SimpleTextureMap(const Vector2 scale, const Vector2 offset, Texture* const texture);
        Vector3 mapPoint(const Vector2& point) const;
};

#endif