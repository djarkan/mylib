#include "text/bitmaptext/bitmapText.hpp"

namespace mylib
{

BitmapText::BitmapText() :  m_text{""}, m_color{sf::Color::White}, m_letterSpacing{0}, m_lineSpacing{0}, m_font{nullptr}, m_vertices(sf::PrimitiveType::Quads)
{

}

BitmapText::BitmapText(const std::string text) :  m_color{sf::Color::White}, m_letterSpacing{0}, m_lineSpacing{0}, m_font{nullptr}, m_vertices(sf::PrimitiveType::Quads)
{
    m_text = text;
    updateVertices();
}

void BitmapText::setText(const std::string& text)
{
    m_text = text;
    updateVertices();
}

void  BitmapText::setScale(float scale)
{
    setScale(scale, scale);
}
void BitmapText::setScale(float scaleX, float scaleY)
{
    this->Transformable::setScale(scaleX, scaleY);
}

void BitmapText::setScale(sf::Vector2f scale)
{
    setScale(scale.x, scale.y);
}

void BitmapText::setColor(const sf::Color& color)
{
    m_color = color;
    updateVertices();
}

void BitmapText::setFont(const mylib::BitmapFont* font)
{
    m_font = font;
    updateVertices();
}

void BitmapText::setLetterSpacing(float letterSpacing)
{
    m_letterSpacing = letterSpacing;
    updateVertices();
}

void BitmapText::setLineSpacing(float lineSpacing)
{
    m_lineSpacing = lineSpacing;
    updateVertices();
}

std::string BitmapText::getText() const
{
    return m_text;
}

float  BitmapText::getScale() const
{
    sf::Vector2f scale{Transformable::getScale()};
    return scale.x;
}

sf::Color BitmapText::getColor() const
{
    return m_color;
}

sf::FloatRect BitmapText::getLocalBounds() const
{
    unsigned int width{0}, height{m_font->getGlyphHeight()}, currentWidth{0}, currentHeight{0}, lineNumber{1};
    for(auto letter : m_text) {
        if(letter == '\n') {
            if(currentWidth > width) { width = currentWidth; }
            currentWidth = 0;
            currentHeight += m_font->getGlyphHeight() + m_lineSpacing;
            height += m_font->getGlyphHeight();
            lineNumber++;
        }
        else { currentWidth += m_font->getGlyphWidth(letter) + m_letterSpacing; }
    }
    if(currentWidth > width) { width = currentWidth; }
    width -= m_letterSpacing;
    if(lineNumber > 1) { height -= m_lineSpacing; }
    return sf::FloatRect(0.f, 0.f, width, height);
}

sf::FloatRect BitmapText::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}

const sf::Texture* BitmapText::getTexture() const
{
    return m_font->getTexture();
}

void BitmapText::updateVertices()
{
    if(m_font == nullptr) {
        m_vertices.clear();
        return;
    }
    m_vertices.resize(m_text.size() * 4);
    unsigned int index{0};
    sf::Vector2f position(0, 0);
    for(auto letter : m_text) {
        sf::Uint8 ascii{static_cast<sf::Uint8>(letter)};
        float glyphWidth = m_font->getGlyphWidth(ascii);
        float glyphHeight = m_font->getGlyphHeight();
        sf::Vector2f textureCoords = m_font->getTextureCoords(ascii);
        if(letter == '\n') {
            position.x = 0;
            position.y += glyphHeight + m_lineSpacing;
        }
        else {
            m_vertices[(index * 4)].position = position;
            m_vertices[(index * 4) + 1].position = sf::Vector2f(position.x + glyphWidth, position.y);
            m_vertices[(index * 4) + 2].position = sf::Vector2f(position.x + glyphWidth, position.y + glyphHeight);
            m_vertices[(index * 4) + 3].position = sf::Vector2f(position.x, position.y + glyphHeight);

            m_vertices[(index * 4)].texCoords = textureCoords;
            m_vertices[(index * 4) + 1].texCoords = sf::Vector2f(textureCoords.x + glyphWidth, textureCoords.y);
            m_vertices[(index * 4) + 2].texCoords = sf::Vector2f(textureCoords.x + glyphWidth, textureCoords.y + glyphHeight);
            m_vertices[(index * 4) + 3].texCoords = sf::Vector2f(textureCoords.x, textureCoords.y + glyphHeight);

            m_vertices[(index * 4)].color = m_color;
            m_vertices[(index * 4) + 1].color =  m_color;
            m_vertices[(index * 4) + 2].color =  m_color;
            m_vertices[(index * 4) + 3].color =  m_color;
            ++index;
            position.x += glyphWidth + m_letterSpacing;
        }
    }
}

void BitmapText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(m_font != nullptr) {
        states.transform *= this->getTransform();
        states.texture = m_font->getTexture();
        target.draw(m_vertices, states);
    }
}

}
