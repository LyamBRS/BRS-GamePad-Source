/**
 * @file Data.ino
 * @author Lyam (lyam.brs@gmail.com)
 * @brief This file contains the core
 * methods of the Data class as declared
 * in Data.h
 * @version 0.1
 * @date 2023-04-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
/////////////////////////////////////////////////////////////////////////////
#include "Globals.h"
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief Construct a new Data object
 * Will set the built variable to true.
 */
cData::cData()
{
    built = true;
}
//////////////////////////////////////////////////////////// - TO BYTES OVERLOADS - 
#pragma region ToBytes
/// @brief Convert a boolean to an array of bytes
/// @param value variable to convert
/// @param resultedByteArray array to fill with bytes
/// @param sizeOfGivenArray size of the array to fill with bytes
/// @return 
Execution cData::ToBytes(bool value,                unsigned char* resultedByteArray, int sizeOfGivenArray)
{
    _sizeOfByteArray = 1;

    if(sizeOfGivenArray >= _sizeOfByteArray)
    {
        resultedByteArray[0] = (unsigned char)value;
        return Execution::Passed;
    }
    else
    {
        return Execution::Failed;
    }
}

/// @brief Convert an unsigned char to an array of bytes
/// @param value variable to convert
/// @param resultedByteArray array to fill with bytes
/// @param sizeOfGivenArray size of the array to fill with bytes
/// @return 
Execution cData::ToBytes(unsigned char value,       unsigned char* resultedByteArray, int sizeOfGivenArray)
{
    _sizeOfByteArray = 1;

    if(sizeOfGivenArray >= _sizeOfByteArray)
    {
        resultedByteArray[0] = value;
        return Execution::Passed;
    }
    else
    {
        return Execution::Failed;
    }
}

/// @brief Convert a char to an array of bytes
/// @param value variable to convert
/// @param resultedByteArray array to fill with bytes
/// @param sizeOfGivenArray size of the array to fill with bytes
/// @return 
Execution cData::ToBytes(char value,                unsigned char* resultedByteArray, int sizeOfGivenArray)
{
    _sizeOfByteArray = 1;

    if(sizeOfGivenArray >= _sizeOfByteArray)
    {
        unsigned char newValue = 0;
        if (value >= 0) {
            // If the original char is non-negative, we can simply cast it to an unsigned char
            newValue = static_cast<unsigned char>(value);
        } else {
            // If the original char is negative, we need to first cast it to an unsigned int
            // to ensure that the sign bit is properly converted to an unsigned value
            newValue = static_cast<unsigned char>(static_cast<unsigned int>(value));
        }

        resultedByteArray[0] = newValue;
        return Execution::Passed;
    }
    else
    {
        return Execution::Failed;
    }
}

/// @brief Convert an unsigned short to an array of bytes
/// @param value variable to convert
/// @param resultedByteArray array to fill with bytes
/// @param sizeOfGivenArray size of the array to fill with bytes
/// @return 
Execution cData::ToBytes(unsigned short value,      unsigned char* resultedByteArray, int sizeOfGivenArray)
{
    _sizeOfByteArray = 2;

    if(sizeOfGivenArray >= _sizeOfByteArray)
    {
        unsigned char highValue = 0;
        unsigned char lowValue = 0;

        lowValue = (unsigned char)(value & 0x00FF);
        value = value >> 8;
        highValue = (unsigned char)((value & 0xFF));

        resultedByteArray[0] = lowValue;
        resultedByteArray[1] = highValue;

        return Execution::Passed;
    }
    else
    {
        return Execution::Failed;
    }
}

/// @brief Convert a short to an array of bytes
/// @param value variable to convert
/// @param resultedByteArray array to fill with bytes
/// @param sizeOfGivenArray size of the array to fill with bytes
/// @return 
Execution cData::ToBytes(short value, unsigned char* resultedByteArray, int sizeOfGivenArray)
{
    _sizeOfByteArray = 2;

    if(sizeOfGivenArray >= _sizeOfByteArray)
    {
        unsigned char* p = reinterpret_cast<unsigned char*>(&value);
        for (int i = 0; i < _sizeOfByteArray; i++) {
            resultedByteArray[i] = *(p + i);
        }
        return Execution::Passed;
    }
    else
    {
        return Execution::Failed;
    }
}

/** @brief Convert an int (4 bytes) to an array of bytes
 * @attention THIS CONVERT TO 4 BYTES REGARDLESS OF CPU'S ARCHITECTURE.
 * @param value variable to convert
 * @param resultedByteArray array to fill with bytes
 * @param sizeOfGivenArray size of the array to fill with bytes
 * @return
 */
Execution cData::ToBytes(int value, unsigned char* resultedByteArray, int sizeOfGivenArray)
{
    _sizeOfByteArray = 4;

    if(sizeOfGivenArray >= _sizeOfByteArray)
    {
        unsigned char* p = reinterpret_cast<unsigned char*>(&value);
        for (int i = 0; i < _sizeOfByteArray; i++) {
            resultedByteArray[i] = *(p + i);
        }
        return Execution::Passed;
    }
    else
    {
        return Execution::Failed;
    }
}

/** @brief Convert an unsigned long (8 bytes) to an array of bytes
 * @attention THIS CONVERT TO 8 BYTES REGARDLESS OF CPU'S ARCHITECTURE.
 * @param value variable to convert
 * @param resultedByteArray array to fill with bytes
 * @param sizeOfGivenArray size of the array to fill with bytes
 * @return
 */
Execution cData::ToBytes(unsigned long value,       unsigned char* resultedByteArray, int sizeOfGivenArray)
{
    _sizeOfByteArray = 8;

    if(sizeOfGivenArray >= _sizeOfByteArray)
    {
        for(int i=0; i<8; ++i)
        {
            if(i<4) // unsigned long is 8 bytes on a 64 bit architecture... this is a 32 bit architecture. Youpiii.
            {
                unsigned long result = (value >> (i*8)) & 0xFF;
                resultedByteArray[i] = (unsigned char) result;
            }
            else
            {
                resultedByteArray[i] = 0;
            }
        }
        return Execution::Passed;
    }
    else
    {
        return Execution::Failed;
    }   
}

/** @brief Convert a long (8 bytes) to an array of bytes
 * @attention THIS CONVERT TO 8 BYTES REGARDLESS OF CPU'S ARCHITECTURE.
 * @param value variable to convert
 * @param resultedByteArray array to fill with bytes
 * @param sizeOfGivenArray size of the array to fill with bytes
 * @return
 */
Execution cData::ToBytes(long value, unsigned char* resultedByteArray, int sizeOfGivenArray)
{
    _sizeOfByteArray = 8;

    if(sizeOfGivenArray >= _sizeOfByteArray)
    {
        unsigned char* p = reinterpret_cast<unsigned char*>(&value);
        for (int i = 0; i < _sizeOfByteArray; i++) {
            resultedByteArray[i] = *(p + i);
        }
        return Execution::Passed;
    }
    else
    {
        return Execution::Failed;
    }
}

/// @brief Convert an unsigned int (4 bytes) to an array of bytes
/// @param value variable to convert
/// @param resultedByteArray array to fill with bytes
/// @param sizeOfGivenArray size of the array to fill with bytes
/// @return 
Execution cData::ToBytes(unsigned int value,        unsigned char* resultedByteArray, int sizeOfGivenArray)
{
    _sizeOfByteArray = 4;

    if(sizeOfGivenArray >= _sizeOfByteArray)
    {
        for(int i=0; i<4; ++i)
        {
            unsigned int result = (value >> (i*8)) & 0xFF;
            resultedByteArray[i] = (unsigned char) result;
        }
        return Execution::Passed;
    }
    else
    {
        return Execution::Failed;
    } 
}

/** @brief Convert an unsigned long long (8 bytes) to an array of bytes
 * @attention THIS CONVERT TO 8 BYTES REGARDLESS OF CPU'S ARCHITECTURE.
 * @param value variable to convert
 * @param resultedByteArray array to fill with bytes
 * @param sizeOfGivenArray size of the array to fill with bytes
 * @return
 */
Execution cData::ToBytes(unsigned long long value,  unsigned char* resultedByteArray, int sizeOfGivenArray)
{
    _sizeOfByteArray = 8;

    if(sizeOfGivenArray >= _sizeOfByteArray)
    {
        for(int i=0; i<8; ++i)
        {
            unsigned long long result = (value >> (i*8)) & 0xFF;
            resultedByteArray[i] = (unsigned char) result;
        }
        return Execution::Passed;
    }
    else
    {
        return Execution::Failed;
    }   
}

/** @brief Convert a long long (8 bytes) to an array of bytes
 * @param value variable to convert
 * @param resultedByteArray array to fill with bytes
 * @param sizeOfGivenArray size of the array to fill with bytes
 * @return
 */
Execution cData::ToBytes(long long value, unsigned char* resultedByteArray, int sizeOfGivenArray)
{
    _sizeOfByteArray = 8;

    if(sizeOfGivenArray >= _sizeOfByteArray)
    {
        unsigned char* p = reinterpret_cast<unsigned char*>(&value);
        for (int i = 0; i < _sizeOfByteArray; i++) {
            resultedByteArray[i] = *(p + i);
        }
        return Execution::Passed;
    }
    else
    {
        return Execution::Failed;
    }
}

/** @brief Convert a float to an array of bytes
 * @param value variable to convert
 * @param resultedByteArray array to fill with bytes
 * @param sizeOfGivenArray size of the array to fill with bytes
 * @return
 */
Execution cData::ToBytes(float value, unsigned char* resultedByteArray, int sizeOfGivenArray)
{
    _sizeOfByteArray = sizeof(float);

    if(sizeOfGivenArray >= _sizeOfByteArray)
    {
        unsigned char* p = reinterpret_cast<unsigned char*>(&value);
        for (int i = 0; i < _sizeOfByteArray; i++) {
            resultedByteArray[i] = *(p + i);
        }
        return Execution::Passed;
    }
    else
    {
        return Execution::Failed;
    }
}

/** @brief Convert a double to an array of bytes
 * @param value variable to convert
 * @param resultedByteArray array to fill with bytes
 * @param sizeOfGivenArray size of the array to fill with bytes
 * @return
 */
Execution cData::ToBytes(double value, unsigned char* resultedByteArray, int sizeOfGivenArray) 
{
    _sizeOfByteArray = 8; // 8 bytes in a double
    if (sizeOfGivenArray < _sizeOfByteArray) 
    {
        return Execution::Failed;
    }
    unsigned char* bytes = reinterpret_cast<unsigned char*>(&value);
    for (int i = 0; i < _sizeOfByteArray; ++i) 
    {
        resultedByteArray[i] = bytes[i];
    }
    return Execution::Passed;
}

/** @brief Convert a std::string to an array of bytes
 * @param value variable to convert
 * @param resultedByteArray array to fill with bytes
 * @param sizeOfGivenArray size of the array to fill with bytes
 * @return
 */
Execution cData::ToBytes(const std::string& value, unsigned char* resultedByteArray, int sizeOfGivenArray)
{
    int stringLength = value.length();
    if(sizeOfGivenArray >= stringLength)
    {
        const unsigned char* p = reinterpret_cast<const unsigned char*>(value.c_str());
        for (int i = 0; i < stringLength; i++) {
            resultedByteArray[i] = *(p + i);
        }
        return Execution::Passed;
    }
    else
    {
        return Execution::Failed;
    }
}
#pragma endregion
//////////////////////////////////////////////////////////// - TO TYPE OVERLOADS - 
#pragma region ToType
Execution cData::ToType(bool value,                int* resultedDataType)
{
    *resultedDataType = DataType::Bool;
    return Execution::Passed;
}
Execution cData::ToType(unsigned char value,       int* resultedDataType)
{
    *resultedDataType = DataType::UnsignedChar;
    return Execution::Passed;
}
Execution cData::ToType(char value,                int* resultedDataType)
{
    *resultedDataType = DataType::Char;
    return Execution::Passed;
}
Execution cData::ToType(unsigned short value,      int* resultedDataType)
{
    *resultedDataType = DataType::UnsignedShort;
    return Execution::Passed;
}
Execution cData::ToType(short value,               int* resultedDataType)
{
    *resultedDataType = DataType::Short;
    return Execution::Passed;
}
Execution cData::ToType(unsigned int value,        int* resultedDataType)
{
    *resultedDataType = DataType::UnsignedInt;
    return Execution::Passed;
}
Execution cData::ToType(int value,                 int* resultedDataType)
{
    *resultedDataType = DataType::Int;
    return Execution::Passed;
}
Execution cData::ToType(unsigned long value,       int* resultedDataType)
{
    *resultedDataType = DataType::UnsignedLong;
    return Execution::Passed;
}
Execution cData::ToType(long value,                int* resultedDataType)
{
    *resultedDataType = DataType::Long;
    return Execution::Passed;
}
Execution cData::ToType(unsigned long long value,  int* resultedDataType)
{
    *resultedDataType = DataType::UnsignedLongLong;
    return Execution::Passed;
}
Execution cData::ToType(long long value,           int* resultedDataType)
{
    *resultedDataType = DataType::LongLong;
    return Execution::Passed;
}
Execution cData::ToType(float value,               int* resultedDataType)
{
    *resultedDataType = DataType::Float;
    return Execution::Passed;
}
Execution cData::ToType(double value,              int* resultedDataType)
{
    *resultedDataType = DataType::Double;
    return Execution::Passed;
}
Execution cData::ToType(long double value,         int* resultedDataType)
{
    *resultedDataType = DataType::LongDouble;
    return Execution::Passed;
}
Execution cData::ToType(std::string value,         int* resultedDataType)
{
    *resultedDataType = DataType::String;
    return Execution::Passed;
}

#pragma endregion
//////////////////////////////////////////////////////////// - Other
#pragma region ToData
/**
 * @brief Convert a byte array to a boolean.
 * @param value pointer where the resulted data will be placed
 * @param ConvertedByteArray Array obtained from a ToByte function
 * @param sizeOfGivenArray size of the array given to this function
 * @return Execution 
 */
Execution cData::ToData(bool* value,                unsigned char* ConvertedByteArray, int sizeOfGivenArray)
{
    if(sizeOfGivenArray >= 1)
    {
        *value = (bool)(ConvertedByteArray[0]);
        return Execution::Passed;
    }
    else
    {
        return Execution::Failed;
    }
}

/**
 * @brief Convert a byte array to an unsigned char.
 * @param value pointer where the resulted data will be placed
 * @param ConvertedByteArray Array obtained from a ToByte function
 * @param sizeOfGivenArray size of the array given to this function
 * @return Execution 
 */
Execution cData::ToData(unsigned char* value,       unsigned char* ConvertedByteArray, int sizeOfGivenArray)
{
    if(sizeOfGivenArray >= 1)
    {
        *value = ConvertedByteArray[0];
        return Execution::Passed;
    }
    else
    {
        return Execution::Failed;
    }
}

/**
 * @brief Convert a byte array to a char.
 * @param value pointer where the resulted data will be placed
 * @param ConvertedByteArray Array obtained from a ToByte function
 * @param sizeOfGivenArray size of the array given to this function
 * @return Execution 
 */
Execution cData::ToData(char* value,                unsigned char* ConvertedByteArray, int sizeOfGivenArray)
{
    if(sizeOfGivenArray >= 1)
    {
        unsigned char* p = reinterpret_cast<unsigned char*>(value);
        for (int i = 0; i < 1; i++) {
            *(p + i) = ConvertedByteArray[i];
        }
        return Execution::Passed;
        return Execution::Passed;
    }
    else
    {
        return Execution::Failed;
    }  
}

/**
 * @brief Convert a byte array to an unsigned short.
 * @param value pointer where the resulted data will be placed
 * @param ConvertedByteArray Array obtained from a ToByte function
 * @param sizeOfGivenArray size of the array given to this function
 * @return Execution 
 */
Execution cData::ToData(unsigned short* value,      unsigned char* ConvertedByteArray, int sizeOfGivenArray)
{
    if(sizeOfGivenArray >= 2)
    {
        unsigned char highValue = 0;
        unsigned char lowValue = 0;
        unsigned short result = 0;

        lowValue = ConvertedByteArray[0]; 
        highValue = ConvertedByteArray[1];

        result = (((unsigned short)(highValue)) << 8);
        result = result + lowValue;

        *value = result;
        return Execution::Passed;
    }
    else
    {
        return Execution::Failed;
    }
}

/**
 * @brief Convert a byte array to a short.
 * @param value pointer where the resulted data will be placed
 * @param ConvertedByteArray Array obtained from a ToByte function
 * @param sizeOfGivenArray size of the array given to this function
 * @return Execution 
 */
Execution cData::ToData(short* value, unsigned char* ConvertedByteArray, int sizeOfGivenArray)
{
    if(sizeOfGivenArray >= 2)
    {
        unsigned char* p = reinterpret_cast<unsigned char*>(value);
        for (int i = 0; i < 2; i++) {
            *(p + i) = ConvertedByteArray[i];
        }
        return Execution::Passed;
    }
    else
    {
        return Execution::Failed;
    }  
}

/**
 * @brief Convert a byte array to an unsigned int.
 * @param value pointer where the resulted data will be placed
 * @param ConvertedByteArray Array obtained from a ToByte function
 * @param sizeOfGivenArray size of the array given to this function
 * @return Execution 
 */
Execution cData::ToData(unsigned int* value,        unsigned char* ConvertedByteArray, int sizeOfGivenArray)
{
    _sizeOfByteArray = 4;

    if(sizeOfGivenArray >= _sizeOfByteArray)
    {
        unsigned int result = 0;
        for(int i=0; i<4; ++i)
        {
            unsigned char convertedByte = ConvertedByteArray[i];
            result = result + (((unsigned int)convertedByte) << (8*i));
        }
        *value = result;
        return Execution::Passed;
    }
    else
    {
        return Execution::Failed;
    } 
}

/**
 * @brief Convert a byte array to an int.
 * @param value pointer where the resulted data will be placed
 * @param ConvertedByteArray Array obtained from a ToByte function
 * @param sizeOfGivenArray size of the array given to this function
 * @return Execution 
 */
Execution cData::ToData(int* value, unsigned char* ConvertedByteArray, int sizeOfGivenArray)
{
    if(sizeOfGivenArray >= 4)
    {
        unsigned char* p = reinterpret_cast<unsigned char*>(value);
        for (int i = 0; i < 4; i++) {
            *(p + i) = ConvertedByteArray[i];
        }
        return Execution::Passed;
    }
    else
    {
        return Execution::Failed;
    }  
}

/**
 * @brief Convert a byte array to an unsigned long (8 bytes).
 * @attention This decodes ONLY THE FIRST 4 BYTES.
 * @param value pointer where the resulted data will be placed
 * @param ConvertedByteArray Array obtained from a ToByte function
 * @param sizeOfGivenArray size of the array given to this function
 * @return Execution 
 */
Execution cData::ToData(unsigned long* value,       unsigned char* ConvertedByteArray, int sizeOfGivenArray)
{
    _sizeOfByteArray = 8;

    if(sizeOfGivenArray >= _sizeOfByteArray)
    {
        unsigned long result = 0;
        for(int i=0; i<4; ++i)
        {
            unsigned char convertedByte = ConvertedByteArray[i];
            result = result + (((unsigned long)convertedByte) << (8*i));
        }
        *value = result;
        return Execution::Passed;
    }
    else
    {
        return Execution::Failed;
    } 
}

/**
 * @brief Convert a byte array to a long (8 bytes).
 * @attention This decodes ONLY THE FIRST 4 BYTES.
 * @param value pointer where the resulted data will be placed
 * @param ConvertedByteArray Array obtained from a ToByte function
 * @param sizeOfGivenArray size of the array given to this function
 * @return Execution 
 */
Execution cData::ToData(long* value, unsigned char* ConvertedByteArray, int sizeOfGivenArray)
{
    if(sizeOfGivenArray >= 8)
    {
        unsigned char* p = reinterpret_cast<unsigned char*>(value);
        for (int i = 0; i < 4; i++) {
            *(p + i) = ConvertedByteArray[i];
        }
        return Execution::Passed;
    }
    else
    {
        return Execution::Failed;
    }  
}

/**
 * @brief Convert a byte array to an unsigned long long (8 bytes).
 * @param value pointer where the resulted data will be placed
 * @param ConvertedByteArray Array obtained from a ToByte function
 * @param sizeOfGivenArray size of the array given to this function
 * @return Execution 
 */
Execution cData::ToData(unsigned long long* value,  unsigned char* ConvertedByteArray, int sizeOfGivenArray)
{
    _sizeOfByteArray = 8;

    if(sizeOfGivenArray >= _sizeOfByteArray)
    {
        unsigned long long result = 0;
        for(int i=0; i<8; ++i)
        {
            unsigned char convertedByte = ConvertedByteArray[i];
            result = result + (((unsigned long long)convertedByte) << (8*i));
        }
        *value = result;
        return Execution::Passed;
    }
    else
    {
        return Execution::Failed;
    } 
}

/**
 * @brief Convert a byte array to an unsigned long long (8 bytes).
 * @param value pointer where the resulted data will be placed
 * @param ConvertedByteArray Array obtained from a ToByte function
 * @param sizeOfGivenArray size of the array given to this function
 * @return Execution 
 */
Execution cData::ToData(long long* value, unsigned char* ConvertedByteArray, int sizeOfGivenArray)
{
    if(sizeOfGivenArray >= 8)
    {
        unsigned char* p = reinterpret_cast<unsigned char*>(value);
        for (int i = 0; i < 8; i++) {
            *(p + i) = ConvertedByteArray[i];
        }
        return Execution::Passed;
    }
    else
    {
        return Execution::Failed;
    }  
}

/**
 * @brief Convert a byte array to a float value.
 * @param value pointer where the resulted data will be placed
 * @param ConvertedByteArray Array obtained from a ToByte function
 * @param sizeOfGivenArray size of the array given to this function
 * @return Execution 
 */
Execution cData::ToData(float* value, unsigned char* ConvertedByteArray, int sizeOfGivenArray)
{
    if(sizeOfGivenArray >= sizeof(float))
    {
        unsigned char* p = reinterpret_cast<unsigned char*>(value);
        for (int i = 0; i < sizeof(float); i++) {
            *(p + i) = ConvertedByteArray[i];
        }
        return Execution::Passed;
    }
    else
    {
        return Execution::Failed;
    }  
}

/**
 * @brief Convert a byte array to a double value.
 * @param value pointer where the resulted data will be placed
 * @param ConvertedByteArray Array obtained from a ToByte function
 * @param sizeOfGivenArray size of the array given to this function
 * @return Execution 
 */
Execution cData::ToData(double* value, unsigned char* ConvertedByteArray, int sizeOfGivenArray) 
{
    _sizeOfByteArray = 8; // 8 bytes in a double
    if (sizeOfGivenArray < _sizeOfByteArray) 
    {
        return Execution::Failed;
    }
    unsigned char bytes[_sizeOfByteArray];
    for (int i = 0; i < _sizeOfByteArray; ++i) 
    {
        bytes[i] = ConvertedByteArray[i];
    }
    *value = *reinterpret_cast<double*>(bytes);
    return Execution::Passed;
}

/**
 * @brief Convert a byte array to a std::string value.
 * @param value pointer where the resulted data will be placed
 * @param ConvertedByteArray Array obtained from a ToByte function
 * @param sizeOfGivenArray size of the array given to this function
 * @return Execution 
 */
Execution cData::ToData(std::string& value, unsigned char* ConvertedByteArray, int sizeOfGivenArray)
{
    // if(sizeOfGivenArray >= value.length())
    // {
        value.clear();
        for (int i = 0; i < sizeOfGivenArray; i++) {
            value += static_cast<char>(ConvertedByteArray[i]);
        }
        return Execution::Passed;
    // }
    // else
    // {
        // return Execution::Failed;
    // }
}
#pragma endregion

/**
 * @brief Gets the size of the array
 * returned by ToBytes functions.
 * @param size
 * pointer where the size of the byte array will be placed.
 * @return Execution 
 */
Execution cData::GetArraySize(unsigned char* size)
{
    if(_sizeOfByteArray > 0 )
    {
        *size = _sizeOfByteArray;
        return Execution::Passed;
    }
    else
    {
        *size = -1;
        return Execution::Failed;
    }
}
