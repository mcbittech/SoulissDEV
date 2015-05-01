/*
  ardusim.h - Arduino Simulation Routines Header File

  Copyright (c) 2012 Stanley Huang

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

*/

#ifndef _ARDUSIM_H_
#define _ARDUSIM_H_

#ifdef WIN32
#include <windows.h>
#define usleep(us) Sleep(us / 1000)
#define utoa itoa
#define ultoa itoa
#define srandom

#else
#include   <unistd.h>
#endif
#include <stdint.h>
#include <stdlib.h>

extern uint8_t SIM_MEM[];
extern uint8_t SIM_SFR[];

// simulated AVR C stuff
#define sprintf_P sprintf
#define strstr_P strstr
#define strcpy_P strcpy

//extern uint8_t SREG;

#ifdef __cplusplus
extern "C" {
#endif

void cli();
void sei();

#ifdef __cplusplus
}
#endif

#ifdef SYS_MINGW
#ifndef WIN32
#define WIN32
#endif
#endif

#ifdef WIN32
#include <windows.h>
#include <io.h>

#define snprintf _snprintf

#else
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <pthread.h>

#if !defined(O_BINARY)
#define O_BINARY 0
#endif
#endif //WIN32

#ifdef WIN32

#define ssize_t size_t
#define socklen_t int
#ifndef HAVE_PTHREAD
typedef HANDLE pthread_t;
typedef HANDLE pthread_mutex_t;
#endif

typedef DWORD (WINAPI *PFNGetProcessId)(HANDLE hProcess);
#define DD
#else

#define closesocket close
#ifndef MAX_PATH
#define MAX_PATH 256
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

typedef int SOCKET;
typedef unsigned int DWORD;
typedef unsigned short int WORD;
typedef unsigned char BYTE;
typedef int BOOL;
#define DD printf("%s, %s(%d)\n", __FILE__,__FUNCTION__ , __LINE__)
#endif //WIN32
typedef unsigned char OCTET;

#define SHELL_NOREDIRECT 1
#define SHELL_SHOWWINDOW 2
#define SHELL_NOWAIT 4

#ifdef WIN32
#define msleep(ms) (Sleep(ms))
#define PATH_DELIMITER '\\'
#else
#define msleep(ms) (usleep(ms<<10))
#define PATH_DELIMITER '/'
#define _strdup strdup
#define stricmp strcasecmp
#endif

#ifdef __cplusplus
extern "C" {
#endif

int InitSocket();
void UninitSocket();
char *GetTimeString();
int ThreadCreate(pthread_t *pth, void* (*start_routine)(void*), void* arg);
int ThreadKill(pthread_t pth);
int ThreadWait(pthread_t pth, int timeout, void** ret);
void MutexCreate(pthread_mutex_t* mutex);
void MutexDestroy(pthread_mutex_t* mutex);
void MutexLock(pthread_mutex_t* mutex);
void MutexUnlock(pthread_mutex_t* mutex);
int ReadDir(const char* pchDir, char* pchFileNameBuf);
int IsFileExist(const char* filename);
int IsDir(const char* pchName);

#ifndef WIN32
unsigned int GetTickCount();
#endif

#ifdef __cplusplus
}
#endif

#endif
