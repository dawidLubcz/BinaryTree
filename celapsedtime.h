#ifndef CELAPSEDTIME_H
#define CELAPSEDTIME_H

#include "ilogger.h"
#include <ctime>

class CElapsedTime
{
private:
    clock_t m_oClock;
    ILogger* m_pLogger;
public:
    CElapsedTime(ILogger* a_pLogger) 
    {
        if(0 != a_pLogger)m_pLogger = a_pLogger;
        m_oClock = clock(); 
    }
    ~CElapsedTime()
    { 
        m_pLogger->print("Elapsed time: %d", double(clock() - m_oClock));
    }
};
#endif // CELAPSEDTIME_H
