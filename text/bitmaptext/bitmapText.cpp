#include "text/bitmaptext/bitmapText.hpp"

namespace mylib
{

BitmapText::BitmapText()
{

}

BitmapText::BitmapText(std::string fontName, unsigned int glyphWidth, unsigned int glyphHigth) : m_fontName{fontName}, m_glyphWidth{glyphWidth}, m_glyphHigth{glyphHigth}, m_scale{1}
{
    m_bitmapFont.setBitmapFont(fontName, glyphWidth, glyphHigth);
}

BitmapText::BitmapText(std::string text, std::string fontName, unsigned int glyphWidth, unsigned int glyphHigth) : m_text{text}, m_fontName{fontName}, m_glyphWidth{glyphWidth}, m_glyphHigth{glyphHigth}, m_scale{1}
{
    m_bitmapFont.setBitmapFont(fontName, glyphWidth, glyphHigth);
}

void BitmapText::setBitmapText(std::string text)
{
    m_text = text;
}

void  BitmapText::setScale(float scale)
{
    m_scale = scale;
    m_bitmapFont.setScale(scale);
}

float  BitmapText::getScale()
{
    return m_scale;
}

void BitmapText::setBitmapFont(std::string fontName, unsigned int glyphWidth, unsigned int glyphHigth)
{
    m_fontName = fontName;
    m_glyphWidth = glyphWidth;
    m_glyphHigth = glyphHigth;
    m_bitmapFont.setBitmapFont(fontName, glyphWidth, glyphHigth);
}

void BitmapText::drawBitmapText(float x, float y, float step, sf::RenderWindow& window)
{
    float currentX{x};
    float currentY{y};
    for(char letter : m_text) {
        if(letter != '\n') {
            window.draw(m_bitmapFont.getfontToDraw(letter, sf::Vector2f(currentX, currentY)));
            currentX += (static_cast<float>(m_glyphWidth)) * m_scale;
        }
        else {
            currentX = x;
            currentY += (((static_cast<float>(m_glyphWidth)) * m_scale) + step);
        }
    }
}

}
