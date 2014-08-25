#include "zf_rect.hpp"
namespace zf
{
    //////////////////// Utility methods ////////////////////
    int rightOf(const sf::IntRect& rect)
    {
        return rect.left + rect.width - 1;
    }

    int bottomOf(const sf::IntRect& rect)
    {
        return rect.top + rect.height - 1;
    }

    int leftOf(const sf::IntRect& rect)
    {
        return rect.left;
    }

    int topOf(const sf::IntRect& rect)
    {
        return rect.top;
    }

    sf::IntRect& move(sf::IntRect& rect, const sf::Vector2i& moveVect)
    {
        rect.left += moveVect.x;
        rect.top += moveVect.y;
        return rect;
    }

    sf::IntRect moveCopy(sf::IntRect rect, const sf::Vector2i& moveVect)
    {
        return move(rect, moveVect);
    }

    sf::IntRect& setRectByCorners(sf::IntRect& rect, int left, int top, int right, int bottom)
    {
        rect.left = left;
        rect.top = top;
        rect.width = right - left + 1;
        rect.height = bottom - top + 1;
        return rect;
    }

    sf::IntRect& fitRectByShrinking(sf::IntRect& innerRect, const sf::IntRect& outerRect)
    {
        int iLeft = leftOf(innerRect);
        int iRight = rightOf(innerRect);
        int iTop = topOf(innerRect);
        int iBottom = bottomOf(innerRect);
        int oLeft = leftOf(outerRect);
        int oRight = rightOf(outerRect);
        int oTop = topOf(outerRect);
        int oBottom = bottomOf(outerRect);
        iLeft = iLeft < oLeft ? oLeft : iLeft;
        iRight = iRight > oRight ? oRight : iRight;
        iTop = iTop < oTop ? oTop : iTop;
        iBottom = iBottom > oBottom ? oBottom : iBottom;
        return setRectByCorners(innerRect, iLeft, iTop, iRight, iBottom);
    }
    
    
    sf::IntRect centerRect(const sf::IntRect& rect, const sf::IntRect& referenceRect)
    {
        // calculate the spare space.
        int spareX = referenceRect.width - rect.width;
        int spareY = referenceRect.height - rect.height;
        return sf::IntRect(referenceRect.left + spareX / 2, referenceRect.top + spareY / 2, rect.width, rect.height);
    }
}
