//
//  BucketSort.h
//  BucketSort
//
//  Created by yy on 22/10/17.
//  Copyright © 2017 yy. All rights reserved.
//

#ifndef BucketSort_h
#define BucketSort_h
#include <vector>


struct BucketSort {
    // vector of numbers

    std::vector<unsigned int> numbersToSort;
    void sort(unsigned int numCores);
};

#endif /* BucketSort_h */
