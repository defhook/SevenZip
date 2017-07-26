#pragma once
#include <functional>

namespace SevenZip
{

class SevenWorkerPool;
class SevenThread:public NonCopyable
{
public:
	enum ThreadState
	{
		THREAD_CREATE, // �������ڣ���δִ���߳���
		THREAD_SUSPEND, // �̱߳�����
		THREAD_RUNNING, // �߳�����ִ��
		THREAD_DEAD // �̱߳�����
	};
	explicit SevenThread(SevenWorkerPool* pool);
	~SevenThread(void);

	void Join();
	void Destroy(DWORD timeout = 0);
	DWORD GetThreadId() const {return m_id;}
	HANDLE GetThreadHandle() const {return m_hthread;}
	ThreadState GetThreadState() {return static_cast<ThreadState>(::InterlockedCompareExchange(&m_state, m_state, m_state));}

private:
	static DWORD WINAPI ThreadProc(_In_ LPVOID lpParameter);
	void run();

private:
	HANDLE m_hthread;
	DWORD m_id;
	SevenWorkerPool* m_pool;
	LONG m_state;
};

}