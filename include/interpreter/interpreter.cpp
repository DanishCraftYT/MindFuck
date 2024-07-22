#include "interpreter.h"

Interpreter::Interpreter(std::string pathToScript, int arraySize, int lineNum) {
	this->lineNum = lineNum;
	this->arraySize = arraySize;

	// opens file.
	std::ifstream mfsFileStream(pathToScript);

	// checks if file was opened successfully.
	if (!mfsFileStream.is_open()) {
		std::cout << "failed to open \"" + pathToScript + "\"." << std::endl;
	}

	// reads file.
	std::string line;
	while (getline(mfsFileStream, line)) {
		this->fileContent.push_back(line);
		continue;
	}

	// appends a bunch of zero's to the scipt array.
	for (int i = 0; i < arraySize; i++) {
		this->scriptArray.push_back(0);
		continue;
	}
}

int Interpreter::interpretFile() {
	// loops through the entire file.
	this->lineNum--;
	while (this->lineNum < this->fileContent.size()) {
		if (!this->interpretLine(this->lineNum)) {
			return 0;
		}
		this->lineNum++;
		continue;
	}
	return 1;
}

int Interpreter::interpretLine(int lineNum) {
	// loops through the line.
	for (int i = 0; i < this->fileContent.at(lineNum).size(); i++) {
		char lineChar = this->fileContent.at(lineNum).at(i);
		std::cout << lineChar << " " << this->scriptArray.at(this->arrayPos) << std::endl;
		if (lineChar == '+') { // increments a value inside the "scriptArray" array.
			if (this->scriptArray.at(this->arrayPos) == 127) {
				this->scriptArray.at(this->arrayPos) = 0;
			}
			else {
				this->scriptArray.at(this->arrayPos)++;
			}
		}
		else if (lineChar == '-') { // decrements a value inside the "scriptArray" array.
			if (this->scriptArray.at(this->arrayPos) == 0) {
				this->scriptArray.at(this->arrayPos) = 127;
			}
			else {
				this->scriptArray.at(this->arrayPos)--;
			}
		}
		else if (lineChar == '>') { // goes to next index.
			if (this->arrayPos == this->arraySize) {
				this->arrayPos = 0;
			}
			else {
				this->arrayPos++;
			}
		}
		else if (lineChar == '<') { // goes to previous index.
			if (this->arrayPos == 0) {
				this->arrayPos = 127;
			}
			else {
				this->arrayPos--;
			}
		}
		else if (lineChar == '.') { // handles writting to console.
			std::cout << char(this->scriptArray.at(this->arrayPos)) << std::endl;
		}
		else if (lineChar == '[') { // handles entering while loops.
			LoopInfo loopInfo = { this->arrayPos, {lineNum, i}};
			this->loops.push_back(loopInfo);
			this->runningLoops++;
		}
		else if (lineChar == ']') { // handles exiting or continuing a while loop.
			LoopInfo loopInfo = this->loops.at(this->runningLoops-1);
			if (this->scriptArray.at(loopInfo.arrayPos) == 0) {
				this->loops.erase(loops.begin() + this->runningLoops-1);
				this->runningLoops--;
			}
			else {
				this->lineNum = loopInfo.lineBegin.at(0);
				i = loopInfo.lineBegin.at(1);
			}
		}
		else if (lineChar == '{') { // handles entering for loops.

		}
		else if (lineChar == '}') { // handles continuing or exiting for loops.

		}
		else if (lineChar == '*') { // memory allocation / deallocation.
			// use it once to allocate the memory. then use it again on the same address to deallocate it.
			// use "/<num>" to get the allocated memory from a index. each index can only hold 1 number.
		}
		else if (lineChar == '/') { // get's allocated memory from a index.

		}
		continue;
	}
	return 1;
}
