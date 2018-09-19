//
//  BucketSort.cpp
//  BucketSort
//
//  Created by yy on 22/10/17.
//  Copyright © 2017 yy. All rights reserved.
//

#include "BucketSort.h"
#include <thread>
#include <iostream>
#include <vector>
#include <mutex>
#include <algorithm>
#include <cmath>
#include <string>
#include <list>
std::mutex mu[11];


int assignBucket(const unsigned int number,const unsigned int Pos){
    if(number == 0){
        return 0;
    }
    unsigned int length = 10;
    unsigned int c = 1000000000;
    while(number < c){
        c = c/10;
        --length;
    }
    unsigned int d = 0;
    if( length > Pos){
        d = Pos;
    }else{
        if(Pos>length ){
            return 0;
        }else{
            d = length;
        }
    }
    if(d == length){
        return 0;
    }
    unsigned int numOfPos = number;
    numOfPos = numOfPos / int(pow(10,length-d-1));
    numOfPos = numOfPos % 10;
    return int(numOfPos+1);
    
}

std::vector<unsigned int> sortRec(std::vector<unsigned int>& buckets,const int pos){
    std::vector<std::vector<unsigned int>> b(11,std::vector<unsigned int>());
    std::vector<unsigned int> current_results;
    bool created_next_level = false;
    for(auto num:buckets){
        auto j = assignBucket(num,pos);
        b[j].push_back(num);
        if(j > 0){
            created_next_level = true;
        }
    }
    if (!created_next_level) {
        return buckets;
    }
    for (auto bucket : b) {
        if (bucket.size() != 0) {
            auto sub_results = sortRec(bucket, pos + 1);
            std::move(std::begin(sub_results), std::end(sub_results), std::back_inserter(current_results));
            sub_results.clear();
        }
    }
    if (pos == 1) {
        buckets = std::move(current_results);
        return buckets;
    }
    else{
        return current_results;
    }
}
void sortFunc(std::vector<std::vector<unsigned int>>& buckets, int pos){
    for(size_t i = 0; i != buckets.size();++i){
        if(mu[i].try_lock()){
            auto b = sortRec(buckets[i], pos);
        }
    }
}

void BucketSort::sort(unsigned int numCores){
    std::vector<std::vector<unsigned int>> buckets(11,std::vector<unsigned int>());
    std::vector<std::thread> multiThread;
    for(size_t i = 0; i != BucketSort::numbersToSort.size();++i){
        unsigned int num =BucketSort::numbersToSort[i];
        buckets[assignBucket(num,0)].push_back(num);
    }
    for(unsigned int i = 0; i != numCores; ++i){
        multiThread.push_back(std::thread(sortFunc, std::ref(buckets), 1));
    }

    for (auto& th : multiThread) {
        th.join();
    }
    multiThread.clear();
    numbersToSort = std::move(buckets[0]);
    for (size_t i = 1; i != buckets.size(); ++i) {
        std::move(std::begin(buckets[i]), std::end(buckets[i]), std::back_inserter(numbersToSort));
        buckets[i].clear();
    }
    for(size_t i = 0; i != 11;i++){
        mu[i].unlock();
    }
}


