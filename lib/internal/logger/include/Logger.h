#ifndef PHYSICS_RENDERER_LOGGER_H
#define PHYSICS_RENDERER_LOGGER_H

#include <fstream>
#include <iostream>
#include <cstdarg>
#include <string>

namespace phyren {
    namespace logging {
        class Logger {
        public:
            /**
             * Logs a message
             * @param lMessage the message to be logged.
            */
            void LogMessage( const std::string& lMessage, bool print, std::string fileName);
            /**
             * Variable length Logger function
             * @param format lMessage to be logged.
             */
            void LogMessage(const char * format, bool print, std::string fileName,...);
            /**
             * << overloaded function to log a Message
             * @param lMessage to be logged.
             */
            Logger& operator<<(const std::string& lMessage);
            /**
             * Updates our file stream
             * @param newFile new file Name.
             */
            static void updateFilestream(std::string newFile);
            /**
             * Function to create the instance of our Logger class
             * @return singleton object of Logger class.
             */
             static Logger* GetLogger();

             static void disable();
        private:
            /**
             * Default constructor
             */
            Logger();
            /**
             * Copy constructor
             */
            Logger(const Logger&){};
            /**
             * assignment operator for the Logger class.
             */
            Logger& operator=(const Logger&){return *this; };
            /**
             * Log file name
             */
            static const std::string m_lFilename;
            /**
             * Singelton logger class object pointer.
             */
            static Logger* m_pThis;
            /**
             * Log file stream object.
             */
            static std::ofstream m_Logfile;

            static std::string currentFile;

            static bool logging;
        };
    }
}

#endif //PHYSICS_RENDERER_LOGGER_H
