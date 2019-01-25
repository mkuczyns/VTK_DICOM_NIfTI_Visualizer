#include "interactorStyler.hxx"

void myInteractorStyler::setImageViewer( vtkImageViewer2* imageViewer )
{
    _ImageViewer = imageViewer;
    minSlice = imageViewer->GetSliceMin();
    maxSlice = imageViewer->GetSliceMax();
    windowLevel = imageViewer->GetWindowLevel()->GetLevel();
    
    // Start current slice at 0
    slice = minSlice;
}

void myInteractorStyler::setSliceStatusMapper( vtkTextMapper* statusMapper ) 
{
    _SliceStatusMapper = statusMapper;
}

void myInteractorStyler::setWindowLevelStatusMapper( vtkTextMapper* statusMapper ) 
{
    _WindowLevelStatusMapper = statusMapper;
}

void myInteractorStyler::moveSliceForward() 
{
    if ( slice < maxSlice ) 
    {
        slice += 1;

        _ImageViewer->SetSlice( slice );

        // Create the message to be displayed.
        std::string msg = ImageMessage::sliceNumberFormat( slice, maxSlice );

        // Update the mapper and render.
        _SliceStatusMapper->SetInput( msg.c_str() );
        _ImageViewer->Render();
    }
}

void myInteractorStyler::moveSliceBackward() 
{
    if ( slice > minSlice ) 
    {
        slice -= 1;

        _ImageViewer->SetSlice( slice );

        // Create the message to be displayed.
        std::string msg = ImageMessage::sliceNumberFormat( slice, maxSlice );

        // Update the mapper and render.
        _SliceStatusMapper->SetInput( msg.c_str() );
        _ImageViewer->Render();
    }
}

void myInteractorStyler::moveWindowLevelForward() 
{
    windowLevel += 1;

    _ImageViewer->GetWindowLevel()->SetLevel(windowLevel);

    // Create the message to be displayed.
    std::string msg = ImageMessage::windowLevelFormat( int(windowLevel) );

    // Update the mapper and render.
    _WindowLevelStatusMapper->SetInput( msg.c_str() );
    _ImageViewer->Render();
}

void myInteractorStyler::moveWindowLevelBackward() 
{
    windowLevel -= 1;

    _ImageViewer->GetWindowLevel()->SetLevel(windowLevel);

    // Create the message to be displayed.
    std::string msg = ImageMessage::windowLevelFormat( int(windowLevel) );

    // Update the mapper and render.
    _WindowLevelStatusMapper->SetInput( msg.c_str() );
    _ImageViewer->Render();
}