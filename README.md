# PowerOUT

This is a very old University coursework game using WINAPI - part of a second year module.

Some of the code got lost over the years - specifically the main.cpp - but I've rewritten it and got it running and compiling again under VS2019.

For fun, this was actually written on a Linux machine, compiling via WineGCC.

It's ... certainly something!

It's a riff on Deflektor and PipeMania, has ten levels, an attempt at "music" and isn't quite as bad as I remember it being - it's almost enjoyable! Worst part of it is the wires burning out - there is no indication that that has happened other than it disappearing. No effect - sound or graphical - is played, so it's not always obvious.

Codewise, it's a fun mess.
 - Globalsoup.
 - Hardcoded values for all.
 - Bizarre ways of checking tiles ( RGB checks! )
 - Stuff just scattered everywhere.

 It does still build on Linux - see the build.sh. This was last tested on Fedora Core 33 with Wine 6.0 (Staging). I couldn't get the mp3 player to work, so it's disabled.

 A Windows x86 binary is provided.
 
 A Visual Studio 2019 solution and project is also provided.

 