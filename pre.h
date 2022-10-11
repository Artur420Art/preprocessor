#include <iostream>
#include <fstream>
#include <map>
#include <vector>

class Pre {
public:
    Pre();
    ~Pre();
    void pre_process(const std::string&);
private:
    typedef void(Pre::*func)(const std::string&);
    bool flag;
private:
    std::fstream fin;
    std::fstream fout;
    std::map <std::string, func> inst;
    std::map <std::string, std::string> defines;
    std::vector<std::string> split(const std::string& str, std::string spliter);
private:
    void include(const std::string& str);
    void define(const std::string& str);
    void definition(std::string& str);
    void undef(const std::string& str);
    void ifndef(const std::string& str);
    void ifdef(const std::string& str);
    void endif(const std::string& str);
    void make();
};
