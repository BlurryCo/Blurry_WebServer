/*  Version:1.0
    Author:LuoQiYu
    Date:2023-06-21 */
#include "Channel.h"

#include <iostream>
using namespace std;

void Channel::HandleEvents(){
    events_ = 0;
    // Trigger Suspend Event and No Trigger Read Event
    if ((revents_ & EPOLLHUP) && ! (revents_ & EPOLLIN)){
        events_ = 0;
        return;
    }
    // Trigger Error Event
    if (revents_ & EPOLLERR){
        HandleError();
        events_ = 0;
        return;
    }
    // Trigger Read/Write at high priority/Close Connnection Event
    if (revents_ & (EPOLLIN || EPOLLPRI || EPOLLRDHUP)){
        HandleRead();
    }
    // Trigger Write Event
    if (revents_ & EPOLLOUT){
        HandleWrite();
    }
    //Update
    HandleUpdate();
}