#ifndef _TIMER_H
#define _TIMER_H


class Clock;

class Timer {
  public:
     Timer(Clock & clock);

     ~Timer();

    void start();

    void stop();

    double report(double divisor);


  private:
    int m_calls;

    Clock * m_clock;

    double m_startTime;

    double m_totalTime;

};
#endif
