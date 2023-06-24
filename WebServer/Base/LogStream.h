/*  Version:1.0
    Author:LuoQiYu
    Date:2023-06-24 */
#include <vector>

//#include <iostream>
//this class is used to optimize <iostream>

using namespace std;

class LogStream : noncopyable
{
    typedef LogStream self;
private:
    template <typename T>
        void formatInteger T;
    Buffer buffer_;
    static const int kMaxNumbericSize = 32;
public:
    typedef FixedBuffer<kSmallBuffer> Buffer;

    self& operator<<(bool v){
        buffer_.append(v ? "1": "0", 1);
        return *this;
    
    self& operator<<(short);
    self& operator<<(unsigned short);
    self& operator<<(int);
    self& operator<<(unsigned int);
    self& operator<<(long);
    self& operator<<(unsigned long);
    self& operator<<(long long);
    self& operator<<(unsigned long long);

    self& operator<<(const void*);

    //float translate into string
    self& operator<<(float v){
        *this << static_cast<double>(v);
    }
    
    }
};




