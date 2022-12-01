#include "timetracer.hpp"
#include "omp.h"

using namespace TracerLib;

//=============================================================================================================
// DEFINE STATIC MEMBER VARIABLES
//=============================================================================================================

static const char* defaultTracerFileName("default_TimeTracer_file.json");
bool TimeTracer::ms_bIsEnabled(false);
std::ofstream TimeTracer::ms_OutputFileStream;
bool TimeTracer::ms_bIsFirstEvent(true);
std::mutex TimeTracer::ms_outFileMutex;
long long TimeTracer::ms_iZeroTime(0);

//=============================================================================================================
// DEFINE MEMBER METHODS
//=============================================================================================================

TimeTracer::TimeTracer(const std::string &file, const std::string &function, int lineNumber)
: m_bIsInitialized(false)
, m_bPrintToTerminal(false)
, m_sFileName(file)
, m_sFunctionName(function)
, m_iLineNumber(lineNumber)
, m_iThreadId("0")
, m_iBeginTime(0)
, m_iEndTime(0)
, m_dDurationMillis(0.)
{
    if (ms_bIsEnabled)
    {
        initialize();
        writeBeginEvent();
    }
}

//=============================================================================================================

TimeTracer::~TimeTracer()
{
    if (ms_bIsEnabled && m_bIsInitialized)
    {
        registerFinalTime();
        writeEndEvent();
        if (m_bPrintToTerminal)
        {
            calculateDuration();
            printDurationMiliSec();
        }
    }
}

//=============================================================================================================

void TimeTracer::enable(const std::string &jsonFileName)
{
    ms_OutputFileStream.open(jsonFileName);
    writeHeader();
    setZeroTime();
    if (ms_OutputFileStream.is_open())
    {
        ms_bIsEnabled = true;
    }
}

//=============================================================================================================

void TimeTracer::enable()
{
    enable(defaultTracerFileName);
}

//=============================================================================================================

void TimeTracer::disable()
{
    if (ms_bIsEnabled)
    {
        writeFooter();
        ms_OutputFileStream.flush();
        ms_OutputFileStream.close();
        ms_bIsEnabled = false;
    }
}

//=============================================================================================================

void TimeTracer::start(const std::string &jsonFileName)
{
    enable(jsonFileName);
}

//=============================================================================================================

void TimeTracer::start()
{
    enable();
}

//=============================================================================================================

void TimeTracer::stop()
{
    disable();
}

//=============================================================================================================

void TimeTracer::traceQuantity(const std::string &name, long val)
{
    long long timeNow = getTimeNow() - ms_iZeroTime;
    std::string s;
    s.append("{\"name\":\"").append(name).append("\",\"ph\":\"C\",\"ts\":");
    s.append(std::to_string(timeNow)).append(",\"pid\":1,\"tid\":1");
    s.append(",\"args\":{\"").append(name).append("\":").append(std::to_string(val)).append("}}\n");
    writeToFile(s);
}

//=============================================================================================================

void TimeTracer::initialize()
{
    registerConstructionTime();
    registerThreadId();
    formatFileName();
    m_bIsInitialized = true;
}

//=============================================================================================================

void TimeTracer::setZeroTime()
{
    ms_iZeroTime = getTimeNow();
}

//=============================================================================================================

void TimeTracer::registerConstructionTime()
{
    m_iBeginTime = getTimeNow() - ms_iZeroTime;
}

//=============================================================================================================

void TimeTracer::registerFinalTime()
{
    m_iEndTime = getTimeNow() - ms_iZeroTime;
}

//=============================================================================================================

long long TimeTracer::getTimeNow()
{
    auto timeNow = std::chrono::high_resolution_clock::now();
    return std::chrono::time_point_cast<std::chrono::microseconds>(timeNow).time_since_epoch().count();
}

//=============================================================================================================

void TimeTracer::registerThreadId()
{
    auto longId = std::hash<std::thread::id>()(std::this_thread::get_id());
    // int longId = omp_get_thread_num();
    m_iThreadId = std::to_string(longId).substr(0, 5);
}

//=============================================================================================================

void TimeTracer::formatFunctionName()
{
    const char* pattern(" __cdecl");
    const int patternLength(8);
    size_t pos = m_sFunctionName.find(pattern);
    if (pos != std::string::npos) {
        m_sFunctionName.replace(pos, patternLength, "");
    }
}

//=============================================================================================================

void TimeTracer::formatFileName()
{
    const char* patternIn("\\");
    const char* patternOut("\\\\");
    const int patternOutLength(4);
    size_t start_pos = 0;
    while ((start_pos = m_sFileName.find(patternIn, start_pos)) != std::string::npos)
    {
        m_sFileName.replace(start_pos, 1, patternOut);
        start_pos += patternOutLength;
    }
}

//=============================================================================================================

void TimeTracer::calculateDuration()
{
    m_dDurationMillis = (m_iEndTime - m_iBeginTime) * 0.001;
}

//=============================================================================================================

void TimeTracer::printDurationMiliSec()
{
    std::cout << "Scope: " << m_sFileName << " - " << m_sFunctionName << " DurationMs: " << m_dDurationMillis << "ms.\n";
}

//=============================================================================================================

void TimeTracer::writeHeader()
{
    writeToFile("{\"displayTimeUnit\": \"ms\",\"traceEvents\":[\n");
}

//=============================================================================================================

void TimeTracer::writeFooter()
{
    writeToFile("]}");
}

//=============================================================================================================

void TimeTracer::writeToFile(const std::string& str)
{
    ms_outFileMutex.lock();
    if(ms_OutputFileStream.is_open()) {
        ms_OutputFileStream << str;
    }
    ms_outFileMutex.unlock();
}

//=============================================================================================================

void TimeTracer::writeBeginEvent()
{
    std::string s;
    if (!ms_bIsFirstEvent)
        s.append(",");

    s.append("{\"name\":\"").append(m_sFunctionName).append("\",\"cat\":\"bst\",");
    s.append("\"ph\":\"B\",\"ts\":").append(std::to_string(m_iBeginTime)).append(",\"pid\":1,\"tid\":");
    s.append(m_iThreadId).append(",\"args\":{\"file path\":\"").append(m_sFileName).append("\",\"line number\":");
    s.append(std::to_string(m_iLineNumber)).append("}}\n");
    writeToFile(s);
    ms_bIsFirstEvent = false;
}

//=============================================================================================================

void TimeTracer::writeEndEvent()
{
    std::string s;
    s.append(",{\"name\":\"").append(m_sFunctionName).append("\",\"cat\":\"bst\",");
    s.append("\"ph\":\"E\",\"ts\":").append(std::to_string(m_iEndTime)).append(",\"pid\":1,\"tid\":");
    s.append(m_iThreadId).append(",\"args\":{\"file path\":\"").append(m_sFileName).append("\",\"line number\":");
    s.append(std::to_string(m_iLineNumber)).append("}}\n");
    writeToFile(s);
    
}

//=============================================================================================================

bool TimeTracer::printToTerminalIsSet()
{
    return m_bPrintToTerminal;
}

//=============================================================================================================

void TimeTracer::setPrintToTerminal(bool s)
{
    m_bPrintToTerminal = s;
}

