// By using these several preprocessor directives at the top of the header file, the compiler is informed to only
// include and compile this header file if it hasn't been included yet. This applies even if multiple files include the
// callbacks header. This prevents linking conflicts.
#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "framebuffer_size_callback.hpp"
#include "mouse_button_callback.hpp"
#include "cursor_pos_callback.hpp"
#include "scroll_callback.hpp"
#include "input_processing.hpp"

#endif
