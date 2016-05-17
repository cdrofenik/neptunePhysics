#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <iostream>
#include <fstream>

std::string GetStringFromFile(const char * _fPath)
{
	std::string fileString;
	std::ifstream fileStream(_fPath, std::ios::in);

	if (fileStream.is_open()){
		std::string Line = "";
		while (getline(fileStream, Line))
			fileString += "\n" + Line;
		fileStream.close();
	}
	else{
		printf("Impossible to open %s. Are you in the right directory?\n", _fPath);
		getchar();
		return 0;
	}

	return fileString;
}

#endif