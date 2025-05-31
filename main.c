#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <unistd.h>

/* Function declarations */
static void get_position(void);
static void setup_display(void);
static void show_all(void);
static void show_x(void);
static void show_y(void);
static void usage(void);

/* Variable declarations */
static int chr;
static Display *display;
static unsigned int mask;
extern char *optarg;
extern int optind;
static Window   root;
static int root_x, root_y, win_x, win_y;

/* Function definitions */
void get_position(void)
{
    int is_ok = XQueryPointer(
                    display,
                    root,
                    &root,
                    &root,
                    &root_x,
                    &root_y,
                    &win_x,
                    &win_y,
                    &mask
                    );

    if (!is_ok)
        errx(EXIT_FAILURE, "Error while getting cursor position.");
}

void setup_display(void)
{
    if (!(display = XOpenDisplay(NULL)))
        errx(EXIT_FAILURE, "Error while opening connection to server X.");
    root = DefaultRootWindow(display);
}

void show_all(void) 
{
    fprintf(stdout, "%d,%d\n", root_x, root_y);
}

void show_x(void)
{
    fprintf(stdout, "%d\n", root_x);
}

void show_y(void) 
{
    fprintf(stdout, "%d\n", root_y);
}

void usage(void)
{
    fprintf(stdout, "usage: getcp [-hxy]\n");
}

int main(int argc, char *argv[])
{
    setup_display(); 
    get_position();

    while ((chr = getopt(argc, argv, "hxy")) != -1) {
        switch (chr) {
            case 'x':
                show_x();
                return EXIT_SUCCESS;
            case 'y':
                show_y();
                return EXIT_SUCCESS;
            case 'h':
                usage();
                return EXIT_SUCCESS;
            default:
                /* Invalid option */
                usage();
                return EXIT_FAILURE;
        }
    }
    argc -= optind;
    argv += optind;
    
    /* Default behaviour */
    show_all();

    XCloseDisplay(display);
    return EXIT_SUCCESS;
}
