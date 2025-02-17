#include <iostream>
#include <string>
#include "lib.h"

using namespace std;
void Greeting::print()
{
    cout << this->message;
    system("echo hello world");
}
