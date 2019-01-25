#include "DICOM_viewer.hxx"

void myVtkInteractorStyleImage::SetImageViewer(vtkImageViewer2* imageViewer)
{
    _ImageViewer = imageViewer;
    _MinSlice = imageViewer->GetSliceMin();
    _MaxSlice = imageViewer->GetSliceMax();
    _Slice = _MinSlice;
    cout << "Slicer: Min = " << _MinSlice << ", Max = " << _MaxSlice << std::endl;
}

void myVtkInteractorStyleImage::SetStatusMapper(vtkTextMapper* statusMapper) 
{
    _StatusMapper = statusMapper;
}

void myVtkInteractorStyleImage::MoveSliceForward() 
{
    if(_Slice < _MaxSlice) 
    {
        _Slice += 1;
        cout << "MoveSliceForward::Slice = " << _Slice << std::endl;
        _ImageViewer->SetSlice(_Slice);
        std::string msg = SliceMessage::sliceNumberFormat(_Slice, _MaxSlice);
        _StatusMapper->SetInput(msg.c_str());
        _ImageViewer->Render();
    }
}

void myVtkInteractorStyleImage::MoveSliceBackward() 
{
    if(_Slice > _MinSlice) 
    {
        _Slice -= 1;
        cout << "MoveSliceBackward::Slice = " << _Slice << std::endl;
        _ImageViewer->SetSlice(_Slice);
        std::string msg = SliceMessage::sliceNumberFormat(_Slice, _MaxSlice);
        _StatusMapper->SetInput(msg.c_str());
        _ImageViewer->Render();
    }
}