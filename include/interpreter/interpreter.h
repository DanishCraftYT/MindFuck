#include "lexer/lexer.h"
#include <algorithm>

class Interpreter {
public:
	Interpreter(std::string pathToScript, int arraySize=100, int lineNum=1);
	struct ArrayElementInfo {
		int value;
		std::string funcCode;
	};
	int interpretFile();
	int interpretCode(std::string code, int offset=0);
	std::string findCode(char beginChar, char endChar, int& lineNum, int& charNum);
private:
	Lexer lexer;
	int lineNum;
	int arraySize;
	int arrayPos = 0;
	std::vector<ArrayElementInfo> scriptArray;
	std::vector<std::string> fileContent;
};
