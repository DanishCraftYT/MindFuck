# Overview

# class Interpreter

## public Interpreter(std::string pathToScript, int arraySize=100, int lineNum=1)
constructor for the "Interpreter" class.<br>

### params:
* std::string pathToScript - the path to the ".mfs" script.<br>
* int arraySize=100 - the size of the array that the script should use.<br>
* int lineNum=1 - the number that "interpretFile()" should start interpreting from.<br>

## public interpretFile()
interprets a file.<br>

## public interpretLine(int lineNum)
interprets a specific line in a file.<br>

### params:
* int lineNum - the line to interpret.<br>

## public struct LoopInfo
contains infomation about loops in MindFuck.<br>

### varibles:
* int arrayPos - the current index is used as the loop iterator.<br>
* std::array<int, 2> lineBegin - contains infomation about the line and char number of when the loop started (position of "[").<br>

## public struct ArrayElementInfo
contains infomation about each element in the "scriptArray" array.<br>

### varibles
* int value - the value of the array element.<br>
* std::string funcCode - contains the code from a function.<br>

## private Lexer lexer
contains the lexer used by the interpreter.<br>

## private int lineNum
contains the line number used by "interpretFile()".<br>

## private int runningLoops = 0
determines how many loops are currently running.<br>

## private int arraySize
contains the size of the array used by "MindFuck".<br>

## private int arrayPos = 0
contains the position the script is inside the "scriptArray".<br>

## private std::vector<int> scriptArray
contains the array used by "MindFuck".<br>

## private std::vector<std::string> fileContent
contains the content of the ".mfs" script.<br>

## private std::vector<LoopInfo> loops
contains all loops that are currently running in the script.<br>
