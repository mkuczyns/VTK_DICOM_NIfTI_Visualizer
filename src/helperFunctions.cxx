#include "helperFunctions.hxx"

/****************** Helper class "ImageMessage" functions ******************/
std::string ImageMessage::sliceNumberFormat( int minSlice, int maxSlice ) 
{
    std::stringstream tmp;
    tmp << "Slice Number:  " << minSlice + 1 << "/" << maxSlice + 1;
    return tmp.str();
}

std::string ImageMessage::windowLevelFormat( int windowLevel ) 
{
    std::stringstream tmp;
    tmp << "Window Level:  " << windowLevel;
    return tmp.str();
}

std::string ImageMessage::windowFormat( int window ) 
{
    std::stringstream tmp;
    tmp << "Window:  " << window;
    return tmp.str();
}
/***************************************************************************/

/************************* Other helper functions **************************/
int checkInputs( std::string inputArguement )
{
    /* int inputType:
    *   -1 = error
    *    0 = Directory with DICOM series
    *    1 = NIfTI file
    */ 
    int inputType = -1;

    /* 
    *   Attempt to find a period in the input arguement that seperates filename and filetype.
    *   Attempt to find a slash as well to determine if the input is a directory path.
    * 
    *   If no period exists or we have a slash, we have a directory name or path. 
    *   Otherwise check the file extension for the filetype.
    * 
    *   This may not be the best way to do this, but it should work on all systems.
    *   There are ways to check if a variable contains a file or directory, but they are specific to
    *   certain operating systems...
    */
    std::size_t period_Index = inputArguement.find_last_of(".");
    std::size_t backSlash_Index = inputArguement.find("\\");
    std::size_t forwardSlash_Index = inputArguement.find("/");

    /* 
    *   We can have potential problems here where a period is included in the file path.
    *   For this assignment, file extensions will only be ".dcm" or ".nii".
    *   Thus, we can say that if the third last character in the input is not a period, we likely have a directory.
    */
    if ( period_Index == std::string::npos || (inputArguement[inputArguement.length() - 4]) != '.' )
    {
        // Input is a directory containing a DICOM series
        inputType = 0;
        std::cout << "Input provided is a directory. Checking contents of the directory..." << std::endl;
        std::cout << "Reading DICOM series..." << std::endl;
    }
    else if ( period_Index != std::string::npos )
    {
        // Input is a file. Check filetype.
        std::cout << "Input provided is a file. Checking the filetype..." << std::endl;
        
        std::string fileExtension;
        fileExtension.assign(inputArguement, period_Index, 4);

        if ( fileExtension == ".dcm" )
        {
            inputType = -1;
        }
        else if ( fileExtension == ".nii" )
        {
            inputType = 1;
            std::cout << "Reading NIfTI image..." << std::endl;
        }
        else
        {
            // Only accept DICOM or NIfTI filetypes.
            inputType = -1;
        }
    }

    return inputType;
}
/***************************************************************************/