#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <iostream>
#include <sstream>
#include <string>

/* 
*   A helper class to display messages with information about current slice
*   number and current window level in the rendered window.
*/
class ImageMessage 
{
    public:
        /*
        *   Create a message that shows the current slice number.
        *
        *   @param   minSlice   The minimum slice number
        *   @param   maxSlice   The maximum slice number
        *
        *   @returns A string steam with the slice message
        */
        static std::string sliceNumberFormat( int minSlice, int maxSlice );

        /*
        *   Create a message that shows the current window level.
        *
        *   @param   windowLevel   The current window level
        *
        *   @returns A string steam with the window level message
        */
        static std::string windowLevelFormat( int windowLevel );

        /*
        *   Create a message that shows the current window.
        *
        *   @param   window   The current window
        *
        *   @returns A string steam with the window message
        */
        static std::string windowFormat( int window );
};

/************************* Other helper functions **************************/
/*
*   Check the input arguements provided in the commandline when running the program.
*
*   @param   inputArguement   Input arguement from commandline
*
*   @returns the integer corresponding to the input type
*            -1 for invalid arguement
*             0 for a DICOM directory
*             1 for a NIfTI file
*/
int checkInputs(std::string inputArguement);

/***************************************************************************/

#endif // HELPERFUNCTIONS_H