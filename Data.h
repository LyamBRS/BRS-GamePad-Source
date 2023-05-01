/**
 * @file Data.h
 * @author Lyam (lyam.brs@gmail.com)
 * @brief This file contains the declaration
 * of the global data class commonly used
 * throughout this application.
 * See the data class definition for more
 * information regarding its members and
 * methods aswell as generic purpose.
 * @version 0.1
 * @date 2023-04-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/*  ############    ############     ##########
    ############    ############     ##########
              ##              ##   ## 
    ####    ##      ####    ##     ############
    ####    ##      ####    ##     ############
              ##              ##             ##
    ############    ####      ##   ##########
    ############    ####      ##   ##########*/

#ifndef DATA_H
  #define DATA_H

#pragma region  Include
#include "Globals.h"
#pragma endregion

#pragma region Class
/**
 * @brief The Data class is used
 * to handle intermediate type
 * conversions for BFIO highway
 * transmissions and receptions.
 */
class cData
{       
    private:
        int _status = Status::Booting;   
        /** @brief The size of the data byte array */
        int _sizeOfByteArray = 0;

    public:
        /////////////////////////////////////////
        /**
         * @brief Variable which holds the 
         * object's initialization status.
         * If set to true, the object was 
         * successfully initialized and thus 
         * can be used without potential errors. 
         * Otherwise, it is set to false by 
         * default.
         */
        bool built = false;
        /////////////////////////////////////////
        ///@brief Construct a new cData object
        cData();
        //////////////////////////////////////////////////////////// - TO BYTES OVERLOADS - 
        /** @brief Convert a boolean to an array of bytes
         * @param value variable to convert
         * @param resultedByteArray array to fill with bytes
         * @param sizeOfGivenArray size of the array to fill with bytes (Minimum: 1)
         * @return
         */
        Execution ToBytes(bool value,                unsigned char* resultedByteArray, int sizeOfGivenArray);
        /** @brief Convert an unsigned char to an array of bytes
         * @param value variable to convert
         * @param resultedByteArray array to fill with bytes
         * @param sizeOfGivenArray size of the array to fill with bytes (Minimum: 1)
         * @return
         */
        Execution ToBytes(unsigned char value,       unsigned char* resultedByteArray, int sizeOfGivenArray);
        /** @brief Convert a char to an array of bytes
         * @param value variable to convert
         * @param resultedByteArray array to fill with bytes
         * @param sizeOfGivenArray size of the array to fill with bytes (Minimum: 1)
         * @return
         */
        Execution ToBytes(char value,                unsigned char* resultedByteArray, int sizeOfGivenArray);
        /** @brief Convert an unsigned short to an array of bytes
         * @param value variable to convert
         * @param resultedByteArray array to fill with bytes
         * @param sizeOfGivenArray size of the array to fill with bytes (Minimum: 2)
         * @return
         */
        Execution ToBytes(unsigned short value,      unsigned char* resultedByteArray, int sizeOfGivenArray);
        /** @brief Convert a short to an array of bytes
         * @param value variable to convert
         * @param resultedByteArray array to fill with bytes
         * @param sizeOfGivenArray size of the array to fill with bytes (Minimum: 2)
         * @return
         */
        Execution ToBytes(short value,               unsigned char* resultedByteArray, int sizeOfGivenArray);
        /** @brief Convert an unsigned int to an array of bytes
         * @param value variable to convert
         * @param resultedByteArray array to fill with bytes
         * @param sizeOfGivenArray size of the array to fill with bytes (Minimum: 4)
         * @return
         */
        Execution ToBytes(unsigned int value,        unsigned char* resultedByteArray, int sizeOfGivenArray);
        /** @brief Convert an int to an array of bytes
         * @param value variable to convert
         * @param resultedByteArray array to fill with bytes
         * @param sizeOfGivenArray size of the array to fill with bytes (Minimum: 4)
         * @return
         */
        Execution ToBytes(int value,                 unsigned char* resultedByteArray, int sizeOfGivenArray);
        /** @brief Convert an unsigned long to an array of bytes
         * @attention Array size based off 64 bits architecture regardless of actual architecture.
         * @param value variable to convert
         * @param resultedByteArray array to fill with bytes
         * @param sizeOfGivenArray size of the array to fill with bytes (Minimum: 8)
         * @return
         */
        Execution ToBytes(unsigned long value,       unsigned char* resultedByteArray, int sizeOfGivenArray);
        /** @brief Convert a long to an array of bytes
         * @attention Array size based off 64 bits architecture regardless of actual architecture.
         * @param value variable to convert
         * @param resultedByteArray array to fill with bytes
         * @param sizeOfGivenArray size of the array to fill with bytes (Minimum: 8)
         * @return
         */
        Execution ToBytes(long value,                unsigned char* resultedByteArray, int sizeOfGivenArray);
        /** @brief Convert an unsigned long long to an array of bytes
         * @attention Array size based off 64 bits architecture regardless of actual architecture.
         * @param value variable to convert
         * @param resultedByteArray array to fill with bytes
         * @param sizeOfGivenArray size of the array to fill with bytes (Minimum: 8)
         * @return
         */
        Execution ToBytes(unsigned long long value,  unsigned char* resultedByteArray, int sizeOfGivenArray);
        /** @brief Convert a long long to an array of bytes
         * @attention Array size based off 64 bits architecture regardless of actual architecture.
         * @param value variable to convert
         * @param resultedByteArray array to fill with bytes
         * @param sizeOfGivenArray size of the array to fill with bytes (Minimum: 8)
         * @return
         */
        Execution ToBytes(long long value,           unsigned char* resultedByteArray, int sizeOfGivenArray);
        /** @brief Convert a float to an array of bytes
         * @attention Array size based off sizeOf function. This can be dangerous.
         * @param value variable to convert
         * @param resultedByteArray array to fill with bytes
         * @param sizeOfGivenArray size of the array to fill with bytes (Minimum: 4)
         * @return
         */
        Execution ToBytes(float value,               unsigned char* resultedByteArray, int sizeOfGivenArray);
        /** @brief Convert a double to an array of bytes
         * @attention Array size based off sizeOf function. This can be dangerous.
         * @param value variable to convert
         * @param resultedByteArray array to fill with bytes
         * @param sizeOfGivenArray size of the array to fill with bytes (Minimum: 8)
         * @return
         */
        Execution ToBytes(double value,              unsigned char* resultedByteArray, int sizeOfGivenArray);
        /** @brief Convert a string to an array of bytes
         * @attention Array size based off string lenght. This can be dangerous.
         * @param value variable to convert
         * @param resultedByteArray array to fill with bytes
         * @param sizeOfGivenArray size of the array to fill with bytes (Minimum: depends)
         * @return
         */
        Execution ToBytes(const std::string& value,        unsigned char* resultedByteArray, int sizeOfGivenArray);
        //////////////////////////////////////////////////////////// - TO TYPE OVERLOADS - 
        Execution ToType(bool value,                int* resultedDataType);
        Execution ToType(unsigned char value,       int* resultedDataType);
        Execution ToType(char value,                int* resultedDataType);
        Execution ToType(unsigned short value,      int* resultedDataType);
        Execution ToType(short value,               int* resultedDataType);
        Execution ToType(unsigned int value,        int* resultedDataType);
        Execution ToType(int value,                 int* resultedDataType);
        Execution ToType(unsigned long value,       int* resultedDataType);
        Execution ToType(long value,                int* resultedDataType);
        Execution ToType(unsigned long long value,  int* resultedDataType);
        Execution ToType(long long value,           int* resultedDataType);
        Execution ToType(float value,               int* resultedDataType);
        Execution ToType(double value,              int* resultedDataType);
        Execution ToType(long double value,         int* resultedDataType);
        Execution ToType(std::string value,         int* resultedDataType);
        //////////////////////////////////////////////////////////// - Others
        
        Execution ToData(bool* value,                unsigned char* ConvertedByteArray, int sizeOfGivenArray);
        Execution ToData(unsigned char* value,       unsigned char* ConvertedByteArray, int sizeOfGivenArray);
        Execution ToData(char* value,                unsigned char* ConvertedByteArray, int sizeOfGivenArray);
        Execution ToData(unsigned short* value,      unsigned char* ConvertedByteArray, int sizeOfGivenArray);
        Execution ToData(short* value,               unsigned char* ConvertedByteArray, int sizeOfGivenArray);
        Execution ToData(unsigned int* value,        unsigned char* ConvertedByteArray, int sizeOfGivenArray);
        Execution ToData(int* value,                 unsigned char* ConvertedByteArray, int sizeOfGivenArray);
        Execution ToData(unsigned long* value,       unsigned char* ConvertedByteArray, int sizeOfGivenArray);
        Execution ToData(long* value,                unsigned char* ConvertedByteArray, int sizeOfGivenArray);
        Execution ToData(unsigned long long* value,  unsigned char* ConvertedByteArray, int sizeOfGivenArray);
        Execution ToData(long long* value,           unsigned char* ConvertedByteArray, int sizeOfGivenArray);
        Execution ToData(float* value,               unsigned char* ConvertedByteArray, int sizeOfGivenArray);
        Execution ToData(double* value,              unsigned char* ConvertedByteArray, int sizeOfGivenArray);
        Execution ToData(std::string& value,         unsigned char* ConvertedByteArray, int sizeOfGivenArray);
        /**
         * @brief Gets the size of the array
         * returned by ToBytes functions.
         * @param size
         * pointer where the size of the byte array will be placed.
         * @return Execution 
         */
        Execution GetArraySize(unsigned char* size);

};
#pragma endregion

#endif
  