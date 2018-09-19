/**
 * THE CODE HEREIN IS PROVIDED AS IS, WITH NO EXPRESS, OR IMPLIED, WARRANTIES
 * OR SUITABILITY FOR PURPOSE! This means it is up to you to figure out how
 * it works, fix it if something is broken, and adapt it as appropriate for
 * your needs.
 *
 * It is supplied as a starting point for your testing. Of course, it is
 * inadequate as your only test and you will be in trouble if you
 * do not write lots and lots of additional tests of your own!
 **/

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <cassert>
#include "btree.h"
#include <sstream>

using std::copy;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::set;
using std::string;

int main(){
    btree<int> testContainer(4);
    testContainer.insert(1);
    testContainer.insert(3);
    testContainer.insert(5);
    testContainer.insert(7);
    testContainer.insert(0);
    testContainer.insert(2);
    
    btree<int>::iterator iter = testContainer.begin();
    std::cout << *iter << std::endl;
    ++iter;
    std::cout << *iter << std::endl;
        
    
        
}


