#include "zf_sprite.hpp"

namespace zf
{
    sf::Sprite& setColor(sf::Sprite& sprite, const sf::Color& color, bool modifyAlpha)
    {
        if (modifyAlpha)
        {
            sprite.setColor(color);
        }
        else
        {
            auto c = sprite.getColor();
            c.r = color.r;
            c.g = color.g;
            c.b = color.b;
            sprite.setColor(c);
        }
        return sprite;
    }

    sf::Sprite setCopyColor(sf::Sprite sprite, const sf::Color& color, bool modifyAlpha)
    {
        return setColor(sprite, color, modifyAlpha);
    }

    sf::Sprite& setAlpha(sf::Sprite& sprite, sf::Uint8 alpha, const sf::Uint8 min, const sf::Uint8 max)
    {
        auto c = sprite.getColor();
        c.a = alpha > max ? max : alpha < min ? min : alpha;
        return sprite;
    }

    sf::Sprite setCopyAlpha(sf::Sprite sprite, sf::Uint8 alpha, const sf::Uint8 min, const sf::Uint8 max)
    {
        return setAlpha(sprite, alpha, min, max);
    }

}
