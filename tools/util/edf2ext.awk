# edf2ext.awk Converts .edf files to .ext for TMC input.
# Revision 1.1  2008/09/22 13:36:29  ntallen
# edf tools for QNX6
#
# Revision 1.1  1993/05/28  20:06:11  nort
# Initial revision
function parse_datum(datum, results,     elements, seps) {
  delete results
  split(datum, elements, /[\[\]]/, seps)
  if (length(elements) == 1 && length(seps) == 0) {
    results[1] = elements[1]
  } else {
    if (length(seps) == 2 && seps[1] == "[" && seps[2] == "]" && length(elements) == 3) {
      results[1] = elements[1]
      results[2] = elements[2]
    } else {
      system( "echo " FILENAME ":" NR " unsupported array syntax: \\'" datum "\\' >&2" )
      exit( rv = 1 )
    }
  }
}

BEGIN {
  rv = 0
  using_sps = 0
  using_csv = 0
  using_json = 0
}
/^ *spreadsheet/ {
  if (using_csv) {
    system( "echo " FILENAME ":" NR " Cannot produce both csv and spreadsheet >&2" )
    exit( rv = 1 )
  }
  using_sps = 1
  if (written == 1) nsps++
  else {
    print "%{ /* edf2ext.awk reading " FILENAME " */"
    # A trailing }
    print "  #include <stdlib.h>"
    print "  #include <errno.h>"
    print "  #include \"ssp.h\""
    print "  #include \"snafuerr.h\""
    print "  #include \"msg.h\""
    print "  #include \"tmctime.h\""
    printf "\n"
    print "  #define Ct24_Long(x) (0xFFFFFF & *(TMLONG *)&x)"
    print "  #define Ct24_Double(x) (double)Ct24_Long(x)"
    print "  #define To_Double(x) (double)(x)"
    print "  #define EXTRACTION_INIT initialize()"
    print "  #define EXTRACTION_TERM terminate()"
    print "  #define ALL_SPSS"
    printf "\n"
    print "  static double ext_delta = 0.;"
    printf "\n"
    print "  static sps_ptr edf_ss_open( const char *name, int width ) {"
    print "    sps_ptr ss;"
    printf "\n"
    print "    ss = ss_open( name );"
    print "    if ( ss_error( ss ) ) {"
    print "      ss = ss_create( name, SPT_INCREASING, width, 0 );"
    print "      if ( ss_error( ss ) )"
    print "        msg( 3, \"Unable to create spreadsheet %s\", name );"
    print "      errno = 0;"
    print "      msg( 0, \"Creating spreadsheet %s.sps\", name );"
    print "    } else if ( ss_width( ss ) != width )"
    print "      msg( 3,"
    print "        \"Existing spreadsheet %s.sps not of width %d\", width );"
    print "    else msg( 0, \"Appending to spreadsheet %s.sps\", name );"
    print "    return ss;"
    print "  }"
    printf "\n"
    print "  static void edf_ss_insert_val( sps_ptr ssp, double V, double delta ) {"
    print "    int rv = ss_insert_value( ssp, V, delta );"
    print "    if (rv != 0 ) {"
    print "      ss_close_all();"
    print "      if ( rv == SFU_SPDSHT_FULL ) nl_error( 3, \"Spreadsheet full\");"
    print "      else nl_error( 3, \"SNAFU Error %d on insert\", rv );"
    print "    }"
    print "  }"
    printf "\n"
    written = 1;
    nsps = 0;
  }
  sps[nsps] = $2
  ncols[nsps] = $3
  cond[nsps] = ""
  if (NF > 3 && $4 == "separate") sep[nsps] = "y"
  next
}
/^ *(csv|json)/ {
  if (using_sps) {
    system( "echo " FILENAME ":" NR " Cannot produce both csv and spreadsheet >&2" )
    exit( rv = 1 )
  }
  using_csv = 1
  if (written == 1) nsps++
  else {
    print "%{ /* edf2ext.awk reading " FILENAME " */"
    # a trailing }
    print "  #include \"dasio/csv_file.h\""
    print "  #include \"dasio/msg.h\""
    print "  #include \"dasio/tmctime.h\""
    printf "\n"
    print "  #define Ct24_Long(x) (0xFFFFFF & *(TMLONG *)&x)"
    print "  #define Ct24_Double(x) (double)Ct24_Long(x)"
    print "  #define To_Double(x) (double)(x)"
    printf "\n"
    print "  static double ext_delta = 0.;"
    printf "\n"
    written = 1;
    nsps = 0;
  }
  sps[nsps] = $2
  ncols[nsps] = $3
  cond[nsps] = ""
  if (NF > 3 && $4 == "separate") sep[nsps] = "y"
}
/^ *csv/ {
  json[nsps] = 0
  next
}
/^ *json/ {
  json[nsps] = 1
  using_json = 1
  next
}

/^[ \t]*condition/ {
  cnd = $0
  sub( "^[ \t]*condition[ \t]*", "", cnd )
  cond[nsps] = cnd " "
  next
}
/^[ \t]*nan-text/ {
  cnd = $0
  sub( "^[ \t]*nan-text[ \t]*", "", cnd )
  nan_text[nsps] = cnd
  next
}
/^[ \t]*[0-9]/ {
  datum[nsps,$1] = $2
  if (using_sps) {
    if (NF >= 3) datfmt[nsps,$1] = $3
    else datfmt[nsps,$1] = "%9.2e"
    if (NF >= 4) datcnv[nsps,$1] = $4
    else datcnv[nsps,$1] = "convert"
  } else {
    if (NF >= 3) {
      datfmt[nsps,$1] = $3
      if (NF >= 4) datcnv[nsps,$1] = $4
      else datcnv[nsps,$1] = "convert"
    } else {
      datfmt[nsps,$1] = ""
      datcnv[nsps,$1] = "text"
    }
  }
  next
}
/init_only/ { init_only = "yes"; next }
/^[ \t]*[#;%]/ { next }
/^[ \t]*$/ { next }
{ system( "echo " FILENAME ":" NR " Syntax error >&2" )
  exit( rv = 1 )
}
END {
  if ( rv ) { exit(1); }
  if (using_sps) {
    # print the spreadsheet declarations
    for (i = 0; i <= nsps; i++)
      print "  sps_ptr " sps[i] ";"

    # print the initializations
    print "  void initialize(void) {"
    print "    {"
    print "      char *s;"
    print "      s = getenv(\"EXT_DELTA\");"
    print "      if (s != NULL) {"
    print "        ext_delta=atof(s);"
    print "        msg(MSG, \"Using Time Delta of %lf\", ext_delta);"
    print "      }"
    print "    }"
    for (i = 0; i <= nsps; i++) {
      print "    " sps[i] " = edf_ss_open( \"" sps[i] "\", " ncols[i] " );"
      print "    ss_set_column(" sps[i] ", 0, \"%14.11lt\", \"Time\");"
      for (j = 1; j < ncols[i]; j++) {
        if (datfmt[i,j] == "") datfmt[i,j] = "%9.2e"
        printf "    ss_set_column(" sps[i] ", " j ", "
        print "\"" datfmt[i,j] "\", \"" datum[i,j] "\");"
      }
    }
    print "  }"
    
    # print the terminations
    print "  void terminate(void) {"
    for (i = 0; i <= nsps; i++) {
      print "    ss_close(" sps[i] ");"
    }
    print "  }"
    # A leading {
    print "%}"

    # print the extraction statements
    if (init_only != "yes") {
      for (i = 0; i <= nsps; i++) {
        k = 0;
        for (j = 1; j < ncols[i]; j++) {
          if (datum[i,j] != "") {
            if (k > 0 && sep[i] == "y") print "}"
            if (k == 0 || sep[i] == "y") {
              print cond[i] "{"
              print "  edf_ss_insert_val(" sps[i] ", dtime()+ext_delta, 0);"
            }
            printf "  ss_set(" sps[i] ", " j ", "
            print datcnv[i,j] "(", datum[i,j] "));"
            k++;
          }
        }
        # leading {
        print "}"
      }
    }
  } else {
    # print the csv_file declarations
    if (using_json) {
      print "  #include \"dasio/json_srvr.h\""
    }
    for (i = 0; i <= nsps; i++) {
      if (json[i]) {
        if (nan_text[i] == "") {
          nan = ", \"\\\"\\\"\""
        } else {
          nan = ", \"" nan_text[i] "\""
        }
        print "  csv_file " sps[i]"(\"" sps[i] "\", " ncols[i] nan ", 1);"
      } else {
        if (nan_text[i] == "") {
          nan = ""
        } else {
          nan = ", \"" nan_text[i] "\""
        }
        print "  csv_file " sps[i]"(\"" sps[i] ".csv\", " ncols[i] nan ");"
      }
    }

    # print the initializations
    print "  void initialize(void) {"
    print "    {"
    print "      char *s;"
    print "      s = getenv(\"EXT_DELTA\");"
    print "      if (s != NULL) {"
    print "        ext_delta=atof(s);"
    print "        msg(MSG, \"Using Time Delta of %lf\", ext_delta);"
    print "      }"
    print "    }"
    # trailing }
    for (i = 0; i <= nsps; i++) {
      printf "    " sps[i] ".init();\n"
      if (datum[i,0] == "") datum[i,0] = "Time";
      col = 0
      for (j = 0; j < ncols[i]; j++) {
        if (j == col) {
          parse_datum(datum[i,j], res)
          if (length(res) == 1) {
            # print "scalar " res[1]
            printf "    " sps[i] ".init_col(" j ", \"" datum[i,j] "\""
            if ( datfmt[i,j] != "" ) printf ", \"%s\"", datfmt[i,j]
            print ");"
            ++col
          } else {
            # print "array " res[1] " length " res[2]
            printf "    " sps[i] ".init_col(" col ", \"" res[1] "\""
            if ( datfmt[i,j] != "" ) printf ", \"%s\"", datfmt[i,j]
            print ");"
            print "    " sps[i] ".init_array(" col ", " res[2] ");"
            col += res[2]
          }
        } else {
          # verify that datum[i,j] does not exist
          if (datum[i,j] != "") {
            system( "echo " FILENAME ":" NR " Column " j " multiply defined >&2" )
            exit( rv = 1 )
          }
        }
      }
      if (json[i]) {
        print "    " sps[i] ".set_jcb(DAS_IO::json_server::jcb);"
      }
    }
    # A leading { 
    print "  }"
    # A leading { 
    print "%}"
    print "TM INITFUNC initialize();"

    # print the extraction statements
    if (init_only != "yes") {
      for (i = 0; i <= nsps; i++) {
        k = 0
        col = 1
        for (j = 1; j < ncols[i]; j++) {
          if (datum[i,j] != "") {
            # leading {
            if (k > 0 && sep[i] == "y") print "}"
            if (k == 0 || sep[i] == "y") {
              print cond[i] "{"
              # trailing }
              if (using_sps) {
                print "  edf_ss_insert_val(" sps[i] ", dtime()+ext_delta, 0);"
              } else {
                print "  " sps[i] ".set_time(dtime()+ext_delta);"
              }
            }
            parse_datum(datum[i,j], res)
            if (length(res) == 1) {
              # print "scalar " res[1]
              if (using_sps) {
                printf "  ss_set(" sps[i] ", " j ", "
                print datcnv[i,j] "(" res[1] "));"
              } else {
                printf "  " sps[i] ".set_col(" j ", "
                print datcnv[i,j] "(" res[1] "));"
              }
              ++col
              ++k
            } else {
              # print "array " res[1] " length " res[2]
              while (col < j+res[2]) {
                if (using_sps) {
                  printf "  ss_set(" sps[i] ", " col ", "
                  print datcnv[i,j] "(" res[1] "[" col-j  "]));"
                } else {
                  printf "  " sps[i] ".set_col(" col ", "
                  print datcnv[i,j] "(" res[1] "[" col-j  "]));"
                }
                ++col
              }
              ++k
            }
          }
        }
        # leading {
        print "}"
      }
    }
  }
}
