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
		this->scriptArray.push_back({ 0, "" });
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
		std::cout << lineChar << " " << this->scriptArray.at(this->arrayPos).value << std::endl;

		if (lineChar == '+') { // increments a value inside the "scriptArray" array.
			if (this->scriptArray.at(this->arrayPos).value == 127) {
				this->scriptArray.at(this->arrayPos).value = 0;
			}
			else {
				this->scriptArray.at(this->arrayPos).value++;
			}
		}
		else if (lineChar == '-') { // decrements a value inside the "scriptArray" array.
			if (this->scriptArray.at(this->arrayPos).value == 0) {
				this->scriptArray.at(this->arrayPos).value = 127;
			}
			else {
				this->scriptArray.at(this->arrayPos).value--;
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
			if (i < this->fileContent.at(lineNum).length()-1) {
				if (this->fileContent.at(lineNum).at(i + 1) == '&') { // prints array position.
					std::cout << this->arrayPos << std::endl;
					i++;
				}
				else if (this->fileContent.at(lineNum).at(i + 1) == '!') { // prints the value of the selected index in the "scriptArray" array.
					std::cout << this->scriptArray.at(this->arrayPos).value << std::endl;
					i++;
				}
				else { // prints the character of the selected index in the "scriptArray" array.
					std::cout << char(this->scriptArray.at(this->arrayPos).value) << std::endl;
				}
			}
			else { // prints the character of the selected index in the "scriptArray" array.
				std::cout << char(this->scriptArray.at(this->arrayPos).value) << std::endl;
			}
		}
		else if (lineChar == '[') { // handles entering while loops.
			LoopInfo loopInfo = { this->arrayPos, 0, {lineNum, i}};
			this->loops.push_back(loopInfo);
			this->runningLoops++;
		}
		else if (lineChar == ']') { // handles exiting or continuing a while loop.
			LoopInfo loopInfo = this->loops.at(this->runningLoops-1);
			if (this->scriptArray.at(loopInfo.arrayPos).value == 0) {
				this->loops.erase(loops.begin() + this->runningLoops-1);
				this->runningLoops--;
			}
			else {
				this->lineNum = loopInfo.lineBegin.at(0);
				i = loopInfo.lineBegin.at(1);
			}
		}
		else if (lineChar == '{') { // handles entering for loops.
			LoopInfo loopInfo = { this->arrayPos, this->scriptArray.at(this->arrayPos).value, {lineNum, i} };
			this->loops.push_back(loopInfo);
			this->runningLoops++;
		}
		else if (lineChar == '}') { // handles continuing or exiting for loops.
			LoopInfo& loopInfo = this->loops.at(this->runningLoops - 1); // took me forever to figure out i needed to reference the LoopInfo instead of copy it to modify the iterator.
			loopInfo.iterator--; // decremented here to avoid the loop running an extra time.
			if (loopInfo.iterator == 0) {
				this->loops.erase(loops.begin() + this->runningLoops - 1);
				this->runningLoops--;
			}
			else {
				this->lineNum = loopInfo.lineBegin.at(0);
				i = loopInfo.lineBegin.at(1);
			}
		}
		else if (lineChar == '(') {
			std::string line; // used to get the line of a file.
			bool reachedFuncEnd = false; // tells the first for loop that it has reached the end of the function.
			ArrayElementInfo& elementInfo = this->scriptArray.at(this->arrayPos); // get's the array element which should contain a function.
			// loops through the file until it finds the end of the function (AKA the ")" character).
			for (int j = lineNum; j < this->fileContent.size(); j++) {
				line = this->fileContent.at(j);
				// loops through each chacter of the line to check if one of the characters is ")".
				for (int k = 0; k < line.length(); k++) {
					if (line.at(k) == '(') { // beginning parenthesis.
						continue;
					}
					else if (line.at(k) == ')') { // exits both loops once the end parenthesis is reached.
						this->lineNum = j;
						i = k+1;
						// removes whitespaces from the function code.
						elementInfo.funcCode.erase(remove_if(elementInfo.funcCode.begin(), elementInfo.funcCode.end(), isspace), elementInfo.funcCode.end());
						elementInfo.value = -1; // tells the interpreter that this value is a function.
						reachedFuncEnd = true;
						break;
					}
					else { // adds the character to the func code.
						elementInfo.funcCode += line.at(k);
					}
				}
				if (reachedFuncEnd == true) {
					break;
				}
				continue;
			}
		}
		else if (lineChar == ':') { // calls functions.

		}
		else if (lineChar == ';') { // unbinds a function from the current element (if a function is attached to the element).

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
