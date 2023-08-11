#include "bitmapfont.hpp"
#include "iostream"
namespace mylib
{

BitmapFont::BitmapFont(unsigned int glyphWidth, unsigned int glyphHeight) : m_externalTextureUsed{false}, m_glyphWidth{glyphWidth}, m_glyphHeight{glyphHeight}
{

}

void BitmapFont::initGhyphs()
{
    sf::Vector2u textSize;
    if(m_externalTextureUsed) { textSize = m_externalTexture->getSize(); }
    else { textSize = m_internalTexture.getSize(); }
    m_nbColunms = textSize.x / m_glyphWidth;
    for(auto i = 0; i < 256; ++i) {
        m_glyphs[i].width = m_glyphWidth;
        m_glyphs[i].textureCoords.x = (i % m_nbColunms) * m_glyphWidth;
        m_glyphs[i].textureCoords.y = (i / m_nbColunms) * m_glyphHeight;
    }
}

bool BitmapFont::loadTexture(const std::string fileName)
{
    bool success = m_internalTexture.loadFromFile(fileName);
    initGhyphs();
    return success;
}

void BitmapFont::setTexture(const sf::Texture& texture)
{
    m_externalTexture = &texture;
    m_externalTextureUsed = true;
    initGhyphs();
}

void BitmapFont::setGlyphWidth(const char letter, const unsigned int glyphWidth)
{
    sf::Uint8 ascii{static_cast<sf::Uint8>(letter)};
    m_glyphs[ascii].width = glyphWidth;
}

const sf::Vector2f& BitmapFont::getTextureCoords(const char letter) const
{
    sf::Uint8 ascii{static_cast<sf::Uint8>(letter)};
    return m_glyphs[ascii].textureCoords;
}

unsigned int BitmapFont::getGlyphWidth(const char letter) const
{
    sf::Uint8 ascii{static_cast<sf::Uint8>(letter)};
    return m_glyphs[ascii].width;
}

unsigned int BitmapFont::getGlyphHeight() const
{
    return m_glyphHeight;
}

const sf::Texture* BitmapFont::getTexture() const
{
    if(m_externalTextureUsed) { return m_externalTexture; }
    else { return &m_internalTexture; }
}

}

