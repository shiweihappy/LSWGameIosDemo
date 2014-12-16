//
//  MyRichText.h
//  LSWGameIOS
//
//  Created by lsw on 14-9-25.
//
//

#ifndef __LSWGameIOS__MyRichText__
#define __LSWGameIOS__MyRichText__

#include "cocos2d.h"
#include "ui/UIWidget.h"
USING_NS_CC;

namespace cwaLy{
    
    class CwaRichElement : public Ref
    {
    public:
        enum class Type
        {
            TEXT,
            IMAGE,
            CUSTOM
        };
        CwaRichElement(){};
        virtual ~CwaRichElement(){};
        bool init(int tag, const Color3B& color, GLubyte opacity);
    protected:
        Type _type;
        int _tag;
        Color3B _color;
        GLubyte _opacity;
        friend class CwaRichText;
    };
    
    class CwaRichElementText : public CwaRichElement
    {
    public:
        CwaRichElementText(){_type = Type::TEXT;};
        virtual ~CwaRichElementText(){};
        bool init(int tag, const Color3B& color, GLubyte opacity, const std::string& text, const std::string& fontName, float fontSize);
        static CwaRichElementText* create(int tag, const Color3B& color, GLubyte opacity, const std::string& text, const std::string& fontName, float fontSize);
    protected:
        std::string _text;
        std::string _fontName;
        float _fontSize;
        friend class CwaRichText;
        
    };
    
    class CwaRichElementImage : public CwaRichElement
    {
    public:
        CwaRichElementImage(){_type = Type::IMAGE;};
        virtual ~CwaRichElementImage(){};
        bool init(int tag, const Color3B& color, GLubyte opacity, const std::string& filePath);
        static CwaRichElementImage* create(int tag, const Color3B& color, GLubyte opacity, const std::string& filePath);
    protected:
        std::string _filePath;
        Rect _textureRect;
        int _textureType;
        friend class CwaRichText;
    };
    
    class CwaRichElementCustomNode : public CwaRichElement
    {
    public:
        CwaRichElementCustomNode(){_type = Type::CUSTOM;};
        virtual ~CwaRichElementCustomNode(){CC_SAFE_RELEASE(_customNode);};
        bool init(int tag, const Color3B& color, GLubyte opacity, Node* customNode);
        static CwaRichElementCustomNode* create(int tag, const Color3B& color, GLubyte opacity, Node* customNode);
    protected:
        Node* _customNode;
        friend class CwaRichText;
    };
    
    class CwaRichText : public ui::Widget
    {
    public:
        CwaRichText();
        virtual ~CwaRichText();
        static CwaRichText* create();
        void insertElement(CwaRichElement* element, int index);
        void pushBackElement(CwaRichElement* element);
        void removeElement(int index);
        void removeElement(CwaRichElement* element);
        virtual void visit(cocos2d::Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;
        void setVerticalSpace(float space);
        virtual void setAnchorPoint(const Vec2 &pt);
        virtual const Size& getVirtualRendererSize() const override;
        void formatText();
        virtual void ignoreContentAdaptWithSize(bool ignore);
        virtual std::string getDescription() const override;
        
    CC_CONSTRUCTOR_ACCESS:
        virtual bool init() override;
        
    protected:
        virtual void initRenderer();
        void pushToContainer(Node* renderer);
        void handleTextRenderer(const std::string& text, const std::string& fontName, float fontSize, const Color3B& color, GLubyte opacity);
        void handleImageRenderer(const std::string& fileParh, const Color3B& color, GLubyte opacity);
        void handleCustomRenderer(Node* renderer);
        void formarRenderers();
        void addNewLine();
    protected:
        bool _formatTextDirty;
        Vector<CwaRichElement*> _richElements;
        std::vector<Vector<Node*>*> _elementRenders;
        float _leftSpaceWidth;
        float _verticalSpace;
        Node* _elementRenderersContainer;
    };
    
}

#endif /* defined(__LSWGameIOS__MyRichText__) */
