
#ifndef TIMER_H
#define TIMER_H
#include <functional>
#include <map>
#include <vector>
#include <time.h>

#define  NowTime  (int64_t)time(0)

typedef std::function<void()> Functional;

struct Timer
{ 	
	Timer(Functional fp, int32_t count, int32_t nloop,int32_t nInterval) : m_fp(fp), m_count(count), m_nLoop(nloop), m_Interval(nInterval)
	{

	}

	~Timer()
	{

	}
	
	int32_t m_count;
	Functional m_fp;
	int32_t m_nLoop;
	uint32_t m_Interval;
};

class TimerManager
{
	TimerManager();

	~TimerManager();

public:

	static TimerManager* GetInstancePtr();

	void checkTimer();

	void checkTimer(uint64_t curtime);

	void addTimer(uint64_t startTime, Functional fp, int32_t nCount = -1, int32_t nloop = 1, int32_t nInterval = 1);

private:

	std::map<uint64_t, std::vector<Timer>>m_TimerMap;
	
};


#endif 
