# put this line into the main .gdbinit file in $HOME
set auto-load safe-path /

# remote connection
#target remote 10.0.0.10:9999

# Set binary arguments
set args --encrypt /home/christian/projects/butterfly/fs/home/butterfly/data/small/ --config /home/christian/projects/butterfly/config/console.ini

# Generic break point
break main
