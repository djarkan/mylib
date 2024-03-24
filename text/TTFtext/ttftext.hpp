#ifndef TTFTEXT_H
#define TTFTEXT_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
                                                     /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                     //                                                                                                                                             //
                                                     //                                                                                                                                             //
                                                     //                                    Display on screen a TTF font text of any size at coords x, y                                             //
                                                     //                              text can be enriched with balises : "C[s120][c6]O[c8]U[c10][i][s55]C[c12]O[b][c14][u]U"                        //
                                                     //                                                                                                                                             //
                                                     //                     [/r] remove all balises to set previous settings.                                                                       //
                                                     //                     [i] [/i] add or remove italic.                                                                                          //
                                                     //                     [b] [/b] add or remove bold.                                                                                            //
                                                     //                     [u] [/u] add or remove underlined.                                                                                      //
                                                     //                     [t] [/t] add or remove striketrought.                                                                                   //
                                                     //                     [o] [/o] add or remove outline color                                                                                    //
                                                     //                     [sXXX] [/s] change or swap back the character size. XXX from 5 to 999.                                                  //
                                                     //                     [cXX] [/c] change or swap back the color. XX from 0 to 28.                                                              //
                                                     //                         Black = 0, LightBrown = 1, Brown = 2, DarkBrown = 3, LightRed = 4, Red = 5, DarkRed = 6,                            //
                                                     //                         LightPink = 7, Pink = 8, DarkPink = 9, LightOrange = 10, Orange = 11, DarkOrange = 12,                              //
                                                     //                         LightYellow = 13, Yellow = 14, DarkYellow = 15, LightBlue = 16, Blue = 17, DarkBlue = 18,                           //
                                                     //                         LightGreen = 19, Green = 20, DarkGreen = 21, LightPurple = 22, Purple = 23, DarkPurple = 24,                        //
                                                     //                         LightGrey = 25, Grey = 26, DarkGrey = 27, White = 28                                                                //
                                                     //                                                                                                                                             //
                                                     //                                                                                                                                             //
                                                     //                     note: all \n in text must be AFTER all next character's balises.
                                                     //
                                                     /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace mylib {

class TTFtext
{
    public:
                enum class              TextColor { Black = 0, LightBrown = 1, Brown = 2, DarkBrown = 3, LightRed = 4, Red = 5, DarkRed = 6, LightPink = 7, Pink = 8, DarkPink = 9, LightOrange = 10, Orange = 11, DarkOrange = 12, LightYellow = 13, Yellow = 14,
                                        DarkYellow = 15, LightBlue = 16, Blue = 17, DarkBlue = 18, LightGreen = 19, Green = 20, DarkGreen = 21, LightPurple = 22, Purple = 23, DarkPurple = 24, LightGrey = 25, Grey = 26, DarkGrey = 27, White = 28};

                                        TTFtext(sf::RenderWindow& window);
                                        TTFtext(const std::string& text, const std::string& fontName, unsigned int fontSize, TextColor color, sf::RenderWindow& window);

                bool                    setFont(const std::string& fontName);
                void                    setText(const std::string& text);
                void                    setCharacterSize(const unsigned int charSize);
                void                    setColor(const TextColor color);
                void                    setOutlineColor(const TextColor color);
                void                    setOutlineTickness(float thickness);
                void                    setPosition(const float x, const float y);
                void                    setPosition(const sf::Vector2f& coords);

                const std::string&      getText() const;
                unsigned int            getCharacterSize() const;
                TextColor               getColor() const;
                TextColor               getOutlineColor() const;
                float                   getOutlineTickness() const;
                const sf::Vector2f      getPosition() const;

                void                    displayEnrichedText(float x, float y);
                void                    displayEnrichedText();
                void                    displaySimpleText(const float x, const float y);
                void                    displaySimpleText();

    private :
                std::string             m_string;
                sf::Text                m_text;
                sf::Font                m_font;
                unsigned int            m_fontSize;
                TextColor               m_color;
                TextColor               m_outlineColor;
                float                   m_outlineThickness;
                sf::Vector2f            m_coords;
                sf::RenderWindow&       m_window;

                sf::Color               convertEnumColorToSfmlColor(TextColor colorNb);
                void                    displayChar(float& x, const float y, const int charSize, const char printedChar);
};

}
#endif
