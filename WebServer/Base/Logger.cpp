/*  Version:1.0
    Author:LuoQiYu
    Date:2023-06-29 */
#include "Logger.h"
#include <vector>

Logger::Logger(const char* fileName, int line)
    : impl_(fileName, line) {}

Logger::~Logger(){
    impl_.stream_ << " -- " << impl_.basename_ << ':' << impl_.line_ << '\n';
    const LogStream::Buffer& buf(stream().buffer());
    output(buf.data(), buf.length());
}