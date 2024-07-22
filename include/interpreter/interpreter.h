#include "lexer/lexer.h"

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
private:
	Lexer lexer;
	int lineNum;
	int arraySize;
	int arrayPos = 0;
	int runningLoops = 0;
	std::vector<int> scriptArray;
	std::vector<std::string> fileContent;
	std::vector<LoopInfo> loops;
};
