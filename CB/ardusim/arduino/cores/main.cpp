#include <Arduino.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <fcntl.h>

#ifndef WIN32
#include <sys/types.h>
#include <sys/time.h>
#include <dirent.h>
#include <unistd.h>
#endif

int IsFileExist(const char* filename)
{
	struct stat stat_ret;
	if (stat(filename, &stat_ret) != 0) return 0;

	return (stat_ret.st_mode & S_IFREG) != 0;
}

#ifndef WIN32
unsigned int GetTickCount()
{
	struct timeval ts;
	gettimeofday(&ts,0);
	return ts.tv_sec * 1000 + ts.tv_usec / 1000;
}
#endif

int ThreadCreate(pthread_t *pth, void* (*start_routine)(void*), void* arg)
{
#ifdef WIN32
	DWORD dwid;
	*pth=CreateThread(0,0,(LPTHREAD_START_ROUTINE)start_routine,arg,0,&dwid);
	return *pth!=NULL?0:1;
#else
	pthread_attr_t attr;
	pthread_attr_init(&attr);
// Change policy
	pthread_attr_setschedpolicy(&attr,   SCHED_RR);
	int ret = pthread_create(pth, &attr, start_routine, arg);
	pthread_attr_destroy(&attr);
	return ret;
#endif
}

int ThreadKill(pthread_t pth)
{
#ifdef WIN32
	return TerminateThread(pth,0)?0:1;
#else
	return pthread_cancel(pth);
#endif
}

int ThreadWait(pthread_t pth, int timeout, void** ret)
{
#ifdef WIN32
	if (WaitForSingleObject(pth, timeout)==WAIT_TIMEOUT)
		return 1;
	if (ret) GetExitCodeThread(pth,(LPDWORD)ret);
	CloseHandle(pth);
	return 0;
#else
	return pthread_join(pth,ret);
#endif
}

void MutexCreate(pthread_mutex_t* mutex)
{
#ifdef WIN32
	*mutex = CreateMutex(0,FALSE,NULL);
#else
	pthread_mutex_init(mutex,NULL);
#endif
}

void MutexDestroy(pthread_mutex_t* mutex)
{
#ifdef WIN32
	CloseHandle(*mutex);
#else
	pthread_mutex_destroy(mutex);
#endif
}

void MutexLock(pthread_mutex_t* mutex)
{
#ifdef WIN32
	WaitForSingleObject(*mutex,INFINITE);
#else
	pthread_mutex_lock(mutex);
#endif
}

void MutexUnlock(pthread_mutex_t* mutex)
{
#ifdef WIN32
	ReleaseMutex(*mutex);
#else
	pthread_mutex_unlock(mutex);
#endif
}

void setup();
void loop();

uint8_t SIM_MEM[65536] = {0};

void cli()
{
    //fprintf(stderr, "[MCU] Global interrupt disabled\n");
}

void sei()
{
    //fprintf(stderr, "[MCU] Global interrupt enabled\n");
}

int main(void)
{
    unsigned int loopcount = 0;

	fprintf(stderr, "ARDUSIM 0.1.1 - API-Level Arduino Simulator (C)2012-13 Written by Stanley Huang\n\n");

	init();
#if defined(USBCON)
	USB.attach();
#endif

	setup();

	for (;;) {
		loop();
		//if (serialEventRun) serialEventRun();
		//fprintf(stderr, "Loop %d\r", ++loopcount);
		usleep(0);
	}
	return 0;
}
