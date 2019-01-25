#ifndef INTERACTORSTYLER_H
#define INTERACTORSTYLER_H

#include "helperFunctions.hxx"

#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkActor2D.h>

#include <vtkImageViewer2.h>
#include <vtkDICOMImageReader.h>
#include <vtkNIFTIImageReader.h>
#include <vtkInteractorStyleImage.h>

#include <vtkTextProperty.h>
#include <vtkTextMapper.h>
#include <vtkImageMapToWindowLevelColors.h>

#include <vtkSmartPointer.h>
#include <vtkObjectFactory.h>

#include <string>

/* 
*   A class for a custom interactor style to override the default interactor style.
*/
class myInteractorStyler : public vtkInteractorStyleImage
{
public:
   static myInteractorStyler* New();

   vtkTypeMacro(myInteractorStyler, vtkInteractorStyleImage);

   /*
   *   Set the class image viewer.
   *
   *   @param   imageViewer   Image viewer from main
   */
   void setImageViewer(vtkImageViewer2* imageViewer);

   /*
   *   Set the class status mapper for the slice message.
   *
   *   @param   imageViewer   Mapper from main for the slice message
   */
   void setSliceStatusMapper(vtkTextMapper* _SliceStatusMapper);

   /*
   *   Set the class status mapper for the window level message.
   *
   *   @param   imageViewer   Mapper from main for the window level message
   */
   void setWindowLevelStatusMapper(vtkTextMapper* _WindowLevelStatusMapper);

protected:
   vtkImageViewer2* _ImageViewer;
   vtkTextMapper*   _SliceStatusMapper;
   vtkTextMapper*   _WindowLevelStatusMapper;
   int slice;
   int minSlice;
   int maxSlice;
   double windowLevel;

   /*
   *   Move the next slice in the image.
   */
   void moveSliceForward();

   /*
   *   Move the previous slice in the image.
   */
   void moveSliceBackward();

   /*
   *   Increase the window level.
   */
   void moveWindowLevelForward();

   /*
   *   Decrease the window level.
   */
   void moveWindowLevelBackward();

   /*
   *   Overload the default interactor event listener for key presses.
   *   UP ARROW key    = move to next slice
   *   DOWN ARROW key  = move to previous slice
   *   LEFT ARROW key  = increase window level
   *   RIGHT ARROW key = decrease window level
   */
   virtual void OnKeyDown()
   {
      std::string key = this->GetInteractor()->GetKeySym();

      if ( key.compare("Up") == 0 ) 
      {
         moveSliceForward();
      }
      else if ( key.compare("Down") == 0 ) 
      {
         moveSliceBackward();
      }
      else if ( key.compare("Left") == 0 )
      {
         moveWindowLevelForward();
      }
      else if ( key.compare("Right") == 0 )
      {
         moveWindowLevelBackward();
      }

      vtkInteractorStyleImage::OnKeyDown();
   }

   /*
   *   Overload the default interactor event listener for the mouse scroll wheel.
   *   Moves to the next slice.
   */
   virtual void OnMouseWheelForward()
   {
      moveSliceForward();
   }

   /*
   *   Overload the default interactor event listener for the mouse scroll wheel.
   *   Moves to the previous slice.
   */
   virtual void OnMouseWheelBackward()
   {
      if ( slice > minSlice )
      {
         moveSliceBackward();
      }
   }

   /*
   *  Overload the default interactor event listener for the left mouse button.
   *  Need to overload this function and leave blank so that the default window 
   *  leveling is only done with the left and right arrow keys as desired.
   */
   virtual void OnLeftButtonDown()  { }
};

#endif  // INTERACTORSTYLER_H