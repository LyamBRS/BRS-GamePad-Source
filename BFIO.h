/*
    ############    ############     ##########
    ############    ############     ##########
              ##              ##   ## 
    ####    ##      ####    ##     ############
    ####    ##      ####    ##     ############
              ##              ##             ##
    ############    ####      ##   ##########
    ############    ####      ##   ##########

    Title: BFIO.h
    Author: Lyam
*/

#ifndef BFIO_H
  #define BFIO_H
//================================================================================================//
//	Include
//================================================================================================//
#include "Enums.h"
#include <stdio>
//================================================================================================//
//	Define
//================================================================================================//
  
class Data
 {       
    private:
        /** @brief The size of the data byte array */
        int size = 0;
           
    public:
        //////////////////////////////////////////////////////////// - TO BYTES OVERLOADS - 
        unsigned char* ToBytes(bool value);
        unsigned char* ToBytes(unsigned char value);
        unsigned char* ToBytes(char value);
        unsigned char* ToBytes(unsigned short value);
        unsigned char* ToBytes(short value);
        unsigned char* ToBytes(unsigned int value);
        unsigned char* ToBytes(int value);
        unsigned char* ToBytes(unsigned long value);
        unsigned char* ToBytes(long value);
        unsigned char* ToBytes(unsigned long long value);
        unsigned char* ToBytes(long long value);
        unsigned char* ToBytes(float value);
        unsigned char* ToBytes(double value);
        unsigned char* ToBytes(long double value);
        unsigned char* ToBytes(std::string value);
        unsigned char* ToBytes(const char value);
        //////////////////////////////////////////////////////////// - TO TYPE OVERLOADS - 
        DataType ToBytes(bool value);
        DataType ToBytes(unsigned char value);
        DataType ToBytes(char value);
        DataType ToBytes(unsigned short value);
        DataType ToBytes(short value);
        DataType ToBytes(unsigned int value);
        DataType ToBytes(int value);
        DataType ToBytes(unsigned long value);
        DataType ToBytes(long value);
        DataType ToBytes(unsigned long long value);
        DataType ToBytes(long long value);
        DataType ToBytes(float value);
        DataType ToBytes(double value);
        DataType ToBytes(long double value);
        DataType ToBytes(std::string value);
        DataType ToBytes(const char value);
        //////////////////////////////////////////////////////////// - Others
        Execution GetArraySize(unsigned char* size);
 };

#endif