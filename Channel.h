/*  Version:1.0
    Author:LuoQiYu
    Date:2023-06-21 */

#include <iostream>
using namespace std;

class Channel{
    public:
        typedef std::function<void()> EventCallBack;

        Channel();
        explicit Channel(int fd);
        ~Channel();

        void HandleEvents();  // EventLoop use this function to perform Channel action like write or read

        void HandleRead();

        void HandleWrite();

        void HandleUpdate();

        void HandleError();

        int get_fd();

        void set_fd(int fd);

        std::shared_ptr<http::HttpConnection> holder();
        void set_holder(std::shared_ptr<http::HttpConnection> holder);

        void set_read_handler(EventCallBack&& read_hander);

        void set_write_handler(EventCallBack&& write_hander);

        void set_update_handler(EventCallBack&& update_hander);

        void set_error_handler(EventCallBack&& error_hander);

        void set_revent(int revents);
        int& events();
        void set_events(int events);
        int last_events();
        bool update_last_events();
    private:
        int fd_;
        int events_;
        int revents_;
        int last_events_;

        std::weak_ptr<http::HttpConnection> holder_;

        EventCallBack read_hander_;
        EventCallBack write_hander_;
        EventCallBack update_hander_;
        EventCallBack error_hander_;       
};