#include "text/TTFtext/ttftext.hpp"

namespace mylib
{

TTFText::TTFText(sf::RenderWindow& window):  m_window{window}
{

}

TTFText::TTFText(const std::string& text, const std::string& fontName, unsigned int fontSize, TextColor color, sf::RenderWindow& window) :  m_string{text}, m_fontSize{fontSize}, m_color{color}, m_outlineColor{TextColor::White},
                                                                                                                                            m_outlineThickness{0}, m_coords(0, 0), m_window{window}
{
    m_font.loadFromFile(fontName);
    m_text.setFont(m_font);
}

bool TTFText::setFont(const std::string& fontName)
{
    bool fontOK = m_font.loadFromFile(fontName);
    m_text.setFont(m_font);
    return fontOK;
}

void TTFText::setText(const std::string& text)
{
    m_string = text;
}

void TTFText::setCharacterSize(const unsigned int charSize)
{
    m_text.setCharacterSize(charSize);
    m_fontSize = charSize;
}

void TTFText::setColor(const TextColor color)
{
    m_text.setFillColor(convertEnumColorToSfmlColor(color));
    m_color = color;
}

void TTFText::setOutlineColor(const TextColor color)
{
    m_text.setOutlineColor(convertEnumColorToSfmlColor(color));
    m_outlineColor = color;
}

void TTFText::setOutlineTickness(float thickness)
{
    m_text.setOutlineThickness(thickness);
    m_outlineThickness = thickness;
}

void TTFText::setPosition(const float x, const float y)
{
    m_text.setPosition(x, y);
    m_coords.x = x;
    m_coords.y = y;
}

void TTFText::setPosition(const sf::Vector2f& coords)
{
    m_text.setPosition(coords);
    setPosition(coords.x, coords.y);
}

const std::string& TTFText::getText() const
{
    return m_string;
}

unsigned int TTFText::getCharacterSize() const
{
    return m_fontSize;
}

mylib::TTFText::TextColor TTFText::getColor() const
{
    return m_color;
}

mylib::TTFText::TextColor TTFText::getOutlineColor() const
{
    return m_outlineColor;
}

float TTFText::getOutlineTickness() const
{
    return m_outlineThickness;
}

const sf::Vector2f TTFText::getPosition() const
{
    return m_coords;
}

void TTFText::displayEnrichedText(float x, float y)
{
    float oldx = x;
    float oldY = y;
    unsigned int firstCharSizeLine{m_fontSize};
    m_text.setPosition(x, y);
    m_text.setStyle(sf::Text::Regular);
    for(unsigned int i = 0; i < m_string.size(); ++i) {
        if(m_string[i] != '[') {
            if(m_string[i] == '\n') {
                x = oldx;
                y += m_text.getCharacterSize() + 4;
                oldY = y;
                firstCharSizeLine = m_text.getCharacterSize();
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
            if(letter == 'r' || letter == 'b' || letter == 'i' || letter == 'u' || letter == 't' || letter == 'o') {
                if(m_string[i + 1] == ']') {
                    switch (letter) {
                        case 'r':
                            m_text.setStyle(style& 0b00000000);                                                         // regular : remove all styles. [r] or [/r] are equals
                            if(m_text.getCharacterSize() > m_fontSize) { y = oldY + firstCharSizeLine - m_fontSize; }
                            else { y = oldY + firstCharSizeLine - m_fontSize; }
                            m_text.setCharacterSize(m_fontSize);
                            m_text.setFillColor(convertEnumColorToSfmlColor(m_color));
                            m_text.setOutlineThickness(0);
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
                        case 'o':
                            if(addStyle) { m_text.setOutlineThickness(m_outlineThickness); }
                            else { m_text.setOutlineThickness(0); }
                        default:
                            break;
                    }
                    ++i;
                }
                else {
                    if(addStyle) {                                                                                      // bad balise
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
                            if(letter == 's') {                                                                             // [s]
                                m_text.setCharacterSize(number);
                                y = oldY;
                                if(number > firstCharSizeLine) { y -= (number - firstCharSizeLine); }
                                else { y += (firstCharSizeLine - number);}
                            }
                            else { if(number <= 28 && number >= 0) { m_text.setFillColor(convertEnumColorToSfmlColor(static_cast<TextColor>(number))); }}  // [c]
                        }
                        else {
                           for(unsigned int j = baliseStartIndex; j <= i; ++j) { displayChar(x, y , m_fontSize,m_string[j]);  }
                        }
                    }
                    else {
                        if(m_string[i + 1] == ']') {
                            if(letter == 's'){                                                                              // [/s]
                                y = oldY;
                                if(m_fontSize > firstCharSizeLine) { y -= (m_fontSize - firstCharSizeLine); }
                                else { y += (firstCharSizeLine - m_fontSize);}
                                m_text.setCharacterSize(m_fontSize);
                            }
                            else { m_text.setFillColor(convertEnumColorToSfmlColor(m_color)); }                                             // [/c]
                            ++i;
                        }
                        else {                                                                                              // bad balise
                            for(unsigned int j = baliseStartIndex; j <= i; ++j) { displayChar(x, y , m_fontSize,m_string[j]);  }
                        }
                    }
                }
                else {                                                                                                      // bad balise
                    std::string letters{"["};
                    if(!addStyle) { letters.push_back(m_string['/']); }
                    letters.push_back(m_string[i]);
                    m_text.setString(letters);
                    m_text.setPosition(x, y);
                    m_window.draw(m_text);
                    x +=  m_fontSize * (0.45 * letters.size());
                }
            }
       }
    }
}

void TTFText::displayEnrichedText()
{
    displayEnrichedText(m_coords.x, m_coords.y);
}

void TTFText::displaySimpleText(const float x, const float y)
{
    m_text.setPosition(x, y);
    m_text.setString(m_string);
    m_window.draw(m_text);
}

void TTFText::displaySimpleText()
{
    displaySimpleText(m_coords.x, m_coords.y);
}

sf::Color TTFText::convertEnumColorToSfmlColor(TextColor colorNb)
{
    switch (colorNb) {
        case TextColor::Black:                                                // 0
            return sf::Color::Black;
        case TextColor::LightBrown:                                           // 1
            return  sf::Color(0xE49467FF);
        case TextColor::Brown:                                                // 2
            return sf::Color(0xB97A56FF);
        case TextColor::DarkBrown:                                            // 3
            return sf::Color(0x805740FF);
        case TextColor::LightRed:                                             // 4
            return sf::Color(0xff343cFF);
        case TextColor::Red:                                                  // 5
            return sf::Color(0xe61a22FF);
        case TextColor::DarkRed:                                              // 6
            return sf::Color(0xeb1b21FF);
        case TextColor::LightPink:                                            // 7
            return sf::Color(0xffacc7FF);
        case TextColor::Pink:                                                 // 8
            return sf::Color(0xff8eb2FF);
        case TextColor::DarkPink:                                             // 9
            return sf::Color(0xff6496FF);
        case TextColor::LightOrange:                                          // 10
            return sf::Color(0xffa263FF);
        case TextColor::Orange:                                               // 11
            return sf::Color(0xff7f27FF);
        case TextColor::DarkOrange:                                           // 12
            return sf::Color(0xe67a2fFF);
        case TextColor::LightYellow:                                          // 13
            return sf::Color(0xfffbb0FF);
        case TextColor::Yellow:                                               // 14
            return sf::Color(0xfff200FF);
        case TextColor::DarkYellow:                                           // 15
            return sf::Color(0xd1c707FF);
        case TextColor::LightBlue:                                            // 16
            return sf::Color(0x4479ffFF);
        case TextColor::Blue:                                                 // 17
            return sf::Color(0x0048ffFF);
        case TextColor::DarkBlue:                                             // 18
            return sf::Color(0x0534abFF);
        case TextColor::LightGreen:                                           // 19
            return sf::Color(0x18df50FF);
        case TextColor::Green:                                                // 20
            return sf::Color(0x16b944FF);
        case TextColor::DarkGreen:                                            // 21
            return sf::Color(0x0a8b2eFF);
        case TextColor::LightPurple:                                          // 22
            return sf::Color(0xfb07ffFF);
        case TextColor::Purple:                                               // 23
            return sf::Color(0xcd2bcfFF) ;
        case TextColor::DarkPurple:                                           // 24
            return sf::Color(0xa120a3FF);
        case TextColor::LightGrey:                                            // 25
            return sf::Color(0xBBBBBBFF);
        case TextColor::Grey:                                                 // 26
            return sf::Color(0x999999FF);
        case TextColor::DarkGrey:                                             // 27
            return sf::Color(0x777777FF);
        case TextColor::White:                                                // 28
        default:
            return sf::Color::White;
    }
    return sf::Color::White;
}

void TTFText::displayChar(float& x, const float y, const int charSize, const char printedChar)
{
    m_text.setString(printedChar);
    m_text.setPosition(x, y);
    m_window.draw(m_text);
    x +=  m_text.getCharacterSize()* 0.45;
}

}
