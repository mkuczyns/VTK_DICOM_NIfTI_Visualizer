# DICOM_NIfTI_Visualizer
C++ program to view a DICOM series or NIfTI image using VTK

## Features:
1. Displays a DICOM series or NIfTI image.
2. Scrolling through slices with the UP/DOWN arrow keys. Scrolling is also available with the mouse wheel.
3. Adjust the window level with the LEFT/RIGHT arrow keys.
4. Adjust the window of the image with the Z and X keys (Z = increase window, X = decrease window).
5. Zoom in or out of the current slice by clicking with the left mouse button and dragging up/down.

## How-to Run:
1. Create a folder for the build (e.g. bin, build, etc.)
2. Build with CMake and your favorite compiler.
3. Run the executable that is generated in the bin\Debug folder from the command line
    ```
    mdsc689_03_assignment_01.exe <PATH_TO_DICOM_FOLDER>
    ```
    OR:

    ```
    mdsc689_03_assignment_01.exe <NIfTI_IMAGE_FILE>.nii
    ```