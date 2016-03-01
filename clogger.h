#ifndef CLOGGER_H
#define CLOGGER_H

#include "ilogger.h"

class CLogger : public ILogger
{
public:
    CLogger();
    
    void print(char[] ...);
    
    ~CLogger();
};

#endif // CLOGGER_H
