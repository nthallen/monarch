#! /usr/bin/bash
function sgr_error {
   echo "setup_getrun.sh: $*" >&2
}

# Override this function to process the data from
# one Experiment in the input file. Can assume
# That $cur_exp and $data_dir_func are defined
function output_getrun_exp_ini {
  echo "Experiment=$cur_exp"
  echo "  data_dir_func=$data_dir_func"
  echo "  data_dir_desc='$data_dir_desc'"
  echo "  startup_func=$startup_func"
  echo "  ui_func=$ui_func"
  echo "  eng_dir=$eng_dir"
}

function clear_getrun_vars {
  cur_exp=''
  data_dir_func=''
  data_dir_desc=''
  startup_func=''
  ui_func=''
  eng_dir=''
}

function output_getrun_exp {
  if [ -n "$cur_exp" ]; then
    if [ -n "$data_dir_func" ]; then
      output_getrun_exp_ini
    else
      sgr_error "data_dir_func undefined for exp $cur_exp"
    fi
  fi
  clear_getrun_vars
}

function process_getrun_ini {
  ifile=$1
  clear_getrun_vars
  [ -f "$ifile" -a -r "$ifile" ] || {
    sgr_error "Unable to locate and/or read from input file '$ifile'"
    return
  }
  while read line; do
    #echo "Line is '$line'"
    var=''
    val=''
    case "$line" in
      '['*)
        output_getrun_exp
        next_exp=${line#[}
        cur_exp=${next_exp%]}
        ;;
      *=*)
        var=${line%%=*}
        val=${line##*=}
        case $var in
          data_dir_func) data_dir_func=$val;;
          startup_func) startup_func=$val;;
          eng_dir) eng_dir=$val;;
          data_dir_desc) data_dir_desc=$val;;
          ui_func) ui_func=$val;;
          *) nl_error "Unrecognized var '$var'";;
        esac;;
      *) [ -n "$line" ] && sgr_error "Unrecognized input in $ifile: '$line'";;
    esac
  done <$ifile
  output_getrun_exp
}
