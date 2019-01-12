#include "helper.h"

__thread uint32 seedp;
Helper g_help;


int32 GetKeyInt32(int16 a, int16 b)
{
	int32 key = int32(a) << 16;
	key += b;
	return key;
}

int16 GetKeyLowerInt32(int32 key)
{
	int16 low = (key & 0xffff);
	return low;
}

int16 GetKeyHigherInt32(int32 key)
{
	int16 high = ((key >> 16) & 0xffff);
	return high;
}

//===============================================

uint32 GetKeyUint32(uint16 a, uint16 b)
{

	uint32 key = uint32(a) << 16;
	key += b;
	return key;
}

uint16 GetKeyLowerUint32(uint32 key)
{
	uint16 low = (key & 0xffff);
	return low;
}

uint16 GetKeyHigherUint32(uint32 key)
{
	uint16 high = ((key >> 16) & 0xffff);
	return high;
}

//===============================================

int64 GetKeyInt64(int32 a, int32 b)
{
	int64 key = int64(a) << 32;
	key += b;
	return key;
}


int32 GetKeyLowerInt64(int64 key)
{
	int32 low = (key & 0xffffffff);
	return low;
}

int32 GetKeyHigherInt64(int64 key)
{
	int32 high = ((key >> 32) & 0xffffffff);
	return high;
}


//==================================================
uint64 GetKeyUint64(uint32 a, uint32 b)
{
	uint32 key = uint64(a) << 32;
	key += b;
	return key;
}

uint32 GetKeyLowerUint64(uint64 key)
{
	int32 low = (key & 0xffffffff);
	return low;
}

uint32 GetKeyHigherUint64(uint64 key)
{
	uint32 high = ((key >> 32) & 0xffffffff);
	return high;
}

//=======================================================


bool IsSameDay(int32 time1, int32 time2)
{
	int32 day1 = (time1 - timezone);
	int32 day2 = (time2 - timezone);
	return (day1 / ONE_DAY) == (day2 / ONE_DAY);
}


int32 Diffday(int32 time1, int32 time2, bool bignore/* = true*/)
{
	if (bignore == false)
	{
		return abs(time1 - time2) / ONE_DAY;
	}
	else
	{
		int32 time_day1 = time1 - (time1 - timezone) % ONE_DAY;
		int32 time_day2 = time2 - (time2 - timezone) % ONE_DAY;
		return abs(time_day1 - time_day2) / ONE_DAY;
	}
}

int32 RandBetween(int32 min, int32 max)
{
	if (min == max)
	{
		return min;
	}
	if (min > max)
	{
		return max + (int32) (((double) min - (double)max + 1.0) * rand_r(&seedp) / (RAND_MAX + 1.0));
	}
	else
	{
		return min + (int32) (((double) max - (double)min + 1.0) * rand_r(&seedp) / (RAND_MAX + 1.0));
	}
}

void RandNumInRegion(int32 region, int32 num, std::vector<int32>& rands)
{
	if(region <= 0)
	{
		return;
	}

	if (region < num)
	{
		return;
	}

	std::vector<int32> nums;
	for(int32 i = 0 ; i < region; i++)
	{
		nums.push_back(i);
	}

	for(int32 i = 0; i < num; i++)
	{
		int32 index = RandBetween(0, nums.size() - 1);
		rands.push_back(nums[index]);
		nums[index] = nums.back();
		nums.pop_back();
	}
}

void ReadDir(xstring cate_dir, std::vector<xstring>& vecFile)
{
	DIR* dir;
	struct dirent* ptr;
	xstring base;

	if ((dir = opendir(cate_dir.c_str())) == NULL)
	{
		perror("Open dir error...");
		exit(1);
	}

	while ((ptr = readdir(dir)) != NULL)
	{
		if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0) ///current dir OR parrent dir
		{ continue; }
		else if(ptr->d_type == 8)    ///file
		{ vecFile.push_back(cate_dir + "/" + ptr->d_name); }
		else if(ptr->d_type == 10)    ///link file
		{ continue; }
		else if(ptr->d_type == 4)    ///dir
		{
			base.clear();
			base += cate_dir + "/";
			base += ptr->d_name;
			ReadDir(base, vecFile);
		}
	}
	closedir(dir);
}
