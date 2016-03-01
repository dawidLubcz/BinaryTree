#ifndef ILOGGER
#define ILOGGER

class ILogger
{
public:
    virtual void print(const char[] ...) = 0;
};

#endif // ILOGGER

