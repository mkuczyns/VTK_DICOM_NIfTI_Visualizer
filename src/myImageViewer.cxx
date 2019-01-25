/************************************************************************************************
*   myImageViewer.cxx
*
*   Created by:     Michael Kuczynski
*   Created on:     19/01/2019
*   Description:    VTK based program to display DICOM or NIfTI images.
*                   Allows for adjustment of zoom, window, window level, 
*                   and slice number.
************************************************************************************************/

#include "interactorStyler.hxx"

vtkStandardNewMacro(myInteractorStyler);

int main(int argc, char* argv[])
{
    // Check if the provided input arguement is a file or directory.
    // Assign the correct value to inputType variable.
    if ( argc != 2 )
    {
        std::cout << "ERROR: Incorrect program usage." << std:: endl;
        std::cout << "Correct usage: " << argv[0] << " <Folder_Name/Filename>" << std::endl;
        return EXIT_FAILURE;
    }

    /* int inputType:
    *   -1 = error
    *    0 = Directory with DICOM series
    *    1 = NIfTI file
    */ 
    int inputType = checkInputs(argv[1]);

    // Create a reader for DICOM and NIfTI images
    vtkSmartPointer<vtkDICOMImageReader> DICOM_reader;
    vtkSmartPointer<vtkNIFTIImageReader> NIFTI_reader;

    // Create the viewer for visualization
    vtkSmartPointer<vtkImageViewer2> imageViewer = vtkSmartPointer<vtkImageViewer2>::New();

    // Create a variable for the input arguement (if valid type).
    std::string inputFile = "";

    if ( inputType == 0 || inputType == 1)
    {
        inputFile = argv[1];
    }

    // Assign values to appropriate variables depending on if we have a DICOM series or NIfTI file.
    switch( inputType )
    {
        case -1:
        {
            std::cout << "ERROR: Provided input arguement is neither a directory containing a DICOM series or NIfTI file." << std::endl;
            std::cout << "Correct usage: " << argv[0] << " <DICOM_Folder_Name/Filename.nii>" << std::endl;
            break;
        }

        case 0:     // Directory with DICOM series
        {
            // Read all files from the DICOM series in the specified directory.
            DICOM_reader = vtkSmartPointer<vtkDICOMImageReader>::New();
            DICOM_reader->SetDirectoryName( inputFile.c_str() );
            DICOM_reader->Update();

            imageViewer->SetInputConnection( DICOM_reader->GetOutputPort() );
    
            break;
        }

        case 1:     // NIfTI
        {
            // Create a reader and check if the input file is readable.
            NIFTI_reader = vtkSmartPointer<vtkNIFTIImageReader>::New();

            if ( !( NIFTI_reader->CanReadFile( inputFile.c_str() ) ) )
            {
                std::cout << "ERROR: vtk NIFTI image reader cannot read the provided file: " << inputFile << std::endl;
                return EXIT_FAILURE;
            }

            NIFTI_reader->SetFileName( inputFile.c_str() );
            NIFTI_reader->Update();

            imageViewer->SetInputConnection( NIFTI_reader->GetOutputPort() );

            break;
        }
        default:
        {
            return EXIT_FAILURE;
            break;
        }
    }

    // Create a message with current slice out of total slices and current window level.
    // Use Time New Roman as the font, size 18.
    vtkSmartPointer<vtkTextProperty> sliceTextProperty = vtkSmartPointer<vtkTextProperty>::New();
    sliceTextProperty->SetFontFamilyToTimes();
    sliceTextProperty->SetFontSize(18);

    vtkSmartPointer<vtkTextProperty> WindowLevelTextProperty = vtkSmartPointer<vtkTextProperty>::New();
    WindowLevelTextProperty->SetFontFamilyToTimes();
    WindowLevelTextProperty->SetFontSize(18);

    vtkSmartPointer<vtkTextProperty> WindowTextProperty = vtkSmartPointer<vtkTextProperty>::New();
    WindowTextProperty->SetFontFamilyToTimes();
    WindowTextProperty->SetFontSize(18);

    // Create the text mappers for both slice number, window level, and window. Use a helper class "ImageMessage" for this.
    vtkSmartPointer<vtkTextMapper> sliceTextMapper = vtkSmartPointer<vtkTextMapper>::New();
    std::string sliceMessage = ImageMessage::sliceNumberFormat( imageViewer->GetSliceMin(), imageViewer->GetSliceMax() );
    sliceTextMapper->SetInput( sliceMessage.c_str() );
    sliceTextMapper->SetTextProperty( sliceTextProperty );

    vtkSmartPointer<vtkTextMapper> WindowLevelTextMapper = vtkSmartPointer<vtkTextMapper>::New();
    std::string windowLevelMessage = ImageMessage::windowLevelFormat( int( imageViewer->GetWindowLevel()->GetLevel() ) );
    WindowLevelTextMapper->SetInput( windowLevelMessage.c_str() );
    WindowLevelTextMapper->SetTextProperty( WindowLevelTextProperty );

    imageViewer->GetWindowLevel()->SetWindow(500);
    vtkSmartPointer<vtkTextMapper> WindowTextMapper = vtkSmartPointer<vtkTextMapper>::New();
    std::string windowMessage = ImageMessage::windowFormat( int( imageViewer->GetWindowLevel()->GetWindow() ) );
    WindowTextMapper->SetInput( windowMessage.c_str() );
    WindowTextMapper->SetTextProperty( WindowTextProperty );

    // Create the actors for each message.
    vtkSmartPointer<vtkActor2D> sliceTextActor = vtkSmartPointer<vtkActor2D>::New();
    sliceTextActor->SetMapper( sliceTextMapper );

    vtkSmartPointer<vtkActor2D> windowLevelTextActor = vtkSmartPointer<vtkActor2D>::New();
    windowLevelTextActor->SetMapper( WindowLevelTextMapper );

    vtkSmartPointer<vtkActor2D> windowTextActor = vtkSmartPointer<vtkActor2D>::New();
    windowTextActor->SetMapper( WindowTextMapper );

    // Specify the position of each message to be in the top left corner of the display.
    sliceTextActor->GetPositionCoordinate()->SetCoordinateSystemToNormalizedDisplay();
    sliceTextActor->GetPositionCoordinate()->SetValue( 0.05, 0.95);

    windowLevelTextActor->GetPositionCoordinate()->SetCoordinateSystemToNormalizedDisplay();
    windowLevelTextActor->GetPositionCoordinate()->SetValue( 0.05, 0.90);

    windowTextActor->GetPositionCoordinate()->SetCoordinateSystemToNormalizedDisplay();
    windowTextActor->GetPositionCoordinate()->SetValue( 0.05, 0.85);

    // Create an interactor to catch mouse and keyboard events.
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<myInteractorStyler> interactorStyle = vtkSmartPointer<myInteractorStyler>::New();

    // Set the image viewer and status mapper to enable message updates when interacting with the image.
    interactorStyle->setImageViewer( imageViewer );
    interactorStyle->setSliceStatusMapper( sliceTextMapper );
    interactorStyle->setWindowLevelStatusMapper( WindowLevelTextMapper );
    interactorStyle->setWindowStatusMapper( WindowTextMapper );

    // Set the interactor to use the custom interactor style (override the default style).
    imageViewer->SetupInteractor( renderWindowInteractor );

    renderWindowInteractor->SetInteractorStyle( interactorStyle );

    // Send the current slice message and window level message to the renderer.
    imageViewer->GetRenderer()->AddActor2D( sliceTextActor );
    imageViewer->GetRenderer()->AddActor2D( windowLevelTextActor );
    imageViewer->GetRenderer()->AddActor2D( windowTextActor );

    // Set the window size to the current monitor size.
    imageViewer->GetRenderWindow()->SetSize( imageViewer->GetRenderWindow()->GetScreenSize() );

    // Create/render the window.
    imageViewer->Render();
    imageViewer->GetRenderer()->ResetCamera();

    // Set the window title. Must be done AFTER the window is rendered.
    std::string windowTitle = "MDSC 689.03 - Assignment #1 - Image Visualization - Michael Kuczynski";
    imageViewer->GetRenderWindow()->SetWindowName( windowTitle.c_str() );

    renderWindowInteractor->Start();

    return EXIT_SUCCESS;
}