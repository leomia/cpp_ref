#include <iostream>
#include <thread>

class ThreadDemo
{
private:
	typedef void(*FunctionPointer)(ThreadDemo*);
public:
	ThreadDemo();
	virtual ~ThreadDemo();
	static void thread_callback(ThreadDemo *pclass);
	bool _bThread;
	bool _CreateThread(FunctionPointer pfun);
	bool _EndThread();	
};

ThreadDemo::ThreadDemo()
{
}

ThreadDemo::~ThreadDemo()
{

}

void ThreadDemo::thread_callback(ThreadDemo *pclass)
{
	while (pclass->_bThread)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << "Thread callback function running." << std::endl;
	}
	return;
}

bool ThreadDemo::_CreateThread(FunctionPointer pfun)
{
	_bThread = true;
	std::thread t(pfun, this);
	t.detach();
	return true;
}

bool ThreadDemo::_EndThread()
{
	_bThread = false;
	return true;
}

int main() {
	ThreadDemo myclass;
	myclass._CreateThread(myclass.thread_callback);
	getchar();
	myclass._EndThread();
	getchar();
	return 0;
}