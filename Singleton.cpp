#include "Singleton.h"

#include <iostream>
#include <string>
using namespace std;


Singleton* Singleton::inst_ = NULL;

Singleton* Singleton::getInstance() {
    if (inst_ == NULL) {
        inst_ = new Singleton();
    }
    return(inst_);
}
