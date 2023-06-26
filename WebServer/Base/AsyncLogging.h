/*  Version:1.0
    Author:LuoQiYu
    Date:2023-06-27 */
#include "LogStream.h"
#include <vector>
//#include <iostream> do not user standard I/O, for we optimize in LogStream.h
class AsyncLogging : noncopyable{
public:
    AsyncLogging(const std::string basename, int flushInterval = 2);
    ~AsyncLogging(){
        if(running_)   
            stop();
    }
    void append(const char* logline, int len);
    void start();
    void stop();
private:
    typedef FixedBuffer<kLargeBuffer> Buffer;
    typedef std::vector<std::shared_ptr<Buffer>> BufferVector;
    typedef std::shared_ptr<Buffer> BufferPtr;

    void threadFunc();

    const int flushInterval_;   //Timeout Limit Time
    
    bool running_;

    const std::string basename_;

    Thread thread_;     //Background use a thread to write logs into files 

    MutexLock mutex_;

    Condition cond_;

    BufferPtr currentBuffer_;

    BufferPtr nextBuffer_;      //Double Buffer to cost down time

    BufferVector buffers_;      //the queue of Buffer

    CountDownLatch latch_;      //CountDown for Log System working
};