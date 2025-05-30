#include <X11/Xlib.h>
#include <stdio.h>

int main(void)
{
    Display *display;
    Window  *root;
    int root_x, root_y, win_x, win_y;
    unsigned int mask;

    display = XOpenDisplay(NULL);
    if (!display) {
        fprintf(stderr, "Error while opening connection to server X.\n");
        return 1;
    }

    XCloseDisplay(display);

    return 0;
}
