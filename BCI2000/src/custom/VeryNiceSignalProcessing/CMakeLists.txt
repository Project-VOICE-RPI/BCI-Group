###########################################################################
## Authors: kotlab@DESKTOP-Q28EPBK.dynamic.rpi.edu
## Description: Build information for the VeryNiceSignalProcessing project
###########################################################################

# Use the bci2000_include macro if you need to link with frameworks from /src/extlib:
# bci2000_include( MATLAB )

bci2000_add_signal_processing_module(
  VeryNiceSignalProcessing NOBUNDLE
  PipeDefinition.cpp
  VeryNiceFilter.cpp
)
