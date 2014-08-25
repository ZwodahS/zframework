#ifndef _ZFRAMEWORK_ZF_RECT_HPP_
#define _ZFRAMEWORK_ZF_RECT_HPP_
#include <SFML/Graphics.hpp>
#include <string>
namespace zf
{
    /**
     * Get the right of the rect
     */
    int rightOf(const sf::IntRect& rect);
    /**
     * Get the bottom of the rect.
     */
    int bottomOf(const sf::IntRect& rect);
    /**
     * For completeness sake
     */
    int leftOf(const sf::IntRect& rect);
    int topOf(const sf::IntRect& rect);

    sf::IntRect& move(sf::IntRect& rect, const sf::Vector2i& moveVect);
    sf::IntRect moveCopy(sf::IntRect rect, const sf::Vector2i& moveVect);
    
    sf::IntRect& setRectByCorners(sf::IntRect& rect, int left, int top, int right, int bottom);
    /**
     * Try to fix the inner rect into outer rect.
     * This fit the inner rect using shrinking.
     */
    sf::IntRect& fitRectByShrinking(sf::IntRect& innerRect, const sf::IntRect& outerRect);

    /**
     * Center the rect with respect to referenceRect.
     */
    sf::IntRect centerRect(const sf::IntRect& rect, const sf::IntRect& referenceRect);
}
#endif
