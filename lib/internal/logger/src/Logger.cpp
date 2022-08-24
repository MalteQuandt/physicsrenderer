//
// Created by malte on 6/5/2022.
//

#include "../include/Logger.h"
#include "../include/Utilities.h"

using namespace phyren::logging;

const std::string Logger::m_lFilename {"Log.txt"};
std::string Logger::currentFile{"Log"};
bool Logger::logging{true};
Logger* Logger::m_pThis{NULL};
std::ofstream Logger::m_Logfile;
Logger::Logger() {
}
Logger* Logger::GetLogger() {
    if(NULL == m_pThis){
        m_pThis = new Logger();
        m_Logfile.open(m_lFilename.c_str(), std::ios::out | std::ios::app);
    }
    return m_pThis;
}

void Logger::LogMessage(const char * format, bool const print, std::string fileName,...){
    if(!logging){
        return;
    }
    if(!fileName.compare("")){
        fileName = "Log";
    }
    char* lMessage {NULL};
    int nLength{0};
    va_list args;
    va_start(args, format);
    nLength = _vscprintf(format, args) + 1;
    lMessage = new char[nLength];
    vsprintf_s(lMessage, nLength, format, args);
    if(print) {
        updateFilestream(fileName);
        m_Logfile << Util::CurrentDateTime() << ":\t";
        m_Logfile << lMessage << "\n";
    }
    va_end(args);
    std::cout << Util::CurrentDateTime() << ":\t" ;
    std::cout << lMessage << "\n" ;

    delete [] lMessage;
}

void Logger::LogMessage(const std::string& lMessage, bool print, std::string fileName){
    if(!logging){
        return;
    }
    if(!fileName.compare("")){
        fileName = "Log";
    }
    if(print) {
        updateFilestream(fileName);
        m_Logfile << "\n" << Util::CurrentDateTime() << ":\t";
        m_Logfile << lMessage << "\n";
    }
    std::cout << Util::CurrentDateTime() << ":\t" ;
    std::cout << lMessage << "\n" ;
}

Logger& Logger::operator<<(const std::string &lMessage) {
    m_Logfile << "\n" << Util::CurrentDateTime() << ":\t";
    m_Logfile << lMessage << "\n";
    std::cout << Util::CurrentDateTime() << ":\t" ;
    std::cout << lMessage << "\n" ;
    return *this;
}

void Logger::updateFilestream(std::string newFile) {
    if(newFile.compare(currentFile)) {
        m_pThis->m_Logfile.close();
        m_pThis->m_Logfile.open((newFile + ".txt").c_str(), std::ios::out | std::ios::app);
        currentFile = newFile;
    }
}

void Logger::disable() {
    logging = false;
}