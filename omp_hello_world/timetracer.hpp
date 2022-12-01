
#ifndef TRACERLIB_TRACER_H
#define TRACERLIB_TRACER_H

#ifdef TRACE
#define GET_MACRO(_0, _1, _2, NAME, ...) NAME
#define TIME_TRACE(...) GET_MACRO(_0, ##__VA_ARGS__, TIME_TRACE_2, TIME_TRACE_1, TIME_TRACE_0)(__VA_ARGS__)
#define TIME_TRACE_0() TracerLib::TimeTracer _TimeTracer__LINE__(__FILE__,__func__,__LINE__)
#define TIME_TRACE_1(STRING_TAG) TracerLib::TimeTracer _TimeTracer__LINE__(__FILE__,STRING_TAG,__LINE__)
#define TIME_TRACER_ENABLE(FILENAME) TracerLib::TimeTracer::enable(FILENAME)
#define TIME_TRACER_DISABLE TracerLib::TimeTracer::disable()
#define TIME_TRACE_VALUE(NAME, VALUE) TracerLib::TimeTracer::traceQuantity(NAME, VALUE)
#else
#define TIME_TRACE()
#define TIME_TRACE(STRING_TAG) 
#define TIME_TRACER_ENABLE(FILENAME)
#define TIME_TRACER_DISABLE
#define TIME_TRACE_VALUE()
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>

namespace TracerLib
{

class TimeTracer {
public:
    TimeTracer(const std::string& file, const std::string& function, int lineNumber);
    ~TimeTracer();
    static void enable(const std::string& jsonFileName);
    static void enable();
    static void disable();
    static void start(const std::string& jsonFileName);
    static void start();
    static void stop();
    static void traceQuantity(const std::string& name, long val);
    bool printToTerminalIsSet();
    void setPrintToTerminal(bool s);
private:
    static void writeHeader();
    static void writeFooter();
    static void writeToFile(const std::string& str);
    static void setZeroTime();
    static long long getTimeNow();
    void initialize();
    void formatFileName();
    void formatFunctionName();
    void registerConstructionTime();
    void registerFinalTime();
    void registerThreadId();
    void calculateDuration();
    void printDurationMiliSec();
    void writeBeginEvent();
    void writeEndEvent();

    static bool ms_bIsEnabled;                  /**< Bool variable to store if the "class" (ie. the TimeTracer) has been enabled. */
    static std::ofstream ms_OutputFileStream;   /**< Output file stream to write results. */
    static bool ms_bIsFirstEvent;               /**< Bool variable to check if this is the first event to be written to the file. */
    static std::mutex ms_outFileMutex;          /**< Mutex to guard the writing to file between threads. */
    static long long ms_iZeroTime;              /**< Integer value to store the origin-time (ie the Zero time) from which all other time measurements will depend. */

    bool m_bIsInitialized;          /**< Store if this object has been initialized properly. */
    bool m_bPrintToTerminal;        /**< Store if it is needed from this TimeTracer object. to print to terminal too. */
    std::string m_sFileName;        /**< String to store the code file name where the TimeTracer obj is instantiated. */
    std::string m_sFunctionName;    /**< String to store the function name. */
    int m_iLineNumber;              /**< The line number within the code file where the TimeTracer obj is instantiated. */
    std::string m_iThreadId;        /**< A string identifier for the thread id in which the TimeTracer obj is instantiated. */
    long long m_iBeginTime;         /**< The time when the tracer TimeTracer obj is created. */
    long long m_iEndTime;           /**< The time when the tracer TimeTracer obj is destructed. */
    double m_dDurationMillis;        /**< The time difference between TimeTracer object creation and destruction in in milli seconds. */

}; // TimeTracer

} // namespace TRACERLIB

#endif //if TRACERLIB_TRACER_H defined
