#ifndef BITMAPFONT_HPP
#define BITMAPFONT_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <array>
#include <memory>

namespace mylib
{

 class BitmapFont
{
    public :
                                                BitmapFont();                  // if used, setSize(unsigned int glyphWidth, unsigned int glyphHeight) MUST be called BEFORE setTexture or moadTexture //
                                                BitmapFont(unsigned int glyphWidth, unsigned int glyphHigth);
        void                                    setSize(unsigned int glyphWidth, unsigned int glyphHeight);
        bool                                    loadTexture(const std::string fileName);
        void                                    setTexture(const sf::Texture& texture);
        void                                    setGlyphWidth(const char letter, const unsigned int glyphWidth);
        unsigned int                            getGlyphWidth(const char letter) const;
        unsigned int                            getGlyphHeight() const;
        const sf::Vector2f&                     getTextureCoords(const char letter) const;
        const sf::Texture*                      getTexture() const;


    private :
        struct                                  glyph
        {
            float                               width;
            sf::Vector2f                        textureCoords;
        };
        sf::Texture                             m_internalTexture;
        const sf::Texture*                      m_externalTexture;
        bool                                    m_externalTextureUsed;
        unsigned int                            m_glyphWidth;
        unsigned int                            m_glyphHeight;
        unsigned int                            m_nbColunms;
        std::array<glyph, 256>                  m_glyphs;

        void                                    initGhyphs();
};

}

#endif //BITMAPFONT_HPP
