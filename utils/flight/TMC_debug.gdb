start
set logging file monarch_gdb_pid_tmp.txt
set logging enabled on
p getpid()
set logging enabled off
!mv monarch_gdb_pid_tmp.txt monarch_gdb_pid.txt
