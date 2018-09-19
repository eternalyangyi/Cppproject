//
//  EuclideanVector.cpp
//  EuclideanVector
//
//  Created by YiYANG on 31/8/17.
//  z5045056
//  Copyright © 2017 yy. All rights reserved.
//
#include <iostream>
#include <vector>
#include <list>
#include "EuclideanVector.h"
    //EuclidenVector c; // or c{}
    evec::EuclideanVector::EuclideanVector() : evec::EuclideanVector::EuclideanVector(1) {}

    //EuclidenVector b(2)
    evec::EuclideanVector::EuclideanVector(const unsigned int VS) : vector_size{VS}{
        my_vector = new double[VS];
        for(unsigned int i=0;i != (unsigned int) VS;++i){
            my_vector[i] = 0.0;
        }
    }

    //EuclideanVector a(2,4.0)
    evec::EuclideanVector::EuclideanVector(const unsigned int VS, double V):vector_size{VS}{
        my_vector = new double[VS];
        for(unsigned int i=0;i != (unsigned int)VS;++i){
            my_vector[i] = V;
        }
    }
    //initialiser-list constructor
    evec::EuclideanVector::EuclideanVector(std::initializer_list<double> list){
            vector_size = (unsigned int) (list.size());
            my_vector = new double[vector_size];
            unsigned int i = 0;
            for(auto first = list.begin(); first != list.end();++first){
                my_vector[i] = *first;
                i++;
            }
        
    }
    /*EuclideanVector a{list.begin(),list.end()}
     or
     EuclideanVector a{vector.begin(),vector.end()}*/
    evec::EuclideanVector::EuclideanVector(const std::list<double>::const_iterator begin, const std::list<double>::const_iterator end){
        vector_size = (unsigned int) (std::distance(begin, end));
        my_vector = new double[vector_size];
        unsigned int i = 0;
        for(auto first = begin; first != end;++first){
            my_vector[i] = *first;
            i++;
        }
    }
    evec::EuclideanVector::EuclideanVector(const std::vector<double>::const_iterator begin, const std::vector<double>::const_iterator end){
        vector_size = (unsigned int) (std::distance(begin, end));
        my_vector = new double[vector_size];
        unsigned int i = 0;
        for(auto first = begin; first != end;++first){
            my_vector[i] = *first;
            i++;
        }
    }

    //Delete function
    void evec::EuclideanVector::delete_function(){
        if (my_vector != nullptr) {
            delete[] my_vector;
        }
    }
    //Destructor
    evec::EuclideanVector::~EuclideanVector(){
        delete_function();
        my_vector = nullptr;
    }
    
    //Copy construtor
    evec::EuclideanVector::EuclideanVector(const evec::EuclideanVector& Copy) :
        vector_size{Copy.vector_size}
    {
        delete_function();
        my_vector = new double [vector_size];
        double *temp = Copy.my_vector;
        for (unsigned int i = 0; i < vector_size; i++) {
            my_vector[i] = temp[i];
        }
        
    }
    
    //Move construtor
    evec::EuclideanVector::EuclideanVector(evec::EuclideanVector&& Move) :
        vector_size{std::move(Move.vector_size)}
    {
        delete_function();
        Move.vector_size = 0;
        my_vector = std::move(Move.my_vector);
        Move.my_vector = nullptr;
        
    }
    
    //Copy assignment operator
    evec::EuclideanVector& evec::EuclideanVector::operator=(const evec::EuclideanVector& Copy)
    {
        if (this != &Copy) {
            delete_function();
            vector_size = Copy.vector_size;
            my_vector = new double [vector_size];
            double *temp = Copy.my_vector;
            for (unsigned int i = 0; i != vector_size;i++) {
                my_vector[i] = temp[i];
            }
        }
        
        return *this;
    }
    
    //Move assignment operator
    evec::EuclideanVector& evec::EuclideanVector::operator=(evec::EuclideanVector&& Move)
    {
        if (this != &Move) {
            delete_function();
            vector_size = std::move(Move.vector_size);
            Move.vector_size = 0;
            my_vector = std::move(Move.my_vector);
            Move.my_vector = nullptr;
        }
        return *this;
    }
    
    //getNumDimensions operator
    unsigned int evec::EuclideanVector::getNumDimensions() const {
        return (unsigned int) vector_size;;
    }
    
    //get() operator
    double evec::EuclideanVector::get(unsigned int index) const {
        return my_vector[index];
    }
    
    //getEuclideanNorm operator
    double evec::EuclideanVector::getEuclideanNorm() const{
        double sum = 0.0;
        for(unsigned int i=0; i != vector_size;++i){
            double sub_sum = my_vector[i];
            sum += sub_sum * sub_sum;
        }
        return sqrt(sum);
    }
    
    //createUnitVector operator
    evec::EuclideanVector& evec::EuclideanVector::createUnitVector() const{
        double norm = getEuclideanNorm();
        std::vector<double> temp;
        for(unsigned int i=0;i!= vector_size; ++i){
            temp.push_back(my_vector[i] / norm);
        }
        //Using temp to store result, then convert it into EuclideanVector object.
        EuclideanVector *UnitVector = new EuclideanVector(temp.begin(),temp.end());
        return *UnitVector;
    }
    
    
    //Type Conversion operator
    evec::EuclideanVector::operator std::vector<double>() const{
        std::vector<double> v;
        for(unsigned int i=0; i != vector_size; ++i ){
            v.push_back(my_vector[i]);
        }
        return v;
    }
    evec::EuclideanVector::operator std::list<double>() const{
        std::list<double> l;
        for(unsigned int i=0; i < vector_size; ++i ){
            l.push_back(my_vector[i]);
        }
        return l;
    }
    
    //Operator {+=, -=, *=, /=}
    evec::EuclideanVector& evec::EuclideanVector::operator+= (const evec::EuclideanVector& vector){
        for(unsigned int i= 0; i != vector.vector_size;++i){
            my_vector[i] += vector.my_vector[i];
        }
        return *this;
    }
    evec::EuclideanVector& evec::EuclideanVector::operator-= (const evec::EuclideanVector& vector){
        for(unsigned int i= 0; i != vector.vector_size;++i){
            my_vector[i] -= vector.my_vector[i];
        }
        return *this;
    }
    
    evec::EuclideanVector& evec::EuclideanVector::operator*= (const double num){
        for(unsigned int i= 0; i != vector_size;++i){
            my_vector[i] *= num;
        }
        return *this;
    }
    evec::EuclideanVector& evec::EuclideanVector::operator/= (const double num){
        for(unsigned int i= 0; i != vector_size;++i){
            my_vector[i] /= num;
        }
        return *this;
    }
    
    
    //Nonmember functions {+,-,*,/}
    evec::EuclideanVector& evec::operator+ (const evec::EuclideanVector &EV1, const evec::EuclideanVector &EV2){
        unsigned int size = EV1.vector_size;
        std::vector<double> temp;
        for(unsigned int i= 0;i != size;++i ){
            temp.push_back(EV1.get(i) + EV2.get(i));
        }
        //Using temp to store result, then convert it into EuclideanVector object.
        EuclideanVector *SumVector = new EuclideanVector(temp.begin(),temp.end());
        return *SumVector;
    }
    evec::EuclideanVector& evec::operator- (const evec::EuclideanVector &EV1,const evec::EuclideanVector &EV2){
        unsigned int size = EV1.vector_size;
        std::vector<double> temp;
        for(unsigned int i= 0;i != size;++i ){
            temp.push_back(EV1.get(i) - EV2.get(i));
        }
        //Using temp to store result, then convert it into EuclideanVector object.
        EuclideanVector *SubVector = new EuclideanVector(temp.begin(),temp.end());
        return *SubVector;
    }
    double evec::operator* (const evec::EuclideanVector &EV1,const evec::EuclideanVector &EV2){
        double sum = 0.0;
        unsigned int size = EV1.vector_size;
        for(unsigned int i= 0;i != size;++i ){
            sum += EV1.get(i) * EV2.get(i);
        }
        return sum;
    }
    evec::EuclideanVector evec::operator/ ( evec::EuclideanVector EV1,const double num){
        return EV1 /= num;
    }
    evec::EuclideanVector evec::operator* ( evec::EuclideanVector EV1,const double num){
        return EV1 *= num;
    }
    evec::EuclideanVector evec::operator* (const double num, evec::EuclideanVector EV1){
        return EV1 *= num;
    }
    
    //Operator <<
    std::ostream& evec::operator<< (std::ostream& os, const evec::EuclideanVector& EV){
        os<<"[";
        unsigned int size= EV.vector_size;
        if (size !=0){
        for(unsigned int i =0;i != size;i++){
            os<< EV.my_vector[i];
            if(i != (size-1)){
                os<<" ";
                }
            }
        }
        os<<"]";
        return os;
    }
    
    //Nonmember functions {==,!=}
    bool evec::operator== (const evec::EuclideanVector &EV1,const evec::EuclideanVector &EV2){
        if(EV1.vector_size!=EV2.vector_size){
            return false;
        }
        for(unsigned int i = 0; i !=  EV1.vector_size;++i){
            if(EV1.my_vector[i] != EV2.my_vector[i]){
                return false;
            }
        }
        return true;
    }
    bool evec::operator!= (const evec::EuclideanVector &EV1,const evec::EuclideanVector &EV2){
        if(EV1.vector_size!=EV2.vector_size){
            return true;
        }
        for(unsigned int i = 0; i != EV1.vector_size;++i){
            if(EV1.my_vector[i] != EV2.my_vector[i]){
                return true;
            }
        }
        return false;
    }
