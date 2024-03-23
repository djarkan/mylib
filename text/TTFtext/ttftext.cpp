#include "ttftext.hpp"

#include <iostream>

namespace mylib
{

TTFtext::TTFtext(sf::RenderWindow& window): m_fontSize{10}, m_color{sf::Color::White}, m_outlinedColor{sf::Color::White}, m_window{window}
{

}

TTFtext::TTFtext(const std::string& text, const std::string& fontName, unsigned int fontSize, sf::Color color, sf::RenderWindow& window) : m_string{text}, m_fontSize{fontSize}, m_color{color}, m_window{window}
{
    m_font.loadFromFile(fontName);
    m_text.setFont(m_font);
}

bool TTFtext::setFont(const std::string& fontName)
{
    bool fontOK = m_font.loadFromFile(fontName);
    m_text.setFont(m_font);
    return fontOK;
}

void TTFtext::setText(const std::string& text)
{
    m_string = text;
}

void TTFtext::setColor(const sf::Color color)
{
    m_text.setFillColor(color);
    m_color = color;
}

void TTFtext::setOutlineColor(const sf::Color color)
{
    m_text.setOutlineColor(color);
}

void TTFtext::setCharacterSize(const unsigned int charSize)
{
    m_text.setCharacterSize(charSize);
    m_fontSize = charSize;
}

void TTFtext::displayEnrichedText(float x, float y)
{
    float oldx = x;
    float oldY = y;
    m_text.setPosition(x, y);
    m_text.setStyle(sf::Text::Regular);
    for(unsigned int i = 0; i < m_string.size(); ++i) {
        if(m_string[i] != '[') {
            if(m_string[i] == '\n') {
                x = oldx;
                y += m_text.getCharacterSize() + 4;
                m_text.setPosition(x, y);
            }
            else { displayChar(x, y , m_fontSize, m_string[i]); }
        }
        else {                                                                                                           // enter in a balise
            unsigned int baliseStartIndex{i};
            ++i;
            char letter = m_string[i];
            bool addStyle;                                                                                               // add or remove text style
            sf::Uint32 style = m_text.getStyle();
            if(letter != '/') { addStyle = true; }
            else {
                    addStyle =  false;
                    ++i;
                    letter = m_string[i];
            }
            if(letter == 'r' || letter == 'b' || letter == 'i' || letter == 'u' || letter == 't') {
                if(m_string[i + 1] == ']') {
                    switch (letter) {
                        case 'r':                                                                                        // regular : remove all styles [r] or [/r]  only one is enough
                            m_text.setStyle(style& 0b00000000);
                            m_text.setCharacterSize(m_fontSize);
                            m_text.setFillColor(m_color);
                            break;
                        case 'b':                                                                                        // bold
                            if(addStyle) { m_text.setStyle(style | sf::Text::Bold); }
                            else { m_text.setStyle(style & 0b11111110); }
                            break;
                        case 'i':                                                                                        // italic
                            if(addStyle) { m_text.setStyle(style | sf::Text::Italic); }
                            else { m_text.setStyle(style & 0b11111101); }
                            break;
                        case 'u':                                                                                        // underlined
                            if(addStyle) { m_text.setStyle(style | sf::Text::Underlined); }
                            else { m_text.setStyle(style & 0b11111011); }
                            break;
                        case 't':                                                                                       // StrikeThrough
                            if(addStyle) { m_text.setStyle(style | sf::Text::StrikeThrough); }
                            else { m_text.setStyle(style & 0b11110111); }
                            break;
                        default:
                            break;
                    }
                    ++i;
                }
                else {
                    if(addStyle) {
                        displayChar(x, y , m_fontSize,m_string[i - 1]);
                        displayChar(x, y , m_fontSize,m_string[i]);
                    }
                    else {
                       for(unsigned int j = baliseStartIndex; j <= i; ++j) { displayChar(x, y , m_fontSize,m_string[j]);  }
                    }
                }
            }
            else {
                if(letter == 's' or letter == 'c') {
                    if(addStyle && (m_string[i + 1] == ']' || m_string[i + 2] == ']' || m_string[i + 3] == ']' || m_string[i + 4] == ']' )) {
                        std::string numberSize{""};
                        ++i;
                        int offset{0};
                        bool isNumericDigit{true};
                        unsigned int supposedSizeLength{0};
                        while(m_string[i + supposedSizeLength] != ']') { ++supposedSizeLength; }
                        while(m_string[i + offset] != ']' && offset < 3 && isNumericDigit && m_string[i + offset] != ']') {
                            if(std::isdigit(m_string[i + offset])) {
                                numberSize.push_back(m_string[i + offset]);
                                ++offset;
                            }
                            else { isNumericDigit = false; }
                        }
                        if(numberSize.size() == supposedSizeLength && supposedSizeLength > 0) {
                            unsigned int number = std::stoi(numberSize);
                            i += numberSize.size();
                            if(letter == 's') {                                                                         // font size
                                m_text.setCharacterSize(number);
                                y = oldY;
                                if(number > m_fontSize) { y -= (number - m_fontSize); std::cout << "number " << number << " offset Y " << number - m_fontSize << std::endl; }
                                else { y += (m_fontSize - number);}
                            }
                            else { if(number <= 28 && number >= 0) { m_text.setFillColor(selectColor(number)); }}                      // color
                        }
                        else {
                           for(unsigned int j = baliseStartIndex; j <= i; ++j) { displayChar(x, y , m_fontSize,m_string[j]);  }
                        }
                    }
                    else {
                        if(m_string[i + 1] == ']') {
                            if(letter == 's'){
                                y = oldY;
                                m_text.setCharacterSize(m_fontSize);
                            }
                            else { m_text.setFillColor(m_color); }
                            ++i;
                        }
                        else {
                            for(unsigned int j = baliseStartIndex; j <= i; ++j) { displayChar(x, y , m_fontSize,m_string[j]);  }
                        }
                    }
                }
                else {
                    std::string letters{"["};
                    if(!addStyle) { letters.push_back(m_string['/']); }
                    letters.push_back(m_string[i]);
                    m_text.setString(letters);
                    m_text.setPosition(x, y);
                    m_window.draw(m_text);
                    x +=  m_fontSize * (0.40 * letters.size());
                }
            }
       }
    }
}

sf::Color TTFtext::selectColor( int colorNb)
{
    switch (colorNb) {
        case static_cast<int>(TextColor::Black):                                                // 0
            return sf::Color::Black;
        case static_cast<int>(TextColor::LightBrown):                                           // 1
            return  static_cast<sf::Color>(0xE49467FF);
        case static_cast<int>(TextColor::Brown):                                                // 2
            return static_cast<sf::Color>(0xB97A56FF);
        case static_cast<int>(TextColor::DarkBrown):                                            // 3
            return static_cast<sf::Color>(0x805740FF);
        case static_cast<int>(TextColor::LightRed):                                             // 4
            return static_cast<sf::Color>(0xff343cFF);
        case static_cast<int>(TextColor::Red):                                                  // 5
            return static_cast<sf::Color>(0xe61a22FF);
        case static_cast<int>(TextColor::DarkRed):                                              // 6
            return static_cast<sf::Color>(0xeb1b21FF);
        case static_cast<int>(TextColor::LightPink):                                            // 7
            return static_cast<sf::Color>(0xffacc7FF);
        case static_cast<int>(TextColor::Pink):                                                 // 8
            return static_cast<sf::Color>(0xff8eb2FF);
        case static_cast<int>(TextColor::DarkPink):                                             // 9
            return static_cast<sf::Color>(0xff6496FF);
        case static_cast<int>(TextColor::LightOrange):                                          // 10
            return static_cast<sf::Color>(0xffa263FF);
        case static_cast<int>(TextColor::Orange):                                               // 11
            return static_cast<sf::Color>(0xff7f27FF);
        case static_cast<int>(TextColor::DarkOrange):                                           // 12
            return static_cast<sf::Color>(0xe67a2fFF);
        case static_cast<int>(TextColor::LightYellow):                                          // 13
            return static_cast<sf::Color>(0xfffbb0FF);
        case static_cast<int>(TextColor::Yellow):                                               // 14
            return static_cast<sf::Color>(0xfff200FF);
        case static_cast<int>(TextColor::DarkYellow):                                           // 15
            return static_cast<sf::Color>(0xd1c707FF);
        case static_cast<int>(TextColor::LightBlue):                                            // 16
            return static_cast<sf::Color>(0x4479ffFF);
        case static_cast<int>(TextColor::Blue):                                                 // 17
            return static_cast<sf::Color>(0x0048ffFF);
        case static_cast<int>(TextColor::DarkBlue):                                             // 18
            return static_cast<sf::Color>(0x0534abFF);
        case static_cast<int>(TextColor::LightGreen):                                           // 19
            return static_cast<sf::Color>(0x18df50FF);
        case static_cast<int>(TextColor::Green):                                                // 20
            return static_cast<sf::Color>(0x16b944FF);
        case static_cast<int>(TextColor::DarkGreen):                                            // 21
            return static_cast<sf::Color>(0x0a8b2eFF);
        case static_cast<int>(TextColor::LightPurple):                                          // 22
            return static_cast<sf::Color>(0xfb07ffFF);
        case static_cast<int>(TextColor::Purple):                                               // 23
            return static_cast<sf::Color>(0xcd2bcfFF) ;
        case static_cast<int>(TextColor::DarkPurple):                                           // 24
            return static_cast<sf::Color>(0xa120a3FF);
        case static_cast<int>(TextColor::LightGrey):                                            // 25
            return static_cast<sf::Color>(0xBBBBBBFF);
        case static_cast<int>(TextColor::Grey):                                                 // 26
            return static_cast<sf::Color>(0x999999FF);
        case static_cast<int>(TextColor::DarkGrey):                                             // 27
            return static_cast<sf::Color>(0x777777FF);
        case static_cast<int>(TextColor::White):                                                // 28
        default:
            return sf::Color::White;
    }
    return sf::Color::White;
}

void TTFtext::displaySimpleText(const float x, const float y)
{
    const sf::Vector2f position(x,y);
    m_text.setPosition(position);
    m_text.setString(m_string);
    m_window.draw(m_text);
std::cout << m_string << std::endl;
}

void TTFtext::displayChar(float& x, const float y, const int charSize, const char printedChar)
{
    m_text.setString(printedChar);
    m_text.setPosition(x, y);
    m_window.draw(m_text);
    x +=  m_text.getCharacterSize() * 0.4;
}

}
