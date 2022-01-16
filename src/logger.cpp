#include "logger.h"

Logger::Logger()
{
     m_client = P7_Create_Client( TM( "/P7.Sink=FileTxt" ) );
     m_trace = P7_Create_Trace( m_client, TM( "Test" ) );
}

Logger::~Logger()
{
    m_client->Release();
}

Logger& Logger::instance()
{
    static Logger logger;
    return logger;
}

void Logger::log( const char* message )
{
    m_trace->P7_WARNING( 0, TM( message ) );
}

