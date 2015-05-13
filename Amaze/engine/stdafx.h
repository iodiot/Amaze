// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define _SECURE_SCL 0										// Disable STL checked iterators
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL_THROWS 0
#define _SCL_SECURE_NO_WARNINGS					
#define _CRT_SECURE_NO_WARNINGS					// Turn off compiler warnings about unsafe calls of old stdlib funcs

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#define _USE_MATH_DEFINES								// Pi const and others

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <cmath>
#include <cassert>
#include <cstdlib>
#include <ctime>

// STL
#include <map>
#include <list>
using namespace std;

// SDL
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_audio.h"

typedef unsigned int uint;

// TODO: reference additional headers your program requires here
//#include <vld.h>