#pragma once

#include <windows.h>
#include <string>

class FileSystem
{
public:
	FileSystem();

	static inline float getFileSize(const std::string& path) 
	{
		FILE *p_file = NULL;
		p_file = fopen(path.c_str(), "rb");
		fseek(p_file, 0, SEEK_END);
		int size = ftell(p_file);
		fclose(p_file);

		return size / 1024.0f / 1024.0f;
	};

	static bool dirExists(const std::string& path)
	{
		DWORD ftyp = GetFileAttributesA(path.c_str());
		if (ftyp == INVALID_FILE_ATTRIBUTES)
			return false;

		if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
			return true;

		return false;
	}

	~FileSystem();
};
