#include "timer.h"


TimerManager::TimerManager()
{

}

TimerManager::~TimerManager()
{

}

TimerManager* TimerManager::GetInstancePtr()
{
	static TimerManager timerManager;
	return &timerManager;
}

void TimerManager::checkTimer()
{
	int32_t curtime = NowTime;
	checkTimer(curtime);
}

void TimerManager::checkTimer(uint64_t curtime)
{
	for (std::map<uint64_t, std::vector<Timer>>::iterator iter = m_TimerMap.begin(); iter != m_TimerMap.end();)
	{
		if (curtime > iter->first)
		{
			for (int32_t i = 0; i < iter->second.size(); i++)
			{
				iter->second[i].m_fp();
				iter->second[i].m_nLoop--;
				if (iter->second[i].m_nLoop > 0 || iter->second[i].m_nLoop < 0)
				{
					m_TimerMap[iter->first + iter->second[i].m_Interval].push_back(iter->second[i]);
				}

				if (iter->second[i].m_count - 1 > 0 || iter->second[i].m_count < 0)
				{
					iter->second[i].m_count--;
					m_TimerMap[iter->first + 86400].push_back(iter->second[i]);
				}
			}
			m_TimerMap.erase(iter++);
		}
		else
		{
			break;
		}
	}
}

void TimerManager::addTimer(uint64_t startTime, Functional fp, int32_t nCount /*= -1*/, int32_t nloop /*= 1*/, int32_t nInterval /*= 1*/)
{
	while (NowTime > startTime)
	{
		startTime += 86400;
	}

	Timer timer(fp, nCount, nloop, nInterval);

	m_TimerMap[startTime].push_back(timer);

}
