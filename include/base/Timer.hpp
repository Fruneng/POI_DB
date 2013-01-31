/*
 * Timer.hpp
 *
 *  Created on: 2013-1-30
 *      Author: viewin-cc
 */

#ifndef TIMEPERIOD_HPP_
#define TIMEPERIOD_HPP_
#include <sys/time.h>

struct Timer{
    public:
    struct timeval begin, end;
    Timer(){ gettimeofday(&begin, NULL); }
    void start(){ gettimeofday(&begin, NULL); }
    void finish(){ gettimeofday(&end, NULL); }
    friend inline std::ostream & operator<<(std::ostream &os, Timer &a){
        double use = 1000000 * (a.end.tv_sec - a.begin.tv_sec) + a.end.tv_usec - a.begin.tv_usec;
        use /= 1000000.0;
        os << use;
        return os;
    }
};

#endif /* TIMEPERIOD_HPP_ */
