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
#ifndef _ZFRAMEWORK_ZF_DIRECTION_HPP_
#define _ZFRAMEWORK_ZF_DIRECTION_HPP_
#include <string>
#include <SFML/System.hpp>
namespace zf
{
    enum class Direction
    {
        None,
        North,
        East,
        South,
        West,
        NorthEast,
        SouthEast,
        SouthWest,
        NorthWest,
    };

    const Direction AdjacentDirection[4] = { Direction::North, Direction::East, Direction::South, Direction::West };
    const Direction SurroundingDirection[8] = { Direction::North, Direction::NorthEast, Direction::East, Direction::SouthEast, Direction::South, Direction::SouthWest, Direction::West, Direction::NorthWest };
    const Direction AllDirection[9] = { Direction::None, Direction::North, Direction::NorthEast, Direction::East, Direction::SouthEast, Direction::South, Direction::SouthWest, Direction::West, Direction::NorthWest };
    const std::string DirectionString[9] = { "None", "North", "East", "South", "West", "NorthEast", "SouthEast", "SouthWest", "NorthWest" };
    Direction oppositeOf(Direction direction);
    sf::Vector2i getModifier(Direction direction);
    bool isOpposite(Direction direction1, Direction direction2);
    int getIntValue(Direction direction);
    std::string directionToString(Direction direction);
    bool stringToDirection(const std::string&, Direction& direction);

    /**
     * Convert to bit value.
     * None : 0
     * North : 1
     * East : 2
     * South : 4
     * West : 8
     * NorthEast : 3
     * SouthEast : 6
     * SouthWest : 12
     * NorthWest : 9
     */
    int toBit(Direction direction);
}
#endif
