#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <string>
#include <vector>
#include"timer/timer.hpp"


namespace mylib
{

class Animation : public sf::Drawable, public sf::Transformable
{
    public :
        enum class                                  State{stopped = 0, paused, running};
                                                    Animation();
                                                    Animation(const std::string& texturePathName, const sf::Vector2f& coord);
        bool                                        loadTexture(const std::string& texturePathName);
        void                                        getTexture(const sf::Texture& texture);
        void                                        addFrame(const sf::IntRect& frame);
        void                                        setFrame(unsigned int frame);
        void                                        move(const sf::Vector2f& coords);
        void                                        play();
        void                                        animate();
        void                                        pause();
        void                                        stop();
        State                                       getState();
        unsigned int                                getFrameRate();
        void                                        setColor(const sf::Color& color);
        void                                        setFrameRate(unsigned int framePerSecond);
        void                                        setLoop(bool loop);
        void                                        setRandomised(bool randomised);
        void                                        setDuration(const sf::Int32& duration);
        void                                        setTimeBetweenAnimations(const sf::Int32& duration);

    private :
        sf::Vertex                                  m_frame[4];
        std::vector<sf::IntRect>                    m_frames;
        unsigned int                                m_frameRate;
        unsigned int                                m_currentFrame;
        sf::Texture                                 m_textureAnimation;
        sf::Vector2f                                m_textureCoord;
        bool                                        m_loop;
        bool                                        m_pause;
        bool                                        m_randomisedAnimation;
        mylib::Timer                                m_animationSpeed;
        bool                                        m_animationDurationflag;
        mylib::Timer                                m_animationDuration;
        bool                                        m_delayedrestart;
        mylib::Timer                                m_timeBeforeNextAnimation;
        State                                       m_state;

        virtual void                                draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

}
#endif // ANIMATION_HPP
