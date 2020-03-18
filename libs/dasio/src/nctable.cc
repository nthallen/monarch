#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include "nl.h"
#include "dasio/nctable.h"
#include "dasio/cmd_writer.h"
// #include "tm.h"
// #include "cic.h" perhaps?
// extern int cic_cmd_quit_fd; //###
// int cic_init(void);

#include "nl_assert.h"
#include "oui.h"

#define MAX_DEVS 34

typedef struct {
  char *dev_name;
  SCREEN *screen;
  FILE *ofp, *ifp;
  int ifd;
  int dirty;
} nct_display_t;

static nct_display_t nct_display[MAX_DEVS];
static int n_devs = 0;
static int n_scrs = 0;
static int cur_scr_num;
static char *ttype;
static int ifds_opened = 0;
// static int nct_cmd_quit_fd = -1;

static inline void nct_select(int n) {
  nl_assert(n < n_scrs );
  if (cur_scr_num != n) {
    cur_scr_num = n;
    set_term(nct_display[n].screen);
  }
}

static inline void mark_dirty(void) {
  nct_display[cur_scr_num].dirty = 1;
}

static inline int is_dirty(int n) {
  return nct_display[n].dirty;
}

void nct_args( char *dev_name ) {
  if ( n_devs >= MAX_DEVS )
    msg( 2, "Too many devices specified" );
  else nct_display[n_devs++].dev_name = dev_name;
}

void nct_init_options(int argc, char **argv) {
  int optltr;

  optind = OPTIND_RESET;
  opterr = 0;
  while ((optltr = getopt(argc, argv, opt_string)) != -1) {
    switch (optltr) {
      case 'a':
        nct_charset(NCT_CHARS_ASCII);
        break;
      case '?':
        msg(3, "Unrecognized Option -%c", optopt);
      default:
        break;
    }
  }
  for (; optind < argc; optind++) {
    nct_args(argv[optind]);
  }
}

static void nct_shutdown(void) {
  int i;
  for ( i = 0; i < n_scrs; i++ ) {
    nct_display_t *d = &nct_display[i];
    set_term(d->screen);
    clear();
    refresh();
    reset_prog_mode();
    endwin();
    delscreen(d->screen);
    fclose(d->ofp);
    fclose(d->ifp);
  }
  while ( ifds_opened > 0 ) {
    close(nct_display[--ifds_opened].ifd);
  }
}

/**
 * Initializes an ncurses display. nct_init() cannot be called
 * after nct_getch().
 * @return the screen number.
 */
int nct_init( const char *winname, int n_rows, int n_cols ) {
  FILE *ofp, *ifp;
  char *dev_name;
  SCREEN *scr;
  nct_display_t *d;

  if ( n_scrs >= n_devs )
    msg( 3, "Not enough devices specified" );
  if ( ttype == NULL ) {
    ttype = getenv("TERM");
    if ( ttype == NULL )
      msg(3, "Cannot determine terminal type");
  }
  d = &nct_display[n_scrs];
  dev_name = d->dev_name;
  d->ofp = ofp = fopen( dev_name, "w" );
  if (ofp == NULL)
    msg( 3, "Cannot open %s for write", dev_name ); 
  d->ifp = ifp = fopen( dev_name, "r" );
  if (ifp == NULL)
    msg( 3, "Cannot open %s for read", dev_name );
  d->screen = scr = newterm(ttype, ofp, ifp );
  d->dirty = 0;
  set_term(scr);
  def_prog_mode();
  curs_set(0);
  if ( n_scrs == 0 )
    atexit( &nct_shutdown );
  return n_scrs++;
}

int nct_cmdclt_init() {
  int nct_win = nct_init("cmd", 2, 80);
  if (cic_init()) exit(1);
  // nct_cmd_quit_fd = cic_cmd_quit_fd;
  return nct_win;
}

void nct_refresh(void) {
  int i;
  for (i = 0; i < n_scrs; i++) {
    if (is_dirty(i)) {
      nct_select(i);
      refresh();
      nct_display[i].dirty = 0;
    }
  }
}

/** @brief Write string to an ncurses display
 *
 * winnum is the window number returned by nct_init();
 * attr is the atribute number (a small integer) as set
 * by nctable. This should map to screen colors, but
 * the implementation of that will have to wait.
 *
 */
void nct_string( int winnum, int attr, int row, int col, const char *text ) {
  nct_select(winnum);
  // color_set(color_pair_table(attr), NULL);
  mvaddstr(row, col, text);
  mark_dirty();
}

void nct_clear( int winnum ) {
  nct_select(winnum);
  clear();
  mark_dirty();
}

static unsigned char grphchar[81] = {
  0x20, /*  0 = 0000 */
  0xB3, /*  1 = 0001 */
  0xBA, /*  2 = 0002 */
  0xB3, /*  3 = 0010 */
  0xB3, /*  4 = 0011 */
  0xBA, /*  5 = 0012 */
  0xBA, /*  6 = 0020 */
  0xBA, /*  7 = 0021 */
  0xBA, /*  8 = 0022 */
  0xC4, /*  9 = 0100 */
  0xDA, /* 10 = 0101 */
  0xD6, /* 11 = 0102 */
  0xC0, /* 12 = 0110 */
  0xC3, /* 13 = 0111 */
  0xD6, /* 14 = 0112 */
  0xD3, /* 15 = 0120 */
  0xD3, /* 16 = 0121 */
  0xC7, /* 17 = 0122 */
  0xCD, /* 18 = 0200 */
  0xD5, /* 19 = 0201 */
  0xC9, /* 20 = 0202 */
  0xD4, /* 21 = 0210 */
  0xC6, /* 22 = 0211 */
  0xC9, /* 23 = 0212 */
  0xC8, /* 24 = 0220 */
  0xC8, /* 25 = 0221 */
  0xCC, /* 26 = 0222 */
  0xC4, /* 27 = 1000 */
  0xBF, /* 28 = 1001 */
  0xB7, /* 29 = 1002 */
  0xD9, /* 30 = 1010 */
  0xB4, /* 31 = 1011 */
  0xB7, /* 32 = 1012 */
  0xBD, /* 33 = 1020 */
  0xBD, /* 34 = 1021 */
  0xB6, /* 35 = 1022 */
  0xC4, /* 36 = 1100 */
  0xC2, /* 37 = 1101 */
  0xD2, /* 38 = 1102 */
  0xC1, /* 39 = 1110 */
  0xC5, /* 40 = 1111 */
  0xD2, /* 41 = 1112 */
  0xD0, /* 42 = 1120 */
  0xD0, /* 43 = 1121 */
  0xD7, /* 44 = 1122 */
  0xCD, /* 45 = 1200 */
  0x20, /* 46 = 1201 */
  0x20, /* 47 = 1202 */
  0x20, /* 48 = 1210 */
  0x20, /* 49 = 1211 */
  0x20, /* 50 = 1212 */
  0x20, /* 51 = 1220 */
  0x20, /* 52 = 1221 */
  0x20, /* 53 = 1222 */
  0xCD, /* 54 = 2000 */
  0xB8, /* 55 = 2001 */
  0xBB, /* 56 = 2002 */
  0xBE, /* 57 = 2010 */
  0xB5, /* 58 = 2011 */
  0x20, /* 59 = 2012 */
  0xBC, /* 60 = 2020 */
  0x20, /* 61 = 2021 */
  0xB9, /* 62 = 2022 */
  0x20, /* 63 = 2100 */
  0x20, /* 64 = 2101 */
  0x20, /* 65 = 2102 */
  0x20, /* 66 = 2110 */
  0x20, /* 67 = 2111 */
  0x20, /* 68 = 2112 */
  0x20, /* 69 = 2120 */
  0x20, /* 70 = 2121 */
  0x20, /* 71 = 2122 */
  0xCD, /* 72 = 2200 */
  0xD1, /* 73 = 2201 */
  0xCB, /* 74 = 2202 */
  0xCF, /* 75 = 2210 */
  0xD8, /* 76 = 2211 */
  0x20, /* 77 = 2212 */
  0xCA, /* 78 = 2220 */
  0x20, /* 79 = 2221 */
  0xCE  /* 80 = 2222 */
};

static unsigned char asciichar[81] = {
  ' ', /*  0 = LRTB */
  ',', /*  1 = 0001 */
  ',', /*  2 = 0002 */
  '\'', /*  3 = 0010 */
  '|', /*  4 = 0011 */
  '|', /*  5 = 0012 */
  '"', /*  6 = 0020 */
  '|', /*  7 = 0021 */
  '|', /*  8 = 0022 */
  '-', /*  9 = 0100 */
  '+', /* 10 = 0101 */
  '+', /* 11 = 0102 */
  '+', /* 12 = 0110 */
  '|', /* 13 = 0111 */
  '|', /* 14 = 0112 */
  '+', /* 15 = 0120 */
  '+', /* 16 = 0121 */
  '+', /* 17 = 0122 */
  '=', /* 18 = 0200 */
  '+', /* 19 = 0201 */
  '+', /* 20 = 0202 */
  '+', /* 21 = 0210 */
  '+', /* 22 = 0211 */
  '+', /* 23 = 0212 */
  '+', /* 24 = 0220 */
  '+', /* 25 = 0221 */
  '+', /* 26 = 0222 */
  '-', /* 27 = 1000 */
  '+', /* 28 = 1001 */
  '+', /* 29 = 1002 */
  '+', /* 30 = 1010 */
  '+', /* 31 = 1011 */
  '+', /* 32 = 1012 */
  '+', /* 33 = 1020 */
  '+', /* 34 = 1021 */
  '+', /* 35 = 1022 */
  '-', /* 36 = 1100 */
  '+', /* 37 = 1101 */
  '+', /* 38 = 1102 */
  '+', /* 39 = 1110 */
  '+', /* 40 = 1111 */
  '+', /* 41 = 1112 */
  '+', /* 42 = 1120 */
  '+', /* 43 = 1121 */
  '+', /* 44 = 1122 */
  '-', /* 45 = 1200 */
  '+', /* 46 = 1201 */
  '+', /* 47 = 1202 */
  '+', /* 48 = 1210 */
  '+', /* 49 = 1211 */
  '+', /* 50 = 1212 */
  '+', /* 51 = 1220 */
  '+', /* 52 = 1221 */
  '+', /* 53 = 1222 */
  '=', /* 54 = 2000 */
  '+', /* 55 = 2001 */
  '+', /* 56 = 2002 */
  '+', /* 57 = 2010 */
  '+', /* 58 = 2011 */
  '+', /* 59 = 2012 */
  '+', /* 60 = 2020 */
  '+', /* 61 = 2021 */
  '+', /* 62 = 2022 */
  '-', /* 63 = 2100 */
  '+', /* 64 = 2101 */
  '+', /* 65 = 2102 */
  '+', /* 66 = 2110 */
  '+', /* 67 = 2111 */
  '+', /* 68 = 2112 */
  '+', /* 69 = 2120 */
  '+', /* 70 = 2121 */
  '+', /* 71 = 2122 */
  '=', /* 72 = 2200 */
  '+', /* 73 = 2201 */
  '+', /* 74 = 2202 */
  '+', /* 75 = 2210 */
  '+', /* 76 = 2211 */
  '+', /* 77 = 2212 */
  '+', /* 78 = 2220 */
  '+', /* 79 = 2221 */
  '+'  /* 80 = 2222 */
};

static unsigned char *nct_boxchars = grphchar;

void nct_charset(int n) {
  switch (n) {
    case NCT_CHARS_GR:
      nct_boxchars = grphchar;
      break;
    case NCT_CHARS_ASCII:
      nct_boxchars = asciichar;
      break;
    default:
      msg(2, "Invalid charset code" );
  }
}

void nct_hrule( int winnum, int attr, int row, int col,
                unsigned char *rule ) {
  unsigned char *r = rule;
  nct_select(winnum);
  // color_set(color_pair_table(attr), NULL);
  while (*r) {
    mvaddch(row, col, nct_boxchars[*r]);
    ++r;
    ++col;
  }
}

void nct_vrule( int winnum, int attr, int row, int col,
                unsigned char *rule ) {
  unsigned char *r = rule;
  nct_select(winnum);
  // color_set(color_pair_table(attr), NULL);
  while (*r) {
    mvaddch(row, col, nct_boxchars[*r]);
    ++r;
    ++row;
  }
}

#include <fcntl.h>
#include <errno.h>
// #include <unix.h>
#include <sys/select.h>

#define IBUFSIZE 16

char nct_getch(void) {
  static char ibuf[IBUFSIZE];
  static int nc = 0;
  static int bp = 0;

  while ( ifds_opened < n_devs ) {
    nct_display_t *d = &nct_display[ifds_opened++];
    d->ifd = open( d->dev_name, O_RDONLY|O_NONBLOCK );
    if ( d->ifd == -1 )
      msg(3, "Unable to read from %s: %d", d->dev_name, errno );
    if (ifds_opened < n_scrs) {
      nct_select(ifds_opened);
      curs_set(1); // Turn on the cursor
    }
  }
  nl_assert(ifds_opened >= n_devs);
  // if (ifds_opened == n_devs && nct_cmd_quit_fd >= 0) {
    // nct_display[ifds_opened++].ifd = nct_cmd_quit_fd;
  // }
  for (;;) {
    if ( nc > 0 && bp < nc ) {
      return ibuf[bp++];
    } else {
      int i, width = 0, rv;

      nc = 0;
      bp = 0;
      fd_set fs;
      FD_ZERO(&fs);
      for ( i = 0; i < ifds_opened; i++ ) {
        int ifd = nct_display[i].ifd;
        FD_SET( ifd, &fs );
        if ( ifd >= width )
          width = ifd + 1;
      }
      rv = select(width, &fs, NULL, NULL, NULL);
      if ( rv == -1 ) {
        if ( errno != EINTR )
          msg( 3, "Error %d from select", errno );
      } else {
        for ( i = 0; i < ifds_opened; i++ ) {
          int ifd = nct_display[i].ifd;
          if ( FD_ISSET( ifd, &fs ) ) {
            int nb = read( ifd, &ibuf[nc], IBUFSIZE-nc );
            if ( nb == -1 ) {
              if (errno != EAGAIN && errno != EINTR)
                msg( 3, "Error %d from read()", errno );
            } else if ( nb == 0 ) {
              msg( 0, "Read 0 bytes" );
              exit(0);
            } else {
              nc += nb;
            }
          }
        }
      }
    }
  }
}
