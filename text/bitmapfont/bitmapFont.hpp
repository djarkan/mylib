#ifndef BITMAPFONT_HPP
#define BITMAPFONT_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace mylib
{

class BitmapFont
{
    public :
                                                BitmapFont();
                                                BitmapFont(std::string fileName, unsigned int glyphWidth, unsigned int glyphHigth);
        bool                                    setBitmapFont(std::string fileName, unsigned int glyphWidth, unsigned int glyphHigth);
        void                                    setScale(float scale);
        const sf::Sprite&                       getfontToDraw(char letter, sf::Vector2f coord);
        void                                    setSmooth(bool on);

    private :
        sf::Sprite                              m_letterSprite;
        sf::Texture                             m_letterTexture;
        unsigned int                            m_glyphWidth;
        unsigned int                            m_glyphHigth;
        float                                   m_scale;
        unsigned int                            m_nbColunms;
};

}

#endif //BITMAPFONT_HPP
