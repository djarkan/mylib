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
                                                     //                     [sXXX] [/s] change or swap back the character size. XXX from 5 to 999.                                                  //
                                                     //                     [cXX] [/c] change or swap back the color. XX from 0 to 28.                                                              //
                                                     //                         Black = 0, LightBrown = 1, Brown = 2, DarkBrown = 3, LightRed = 4, Red = 5, DarkRed = 6,                            //
                                                     //                         LightPink = 7, Pink = 8, DarkPink = 9, LightOrange = 10, Orange = 11, DarkOrange = 12,                              //
                                                     //                         LightYellow = 13, Yellow = 14, DarkYellow = 15, LightBlue = 16, Blue = 17, DarkBlue = 18,                           //
                                                     //                         LightGreen = 19, Green = 20, DarkGreen = 21, LightPurple = 22, Purple = 23, DarkPurple = 24,                        //
                                                     //                         LightGrey = 25, Grey = 26, DarkGrey = 27, White = 28                                                                //
                                                     //                                                                                                                                             //
                                                     //                                                                                                                                             //
                                                     /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace mylib {

class TTFtext
{
    public:
                                        TTFtext(sf::RenderWindow& window);
                                        TTFtext(const std::string& text, const std::string& fontName, unsigned int fontSize, sf::Color color, sf::RenderWindow& window);

                 bool                   setFont(const std::string& fontName);
                 void                   setText(const std::string& text);
                 void                   setColor(const sf::Color color);
                 void                   setOutlineColor(const sf::Color color);
                 void                   setCharacterSize(const unsigned int charSize);

                 void                   displayEnrichedText(float x, float y);
                 void                   displaySimpleText(const float x, const float y);

    private :
                 enum class TextColor { Black = 0, LightBrown = 1, Brown = 2, DarkBrown = 3, LightRed = 4, Red = 5, DarkRed = 6, LightPink = 7, Pink = 8, DarkPink = 9, LightOrange = 10, Orange = 11, DarkOrange = 12, LightYellow = 13, Yellow = 14,
                                        DarkYellow = 15, LightBlue = 16, Blue = 17, DarkBlue = 18, LightGreen = 19, Green = 20, DarkGreen = 21, LightPurple = 22, Purple = 23, DarkPurple = 24, LightGrey = 25, Grey = 26, DarkGrey = 27, White = 28};
                 std::string            m_string;
                 sf::Text               m_text;
                 sf::Font               m_font;
                 unsigned int           m_fontSize;
                 sf::Color              m_color;
                 sf::Color              m_outlinedColor;
                 sf::RenderWindow&      m_window;

                sf::Color              selectColor( int colorNb);
                void                   displayChar(float& x, const float y, const int charSize, const char printedChar);
};

}
#endif
