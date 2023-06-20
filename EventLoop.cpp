/*  Version: 1.0
    Author: LuoQiYu
    Date:2023-06-20*/
#include "EventLoop.h"

#include <iostream>
using namespace std;

void EventLoop::Loop(){
    assert(!is_looping_);
    assert(is_in_loop_thread());
    is_looping_ = true;
    is_stop_ = false;

    while (!is_stop_)
    {
        //four steps
        auto ready_channels = poller_->Poll();
        is_event_handling_ = true;

        for (auto& channel : ready_channels){
            channel->HandleEvents();
        }
        is_event_handling_ = false;

        PerformPendingFunctions();
        
        poller_->HandleExpire();
    }
    is_looping_ = false;
    
}