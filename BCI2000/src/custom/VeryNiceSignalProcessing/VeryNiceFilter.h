////////////////////////////////////////////////////////////////////////////////
// Authors: kotlab@DESKTOP-Q28EPBK.dynamic.rpi.edu
// Description: VeryNiceFilter header
////////////////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_VERYNICEFILTER_H  // makes sure this header is not included more than once
#define INCLUDED_VERYNICEFILTER_H

#include "GenericFilter.h"

class VeryNiceFilter : public GenericFilter
{
 public:
  VeryNiceFilter();
  ~VeryNiceFilter();
  void Publish() override;
  void Preflight( const SignalProperties& Input, SignalProperties& Output ) const override;
  void Initialize( const SignalProperties& Input, const SignalProperties& Output ) override;
  void StartRun() override;
  void Process( const GenericSignal& Input, GenericSignal& Output ) override;
  void StopRun() override;
  void Halt() override;

 private:
   // Use this space to declare any VeryNiceFilter-specific methods and member variables you'll need
   float* mpExampleArray;
};

#endif // INCLUDED_VERYNICEFILTER_H
