cmake_minimum_required(VERSION 2.8)

PROJECT(myImageViewer)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(myImageViewer MACOSX_BUNDLE myImageViewer.cxx helperFunctions.cxx interactorStyler.cxx)

if(VTK_LIBRARIES)
  target_link_libraries(myImageViewer ${VTK_LIBRARIES})
else()
  target_link_libraries(myImageViewer vtkHybrid vtkWidgets)
endif()