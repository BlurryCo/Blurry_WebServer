/*  Version:1.0
    Author:LuoQiYu
    Date:2023-06-29 */

#include <vector>

class Logger {
public:
    Logger(const char* filename, int line);
    ~Logger();
    LogStream& stream() { return impl_.stream_;}

    static void setLogFileName(std::string fileNmae) { logFileName_ = fileName; }
    static std::string getLogFileName() { return logFileName_; }
private:
    class Impl  {
    public:
        Impl(const char* fileName, int line);
        void formatTime();

        LogStream stream_;
        int line_;
        std::string basename_;
    };
    Impl impl_;
    static std::string logFileName_;
};

#define LOG Logger(__FILE__, __LINE__).stream()