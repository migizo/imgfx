/*******************************************************************************

 BEGIN_JUCE_MODULE_DECLARATION

  ID:                 imgfx
  vendor:             migizo
  version:            0.0.1
  name:               Image Effect
  description:        image effect filter utility
  website:            https://twitter.com/migizo

  dependencies:       juce_gui_basics

 END_JUCE_MODULE_DECLARATION

*******************************************************************************/

#pragma once
#define IMGFX_H_INCLUDED

//==============================================================================
/** Config: USE_MELATONIN_BLUR
    Enables melatonin_blur module.
    A faster blur can be used by including the melatonin_blur module and turning on this flag.
*/
#ifndef USE_MELATONIN_BLUR
#define USE_MELATONIN_BLUR 0
#endif

//==============================================================================

#include "src/Utility/FxFunctions.h"
#include "src/Utility/CallbackEffect.h"
#include "src/Utility/MultiStackEffect.h"
#include "src/Utility/CachedComponentImage.h"
#include "src/Blurs/InnerShadow.h"
#include "src/Blurs/InnerShadowEffect.h"
#include "src/Blurs/Blur.h"
#include "src/Blurs/BackgroundBlur.h"
#include "src/Blurs/BackgroundBlurEffect.h"
#include "src/Blurs/ObjectBlurEffect.h"
