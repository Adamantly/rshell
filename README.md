This is my project which tries to emulate the bash terminal. However, this is without commands that don't require bin i.e cd. 
I used execvp to execute commands in the bin file.


Bugs:
======

1. Unable to exit from program when there's a space before exit.
2. Unable to do comments
3. Unable to run with connectors.
4. Unable to use the command "finger"
5. Unable to use quotes in command
6. Unable to echo after certain spaces

Bugs with LS:
===========

1. Some colors may not work.
2. Not correctly printed.
3. does not work with user defined directories, and paths.
4. Not alphabetical.
5. Invalid flags runs ls with no flags.

Bugs with Rshell(v2)
===========
1. Prompt is incorrectly outputed after using '&' character for background processes.
2. Append(>>)  does not currently work.
3. If there are no spaces between piping or i/o symbols, it will not work.
4. If you try to append to a non existent file, the program will bug and not work anymore.
5. if you run anything with background permissions, the program will stop printing out the bash prompt.

Bugs with Rshell(v3)
=======================
1. Still unable to pipe without spaces
