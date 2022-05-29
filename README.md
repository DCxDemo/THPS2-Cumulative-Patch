# Cumulative Patch for Tony Hawk's Pro Skater 2 PC
This cumulative patch allows you to run THPS2 at a modern widescreen resolution in 32 bits color depth without FPS limit.

Download latest release here: https://github.com/DCxDemo/THPS2-Cumulative-Patch/releases/latest

For additional support join LegacyTHPS Discord: https://discord.gg/vTWucHS

## Key features:
* unlocked FPS, 32 bits, any resolution up to 2048 (DirectDraw limit)
* increased fog distance, field of view
* XInput controllers support
* additional levels support (from LevelPack)
* additional skater styles support
* unlimited custom soundtrack support, R3 skips track
* bonus: start+select on the controller quits the game instantly

## Compilation notes
C++ DLL project is compiled using Visual Studio 2022, toolset v143. \
Make sure $(ProjectDir) is added to Additional include directories. \
Make sure target binary is called dinput.dll, could be hawk2.dll by default

# Code quality warning
Core functionality was written back when I had little idea how stuff works in C++. \
The initial public release is a bit cleaned up and commented, but still a big mess of huge files and plate commented code.

# Links
* [LegacyTHPS Discord](https://discord.gg/vTWucHS)
* [Video preview of the patch](https://www.youtube.com/watch?v=1eHHqhsgC6w)
* [Original thps-mods thread](http://www.thps-mods.com/forum/viewtopic.php?t=5429)

2016-2018, 2022, DCxDemo*.