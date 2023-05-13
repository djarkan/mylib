#include "animation.hpp"
#include <iostream>
#include "random/random.hpp"

namespace mylib
{

Animation::Animation()
{

}

Animation::Animation(const std::string& texturePathName, const sf::Vector2f& coord) :   m_frameRate{5}, m_currentFrame{0}, m_loop{true}, m_pause{false}, m_randomisedAnimation{false}, m_animationDurationflag{false},
                                                                                        m_delayedrestart{false}, m_state{State::stopped}
{
    m_textureAnimation.loadFromFile(texturePathName);
    move(coord);
    this->setFrameRate(m_frameRate);
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &m_textureAnimation;
    target.draw(m_frame, 4, sf::Quads, states);
}

void Animation::getTexture(const sf::Texture& texture)
{
    m_textureAnimation = texture;
}

void Animation::addFrame(const sf::IntRect& frame)
{
    m_frames.push_back(frame);
}

void Animation::play()
{
    m_pause = false;
    m_state = State::running;
    if(m_state == State::paused) {
        return;
    }
    m_animationSpeed.restartTimer();
    setFrame(m_currentFrame);
    if(m_animationDurationflag == true) {
        m_animationDuration.restartTimer();
    }
}

void Animation::animate()
{
    if(m_pause && !m_loop) {
        if(m_timeBeforeNextAnimation.isTimeElapsed()) {
            m_currentFrame = 0;
            setFrame(m_currentFrame);
            m_pause = false;
            if(m_animationDurationflag == true) {
                m_animationDuration.restartTimer();
            }
                m_animationSpeed.restartTimer();
       }
        return;
    }
    if(m_animationDuration.isTimeElapsed()) {
        stop();
        if(m_delayedrestart == true) { m_timeBeforeNextAnimation.restartTimer(); }
        return;
    }
    if(m_animationSpeed.isTimeElapsed()) {
        if(m_currentFrame == m_frames.size() - 1) {
            if(m_loop) {
                if(!m_randomisedAnimation) {
                        m_currentFrame = 0;
                        this->setFrame(m_currentFrame);
                        m_animationSpeed.restartTimer();
                }

                else {
                    mylib::Random<unsigned int> randomiser;
                    m_currentFrame = randomiser.randomNumber(0, m_frames.size() - 2);
                    this->setFrame(m_currentFrame);
                    m_animationSpeed.restartTimer();
                }
            }
            else {
                if(!m_animationDurationflag)
                {
                    stop();
                    if(m_delayedrestart == true) { m_timeBeforeNextAnimation.restartTimer(); }
                    else ;
                }
                else {
                    m_currentFrame = 0;
                    this->setFrame(m_currentFrame);
                    m_animationSpeed.restartTimer();
                }
            }
        }
        else {
            ++m_currentFrame;
            this->setFrame(m_currentFrame);
            m_animationSpeed.restartTimer();
        }
    }
}

void  Animation::pause()
{
    m_pause = true;
    m_state = State::paused;
}

void  Animation::stop()
{
    m_currentFrame = 0;
    setFrame(m_currentFrame);
    m_state = State::stopped;
    pause();
}

Animation::State Animation::getState()
{
    return m_state;
}

unsigned int Animation::getFrameRate()
{
    return m_frameRate;
}

void Animation::move(const sf::Vector2f& coords)
{
    this->setPosition(coords);
}

void Animation::setFrameRate(unsigned int framePerSecond)
{
    if(framePerSecond < 0) { framePerSecond = 1; }
    m_animationSpeed.setTimerDuration(static_cast<sf::Uint32>((1.f / static_cast<float>(framePerSecond)) * 1000.f));
}

void Animation::setFrame(unsigned int frame)
{
    float width = static_cast<float>(m_frames[frame].width);
    float heigth = static_cast<float>(m_frames[frame].height);

    m_frame[0].position = sf::Vector2f(0,0); //sf::Vector2f(LeftX, topY);
    m_frame[1].position = sf::Vector2f(width,0); //sf::Vector2f(RightX, topY);
    m_frame[2].position = sf::Vector2f(width,heigth); //sf::Vector2f(RightX, bottomY);
    m_frame[3].position = sf::Vector2f(0,heigth); //sf::Vector2f(LeftX, bottomY);

    float LeftX = static_cast<float>(m_frames[frame].left);
    float RightX = LeftX + width;
    float topY = static_cast<float>(m_frames[frame].top);
    float bottomY = topY + heigth;

    m_frame[0].texCoords = sf::Vector2f(LeftX, topY);
    m_frame[1].texCoords = sf::Vector2f(RightX, topY);
    m_frame[2].texCoords = sf::Vector2f(RightX, bottomY);
    m_frame[3].texCoords = sf::Vector2f(LeftX, bottomY);
}

void Animation::setColor(const sf::Color& color)
{
    m_frame[0].color = color;
    m_frame[1].color = color;
    m_frame[2].color = color;
    m_frame[3].color = color;
}

void Animation::setLoop(bool loop)
{
    m_loop = loop;
}

bool Animation::loadTexture(const std::string& texturePathName)
{
    return m_textureAnimation.loadFromFile("texturePathName");
}

void Animation::setRandomised(bool randomised)
{
        m_randomisedAnimation = randomised;
}

void Animation::setDuration(const sf::Int32& duration)
{
    m_animationDuration.setTimerDuration(duration);
    m_animationDuration.startTimer();
    m_animationDurationflag = true;
}

void Animation::setTimeBetweenAnimations(const sf::Int32& duration)
{
    m_timeBeforeNextAnimation.setTimerDuration(duration);
    m_delayedrestart = true;
}

}
