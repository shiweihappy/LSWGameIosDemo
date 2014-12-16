//
//  MyRichText.cpp
//  LSWGameIOS
//
//  Created by lsw on 14-9-25.
//
//

#include "MyRichText.h"
#include "platform/CCFileUtils.h"
#include "2d/CCLabel.h"
#include "2d/CCSprite.h"
#include "base/ccUTF8.h"

namespace cwaLy{
    
    static std::string utf8_substr(const std::string& str, unsigned long start, unsigned long leng)
    {
        if (leng==0)
        {
            return "";
        }
        unsigned long c, i, ix, q, min=std::string::npos, max=std::string::npos;
        for (q=0, i=0, ix=str.length(); i < ix; i++, q++)
        {
            if (q==start)
            {
                min = i;
            }
            if (q <= start+leng || leng==std::string::npos)
            {
                max = i;
            }
            
            c = (unsigned char) str[i];
            
            if      (c<=127) i+=0;
            else if ((c & 0xE0) == 0xC0) i+=1;
            else if ((c & 0xF0) == 0xE0) i+=2;
            else if ((c & 0xF8) == 0xF0) i+=3;
            else return "";//invalid utf8
        }
        if (q <= start+leng || leng == std::string::npos)
        {
            max = i;
        }
        if (min==std::string::npos || max==std::string::npos)
        {
            return "";
        }
        return str.substr(min,max);
    }
    
    static std::vector<std::string> split(std::string str,std::string pattern)
    {
        std::string::size_type pos;
        std::vector<std::string> result;
        str+=pattern;//扩展字符串以方便操作
        int size=str.size();
        for(int i=0; i<size; i++)
        {
            pos=str.find(pattern,i);
            if(pos<size)
            {
                std::string s=str.substr(i,pos-i);
                result.push_back(s);
                i=pos+pattern.size()-1;
            }
        }
        return result;
    }
    
    bool CwaRichElement::init(int tag, const Color3B &color, GLubyte opacity)
    {
        _tag = tag;
        _color = color;
        _opacity = opacity;
        return true;
    }
    
    
    CwaRichElementText* CwaRichElementText::create(int tag, const Color3B &color, GLubyte opacity, const std::string& text, const std::string& fontName, float fontSize)
    {
        CwaRichElementText* element = new CwaRichElementText();
        if (element && element->init(tag, color, opacity, text, fontName, fontSize))
        {
            element->autorelease();
            return element;
        }
        CC_SAFE_DELETE(element);
        return nullptr;
    }
    
    bool CwaRichElementText::init(int tag, const Color3B &color, GLubyte opacity, const std::string& text, const std::string& fontName, float fontSize)
    {
        if (CwaRichElement::init(tag, color, opacity))
        {
            _text = text;
            _fontName = fontName;
            _fontSize = fontSize;
            return true;
        }
        return false;
    }
    
    CwaRichElementImage* CwaRichElementImage::create(int tag, const Color3B &color, GLubyte opacity, const std::string& filePath)
    {
        CwaRichElementImage* element = new CwaRichElementImage();
        if (element && element->init(tag, color, opacity, filePath))
        {
            element->autorelease();
            return element;
        }
        CC_SAFE_DELETE(element);
        return nullptr;
    }
    
    bool CwaRichElementImage::init(int tag, const Color3B &color, GLubyte opacity, const std::string& filePath)
    {
        if (CwaRichElement::init(tag, color, opacity))
        {
            _filePath = filePath;
            return true;
        }
        return false;
    }
    
    CwaRichElementCustomNode* CwaRichElementCustomNode::create(int tag, const Color3B &color, GLubyte opacity, cocos2d::Node *customNode)
    {
        CwaRichElementCustomNode* element = new CwaRichElementCustomNode();
        if (element && element->init(tag, color, opacity, customNode))
        {
            element->autorelease();
            return element;
        }
        CC_SAFE_DELETE(element);
        return nullptr;
    }
    
    bool CwaRichElementCustomNode::init(int tag, const Color3B &color, GLubyte opacity, cocos2d::Node *customNode)
    {
        if (CwaRichElement::init(tag, color, opacity))
        {
            _customNode = customNode;
            _customNode->retain();
            return true;
        }
        return false;
    }
    
    CwaRichText::CwaRichText():
    _formatTextDirty(true),
    _leftSpaceWidth(0.0f),
    _verticalSpace(0.0f),
    _elementRenderersContainer(nullptr)
    {
        
    }
    
    CwaRichText::~CwaRichText()
    {
        _richElements.clear();
    }
    
    CwaRichText* CwaRichText::create()
    {
        CwaRichText* widget = new CwaRichText();
        if (widget && widget->init())
        {
            widget->autorelease();
            return widget;
        }
        CC_SAFE_DELETE(widget);
        return nullptr;
    }
    
    bool CwaRichText::init()
    {
        if (Widget::init())
        {
            return true;
        }
        return false;
    }
    
    void CwaRichText::initRenderer()
    {
        _elementRenderersContainer = Node::create();
        _elementRenderersContainer->setAnchorPoint(Vec2(0.5f, 0.5f));
        addProtectedChild(_elementRenderersContainer, 0, -1);
    }
    
    void CwaRichText::insertElement(CwaRichElement *element, int index)
    {
        _richElements.insert(index, element);
        _formatTextDirty = true;
    }
    
    void CwaRichText::pushBackElement(CwaRichElement *element)
    {
        _richElements.pushBack(element);
        _formatTextDirty = true;
    }
    
    void CwaRichText::removeElement(int index)
    {
        _richElements.erase(index);
        _formatTextDirty = true;
    }
    
    void CwaRichText::removeElement(CwaRichElement *element)
    {
        _richElements.eraseObject(element);
        _formatTextDirty = true;
    }
    
    void CwaRichText::formatText()
    {
        if (_formatTextDirty)
        {
            _elementRenderersContainer->removeAllChildren();
            _elementRenders.clear();
            if (_ignoreSize)
            {
                addNewLine();
                for (ssize_t i=0; i<_richElements.size(); i++)
                {
                    CwaRichElement* element = _richElements.at(i);
                    Node* elementRenderer = nullptr;
                    switch (element->_type)
                    {
                        case CwaRichElement::Type::TEXT:
                        {
                            CwaRichElementText* elmtText = static_cast<CwaRichElementText*>(element);
                            if (FileUtils::getInstance()->isFileExist(elmtText->_fontName))
                            {
                                elementRenderer = Label::createWithTTF(elmtText->_text.c_str(), elmtText->_fontName, elmtText->_fontSize);
                            }
                            else
                            {
                                elementRenderer = Label::createWithSystemFont(elmtText->_text.c_str(), elmtText->_fontName, elmtText->_fontSize);
                            }
                            break;
                        }
                        case CwaRichElement::Type::IMAGE:
                        {
                            CwaRichElementImage* elmtImage = static_cast<CwaRichElementImage*>(element);
                            elementRenderer = Sprite::create(elmtImage->_filePath.c_str());
                            break;
                        }
                        case CwaRichElement::Type::CUSTOM:
                        {
                            CwaRichElementCustomNode* elmtCustom = static_cast<CwaRichElementCustomNode*>(element);
                            elementRenderer = elmtCustom->_customNode;
                            break;
                        }
                        default:
                        break;
                    }
                    elementRenderer->setColor(element->_color);
                    elementRenderer->setOpacity(element->_opacity);
                    pushToContainer(elementRenderer);
                }
            }
            else
            {
                addNewLine();
                for (ssize_t i=0; i<_richElements.size(); i++)
                {
                    
                    CwaRichElement* element = static_cast<CwaRichElement*>(_richElements.at(i));
                    switch (element->_type)
                    {
                        case CwaRichElement::Type::TEXT:
                        {
                            CwaRichElementText* elmtText = static_cast<CwaRichElementText*>(element);
                            handleTextRenderer(elmtText->_text.c_str(), elmtText->_fontName.c_str(), elmtText->_fontSize, elmtText->_color, elmtText->_opacity);
                            break;
                        }
                        case CwaRichElement::Type::IMAGE:
                        {
                            CwaRichElementImage* elmtImage = static_cast<CwaRichElementImage*>(element);
                            handleImageRenderer(elmtImage->_filePath.c_str(), elmtImage->_color, elmtImage->_opacity);
                            break;
                        }
                        case CwaRichElement::Type::CUSTOM:
                        {
                            CwaRichElementCustomNode* elmtCustom = static_cast<CwaRichElementCustomNode*>(element);
                            handleCustomRenderer(elmtCustom->_customNode);
                            break;
                        }
                        default:
                        break;
                    }
                }
            }
            formarRenderers();
            _formatTextDirty = false;
        }
    }
    
    void CwaRichText::handleTextRenderer(const std::string& text, const std::string& fontName, float fontSize, const Color3B &color, GLubyte opacity)
    {
        auto fileExist = FileUtils::getInstance()->isFileExist(fontName);
        Label* textRenderer = nullptr;
        if (fileExist)
        {
            textRenderer = Label::createWithTTF(text, fontName, fontSize);
        }
        else
        {
            textRenderer = Label::createWithSystemFont(text, fontName, fontSize);
        }
        
        std::vector<std::string> vec= split(text, "\n");
        if (vec.size() == 1)
        {
            float textRendererWidth = textRenderer->getContentSize().width;
            _leftSpaceWidth -= textRendererWidth;
            if (_leftSpaceWidth < 0.0f)
            {
                float overstepPercent = (-_leftSpaceWidth) / textRendererWidth;
                std::string curText = text;
                size_t stringLength = StringUtils::getCharacterCountInUTF8String(text);
                int leftLength = stringLength * (1.0f - overstepPercent);
                std::string leftWords = utf8_substr(curText,0,leftLength);
                std::string cutWords = utf8_substr(curText, leftLength, curText.length() - leftLength);
                if (leftLength > 0)
                {
                    Label* leftRenderer = nullptr;
                    if (fileExist)
                    {
                        leftRenderer = Label::createWithTTF(utf8_substr(leftWords, 0, leftLength), fontName, fontSize);
                    }
                    else
                    {
                        leftRenderer = Label::createWithSystemFont(utf8_substr(leftWords, 0, leftLength), fontName, fontSize);
                    }
                    if (leftRenderer)
                    {
                        leftRenderer->setColor(color);
                        leftRenderer->setOpacity(opacity);
                        pushToContainer(leftRenderer);
                    }
                }
                
                addNewLine();
                handleTextRenderer(cutWords.c_str(), fontName, fontSize, color, opacity);
            }
            else
            {
                textRenderer->setColor(color);
                textRenderer->setOpacity(opacity);
                pushToContainer(textRenderer);
            }
        }
        else
        {
            int size = vec.size();
            for (auto i = 0; i<size; i++)
            {
                std::string s = vec[i];
                CCLOG("arr[i] %d= %s", i, s.c_str());
                handleTextRenderer(s, fontName, fontSize, color, opacity);
                if (i != size - 1)
                    addNewLine();
            }
        }
        
        
    }
    
    void CwaRichText::handleImageRenderer(const std::string& fileParh, const Color3B &color, GLubyte opacity)
    {
        Sprite* imageRenderer = Sprite::create(fileParh);
        handleCustomRenderer(imageRenderer);
    }
    
    void CwaRichText::handleCustomRenderer(cocos2d::Node *renderer)
    {
        Size imgSize = renderer->getContentSize();
        _leftSpaceWidth -= imgSize.width;
        if (_leftSpaceWidth < 0.0f)
        {
            addNewLine();
            pushToContainer(renderer);
            _leftSpaceWidth -= imgSize.width;
        }
        else
        {
            pushToContainer(renderer);
        }
    }
    
    void CwaRichText::addNewLine()
    {
        _leftSpaceWidth = _customSize.width;
        _elementRenders.push_back(new Vector<Node*>());
    }
    
    void CwaRichText::formarRenderers()
    {
        if (_ignoreSize)
        {
            float newContentSizeWidth = 0.0f;
            float newContentSizeHeight = 0.0f;
            
            Vector<Node*>* row = (_elementRenders[0]);
            float nextPosX = 0.0f;
            for (ssize_t j=0; j<row->size(); j++)
            {
                Node* l = row->at(j);
                l->setAnchorPoint(Vec2::ZERO);
                l->setPosition(Vec2(nextPosX, 0.0f));
                _elementRenderersContainer->addChild(l, 1);
                Size iSize = l->getContentSize();
                newContentSizeWidth += iSize.width;
                newContentSizeHeight = MAX(newContentSizeHeight, iSize.height);
                nextPosX += iSize.width;
            }
            _elementRenderersContainer->setContentSize(Size(newContentSizeWidth, newContentSizeHeight));
        }
        else
        {
            float newContentSizeHeight = 0.0f;
            float *maxHeights = new float[_elementRenders.size()];
            
            for (size_t i=0; i<_elementRenders.size(); i++)
            {
                Vector<Node*>* row = (_elementRenders[i]);
                float maxHeight = 0.0f;
                for (ssize_t j=0; j<row->size(); j++)
                {
                    Node* l = row->at(j);
                    maxHeight = MAX(l->getContentSize().height, maxHeight);
                }
                maxHeights[i] = maxHeight;
                newContentSizeHeight += maxHeights[i];
            }
            
            
            float nextPosY = _customSize.height;
            for (size_t i=0; i<_elementRenders.size(); i++)
            {
                Vector<Node*>* row = (_elementRenders[i]);
                float nextPosX = 0.0f;
                nextPosY -= (maxHeights[i] + _verticalSpace);
                
                for (ssize_t j=0; j<row->size(); j++)
                {
                    Node* l = row->at(j);
                    l->setAnchorPoint(Vec2::ZERO);
                    l->setPosition(Vec2(nextPosX, nextPosY));
                    _elementRenderersContainer->addChild(l, 1);
                    nextPosX += l->getContentSize().width;
                }
            }
            _elementRenderersContainer->setContentSize(_contentSize);
            delete [] maxHeights;
        }
        
        size_t length = _elementRenders.size();
        for (size_t i = 0; i<length; i++)
        {
            Vector<Node*>* l = _elementRenders[i];
            l->clear();
            delete l;
        }    
        _elementRenders.clear();
        
        if (_ignoreSize)
        {
            Size s = getVirtualRendererSize();
            this->setContentSize(s);
        }
        else
        {
            this->setContentSize(_customSize);
        }
        updateContentSizeWithTextureSize(_contentSize);
        _elementRenderersContainer->setPosition(_contentSize.width / 2.0f, _contentSize.height / 2.0f);
    }
    
    void CwaRichText::pushToContainer(cocos2d::Node *renderer)
    {
        if (_elementRenders.size() <= 0)
        {
            return;
        }
        _elementRenders[_elementRenders.size()-1]->pushBack(renderer);
    }
    
    void CwaRichText::visit(cocos2d::Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags)
    {
        if (_enabled)
        {
            formatText();
            Widget::visit(renderer, parentTransform, parentFlags);
        }
    }
    
    void CwaRichText::setVerticalSpace(float space)
    {
        _verticalSpace = space;
    }
    
    void CwaRichText::setAnchorPoint(const Vec2 &pt)
    {
        Widget::setAnchorPoint(pt);
        _elementRenderersContainer->setAnchorPoint(pt);
    }
    
    const Size& CwaRichText::getVirtualRendererSize() const
    {
        return _elementRenderersContainer->getContentSize();
    }
    
    void CwaRichText::ignoreContentAdaptWithSize(bool ignore)
    {
        if (_ignoreSize != ignore)
        {
            _formatTextDirty = true;
            Widget::ignoreContentAdaptWithSize(ignore);
        }
    }
    
    std::string CwaRichText::getDescription() const
    {
        return "CwaRichText";
    }
}

