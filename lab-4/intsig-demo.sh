#!/bin/bash

intsig_source="intercept_signals.c"
intsig="intsig.o"

# compile sources
gcc -o $intsig $intsig_source

# start intsig.o
./$intsig &
pid=$( pidof $intsig )

kill -SIGINT $pid
test -n "$pid" && echo "Process still exists"

kill -SIGTERM $pid
test -n "$pid" && echo "Process was not terminated"

kill -SIGSTOP $pid
test `ps -q "$pid" -o state --no-header` = 'T' && echo "Process is stopped"

kill -SIGKILL $pid
test -z `pidof $intsig` && echo "Process is killed"
