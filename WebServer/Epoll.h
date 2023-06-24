/*  Version:1.0
    Author:LuoQiYu
    Date:2023-06-24*/
#include <vector>

#include <iostream>
using namespace std;

class Epoll{
    public:
        Epoll();
        ~Epoll();

        void epoll_add(const sp_Channel& request);

        void epoll_mod(const sp_Channel& request);
        
        void epoll_del(const sp_Channel& request);

        void poll(std::vector<sp_Channel>& req);
    private:
        int epollFd_;
        std::vector<epoll_event>event_;    //contain epoll_wait() active events
        std::unordered_map<int,sp_Channel> channelMap_;     //fd -> Channel
}

