#ifndef __FILE_OPERATION__
#define __FILE_OPERATION__

class FileOperation 
{
public:
	static bool SaveFile(const char* relativePath, const char* content);
	static char* ReadFile(const char* relativePath);
};

#endif
