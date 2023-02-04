#pragma once
#include "iostream"

using std::string;

class Log {
    public:
        enum Level {
            ERROR_LEVEL, WARNING_LEVEL, INFO_LEVEL
        };
    private:
        static Level m_logLevel;
        static const string RESET;
        static const string YELLOW;
        static const string GREEN;
        static const string BLUE;
        static const string RED;
        static const string CYAN;


    public:
        static void setLevel(Level level);

        static void warn(string warn);

        static void error(string error);

        static void info(string info);

        static void println(string normal_string);
};