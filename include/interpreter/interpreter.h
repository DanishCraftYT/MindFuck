#include "lexer/lexer.h"
#include <algorithm>

class Interpreter {
public:
	Interpreter(std::string pathToScript, int arraySize=100, int lineNum=1);
	int interpretFile();
	int interpretLine(int lineNum);
	struct LoopInfo {
		int arrayPos;
		int iterator; // used only by for loops.
		std::array<int, 2> lineBegin; // [lineNum, charNum].
	};
	struct ArrayElementInfo {
		int value;
		std::string funcCode;
	};
private:
	Lexer lexer;
	int lineNum;
	int arraySize;
	int arrayPos = 0;
	int runningLoops = 0;
	std::vector<ArrayElementInfo> scriptArray;
	std::vector<std::string> fileContent;
	std::vector<LoopInfo> loops;
};
