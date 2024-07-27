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
	for (this->lineNum; this->lineNum < this->fileContent.size(); this->lineNum) {
		if (!this->interpretCode(this->fileContent.at(this->lineNum))) {
			return 0;
		}
		this->lineNum++;
		continue;
	}
	return 1;
}

int Interpreter::interpretCode(std::string code, int offset) {
	// loops through the line.
	for (int i = offset; i < code.length(); i++) {
		int currentLine = this->lineNum; // used to check if the interpreter should go to the next line or not.
		ArrayElementInfo& elementInfo = this->scriptArray.at(this->arrayPos); // get's the array element.
		char lineChar = code.at(i);
		std::cout << lineChar << " " << this->scriptArray.at(this->arrayPos).value << std::endl;

		if (lineChar == '+' && elementInfo.value >= 0) { // increments a value inside the "scriptArray" array.
			if (this->scriptArray.at(this->arrayPos).value == 127) {
				this->scriptArray.at(this->arrayPos).value = 0;
			}
			else {
				this->scriptArray.at(this->arrayPos).value++;
			}
		}
		else if (lineChar == '-' && elementInfo.value >= 0) { // decrements a value inside the "scriptArray" array.
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
			if (i < code.length()-1) {
				if (code.at(i + 1) == '&') { // prints array position.
					std::cout << this->arrayPos << std::endl;
					i++;
				}
				else if (code.at(i + 1) == '!') { // prints the value of the selected index in the "scriptArray" array.
					std::cout << this->scriptArray.at(this->arrayPos).value << std::endl;
					i++;
				}
				else { // prints the character of the selected index in the "scriptArray" array.
					std::cout << char(this->scriptArray.at(this->arrayPos).value);
				}
			}
			else { // prints the character of the selected index in the "scriptArray" array.
				std::cout << char(this->scriptArray.at(this->arrayPos).value);
			}
		}
		else if (lineChar == '[') { // handles entering while loops.
			std::string loopCode = this->findCode('[', ']', lineNum, i);
			while (this->scriptArray.at(this->arrayPos).value != 0) {
				this->interpretCode(loopCode);
			}
		}
		else if (lineChar == '{') { // handles entering for loops.
			std::string loopCode = this->findCode('{', '}', lineNum, i);
			for (int iterator = this->scriptArray.at(this->arrayPos).value; iterator != 0; iterator--) {
				this->interpretCode(loopCode);
			}
		}
		else if (lineChar == '(') {
			std::string line; // used to get the line of a file.
			bool reachedFuncEnd = false; // tells the first for loop that it has reached the end of the function.
			elementInfo.funcCode = this->findCode('(', ')', this->lineNum, i); // finds code inside the function.
			elementInfo.value = -1; // tells the interpreter that this value is a function.
		}
		else if (lineChar == ':') { // calls functions.
			if (elementInfo.value != -1) { // checks if the element contains a function.
				// ONLY ERROR IF CERTAIN PARAM IS PRESENT.
			}
			else {
				// executes the function.
				this->interpretCode(elementInfo.funcCode);
			}
		}
		else if (lineChar == ';') { // unbinds a function from the current element (if a function is attached to the element).
			if (elementInfo.value != -1) { // checks if the element contains a function.
				// ONLY ERROR IF CERTAIN PARAM IS PRESENT.
			}
			else {
				// unbinds function from the current element.
				elementInfo.funcCode.clear();
				elementInfo.value = 0;
			}
		}
		else if (lineChar == '/') { // if statements.
			int currentArrayPos = this->arrayPos;
			std::string compare = this->findCode('[', ']', lineNum, i); // contains the index to compare against.
			this->interpretCode(compare);
			std::string ifOperator = code.substr(i, 2);
			if (ifOperator.at(0) == '<' && ifOperator.at(1) != '=' && this->scriptArray.at(currentArrayPos).value < this->scriptArray.at(this->arrayPos).value) {
				this->interpretCode(this->findCode('{', '}', lineNum, i));
			}
			else if (ifOperator == "<=" && this->scriptArray.at(currentArrayPos).value >= this->scriptArray.at(this->arrayPos).value) {
				this->interpretCode(this->findCode('{', '}', lineNum, i));
			}
			else if (ifOperator.at(0) == '>' && ifOperator.at(1) != '=' && this->scriptArray.at(currentArrayPos).value > this->scriptArray.at(this->arrayPos).value) {
				this->interpretCode(this->findCode('{', '}', lineNum, i));
			}
			else if (ifOperator == ">=" && this->scriptArray.at(currentArrayPos).value >= this->scriptArray.at(this->arrayPos).value) {
				this->interpretCode(this->findCode('{', '}', lineNum, i));
			}
			else if (ifOperator == "==" && this->scriptArray.at(currentArrayPos).value == this->scriptArray.at(this->arrayPos).value) {
				this->interpretCode(this->findCode('{', '}', lineNum, i));
			}
			else if (ifOperator == "!=" && this->scriptArray.at(currentArrayPos).value != this->scriptArray.at(this->arrayPos).value) {
				this->interpretCode(this->findCode('{', '}', lineNum, i));
			}
			else {
				this->findCode('{', '}', lineNum, i); // set's the line number and char number (AKA i).
			}
		}
		else if (lineChar == '*') { // memory allocation / deallocation.
			// use it once to allocate the memory. then use it again on the same address to deallocate it.
			// use "/<num>" to get the allocated memory from a index. each index can only hold 1 number.
		}
		else if (lineChar == '/') { // get's allocated memory from a index.

		}
		if (currentLine != this->lineNum) { // determines if the interpreter should go to the next line or not.
			return 1;
		}
		continue;
	}
	return 1;
}

std::string Interpreter::findCode(char beginChar, char endChar, int& lineNum, int& charNum) {
	std::string funcCode;
	std::string line;
	for (lineNum; lineNum < this->fileContent.size(); lineNum++) {
		line = this->fileContent.at(lineNum);
		// loops through each chacter of the line to check if one of the characters is ")".
		for (int k = 0; k < line.length(); k++) {
			if (line.at(k) == beginChar) { // beginning parenthesis.
				funcCode.clear(); // prevents any characters before the parenthesis from being added to the function code string.
				continue;
			}
			else if (line.at(k) == endChar) { // exits both loops once the end parenthesis is reached.
				// removes whitespaces from the function code.
				funcCode.erase(remove_if(funcCode.begin(), funcCode.end(), isspace), funcCode.end());
				k++;
				charNum = k;
				return funcCode;
			}
			else { // adds the character to the func code.
				funcCode += line.at(k);
			}
			continue;
		}
		continue;
	}
}
