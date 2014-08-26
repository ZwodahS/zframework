/*
 *           DO WHAT THE F*** YOU WANT TO PUBLIC LICENSE
 *                   Version 2, December 2004
 *
 * Copyright (C) 2014- ZwodahS(ericnjf@gmail.com)
 * zwodahs.github.io
 *
 * Everyone is permitted to copy and distribute verbatim or modified
 * copies of this license document, and changing it is allowed as long
 * as the name is changed.
 *
 *           DO WHAT THE F*** YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *  0. You just DO WHAT THE F*** YOU WANT TO.
 *
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details.
 *
 * visit http://github.com/ZwodahS/zframework for the latest version
 */
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
