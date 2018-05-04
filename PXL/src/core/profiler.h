#ifndef _PROFILER_H
#define _PROFILER_H


class Clock;
class Timer;

class Profiler {
  public:
     Profiler(Clock & clock);

     ~Profiler();

    Timer getTimer(const std::string & name);

    void addTimer(const std::string & name);

    void stopTimer(const std::string & name);

    void startTimer(const std::string & name);

    double getReport(const std::string & name);


  private:
    Clock * m_clock;

    Timer * m_timers;

};
#endif
