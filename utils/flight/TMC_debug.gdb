start
set logging file monarch_gdb_pid_tmp.txt
set logging on
p getpid()
set logging off
!mv monarch_gdb_pid_tmp.txt monarch_gdb_pid.txt
