#ifndef _CORE_CRASH_CATCH_DDKSJLD_
#define _CORE_CRASH_CATCH_DDKSJLD_


#ifdef	__cplusplus
extern "C" {
#endif

	//char *logProgramFile, ����dump�ļ��ĳ�����
	//char *reportParam		����dump����ʱ�ĸ��Ӳ���
	void Init_CrashCatch(const char *logProgramFile = NULL, const char *reportParam = NULL);

	void CrashUpArg(const char *reportParam);

#ifdef	__cplusplus
}
#endif


#endif

