/*  Version:1.0
    Author:LuoQiYu
    Date:2023-06-24 */
#include <vector>
#include <cstring>

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
        return *this;
    }
    self& operator<<(double);

    self& operator<<(char v){
        buffer_.append(&v , 1);
        return *this;
    }

    //char* output buffer
    self& operator<<(const char* str){
        if(str){ buffer_.append(str,strlen(str))};
        else { buffer_.append("(null)",6)       };
        return *this;
    }
    self& operator<<(const unsigned char* str){
        return operator<<(reinterpret_cast<const char*>(str));
    }
    self& operator<<(const std::string& v){
        buffer_.append(v.c_str(),v.size());
        return *this;
    
    void append(const char* data, int len){ buffer_.append(data, lend)};
    const Buffer& buffer() const { return buffer_;}
    void resetBuffer(){ buffer_.reset();    }

    }

    
    }
};




