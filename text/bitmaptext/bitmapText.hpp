#ifndef BITMAPTEXT_HPP
#define BITMAPTEXT_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <string>
#include <memory>

#include "text/bitmapfont/bitmapFont.hpp"

namespace mylib
{

class BitmapText : public sf::Drawable, public sf::Transformable
{
    public :
                                                BitmapText();
                                                BitmapText(const std::string text);
        void                                    setText(const std::string& text);
        void                                    setScale(float scale);
        void                                    setScale(float scaleX, float scaleY);
        void                                    setScale(sf::Vector2f scale);
        void                                    setColor(const sf::Color& color);
        void                                    setFont(const mylib::BitmapFont* font);
        void                                    setLetterSpacing(float letterSpacing);
        void                                    setLineSpacing(float lineSpacing);
        std::string                             getText() const;
        float                                   getScale() const;
        sf::Color                               getColor() const;
        sf::FloatRect                           getLocalBounds() const;
        sf::FloatRect                           getGlobalBounds() const;
        const sf::Texture*                      getTexture() const;

    private :
        std::string                             m_text;
        sf::Color                               m_color;
        float                                   m_letterSpacing;
        float                                   m_lineSpacing;
        const mylib::BitmapFont*                m_font;
        sf::VertexArray                         m_vertices;

        void                                    updateVertices();
        virtual void                            draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

}
#endif //BITMAPTEXT_HPP
