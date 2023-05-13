#include "timer.hpp"

namespace mylib {

Timer::Timer() : inUse{false}
{
    m_pausedTimerDuration = 0;
}

Timer::Timer(sf::Int32 timerDuration) : m_timerDuration{timerDuration}, inUse{false}, m_pausedTimerDuration{0}
{

}

Timer::~Timer(){
}

void Timer::startTimer(){
    m_clock.restart();
    m_pausedTimerDuration = 0;
    inUse = true;
}

void Timer::restartTimer(){
    m_clock.restart();
    inUse = true;
}

bool Timer::isTimeElapsed(){
    sf::Time time = m_clock.getElapsedTime();
    sf::Int32 elapsedTime = time.asMilliseconds();
    if(elapsedTime + m_pausedTimerDuration > m_timerDuration  && inUse) {
        inUse = false;
        return true;
    }
    else { return false; }
}

void Timer::pauseTimer(){
    sf::Time time = m_clock.getElapsedTime();
    m_pausedTimerDuration = time.asMilliseconds();
}

void Timer::setTimerDuration(sf::Int32 timerDuration){
    m_timerDuration = timerDuration;
}

}
