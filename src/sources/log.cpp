#include <iostream>

class Log {
    public:
        enum Level {
            ERROR_LEVEL, WARNING_LEVEL, INFO_LEVEL
        };
    private:
        Level m_logLevel = INFO_LEVEL;


    public:
        void setLevel(Level level) {
            m_logLevel = level;
        }

        void warn(const char *warn) const {
            if (m_logLevel >= WARNING_LEVEL)
                std::cout << "[WARNING]: " << warn << "\n";
        }

        void error(const char *error) const {
            if (m_logLevel >= ERROR_LEVEL)
                std::cout << "[ERROR]: " << error << "\n";
        }

        void info(const char *info) const {
            if (m_logLevel >= INFO_LEVEL)
                std::cout << "[INFO]: " << info << "\n";
        }

        void println(const char *string) const {
            std::cout << string << "\n";
        }
};