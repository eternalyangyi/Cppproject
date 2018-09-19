//
//  EuclideanVector.h
//  EuclideanVector
//
//  Created by YiYANG on 31/8/17.
//  z5045056
//  Copyright © 2017 yy. All rights reserved.
//
#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#ifndef EUCLIDEANVECTOR_H
#define EUCLIDEANVECTOR_H
namespace evec
{
    class EuclideanVector
    {
        
    public:
        
        //EuclidenVector c; // or c{}
        EuclideanVector();
        
        //EuclidenVector b(2);
        EuclideanVector(const unsigned int VS);
        
        
        //EuclideanVector a(2,4.0)
        EuclideanVector(const unsigned int VS, double V);
        /*EuclideanVector a{list.begin(),list.end()}
        or
          EuclideanVector a{vector.begin(),vector.end()}*/
        EuclideanVector(const std::list<double>::const_iterator begin, const std::list<double>::const_iterator end);
        EuclideanVector(const std::vector<double>::const_iterator begin, const std::vector<double>::const_iterator end);
        //initialiser-list constructor
        EuclideanVector(std::initializer_list<double> list);
        
        //Destructor
        void delete_function();
        ~EuclideanVector();
        
        //Copy&Move construtor and assignment
        EuclideanVector(const EuclideanVector& copy);
        EuclideanVector(EuclideanVector&& move);
        EuclideanVector& operator=(const EuclideanVector& copy);
        EuclideanVector& operator=(EuclideanVector&& move);
        
        //Operations
        unsigned int getNumDimensions() const;
        double get(unsigned int index) const;
        double getEuclideanNorm() const;
        EuclideanVector& createUnitVector() const;

        double& operator[] (int index){
            return my_vector[index];
        };
        double operator[] (int index) const{
            return my_vector[index];
        };
        EuclideanVector& operator+= (const EuclideanVector& vector);
        EuclideanVector& operator-= (const EuclideanVector& vector);
        EuclideanVector& operator*= (const double num);
        EuclideanVector& operator/= (const double num);
        
        //Type conversion
        operator std::vector<double>() const;
        operator std::list<double>() const;
        
        //Nonmember function
        friend EuclideanVector& operator+ (const EuclideanVector &EV1,const EuclideanVector &EV2);
        friend EuclideanVector& operator- (const EuclideanVector &EV1,const EuclideanVector &EV2);
        friend double operator* (const EuclideanVector &EV1,const EuclideanVector &EV2);
        friend EuclideanVector operator* ( EuclideanVector EV1,const double num);
        friend EuclideanVector operator* (const double num, EuclideanVector EV1);
        friend EuclideanVector operator/ ( EuclideanVector EV1,const double num);
        friend std::ostream& operator<< (std::ostream& os, const EuclideanVector& EV);
        friend bool operator== (const EuclideanVector &EV1,const EuclideanVector &EV2);
        friend bool operator!= (const EuclideanVector &EV1,const EuclideanVector &EV2);

    private:
        unsigned int vector_size;
        double* my_vector = nullptr;
    };
    EuclideanVector& operator+ (const EuclideanVector &EV1,const EuclideanVector &EV2);
    EuclideanVector& operator- (const EuclideanVector &EV1,const EuclideanVector &EV2);
    double operator* (const EuclideanVector &EV1,const EuclideanVector &EV2);
    EuclideanVector operator* ( EuclideanVector EV1,const double num);
    EuclideanVector operator* (const double num, EuclideanVector EV1);
    EuclideanVector operator/ ( EuclideanVector EV1,const double num);
    std::ostream& operator<< (std::ostream& os, const EuclideanVector& EV);
    bool operator== (const EuclideanVector &EV1,const EuclideanVector &EV2);
    bool operator!= (const EuclideanVector &EV1,const EuclideanVector &EV2);
}
#endif //EUCLIDEANVECTOR_H
