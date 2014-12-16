//
//  Star.cpp
//  LSWGameIOS
//
//  Created by lsw on 14-10-30.
//
//

#include "Star.h"

USING_NS_CC;

Star* Star::create(int color)
{
    auto star = new Star();
    if (star && star->initWithFile(star->getImage(color)))
    {
        star->_color = color;
        star->_selected = false;
        star->autorelease();
        return star;
    }
    
    CC_SAFE_DELETE(star);
    return star;
}

const char* Star::getImage(int color)
{
    switch (color) {
        case GREEN:
            return "green.png";
        case ORANGE:
            return "orange.png";
        case RED:
            return "red.png";
        case PURPLE:
            return "purple.png";
        case BLUE:
            return "blue.png";
        default:
            return "blue.png";
    }
}

int Star::getColor()
{
    return _color;
}

void Star::setDesPosition(Vec2 position)
{
    _desPosition = position;
}

Vec2 Star::getDesPosition()
{
    return _desPosition;
}

void Star::setIndexIJ(int i, int j)
{
    _index_i = i;
    _index_j = j;
}

int Star::getIndexI()
{
    return _index_i;
}

int Star::getIndexJ()
{
    return _index_j;
}

void Star::updatePosition()
{
    if (getDesPosition().y != getPositionY())
    {
        setPositionY(getPositionY() - MOVE_SPEED);
        if (getPositionY() < getDesPosition().y)
        {
            setPositionY(getDesPosition().y);
        }
    }
    
    if (getDesPosition().x != getPositionX())
    {
        setPositionX(getPositionX() - MOVE_SPEED);
        if (getPositionX() < getDesPosition().x)
        {
            setPositionX(getDesPosition().x);
        }
    }
}

void Star::setSelected(bool isSelected)
{
    _selected = isSelected;
}

bool Star::isSelected()
{
    return _selected;
}


