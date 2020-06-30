#ifndef _CORE_CRASH_CATCH_DDKSJLD_
#define _CORE_CRASH_CATCH_DDKSJLD_


#ifdef	__cplusplus
extern "C" {
#endif

	//char *logProgramFile, 处理dump文件的程序名
	//char *reportParam		调用dump程序时的附加参数
	void Init_CrashCatch(const char *logProgramFile = NULL, const char *reportParam = NULL);

	void CrashUpArg(const char *reportParam);

#ifdef	__cplusplus
}
#endif


#endif

