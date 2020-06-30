#ifndef __FILEDEF_H__
#define __FILEDEF_H__

// 下面是 INI 部分

#define FILE_CONFIG_INFO					"./Config/ConfigInfo.ini"
#define FILE_LOGIN_INFO						"./Config/LoginInfo.ini"
#define	FILE_WORLD_INFO						"./Config/WorldInfo.ini"
#define FILE_SHARE_MEM_INFO					"./Config/ShareMemInfo.ini"
#define FILE_MACHINE_INFO					"./Config/MachineInfo.ini"
#define FILE_SERVER_INFO					"./Config/ServerInfo.ini"
#define FILE_SCENE_INFO						"./Config/SceneInfo.ini"

//
#define FILE_STRING_INFO                    "./Config/StringTable.txt"

#define GET_FULL_PATH(fullpath, filepath, filename)	do { \
		sprintf(fullpath, "%s%s", (filepath), (filename)); \
	} while (0)

#define GET_AI_SCRIPT_FULL_PATH(fullpath, filename) GET_FULL_PATH(fullpath, PATH_AI_SCRIPT, (filename))
#define GET_SCENE_FULL_PATH(fullpath, filename) GET_FULL_PATH(fullpath, PATH_SCENE, (filename))
#endif // __FILEDEF_H__