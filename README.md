tvkey
=====

Makes the ThinkVantage button do something. X never sees that key (its code, 360, is past the 255 X can hold),
so tvkey reads it from the ThinkPad's own input device and runs a command. You need to be in the input group.

    tvkey tvpanel &      in .xinitrc

tvpanel is what it opens here: a floating st with fastfetch, the battery, temperature, fan and wifi, and keys
for the ThinkLight and the wallpaper. The ThinkLight needs write access to
/sys/class/leds/tpacpi::thinklight/brightness (a boot script giving it to the video group does it).

    ./build.sh           builds it on c.h, ./build.sh 32 for one i386 binary
