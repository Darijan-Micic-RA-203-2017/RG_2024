// By using these several preprocessor directives at the top of the header file, the compiler is informed to only
// include and compile this header file if it hasn't been included yet. This applies even if multiple files include the
// door_state header. This prevents linking conflicts.
#ifndef DOOR_STATE_H
#define DOOR_STATE_H

enum DoorState
{
	CLOSED, OPENING, OPEN, CLOSING
};

#endif
