/*
    ############    ############     ##########
    ############    ############     ##########
              ##              ##   ## 
    ####    ##      ####    ##     ############
    ####    ##      ####    ##     ############
              ##              ##             ##
    ############    ####      ##   ##########
    ############    ####      ##   ##########

    Title: Enums.h
    Author: Lyam
*/

/**
 * @brief Header file for enumerations
 * 
 * This files contains the various enumerations used throughout this
 * project.
 */

#ifndef BRS_Enums_h
  #define  BRS_Enums_h
//================================================================================================//
//	Enumerations
//================================================================================================//

/**
 * @brief Execution Enum.
 * 
 * This enumeration is used to indicate the outcome
 * of a function's execution.
 * @author Lyam
 */
enum Execution
{
    /** @brief The function's execution was successful. */
    Passed          = 0,

    /** @brief Something crashed when attempting to execute the function. */
    Crashed         = 1,

    /** @brief The function failed to execute due to some internal conditions. */
    Failed          = 2,

    /** @brief The function cannot be executed due to a lack of connection. */
    NoConnection    = 3,

    /** @brief The function cannot be executed due to internal incompatibility issue */
    Incompatibility = 4,

    /** @brief The function's execution was bypassed entirely. */
    Bypassed        = 5,

    /** @brief The function did not execute as it thought it wasn't necessary. */
    Unecessary      = 6
};

/**
 * @brief ChunkType enum.
 * 
 * This enumeration indicates the types
 * of chunks from the BFIO protocol.
 * Their values are hardcoded in this enum.
 * @author Lyam
 */
enum ChunkType
{
    Byte     = 0,
    Div      = 256,
    Start    = 512,
    Check    = 768
};

/**
 * @brief DataType enum.
 * 
 * This enumeration indicates the types
 * of data that can be sent in segments
 * through the BFIO protocol.
 * See the documentation for their chunks
 * values and more in depth information.
 * @author Lyam
 */
enum DataType
{
    Bool,
    UnsignedChar,
    Char,
    UnsignedShort,
    Short,
    UnsignedInt,
    Int,
    UnsignedLong,
    Long,
    UnsignedLongLong,
    LongLong,
    Float,
    Double,
    LongDouble,
    String
};

/**
 * @brief Status enum.
 * 
 * Enumeration that holds the different
 * BFIO complient device status. A 
 * device status is the state in which
 * your device is in.
 * @author Lyam
 */
enum Status
{
    Booting,
    Busy,
    Available,
    Crashing,
    Handshake,
    Shutdown,
    Clueless,
    Debugging,
    SoftwareError,
    HardwareError,
    CompatibilityError,
    CommunicationError,
    NoBattery,
};

/**
 * @brief Highway Status.
 * 
 * Enumeration that holds the different
 * BFIO highway status. See BFIO docs
 * to understand what the highway is
 * and how these status works.
 * @author Lyam
 */
enum HighwayStatus
{
    Empty,
    Jammed,
    Traffic,
    Closed,
    Stopped,
    Error
};
#endif