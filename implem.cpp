#include "pre.h"

void Pre::make() {
    flag = true;

    inst["#include"] = &Pre::include;
    inst["#define"] = &Pre::define;
    inst["#undef"] = &Pre::undef;
    inst["#ifdef"] = &Pre::ifdef;
    inst["#endif"] = &Pre::endif;
    inst["#ifndef"] = &Pre::ifndef;
}

Pre::Pre() {
    this->make();
}
void Pre::pre_process(const std::string& rhs) {
    fin.open(rhs);
    std::string str = "preproc.txt";
    std::string line;
    fout.open(str);
    if(fin.is_open() && (fout.is_open())) {
        while(!fin.eof()) {
            getline(fin, line);
            auto vec = split(line, " ");
            if (inst.find(vec[0]) != inst.end()) {
                (this->*inst[vec[0]])(vec[1] + " " + vec[2]);
            }else {
                if (flag) {
                    definition(line);
                    fout << line << std::endl;
                }
            }
        }
    }
}
std::vector<std::string> Pre::split(const std::string& str, std::string spliter) {
    std::vector<std::string> nstr = {};
    std::string tstr = {};
    for (int i = 0; i < str.size(); ++i) {
        if (spliter.find(str[i]) != std::string::npos) {
            if (tstr != "") {
                nstr.push_back(tstr);
                tstr.clear();
                continue;
            }
            continue;
        }
        tstr.push_back(str[i]);
    }
    nstr.push_back(tstr);
    return nstr;
}

void Pre::include(const std::string& str) {
    std::string ptr = "";
    for (int i = 1; str[i] != static_cast<char>(34); i++) {
        ptr += str[i];
    }
    std::fstream include_header;
    std::string line = "";
    include_header.open(ptr);
    if (include_header.is_open()) {
        while (!include_header.eof()) {
            getline(include_header, line);
            auto vec = split(line, " ");
            if (inst.find(vec[0]) != inst.end()) {
                (this->*inst[vec[0]])(vec[1] + " " + vec[2]);
            }else {
                fout << line << std::endl;
            }
        }
    }
    
}

void Pre::define(const std::string& str) {
    auto name = split(str, " ");
    this->defines[name[0]] = name[1]; 
}

void Pre::definition(std::string& str) {
   for (auto it : defines) {
        if (str.find(it.first) != std::string::npos) {
            int pos = 0;
            while ((pos = str.find(it.first, pos)) != -1) {
                str.erase(str.begin() + str.find(it.first),str.begin() + str.find(it.first) + it.first.size());
                str.insert(pos, it.second);
            }
        }
    }
}
void Pre::undef(const std::string& str) {
      auto vec = split(str, " ");
      for(auto it : vec) {
        auto cp = defines.find(it);
        if (cp != defines.end()) {
            defines.erase(it);
        }
    }
}

void Pre::ifndef(const std::string& str) {
      auto vec = split(str, " ");
    if(defines.find(vec[0]) != defines.end()) {
        flag = false;
        return;
    }
    flag = true;
}
void Pre::ifdef(const std::string& str) {
    auto vec = split(str, " ");
    if(defines.find(vec[0]) != defines.end()) {
        flag = true;
        return;
    }
    flag = false;
}
void Pre::endif(const std::string& str) {
    flag = true;
}

