#ifndef _ZFRAMEWORK_ZF_SPRITE_HPP_
#define _ZFRAMEWORK_ZF_SPRITE_HPP_
#include <SFML/Graphics.hpp>
namespace zf
{
    sf::Sprite& setColor(sf::Sprite& sprite, const sf::Color& color, bool modifyAlpha = true);
    sf::Sprite setCopyColor(sf::Sprite sprite, const sf::Color& color, bool modifiyAlpha = true);
    sf::Sprite& setAlpha(sf::Sprite& sprite, sf::Uint8 alpha, const sf::Uint8 min = 0, const sf::Uint8 max = 255);
    sf::Sprite setCopyAlpha(sf::Sprite sprite, sf::Uint8 alpha, const sf::Uint8 min = 0, const sf::Uint8 max = 255);
}
#endif
