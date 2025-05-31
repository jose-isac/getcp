#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

int main(void)
{
    Display *display;
    Window   root;
    int root_x, root_y, win_x, win_y;
    unsigned int mask;

    display = XOpenDisplay(NULL);
    if (!display) {
        errx(EXIT_FAILURE, "Error while opening connection to server X.");
    }

    root = DefaultRootWindow(display);
    
    if (XQueryPointer(display, root, &root, &root, &root_x, &root_y, &win_x, &win_y, &mask)) {
        fprintf(stdout, "%d,%d\n", root_x, root_y);
    } else {
        errx(EXIT_FAILURE, "Error while getting cursor position.");
    }

    XCloseDisplay(display);

    return EXIT_SUCCESS;
}
