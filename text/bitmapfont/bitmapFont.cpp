#include "bitmapfont.hpp"

#include <iostream>

namespace mylib
{

BitmapFont::BitmapFont()
{

}

BitmapFont::BitmapFont(std::string fileName, unsigned int glyphWidth, unsigned int glyphHigth)
{
    setBitmapFont(fileName, glyphWidth, glyphHigth);
}

bool BitmapFont::setBitmapFont(std::string fileName, unsigned int glyphWidth, unsigned int glyphHigth)
{
    bool success = m_letterTexture.loadFromFile(fileName);
    if(success) { m_letterSprite.setTexture(m_letterTexture); }
    sf::Vector2u textSize = m_letterTexture.getSize();
    m_glyphWidth = glyphWidth;
    m_glyphHigth = glyphHigth;
    m_nbColunms = textSize.x / glyphHigth;
    return success;
}

void BitmapFont::setScale(float scale)
{
    m_letterSprite.setScale(scale, scale);
}

const sf::Sprite& BitmapFont::getfontToDraw(char letter, sf::Vector2f coord)
{
    m_letterSprite.setPosition(coord);
    sf::Uint8 ascii{letter};
    if(letter == '£') { ascii = 156; }
    int x = (ascii % m_nbColunms) * m_glyphWidth;
    int y = (ascii / m_nbColunms) * m_glyphHigth;
    m_letterSprite.setTextureRect(sf::IntRect(x, y, m_glyphWidth, m_glyphHigth));
    return m_letterSprite;
}

void BitmapFont::setSmooth(bool on)
{
    m_letterTexture.setSmooth(on);
}

}

