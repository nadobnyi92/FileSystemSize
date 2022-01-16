#ifndef FSS_LOGGER_H
#define FSS_LOGGER_H

#include <cstddef>

#include <P7_Client.h>
#include <P7_Trace.h>

class Logger
{
public:
    Logger( const Logger& ) = delete;
    Logger& operator=( const Logger& ) = delete;
    Logger( Logger&& ) = delete;
    Logger& operator=( Logger&& ) = delete;

    ~Logger();

    static Logger& instance();

    void log( const char* message );

private:
    Logger();

private:
    IP7_Client* m_client;
    IP7_Trace* m_trace;
};

#endif //FSS_LOGGER_H
