// auto-created file, do not edit
// created 2024-11-05 21:32:42Z
// created from: C:/Users/kotlab/Documents/GitHub/BCI-Group/BCI2000/build/buildutils/BootstrapCustomProjects/templates/ADC.prm.in
#define IS_RESOURCE_ADC_prm_in
#ifdef REGISTER_RESOURCE
REGISTER_RESOURCE( "ADC.prm.in", ADC_prm_in )
#endif

#ifdef DECLARE_RESOURCES
namespace bci {
 namespace Resources {
  extern bci::Resource ADC_prm_in;
 }
}
#else // DECLARE_RESOURCES
#include "Resource.h"
namespace { static const unsigned char ADC_prm_in_data_[] = {
13,10,
}; }
namespace bci {
 namespace Resources {
  bci::Resource ADC_prm_in = { "in", sizeof( ADC_prm_in_data_), (const char*)ADC_prm_in_data_ };
 }
}
#endif // DECLARE_RESOURCES

