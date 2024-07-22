#include "interpreter/interpreter.h"
#include <filesystem>

int main(int argc, char** argv) {
	std::filesystem::path filePath = std::filesystem::path(argv[0]).parent_path().parent_path();
	filePath /= std::filesystem::path("test.mfs");
	Interpreter interpreter(filePath.string());
	interpreter.interpretFile();
	return 0;
}
