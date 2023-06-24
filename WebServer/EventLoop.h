/*  Version: 1.0 
    Author: LuoQiYu
    Date: 2023-06-19*/
#include <vector>
#include <functional>

#include <iostream>
using namespace std;

class EventLoop {
    public:
        typedef std::function<void()> Function;

        EventLoop();

        ~EventLoop();

        void Loop();

        void StopLoop();

        void RunInLoop(Function&& func);

        void QueneInLoop(Function&& func);

        void PollerAdd(std::shared_ptr<Channel> channel, int timeout = 0);

        void PollerMod(std::shared_ptr<Channel> channel, int timeout = 0);

        void PollerDel(std::shared_ptr<Channel> channel);

        void Shutdown(std::shared_ptr<Channel> channel);

        bool is_in_loop_thread();   //whether is in loop thread

    private:
        static int CreateEventfd();

        void HandleRead();

        void HanleUpdate();

        void WakeUp();

        void PerformPendingFunctions();
    
    private:
        std::shared_ptr<Poller> poller_;
        
        int event_fd_;

        std::shared_ptr<Channel> wakeup_channel_;

        pid_t thread_id_;

        mutable locker::MutexLock mutex_;

        std::vector<Function> pending_functions_;

        bool is_stop_;
        bool is_looping_;
        bool is_event_handling_;
        bool is_calling_pending_functions_;
};




}