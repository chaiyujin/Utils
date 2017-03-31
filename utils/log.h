/* -----------------------------
* File   : log.h
* Author : Yuki Chai
* Created: 2017.3.29
* Project: Yuki
*/

#pragma once
#ifndef __YUKI_LOG_H__
#define __YUKI_LOG_H__

// #define CHECK_LEVEL_NONE // uncomment this line to disable runtime check

#include <stdio.h>
#include <stdarg.h>

namespace Yuki {
	enum LOG_LEVEL {
		NONE = 0,
		NOTICE = 1,
		DEBUG = 2,
	};

#ifndef RUNTIME_LOG_LEVEL
#ifdef NDEBUG
#define RUNTIME_LOG_LEVEL NOTICE
#else
#define RUNTIME_LOG_LEVEL DEBUG
#endif
#endif

#define LOG(fmt, ...) \
	if (NOTICE <= RUNTIME_LOG_LEVEL) {\
		printf("[LOG] "); printf(fmt, ##__VA_ARGS__);\
	}
#define DEBUG(fmt, ...) \
	if (DEBUG <= RUNTIME_LOG_LEVEL) {\
		printf("[DEBUG] "); printf(fmt, ##__VA_ARGS__);\
	}
#define ERROR(fmt, ...) do {\
	printf("Error in [%s] (line: %d) : ", __FUNCTION__, __LINE__);\
	printf(fmt, ##__VA_ARGS__);\
	system("pause");exit(1); } while (0);
#define CHECK(assertion) do {\
		bool flag = assertion;\
		if (!flag) {\
			printf("Error in [%s] (line: %d) : CHECK fail.\n", __FUNCTION__, __LINE__);\
			system("pause");exit(1);\
		}\
	} while (0);
}

#endif  // !__YUKI_LOG_H__