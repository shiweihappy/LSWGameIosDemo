//
//  StarMatrix.cpp
//  LSWGameIOS
//
//  Created by lsw on 14-10-31.
//
//

#include "StarMatrix.h"

USING_NS_CC;

StarMatrix *StarMatrix::create(GameLayer *layer)
{
    auto starMatrix = new StarMatrix();
    if (starMatrix && starMatrix->init(layer))
    {
        starMatrix->autorelease();
        return starMatrix;
    }
    CC_SAFE_DELETE(starMatrix);
    return nullptr;
}

bool StarMatrix::init(GameLayer *layer)
{
    m_layer = layer;
    if (!Node::init())
    {
        return false;
    }
    
    this->initMatrix();
    return true;
}

void StarMatrix::initMatrix()
{
    srand(time(0));
    for (auto i = 0; i<ROW_NUM; i++)
    {
        for (auto j = 0; j<COL_NUM; j++)
        {
            auto color = abs(rand() % Star::COLOR_MAX_NUM);
            Star *star = Star::create(color);
            m_star[i][j] = star;
            star->setPosition(getPositionByIndex(i, j));
            star->setDesPosition(getPositionByIndex(i, j));
            star->setIndexIJ(i, j);
            addChild(star);
        }
    }
}

Vec2 StarMatrix::getPositionByIndex(int i, int j)
{
    float x = j * Star::STAR_W + Star::STAR_W/2;
    float y = i * Star::STAR_H + Star::STAR_H/2;
    return Vec2(x, y);
}

void StarMatrix::updateStar(float dt)
{
    for (auto i = 0; i<ROW_NUM; i++)
    {
        for (auto j = 0; j<COL_NUM; j++)
        {
            if (m_star[i][j] != nullptr)
                m_star[i][j]->updatePosition();
        }
    }
}

void StarMatrix::onTouch(Vec2 position)
{
    Star *s = getStarByTouch(position);
    if (s)
    {
        genSelectedList(s);
        deleteSelectedList();
    }
}

Star* StarMatrix::getStarByTouch(Vec2 position)
{
    int i = position.y / Star::STAR_H;
    int j = position.x / Star::STAR_W;
    CCLOG("i = %d, j = %d", i, j);
    if (i >= 0 && i< ROW_NUM
        && j >= 0 && j<COL_NUM
        && m_star[i][j] != nullptr)
    {
        return m_star[i][j];
    }
    
    return nullptr;
}

void StarMatrix::genSelectedList(Star *s)
{
    m_selectedList.clear();
    cocos2d::Vector<Star *> findList;
    findList.pushBack(s);
    
    for (auto it = findList.begin(); it != findList.end();)
    {
        Star *star = *it;
        Star *linkStar = nullptr;
        int index_i = star->getIndexI();
        int index_j = star->getIndexJ();
        
        if (index_i - 1 >= 0)
        {
            linkStar = m_star[index_i-1][index_j];
            if (linkStar != nullptr
                &&!linkStar->isSelected()
                && linkStar->getColor() == star->getColor())
            {
                findList.pushBack(linkStar);
            }
        }
        
        if (index_i + 1 < ROW_NUM)
        {
            linkStar = m_star[index_i + 1][index_j];
            if (linkStar != nullptr
                &&!linkStar->isSelected() && linkStar->getColor() == star->getColor())
            {
                findList.pushBack(linkStar);
            }
        }
        
        if (index_j - 1 >= 0)
        {
            linkStar = m_star[index_i][index_j - 1];
            if (linkStar != nullptr
                &&!linkStar->isSelected() && linkStar->getColor() == star->getColor())
            {
                findList.pushBack(linkStar);
            }
        }
        
        if (index_j + 1 < COL_NUM)
        {
            linkStar = m_star[index_i][index_j + 1];
            if (linkStar != nullptr
                &&!linkStar->isSelected() && linkStar->getColor() == star->getColor())
            {
                findList.pushBack(linkStar);
            }
        }
        
        if (!star->isSelected())
        {
            star->setSelected(true);
            m_selectedList.pushBack(star);
            star = nullptr;
        }
        findList.erase(0);
        it = findList.begin();
    }
}

void StarMatrix::deleteSelectedList()
{
    if (m_selectedList.size() >= 2)
    {
        for (auto it = m_selectedList.begin(); it != m_selectedList.end(); it++)
        {
            Star *s = *it;
            CCLOG("del i = %d, j = %d", s->getIndexI(),s->getIndexJ());
            m_star[s->getIndexI()][s->getIndexJ()] = nullptr;
            s->removeFromParentAndCleanup(true);
        }
    }
    
    adjustMatrix();
}

void StarMatrix::adjustMatrix()
{
    for (auto j = COL_NUM - 1; j>=0; j--)
    {
        for (auto i = 0; i<ROW_NUM; i++)
        {
            if (m_star[i][j] != nullptr)
            {
                continue;
            }
            else
            {
                auto k = i;
                while (k < ROW_NUM) {
                    if (m_star[k][j] != nullptr)
                    {
                        break;
                    }
                    k++;
                }
                if (k >= ROW_NUM) {
                    k = ROW_NUM - 1;
                }
                m_star[i][j] = m_star[k][j];
                if (m_star[k][j] != nullptr)
                {
                    m_star[k][j]->setIndexIJ(i, j);
                    m_star[k][j]->setDesPosition(getPositionByIndex(i, j));
                }
                
                m_star[k][j] = nullptr;
            }
        }
    }
    
    for (auto j = 0; j<COL_NUM; j++)
    {
        if (m_star[0][j] == nullptr)
        {
            auto k = j;
            while (k < COL_NUM) {
                if (m_star[0][k] != nullptr)
                {
                    break;
                }
                k++;
            }
            if (k >= COL_NUM) {
                k = COL_NUM - 1;
            }
            for (auto i = 0; i<ROW_NUM; i++)
            {
                m_star[i][j] = m_star[i][k];
                if (m_star[i][k] != nullptr)
                {
                    m_star[i][k]->setIndexIJ(i, j);
                    m_star[i][k]->setDesPosition(getPositionByIndex(i, j));
                }
                m_star[i][k] = nullptr;
            }
        }
    }
    
    
}

bool StarMatrix::isEnded()
{
    
    return true;
}

