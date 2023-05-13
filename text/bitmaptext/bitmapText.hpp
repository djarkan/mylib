#ifndef BITMAPTEXT_HPP
#define BITMAPTEXT_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include "text/bitmapfont/bitmapFont.hpp"

namespace mylib
{

class BitmapText {
    public :
                                                    BitmapText();
                                                    BitmapText(std::string fontName, unsigned int glyphWidth, unsigned int glyphHigth);
                                                    BitmapText(std::string text, std::string fontName, unsigned int glyphWidth, unsigned int glyphHigth);
        void                                        setBitmapText(std::string text);
        void                                        setBitmapFont(std::string fontName, unsigned int glyphWidth, unsigned int glyphHigth);
        void                                        setScale(float scale);
        float                                       getScale();
        void                                        drawBitmapText(float x, float y, float step, sf::RenderWindow& window);

    private :
        std::string                                 m_text;
        float                                       m_x;
        float                                       m_y;
        mylib::BitmapFont                           m_bitmapFont;
        std::string                                 m_fontName;
        unsigned int                                m_glyphWidth;
        unsigned int                                m_glyphHigth;
        float                                       m_scale;
};

}
#endif //BITMAPTEXT_HPP
