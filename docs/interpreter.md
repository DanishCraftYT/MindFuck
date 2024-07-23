# Overview

# class Interpreter

## public Interpreter(std::string pathToScript, int arraySize=100, int lineNum=1)
constructor for the "Interpreter" class.<br>

### params:
* std::string pathToScript - the path to the ".mfs" script.<br>
* int arraySize=100 - the size of the array that the script should use.<br>
* int lineNum=1 - the number that "interpretFile()" should start interpreting from.<br>

## public struct ArrayElementInfo
contains infomation about each element in the "scriptArray" array.<br>

### varibles
* int value - the value of the array element.<br>
* std::string funcCode - contains the code from a function.<br>

## public interpretFile()
interprets a file.<br>

## public interpretCode(std::string code, int offset=0)
interprets a specific line in a file.<br>

### params:
* std::string code - the code to interpret.<br>
* int offset=0 - the amount of characters in the string to skip before it starts interpreting.<br>

## public std::string findCode(char beginChar, char endChar, int& lineNum, int& charNum)
finds code between first char and last char. also removes any spaces in between them.<br>

### params:
* char beginChar - the character it should start the getting characters from.<br>
* char endChar - the character it should stop getting characters from.<br>
* int& lineNum - the varible containing the line number.<br>
* int& charNum - the varible containing the character number.<br>

## private Lexer lexer
contains the lexer used by the interpreter.<br>

## private int lineNum
contains the line number used by "interpretFile()".<br>

## private int arraySize
contains the size of the array used by "MindFuck".<br>

## private int arrayPos = 0
contains the position the script is inside the "scriptArray".<br>

## private std::vector<int> scriptArray
contains the array used by "MindFuck".<br>

## private std::vector<std::string> fileContent
contains the content of the ".mfs" script.<br>
