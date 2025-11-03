# - DLL Loader for GGXXACPR (Steam) -
by: lovenus

Version: 1.2.1

A Loader used to load custom DLLs into the game.

Instructions:
The DBGHELP.DLL must be placed in the same folder as GGXXACPR_Win.exe 
and any mod that requires it should be placed under a Mods folder 
that you must create yourself (that also has to be in the same folder 
as GGXXACPR_Win.exe, NOT inside Resource).

When playing on Linux/Steam Deck, add `WINEDLLOVERRIDES="dbghelp=n,b" %command%` to the game's launch options.

## Compiling
Release versions of the DLL Loader are compiled in the following way:

`gcc -shared -o DBGHELP.DLL source/source.c exports.def -g`
