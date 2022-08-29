#pragma once

#include <fstream>
#include <iostream>
#include <cstdarg>
#include <string>
#include <memory>

namespace phyren {
    namespace logging {
        /**
         * Logger class that can be either used as a Singleton, or
         */
        class Logger {
        public:

             /**
             * Generate a non-singleton logger instance
             */
            Logger();

            /**
             * @brief   Logs a message.
             *          If the logger is disabled, turn the logging into a noop
             *
             * @param   lMessage the message to be logged.
            */
            inline void LogMessage(const std::string& lMessage, bool print, std::string fileName) {
                if(logging) {
                    _LogMessage(lMessage, print, fileName);
                }
            }

            /**
             * << overloaded function to log a Message
             * @param lMessage to be logged.
             */
            Logger& operator<<(const std::string& lMessage);
            /**
             * Updates our file stream
             * @param newFile new file Name.
             */
            void updateFilestream(const std::string& newFile);
            /**
             * Get the singleton logger instance, or create it if that has not happened yet.
             *
             * @return singleton object of Logger class.
             */
             static Logger* GetLogger();

             /**
              * Generate a new logger instance that is not singleton-bound.
              *
              * @return a unique pointer to a logger instance
              */
             static std::unique_ptr<Logger> createLogger();

             /** Disable logging for the currently bound logger. */
             void disable();
             /** enable logging for the currently bound logger. */
             void enable();
             /** toggle logging for the currently bound logger. */
             void toggle();
             /**
              * @brief  Set the logging according to the parameter.
              *
              * @param  enable if the logger should be enabled or not
              */
             void setEnabled(bool enable);

        private:
            const std::string m_lFilename {"Log.txt"};
            std::string currentFile{"Log"};
            bool logging{true};
            std::ofstream m_Logfile;

            /**
             * Logs a message
             * @param lMessage the message to be logged.
            */
            void _LogMessage( const std::string& lMessage, bool print, std::string fileName);

            // Delete the rule of 5
            Logger(const Logger&)= delete;
            Logger(Logger&&) = delete;

            Logger& operator=(const Logger&) = delete;
            Logger& operator=(Logger&&) = delete;

        };
    }
}