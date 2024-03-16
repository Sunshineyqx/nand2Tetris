#include "../include/Parser.h"
#include "../include/CodeWriter.h"
#include <vector>
#include <string>
#include <filesystem>
namespace fs = std::filesystem;
// namespace fs = std::filesystem;

// 判断文件后缀是否为.vm
bool isVmFile(const fs::path &path)
{
    return path.extension() == ".vm";
}

// 读取目录并返回所有.vm文件的文件相对路径
vector<string> getVmFilesInDirectory(const fs::path &directory)
{
    vector<string> vmFiles;
    for (const auto &file : fs::directory_iterator(directory))
    {
        if (isVmFile(file.path()))
        {
            vmFiles.push_back(file.path().string());
        }
    }
    return vmFiles;
}

// 根据路径是文件还是目录来调用相应的函数
vector<string> getVmFiles(const string &path)
{
    fs::path p(path);
    if (fs::is_regular_file(p) && isVmFile(p))
    {
        return {p.string()};
    }
    else if (fs::is_directory(p))
    {
        return getVmFilesInDirectory(p);
    }
    else
    {
        return {};
    }
}

std::string getOutFileName(const std::string& path) {
    fs::path p(path);
    
    // 检查路径是否存在
    if (!fs::exists(p)) {
        cerr<< "main(): 文件/目录不存在"<<endl;
        exit(1);
    }
    // 检查路径是否是目录
    if (fs::is_directory(p)) {
        // 返回最右侧的目录名称
        return p.filename().string();
    } else if (fs::is_regular_file(p)) {
        // 返回文件名前缀
        return p.stem().string();
    } else {
        cerr<< "main(): 文件错误"<<endl;
        exit(1);
    }
}
int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " "
             << "<input .vm-file/directory name>" << endl;
        exit(1);
    }

    auto vmFiles = getVmFiles(argv[1]);
    string outFile = getOutFileName(argv[1]);
    CodeWriter codeWriter(outFile);
    for (const auto &file : vmFiles)
    {
        //std::cout << file << std::endl;
        Parser parser(file);
        codeWriter.setFileName(getOutFileName(file));
        // cout << parser.RemoveSpaceAndComment("Push hello n //sadad") << endl;
        while (parser.hasMoreCommands())
        {
            parser.advance();
            if(parser.cmd().empty()) continue;
            codeWriter.WriteComment(parser.curCommand()); //往输出文件.asm里写入注释
            switch (parser.commandType()){
                case Parser::Command::C_ARITHMETIC :
                    {
                        codeWriter.WriteArithmetic(parser.cmd());
                        break;
                    }
                case Parser::Command::C_PUSH:
                case Parser::Command::C_POP:
                        codeWriter.WritePushPop(parser.cmd(), parser.arg1(), parser.arg2());
                        break;
                case Parser::Command::C_LABEL:
                    {
                        codeWriter.WriteLabel(parser.arg1());
                        break;
                    }
                case Parser::Command::C_IF:
                    {
                        codeWriter.WriteIf(parser.arg1());
                        break;
                    }
                case Parser::Command::C_GOTO:
                    {
                        codeWriter.WriteGoto(parser.arg1());
                        break;
                    }
                case Parser::Command::C_FUNCTION:
                    {
                        codeWriter.WriteFunction(parser.arg1(), parser.arg2());
                        break;
                    }
                case Parser::Command::C_CALL:
                    {
                        codeWriter.WriteCall(parser.arg1(), parser.arg2());
                        break;
                    }
                case Parser::Command::C_RETURN:
                    {
                        codeWriter.WriteReturn();
                        break;
                    }
                default:
                    {
                        cout << "main(): unknown command:"<< "*" << parser.curCommand() << "*" << endl;
                        break;
                    }
            }
        }
    }
    return 0;
}