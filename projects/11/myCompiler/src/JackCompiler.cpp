#include "../include/JackTokenizer.h"
#include "../include/CompilationEngine.h"
#include "../include/SymbolTable.h"
#include "../include/VMWriter.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void compile_directory(const fs::path directory){
    if (!fs::exists(directory) || !fs::is_directory(directory)) {
        std::cerr << "Directory does not exist: " << directory << std::endl;
        return;
    }
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            fs::path file_path = entry.path();
            // 检查文件是否以.jack结尾
            if (file_path.extension() == ".jack") {
                // 构建新的.vm文件路径
                fs::path vm_file_path = file_path;
                vm_file_path.replace_extension(".vm");

                JackTokenizer tokenizer(file_path.string());
                SymbolTable symbolTable;
                VMWriter vmWriter(vm_file_path.string());
                CompilationEngine compilationEngine(&tokenizer, &vmWriter, &symbolTable);

                std::cout << "Converted " << file_path.filename() << " to " << vm_file_path.filename() << std::endl;
            }
        }
    }
}


int main(int argc, char* argv[]) {
    if(argc != 2){
        cerr << "Usage: " << argv[0] << " " << ".jack/directory" << endl;
        exit(1);
    }
    string srcPath = argv[1];
    if(srcPath.find(".jack") != string::npos){ //.jack file
        string fileName = srcPath.substr(0, srcPath.find(".jack")) + ".vm";

        JackTokenizer tokenizer(srcPath);
        SymbolTable symbolTable;
        VMWriter vmWriter(fileName);
        CompilationEngine compilationEngine(&tokenizer, &vmWriter, &symbolTable);
    }
    else{   //directory
        compile_directory(srcPath);
    }

    return 0;
}