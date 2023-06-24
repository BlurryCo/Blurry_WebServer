/*  Version:1.0
    Author:LuoQiyu
    Date:2023-06-24 */
#include "Epoll.h"

#include <iostream>
using namespace std;

void Epoll::poll(std::vector<sp_Channel>& req){
    int event_count = 
        Epoll_wait(epollFd_, &*events_.begin(), events_.size(), EPOLLWAIT_TIME);
    for (int i = 0; i < event_count; ++i){
        int fd = events_[i].data.fd;
        sp_Channel temp = channelMap_[fd];
        temp->setRevents(events_[i].events);
        req.emplace_back(std::move(temp));
    }
    //LOG << "Epoll Finished"
}