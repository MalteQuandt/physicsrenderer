//
// Created by tristan on 6/5/2022.
//

#include <Logger.h>
#include <Utilities.h>

using namespace phyren::logging;
using namespace std;



Logger::Logger() {
    m_Logfile.open(m_lFilename.c_str(), ios::out | ios::app);
}

Logger* Logger::GetLogger() {
    static Logger logger{};
    return &logger;
}

void Logger::_LogMessage(const string& lMessage, bool print, string fileName){
    if(fileName.empty()) {
        fileName = "Log";
    }
    if(print) {
        updateFilestream(fileName);
        m_Logfile << "\n" << Util::CurrentDateTime() << ":\t";
        m_Logfile << lMessage << "\n";
    }
    cout << Util::CurrentDateTime() << ":\t" ;
    cout << lMessage << "\n" ;
}

Logger& Logger::operator<<(const string &lMessage) {
    cout << Util::CurrentDateTime() << ":\t" ;
    cout << lMessage << "\n" ;
    return *this;
}

void Logger::updateFilestream(const string& newFile) {
    if(newFile == currentFile) {
        m_Logfile.close();
        m_Logfile.open((newFile + ".txt").c_str(), ios::out | ios::app);
        currentFile = newFile;
    }
}

void Logger::disable() {
    logging = false;
}

void Logger::enable() {logging = true;}
void Logger::toggle() {logging =! logging;}
void Logger::setEnabled(bool enable) {logging = enable;}