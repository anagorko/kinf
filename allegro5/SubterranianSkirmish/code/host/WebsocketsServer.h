#ifndef WebsocketsServer_H
#define WebsocketsServer_H

#include <future>
using namespace std;

class WebsocketsServer
{
public:

    WebsocketsServer();
    ~WebsocketsServer();

    void start();
    void stop();

    static const int MAX_MESSAGE_QUEUE = 1024;

private:

    future<int> server_thread;
};

#endif // WebsocketsServer_H
