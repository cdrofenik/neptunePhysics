#include <vector>
#include <string>

using namespace std;

class Logger
{

public:
	Logger() {};
	~Logger() {};

	static void initLogger() { loggerStack = vector<string>(); }
	static void clearLogger() { loggerStack.clear; }

	static void addToLogger(string a) { loggerStack.push_back(a); }
	
	static char* displayStack()
	{
		string res = "";
		for (size_t i = 0; i < loggerStack.size; i++)
		{
			res += loggerStack[i] + "/n";
		}

		return res.c_str;
	}

	static void printToOutput()
	{
		for(size_t i = 0; i < loggerStack.size; i++)
		{
			printf_s(loggerStack[i].c_str+"\n");
		}
	}

	//static void addToLogger(float a) { loggerStack.push_back(atoi(a)); }
	//static void addToLogger(int a);

private:
	static vector<string> loggerStack;
};