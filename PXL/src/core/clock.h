#ifndef _CLOCK_H
#define _CLOCK_H


class Clock {
  public:
     Clock();

     ~Clock();

    double getTime();


  private:
    std::chrono::steady_clock::time_point m_epoch;

};
#endif
