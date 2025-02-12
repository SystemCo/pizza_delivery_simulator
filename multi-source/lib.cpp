#include <iostream>
#include <string>
#include "lib.h"
using namespace std;

Greeting::Greeting() :
    message("Hello World!\n")
{}
void Greeting::print()
{
    cout << this->message;
}
