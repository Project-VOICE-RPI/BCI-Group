////////////////////////////////////////////////////////////////////////////////
// Authors: kotlab@rpi.edu
// Description: VeryNiceFilter implementation
////////////////////////////////////////////////////////////////////////////////

//Import/connect to file
#include "VeryNiceFilter.h"
#include "BCIStream.h"

RegisterFilter( VeryNiceFilter, 2.C );
     // Change the location as appropriate, to determine where your filter gets
     // sorted into the chain. By convention:
     //  - filter locations within SignalSource modules begin with "1."
     //  - filter locations witin SignalProcessing modules begin with "2."
     //       (NB: Filter() commands in a separate PipeDefinition.cpp file may override the default location set here with RegisterFilter)
     //  - filter locations within Application modules begin with "3."

// C++ does not initialize simple types such as numbers, or pointers, by default.
// Rather, they will have random values.
// Take care to initialize any member variables here, so they have predictable values
// when used for the first time.
VeryNiceFilter::VeryNiceFilter()
: mpExampleArray( nullptr )
{
}

VeryNiceFilter::~VeryNiceFilter()
{
  Halt();
  // If you have allocated any memory with malloc(), call free() here.
  // If you have allocated any memory with new[], call delete[] here.
  // If you have created any object using new, call delete here.
  // Either kind of deallocation will silently ignore null pointers, so all
  // you need to do is to initialize those to zero in the constructor, and
  // deallocate them here.
  delete[] mpExampleArray;
}

void
VeryNiceFilter::Publish()
{
  // Define any parameters that the filter needs....

 BEGIN_PARAMETER_DEFINITIONS

   "Filtering:VeryNiceFilter int EnableVeryNiceFilter= 0 0 0 1 // enable VeryNiceFilter? (boolean)",                       // These are just examples:
   "Filtering:VeryNiceFilter float ScaleFactor =  2.0 0.0 0.0 10.0 // scaling factor for filter",   //  changed for scalefactor

 END_PARAMETER_DEFINITIONS


  // ...and likewise any state variables:

 BEGIN_STATE_DEFINITIONS

   "SomeState       8 0 0 0",    // These are just examples. Change them, or remove them.
   "SomeOtherState 16 0 0 0",

 END_STATE_DEFINITIONS

}

void
VeryNiceFilter::Preflight( const SignalProperties& Input, SignalProperties& Output ) const
{
  // The user has pressed "Set Config" and we need to sanity-check everything.
  // For example, check that all necessary parameters and states are accessible:
  //
  // Parameter( "Milk" );
  // State( "Bananas" );
  //
  // Also check that the values of any parameters are sane:
  //
  // if( (float)Parameter( "Denominator" ) == 0.0f )
  //      bcierr << "Denominator cannot be zero";
  //
  // Errors issued in this way, during Preflight, still allow the user to open
  // the Config dialog box, fix bad parameters and re-try.  By contrast, errors
  // and C++ exceptions at any other stage (outside Preflight) will make the
  // system stop, such that BCI2000 will need to be relaunched entirely.

  Output = Input; // this simply passes information through about SampleBlock dimensions, etc....

  // ... or alternatively, we could modify that info here:

  //Check that scale factor is not negative
  if (Parameter("ScaleFactor") < 0.0f) {
      bcierr << "Scale Factor must be non-negative";
  }

  // Let's imagine this filter has only one output, namely the amount of stuff detected in the signal:
  // Output.SetChannels( 1 );
  // Output.ChannelLabels()[0] = "Stuff";

  // Imagine we want to output twice as many samples (or bins) as we receive from the input:
  // Output.SetElements( Input.Elements() * 2 );

  // Note that the VeryNiceFilter instance itself, and its members, are read-only during
  // this phase, due to the "const" at the end of the Preflight prototype above.
  // Any methods called by Preflight must also be "const" in the same way.
}


void
VeryNiceFilter::Initialize( const SignalProperties& Input, const SignalProperties& Output )
{
  // The user has pressed "Set Config" and all Preflight checks have passed.
  // The signal properties can no longer be modified, but the const limitation has gone, so
  // the VeryNiceFilter instance itself can be modified. Allocate any memory you need, start any
  // threads, store any information you need in private member variables.

  // For memory allocation, a reasonable approach is to first deallocate and set the
  // pointer to zero:
  delete[] mpExampleArray;
  mpExampleArray = nullptr;
  // Then, depending on parameter configuration, you may choose to allocate memory,
  // or leave the pointer at zero.
}

void
VeryNiceFilter::StartRun()
{
  // The user has just pressed "Start" (or "Resume")
  bciout << "Hello World!";
}


void
VeryNiceFilter::Process( const GenericSignal& Input, GenericSignal& Output )
{
  //Check if filter enabled
  if (Parameter("EnableVeryNiceFilter") == 1) {
    float scaleFactor = Parameter("ScaleFactor");
    
    //Apply scaling
    for (int chan = 0; chan < Output.Channels(); chan++) {
        for (int elem = 0; elem < Output.Elements(); elem++) {
            Output(chan, elem) = Input(chan, elem) * scaleFactor;
        }
    }
  }
  else {
      // And now we're processing a single SampleBlock of data.
      // Remember not to take too much CPU time here, or you will break the real-time constraint.

      Output = Input; // Pass the signal through unmodified.
      // ( Obviously this will no longer fly if we modified the shape of the
      //   output SignalProperties during Preflight ).

    // Or we could do it one value at a time:
    /*
    for( int ch = 0; ch < Output.Channels(); ch++ )
    {
      for( int el = 0; el < Output.Elements(); el++ )
      {
        Output( ch, el ) = some_function( Input );
      }
    }
    */
  }
}

void
VeryNiceFilter::StopRun()
{
  // The Running state has been set to 0, either because the user has pressed "Suspend",
  // or because the run has reached its natural end.
  bciwarn << "Goodbye World.";
  // You know, you can delete methods if you're not using them.
  // Remove the corresponding declaration from VeryNiceFilter.h too, if so.
}

void
VeryNiceFilter::Halt()
{
  // Stop any threads or other asynchronous activity.
  // Good practice is to write the Halt() method such that it is safe to call it even *before*
  // Initialize, and safe to call it twice (e.g. make sure you do not delete [] pointers that
  // have already been deleted:  set them to nullptr after deletion).
}

