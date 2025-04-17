#ifndef FE_LOGIC
#define FE_LOGIC

#include "model.h"
#include <stdlib.h>

extern "C" {
  void    zigGreetings ();
  void    addModel (Model * modelptr);
  Model * getModel (size_t index);
  void    deleteModels ();
}

#endif // FE_LOGIC
