#define _POSIX_SOURCE
#include <stdio.h>

#ifdef _MSC_VER
#include <io.h>
#define isatty _isatty
#else
#include <sys/ioctl.h>
#endif

#include <unistd.h>

int term_width(void)
{
  int cols = 80;
  if (isatty(fileno(stderr))) {
#ifdef TIOCGSIZE
    struct ttysize ts;
    ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
    cols = ts.ts_cols;
#elif defined(TIOCGWINSZ)
    struct winsize ts;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
    cols = ts.ws_col;
#endif /* TIOCGSIZE */
  }
  return cols;
}
