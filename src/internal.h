//========================================================================
// GLFW - An OpenGL library
// Platform:    Any
// API version: 3.0
// WWW:         http://www.glfw.org/
//------------------------------------------------------------------------
// Copyright (c) 2002-2006 Marcus Geelnard
// Copyright (c) 2006-2010 Camilla Berglund <elmindreda@elmindreda.org>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================

#ifndef _internal_h_
#define _internal_h_


//========================================================================
// Doxygen group definitions
//========================================================================

/*! @defgroup platform Platform API
 *  @brief The API implemented by the platform-specific code.
 *
 *  The platform API is the interface exposed by the platform-specific code for
 *  each platform and is called by the shared code of the public API It mirrors
 *  the public API except it uses objects instead of handles.
 */
/*! @defgroup event Event API
 *  @brief The API used by the platform-specific code to report events.
 *
 *  The event API is used by the platform-specific code to notify the shared
 *  code of events that can be translated into state changes and/or callback
 *  calls.
 */
/*! @defgroup utility Utility functions
 *  @brief Various utility functions.
 *
 *  These functions are shared code and may be used by any part of GLFW
 *  Each platform may add its own utility functions, but those may only be
 *  called by the platform-specific code
 */


//========================================================================
// Input handling definitions
//========================================================================

// Internal key and button state/action definitions
#define GLFW_STICK 2


//========================================================================
// Internal type declarations
//========================================================================

typedef struct _GLFWhints       _GLFWhints;
typedef struct _GLFWwndconfig   _GLFWwndconfig;
typedef struct _GLFWfbconfig    _GLFWfbconfig;
typedef struct _GLFWwindow      _GLFWwindow;
typedef struct _GLFWlibrary     _GLFWlibrary;
typedef struct _GLFWmonitor     _GLFWmonitor;


#include "config.h"

// Disable the inclusion of the platform glext.h by gl.h to allow proper
// inclusion of our own, newer glext.h below
#define GL_GLEXT_LEGACY

#include "../include/GL/glfw3.h"

// This path may need to be changed if you build GLFW using your own setup
// We ship and use our own copy of glext.h since GLFW uses fairly new
// extensions and not all operating systems come with an up-to-date version
#include "../support/GL/glext.h"

#if defined(_GLFW_COCOA)
 #include "cocoa_platform.h"
#elif defined(_GLFW_WIN32)
 #include "win32_platform.h"
#elif defined(_GLFW_X11)
 #include "x11_platform.h"
#else
 #error "No supported window creation API selected"
#endif


//========================================================================
// Internal type definitions
//========================================================================

/*! @brief Window, framebuffer and context hints.
 *
 *  It is used only by shared code and only to store parameters passed to us by
 *  @ref glfwWindowHint for use by @ref glfwCreateWindow.
 */
struct _GLFWhints
{
    int         redBits;
    int         greenBits;
    int         blueBits;
    int         alphaBits;
    int         depthBits;
    int         stencilBits;
    int         accumRedBits;
    int         accumGreenBits;
    int         accumBlueBits;
    int         accumAlphaBits;
    int         auxBuffers;
    GLboolean   stereo;
    GLboolean   resizable;
    GLboolean   visible;
    int         samples;
    GLboolean   sRGB;
    int         clientAPI;
    int         glMajor;
    int         glMinor;
    GLboolean   glForward;
    GLboolean   glDebug;
    int         glProfile;
    int         glRobustness;
    int         positionX;
    int         positionY;
};


/*! @brief Window and context configuration.
 *
 *  Parameters relating to the creation of the context and window but not
 *  directly related to the framebuffer.  This is used to pass window and
 *  context creation parameters from shared code to the platform API.
 */
struct _GLFWwndconfig
{
    const char*   title;
    GLboolean     resizable;
    GLboolean     visible;
    int           positionX;
    int           positionY;
    int           clientAPI;
    int           glMajor;
    int           glMinor;
    GLboolean     glForward;
    GLboolean     glDebug;
    int           glProfile;
    int           glRobustness;
    _GLFWmonitor* monitor;
    _GLFWwindow*  share;
};


/*! @brief Framebuffer configuration.
 *
 *  This describes buffers and their sizes.  It also contains
 *  a platform-specific ID used to map back to the backend API's object.
 *
 *  It is used to pass framebuffer parameters from shared code to the
 *  platform API and also to enumerate and select available framebuffer configs.
 */
struct _GLFWfbconfig
{
    int         redBits;
    int         greenBits;
    int         blueBits;
    int         alphaBits;
    int         depthBits;
    int         stencilBits;
    int         accumRedBits;
    int         accumGreenBits;
    int         accumBlueBits;
    int         accumAlphaBits;
    int         auxBuffers;
    GLboolean   stereo;
    int         samples;
    GLboolean   sRGB;
    GLFWintptr  platformID;
};


/*! @brief Window and context structure.
 */
struct _GLFWwindow
{
    struct _GLFWwindow* next;

    // Window settings and state
    int                 width, height;
    int                 positionX, positionY;
    GLboolean           iconified;
    GLboolean           resizable;
    GLboolean           visible;
    GLboolean           closeRequested;
    void*               userPointer;
    GLFWvidmode         videoMode;
    _GLFWmonitor*       monitor;

    // Window input state
    GLboolean           stickyKeys;
    GLboolean           stickyMouseButtons;
    GLboolean           touchInput;
    int                 cursorPosX, cursorPosY;
    int                 cursorMode;
    double              scrollX, scrollY;
    char                mouseButton[GLFW_MOUSE_BUTTON_LAST + 1];
    char                key[GLFW_KEY_LAST + 1];

    // OpenGL extensions and context attributes
    int                 clientAPI;
    int                 glMajor, glMinor, glRevision;
    GLboolean           glForward, glDebug;
    int                 glProfile;
    int                 glRobustness;
    PFNGLGETSTRINGIPROC GetStringi;

    GLFWwindowposfun     windowPosCallback;
    GLFWwindowsizefun    windowSizeCallback;
    GLFWwindowclosefun   windowCloseCallback;
    GLFWwindowrefreshfun windowRefreshCallback;
    GLFWwindowfocusfun   windowFocusCallback;
    GLFWwindowiconifyfun windowIconifyCallback;
    GLFWmousebuttonfun   mouseButtonCallback;
    GLFWcursorposfun     cursorPosCallback;
    GLFWcursorenterfun   cursorEnterCallback;
    GLFWscrollfun        scrollCallback;
    GLFWkeyfun           keyCallback;
    GLFWcharfun          charCallback;
    GLFWtouchfun         touchCallback;
    GLFWtouchposfun      touchPosCallback;

    // This is defined in the window API's platform.h
    _GLFW_PLATFORM_WINDOW_STATE;
    // This is defined in the context API's platform.h
    _GLFW_PLATFORM_CONTEXT_STATE;
};


/*! @brief Monitor structure.
 */
struct _GLFWmonitor
{
    char*           name;

    GLboolean       primary;

    // Physical dimensions in millimeters.
    int             widthMM, heightMM;
    // Logical orientation of the screen on the desktop
    int             positionX, positionY;

    GLFWvidmode*    modes;
    int             modeCount;

    // This is defined in the window API's platform.h
    _GLFW_PLATFORM_MONITOR_STATE;
};


/*! @brief Library global data.
 */
struct _GLFWlibrary
{
    _GLFWhints      hints;

    _GLFWwindow*    windowListHead;
    _GLFWwindow*    focusedWindow;

    _GLFWmonitor**  monitors;
    int             monitorCount;
    GLFWmonitorfun  monitorCallback;

    GLFWgammaramp   currentRamp;
    GLFWgammaramp   originalRamp;
    int             originalRampSize;
    GLboolean       rampChanged;

    // This is defined in the window API's platform.h
    _GLFW_PLATFORM_LIBRARY_WINDOW_STATE;
    // This is defined in the context API's platform.h
    _GLFW_PLATFORM_LIBRARY_OPENGL_STATE;
};


//========================================================================
// Global state shared between compilation units of GLFW
//========================================================================

/*! @brief Flag indicating whether GLFW has been successfully initialized.
 */
extern GLboolean _glfwInitialized;

/*! @brief All global data protected by @ref _glfwInitialized.
 *  This should only be touched after a call to @ref glfwInit that has not been
 *  followed by a call to @ref glfwTerminate.
 */
extern _GLFWlibrary _glfw;


//========================================================================
// Platform API functions
//========================================================================

/*! @brief Initializes the platform-specific part of the library.
 *  @return @c GL_TRUE if successful, or @c GL_FALSE if an error occurred.
 *  @ingroup platform
 */
int _glfwPlatformInit(void);

/*! @brief Terminates the platform-specific part of the library.
 *  @ingroup platform
 */
void _glfwPlatformTerminate(void);

/*! @brief Returns a string describing the compile-time configuration of the
 *  platform-specific part of the library.
 *  @return The version string.
 *  @ingroup platform
 *
 *  The format of the string is as follows:
 *  @arg The name of the window system API used
 *  @arg The name of the context creation API used
 *  @arg Any additional options or APIs
 *
 *  @note The returned string must be available for the duration of the program.
 *
 *  @note The returned string must not change for the duration of the program.
 */
const char* _glfwPlatformGetVersionString(void);

/*! @ingroup platform
 */
void _glfwPlatformEnableSystemKeys(_GLFWwindow* window);

/*! @ingroup platform
 */
void _glfwPlatformSetTouchInput(_GLFWwindow* window, int enabled);

/*! @brief Sets the position of the system cursor.
 *  @param[in] window The window whose client area the specified posiiton is
 *  relative to.
 *  @param[in] x The new x-coordinate of the cursor, relative to the left edge
 *  of the client area of the window.
 *  @param[in] y The new y-coordinate of the cursor, relative to the top edge
 *  of the client area of the window.
 *  @ingroup platform
 */
void _glfwPlatformSetCursorPos(_GLFWwindow* window, int x, int y);

/*! @brief Sets up the specified cursor mode for the specified window.
 *  @param[in] window The window whose cursor mode to change.
 *  @param[in] mode The desired cursor mode.
 *  @ingroup platform
 */
void _glfwPlatformSetCursorMode(_GLFWwindow* window, int mode);

/*! @ingroup platform
 */
_GLFWmonitor** _glfwPlatformGetMonitors(int* count);

/*! @ingroup platform
 */
void _glfwPlatformDestroyMonitor(_GLFWmonitor* monitor);

/*! @ingroup platform
 */
GLFWvidmode* _glfwPlatformGetVideoModes(_GLFWmonitor* monitor, int* count);

/*! @ingroup platform
 */
void _glfwPlatformGetVideoMode(_GLFWmonitor* monitor, GLFWvidmode* mode);

/*! @brief Returns the current system gamma ramp.
 *  @param[out] ramp The current system gamma ramp.
 *  @ingroup platform
 */
void _glfwPlatformGetGammaRamp(GLFWgammaramp* ramp);

/*! @brief Sets the system gamma ramp.
 *  @param[in] ramp The desired system gamma ramp.
 *  @ingroup platform
 */
void _glfwPlatformSetGammaRamp(const GLFWgammaramp* ramp);

/*! @brief Sets the system clipboard to the specified string.
 *  @param[in] window The window who will own the system clipboard contents, on
 *  systems where this is necessary.
 *  @param[in] string The UTF-8 encoded string to use.
 *  @ingroup platform
 */
void _glfwPlatformSetClipboardString(_GLFWwindow* window, const char* string);

/*! @brief Returns the string in the system clipboard.
 *  @param[in] window The window who will request the system clipboard contents,
 *  on systems where this is necessary.
 *  @return The UTF-8 encoded contents, or @c NULL if the system clipboard did
 *  not contain a string.
 *  @ingroup platform
 *
 *  @note The returned string must be valid until the next call to @ref
 *  _glfwPlatformGetClipboardString or @ref _glfwPlatformSetClipboardString.
 */
const char* _glfwPlatformGetClipboardString(_GLFWwindow* window);

/*! @brief Returns the value of the specified joystick property.
 *  @param[in] joy The joystick to use.
 *  @param[in] param The property whose value to return.
 *  @return The value of the specified property, or zero if an error occurred.
 *  @ingroup platform
 */
int _glfwPlatformGetJoystickParam(int joy, int param);

/*! @ingroup platform
 */
int _glfwPlatformGetJoystickAxes(int joy, float* axes, int numaxes);

/*! @ingroup platform
 */
int _glfwPlatformGetJoystickButtons(int joy, unsigned char* buttons, int numbuttons);

/*! @ingroup platform
 */
const char* _glfwPlatformGetJoystickName(int joy);

/*! @brief Returns the current value of the timer.
 *  @return The value, in seconds, of the timer.
 *  @ingroup platform
 */
double _glfwPlatformGetTime(void);

/*! @brief Sets the value of the timer.
 *  @param[in] time The new value, in seconds, of the timer.
 *  @ingroup platform
 */
void _glfwPlatformSetTime(double time);

/*! @ingroup platform
 */
int _glfwPlatformCreateWindow(_GLFWwindow* window,
                              const _GLFWwndconfig* wndconfig,
                              const _GLFWfbconfig* fbconfig);

/*! @ingroup platform
 */
void _glfwPlatformDestroyWindow(_GLFWwindow* window);

/*! @ingroup platform
 */
void _glfwPlatformSetWindowTitle(_GLFWwindow* window, const char* title);

/*! @ingroup platform
 */
void _glfwPlatformSetWindowSize(_GLFWwindow* window, int width, int height);

/*! @ingroup platform
 */
void _glfwPlatformIconifyWindow(_GLFWwindow* window);

/*! @ingroup platform
 */
void _glfwPlatformRestoreWindow(_GLFWwindow* window);

/*! @ingroup platform
 */
void _glfwPlatformShowWindow(_GLFWwindow* window);

/*! @ingroup platform
 */
void _glfwPlatformHideWindow(_GLFWwindow* window);

/*! @ingroup platform
 */
void _glfwPlatformPollEvents(void);

/*! @ingroup platform
 */
void _glfwPlatformWaitEvents(void);

/*! @ingroup platform
 */
void _glfwPlatformMakeContextCurrent(_GLFWwindow* window);

/*! @ingroup platform
 */
_GLFWwindow* _glfwPlatformGetCurrentContext(void);

/*! @ingroup platform
 */
void _glfwPlatformSwapBuffers(_GLFWwindow* window);

/*! @ingroup platform
 */
void _glfwPlatformSwapInterval(int interval);

/*! @ingroup platform
 */
int _glfwPlatformExtensionSupported(const char* extension);

/*! @ingroup platform
 */
GLFWglproc _glfwPlatformGetProcAddress(const char* procname);

/*! @ingroup platform
 */
int _glfwPlatformExtensionSupported(const char* extension);

/*! @brief Returns the address of the specified client API function.
 *  @param[in] procname The name of the desired function.
 *  @return The address of the function, or @c NULL if it is not available.
 *  @ingroup platform
 */
GLFWglproc _glfwPlatformGetProcAddress(const char* procname);


//========================================================================
// Event API functions
//========================================================================

/*! @brief Notifies shared code of a window focus event.
 *  @param[in] window The window that received the event.
 *  @param[in] focused @c GL_TRUE if the window received focus, or @c GL_FALSE
 *  if it lost focus.
 *  @ingroup event
 */
void _glfwInputWindowFocus(_GLFWwindow* window, GLboolean focused);

/*! @brief Notifies shared code of a window movement event.
 *  @param[in] window The window that received the event.
 *  @param[in] x The new x-coordinate of the client area of the window.
 *  @param[in] x The new y-coordinate of the client area of the window.
 *  @ingroup event
 */
void _glfwInputWindowPos(_GLFWwindow* window, int x, int y);

/*! @brief Notifies shared code of a window resize event.
 *  @param[in] window The window that received the event.
 *  @param[in] width The new width of the client area of the window.
 *  @param[in] height The new height of the client area of the window.
 *  @ingroup event
 */
void _glfwInputWindowSize(_GLFWwindow* window, int width, int height);

/*! @brief Notifies shared code of a window iconification event.
 *  @param[in] window The window that received the event.
 *  @param[in] iconified @c GL_TRUE if the window was iconified, or @c GL_FALSE
 *  if it was restored.
 *  @ingroup event
 */
void _glfwInputWindowIconify(_GLFWwindow* window, int iconified);

/*! @brief Notifies shared code of a window show/hide event.
 *  @param[in] window The window that received the event.
 *  @param[in] visible @c GL_TRUE if the window was shown, or @c GL_FALSE if it
 *  was hidden.
 *  @ingroup event
 */
void _glfwInputWindowVisibility(_GLFWwindow* window, int visible);

/*! @brief Notifies shared code of a window damage event.
 *  @param[in] window The window that received the event.
 */
void _glfwInputWindowDamage(_GLFWwindow* window);

/*! @brief Notifies shared code of a window close request event
 *  @param[in] window The window that received the event.
 *  @ingroup event
 */
void _glfwInputWindowCloseRequest(_GLFWwindow* window);

/*! @brief Notifies shared code of a physical key event.
 *  @param[in] window The window that received the event.
 *  @param[in] key The key that was pressed or released.
 *  @param[in] action @ref GLFW_PRESS or @ref GLFW_RELEASE.
 *  @ingroup event
 */
void _glfwInputKey(_GLFWwindow* window, int key, int action);

/*! @brief Notifies shared code of a Unicode character input event.
 *  @param[in] window The window that received the event.
 *  @param[in] character The Unicode code point of the input character.
 *  @ingroup event
 */
void _glfwInputChar(_GLFWwindow* window, int character);

/*! @brief Notifies shared code of a scroll event.
 *  @param[in] window The window that received the event.
 *  @param[in] x The scroll offset along the x-axis.
 *  @param[in] y The scroll offset along the y-axis.
 *  @ingroup event
 */
void _glfwInputScroll(_GLFWwindow* window, double x, double y);

/*! @brief Notifies shared code of a mouse button click event.
 *  @param[in] window The window that received the event.
 *  @param[in] button The button that was pressed or released.
 *  @param[in] action @ref GLFW_PRESS or @ref GLFW_RELEASE.
 *  @ingroup event
 */
void _glfwInputMouseClick(_GLFWwindow* window, int button, int action);

/*! @brief Notifies shared code of a cursor motion event.
 *  @param[in] window The window that received the event.
 *  @param[in] x The new x-coordinate of the cursor, relative to the left edge
 *  of the client area of the window.
 *  @param[in] y The new y-coordinate of the cursor, relative to the top edge
 *  of the client area of the window.
 *  @ingroup event
 */
void _glfwInputCursorMotion(_GLFWwindow* window, int x, int y);

/*! @brief Notifies shared code of a cursor enter/leave event.
 *  @param[in] window The window that received the event.
 *  @param[in] entered @c GL_TRUE if the cursor entered the client area of the
 *  window, or @c GL_FALSE if it left it.
 *  @ingroup event
 */
void _glfwInputCursorEnter(_GLFWwindow* window, int entered);
void _glfwInputTouch(_GLFWwindow* window, int touch, int action);
void _glfwInputTouchPos(_GLFWwindow* window, int touch, double x, double y);

/*! @ingroup event
 */
void _glfwInputMonitorChange(void);

/*! @brief Notifies shared code of an error.
 *  @param[in] error The error code most suitable for the error.
 *  @param[in] format The @c printf style format string of the error
 *  description.
 *  @ingroup event
 */
void _glfwInputError(int error, const char* format, ...);


//========================================================================
// Utility functions
//========================================================================

/*! @ingroup utility
 */
const GLFWvidmode* _glfwChooseVideoMode(_GLFWmonitor* monitor,
                                        const GLFWvidmode* desired);

/*! @brief Performs lexical comparison between two @ref GLFWvidmode structures.
 *  @ingroup utility
 */
int _glfwCompareVideoModes(const GLFWvidmode* first, const GLFWvidmode* second);

/*! @brief Splits a color depth into red, green and blue bit depths.
 *  @ingroup utility
 */
void _glfwSplitBPP(int bpp, int* red, int* green, int* blue);

/*! @brief Searches an extension string for the specified extension.
 *  @param[in] string The extension string to search.
 *  @param[in] extension The extension to search for.
 *  @return @c GL_TRUE if the extension was found, or @c GL_FALSE otherwise.
 *  @ingroup utility
 */
int _glfwStringInExtensionString(const char* string, const GLubyte* extensions);

/*! @brief Chooses the framebuffer config that best matches the desired one.
 *  @param[in] desired The desired framebuffer config.
 *  @param[in] alternatives The framebuffer configs supported by the system.
 *  @param[in] count The number of entries in the alternatives array.
 *  @return The framebuffer config most closely matching the desired one, or @c
 *  NULL if none fulfilled the hard constraints of the desired values.
 *  @ingroup utility
 */
const _GLFWfbconfig* _glfwChooseFBConfig(const _GLFWfbconfig* desired,
                                         const _GLFWfbconfig* alternatives,
                                         unsigned int count);

/*! @brief Checks and reads back properties from the current context.
 *  @return @c GL_TRUE if successful, or @c GL_FALSE if the context is unusable.
 *  @ingroup utility
 */
GLboolean _glfwRefreshContextParams(void);

/*! @brief Checks whether the desired context properties are valid.
 *  @param[in] wndconfig The context properties to check.
 *  @return @c GL_TRUE if the context properties are valid, or @c GL_FALSE
 *  otherwise.
 *  @ingroup utility
 *
 *  This function checks things like whether the specified client API version
 *  exists and whether all relevant options have supported and non-conflicting
 *  values.
 */
GLboolean _glfwIsValidContextConfig(_GLFWwndconfig* wndconfig);

/*! @brief Checks whether the current context fulfils the specified hard
 *  constraints.
 *  @param[in] wndconfig The desired context properties.
 *  @return @c GL_TRUE if the context fulfils the hard constraints, or @c
 *  GL_FALSE otherwise.
 *  @ingroup utility
 */
GLboolean _glfwIsValidContext(_GLFWwndconfig* wndconfig);

/*! @ingroup utility
 */
_GLFWmonitor* _glfwCreateMonitor(const char* name,
                                 GLboolean primary,
                                 int widthMM, int heightMM,
                                 int x, int y);

/*! @ingroup utility
  */
void _glfwDestroyMonitor(_GLFWmonitor* monitor);

/*! @ingroup utility
  */
void _glfwDestroyMonitors(void);

#endif // _internal_h_
