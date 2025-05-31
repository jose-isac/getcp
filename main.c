#include <X11/Xlib.h>
#include <stdio.h>

int main(void)
{
    Display *display;
    Window   root;
    int root_x, root_y, win_x, win_y;
    unsigned int mask;

    display = XOpenDisplay(NULL);
    if (!display) {
        fprintf(stderr, "Error while opening connection to server X.\n");
        return 1;
    }

    root = DefaultRootWindow(display);
    
    if (XQueryPointer(display, root, &root, &root, &root_x, &root_y, &win_x, &win_y, &mask)) {
        fprintf(stdout, "%d,%d\n", root_x, root_y);
    } else {
        fprintf(stderr, "Error while getting cursor position.\n");
        return 1;
    }

    XCloseDisplay(display);

    return 0;
}
