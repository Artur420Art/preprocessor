#include "pre.h"

int main(int argc, char* argv[]) {
    Pre obj;
    if (argc >= 2) {
        obj.pre_process(argv[1]);
    }else {
        throw std::logic_error("pleas input file");
    }
}
