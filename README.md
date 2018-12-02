# Entry for Ludum Dare 43 - Sacrifices Must Be Made

https://ldjam.com/

[Entry link](https://ldjam.com/events/ludum-dare/43/$131423)

[Screenlapse video showing creation of game jam game](https://youtu.be/ExYgYxRjAL0)

## Downloads

[Windows 32bit](https://seodisparate.com/static/uploads/LD43_byStephen_BurnedKirby_Seo_Win32.zip)

[Linux/Ubuntu 64bit](https://seodisparate.com/static/uploads/LD43_byStephen_BurnedKirby_Seo_Ubuntu64.tar.gz)

## Compiling

You must use cmake (the buildWin/Makefile is only for cross-compiling from
ArchLinux host for 32-bit Windows target).

    mkdir build; cd build
    cmake -DCMAKE_BUILD_TYPE=Release ..
    make
    ./LD43

## Notices

[The source code in this project is under the BSD 2-Clause "Simplified" license.](https://github.com/Stephen-Seo/LudumDare43_SacrificesMustBeMade/blob/master/LICENSE)

[The assets in the assets/ directory is under the Creative Commons
Attribution-ShareAlike 4.0 International license (CC BY-SA 4.0).](https://github.com/Stephen-Seo/LudumDare43_SacrificesMustBeMade/blob/master/assets/ASSETS_LICENSE)

## Playing the game

The game requires some resources found in the assets/ directory of this project.

(Note that the downloads already have these resources packaged in them.)

The .mmpz files are [lmms](https://lmms.io) project files.

The game expects these resources (they should be in the same directory as the
game executable):
 - ld43\_music.ogg
 - ld43\_winmusic.ogg
 - sfx\_death.ogg
 - sfx\_goalreached.ogg
 - sfx\_jump.ogg
 - sfx\_keyget.ogg
 - controls.png

The .ogg files are exported from the lmms project files found in assets/.

The controls.png is found in assets/.
