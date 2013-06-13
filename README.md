eglfsvb
=======

This is a Qt platform plugin based on EGLFS which implements the QPlatformScreenPageFlipper API.
This allows for direct surface rendering under QtWayland compositors.

Currently, page flipping is very simple: it simply takes a QImage handle (from a shared memory buffer) and copies it to
the fbdev (framebuffer) memory. This means that it only works with shm clients (i.e. widgets) and OpenGL implementations
which provide shared memory Wayland buffers (e.g. Mesa LLVMPipe).

## Build

Drop this in a directory next to the original EGLFS platform plugin. It does not need to be in the Qt source tree, but
can (EGLFS can be found at <qtbase>/src/plugins/platforms/eglfs). Assuming you have Qt 5.1 installed, you can now run:

    qmake
    make
    [sudo] make install


## Usage
Now that "eglfsvb" is installed, use it like you would use eglfs:
    ./my_qt_app -platform eglfsvb

If you have a QWaylandCompositor, you can call `setDirectRenderSurface(QWaylandSurface *, QOpenGLContext *)`
to specify the surface which you wish to flip directly to the screen. Call `setDirectRenderSurface(NULL)` to stop
direct rendering.

**NOTE**: currently the page flipper expects the image to be the same size and bit depth as the screen (i.e. a
fullscreen surface). It does not perform any scaling or relayout; it simply performs a wholesale memcpy.
