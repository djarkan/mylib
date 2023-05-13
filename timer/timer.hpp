#ifndef TIMER_H
#define TIMER_H

#include <SFML/Graphics.hpp>

namespace mylib {

class Timer
{
    public:
                                        Timer();
                                        Timer(sf::Int32 timerDuration);
        ~Timer();
        void                            startTimer();
        void                            restartTimer();
        void                            pauseTimer();
        bool                            isTimeElapsed();
        void                            setTimerDuration(sf::Int32 timerDuration);

        sf::Int32 m_timerDuration;

    private:
        bool                            inUse;
        sf::Clock                       m_clock;
        sf::Int32                       m_pausedTimerDuration;
};

}

#endif // TIMER_H
