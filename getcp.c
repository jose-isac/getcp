/* Author       : José Isac Araujo Monção (Rasq).
 * Objective    : Returns the current cursor position in an X11 graphical interface.
 * Usage        : See usage() or read README file.
 * Created      : 05/30/25
 * Last change  : 05/31/25
 * Architecture : x86_64
 * Build        : make
 * License      : See LICENSE file.
 * 
 * "Eu te amo Jesus"
 *
 */

#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>

/* Function declarations */
static void get_cursor_position(void);
static void setup_display(void);
static void show_all(void);
static void show_x(void);
static void show_y(void);
static void usage(void);

/* Variable declarations */
static Display *display;
static unsigned int mask;
static Window root;
static int root_x, root_y, win_x, win_y;

/* For option handling */
static int opt;
extern char *optarg;
extern int optind;

static bool x_flag;
static bool y_flag;
static bool h_flag;

/* Function definitions */
void get_cursor_position(void)
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
    fprintf(stdout, "usage: getcp\n");
    fprintf(stdout, "       getcp -x\n");
    fprintf(stdout, "       getcp -y\n");
    fprintf(stdout, "       getcp -h\n");
}

int main(int argc, char *argv[])
{
    while ((opt = getopt(argc, argv, "hxy")) != -1) {
        switch (opt) {
            case 'x':
                x_flag = true;
                break;
            case 'y':
                y_flag = true;
                break;
            case 'h':
                h_flag = true;
                break;
            case '?':
            default:
                /* Invalid option */
                usage();
                return EXIT_FAILURE;
        }
    }
    argc -= optind;
    argv += optind;

    if (h_flag) {
        usage();
        return EXIT_SUCCESS;
    } 

    setup_display();
    get_cursor_position();

    if (x_flag)
        show_x();
    else if (y_flag)
        show_y();
    else 
        show_all();
    
    XCloseDisplay(display);
    return EXIT_SUCCESS;
}
