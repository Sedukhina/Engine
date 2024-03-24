#pragma once

#define MAX_PATH_LENGTH 255

class CPath
{
public:
	CPath();
	~CPath();

private:
#ifdef _WIN64
	wchar_t AbsolutePath[MAX_PATH_LENGTH];
#elif __linux__
	char_t AbsolutePath[MAX_PATH_LENGTH];
#endif 
};
