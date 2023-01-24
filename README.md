# How to Build
Source code of my first game written on C++

How to create map

```
45x32 Dimension in txt file

1 = Void
2 = Player
5 = Wall
6 = Phoenix
9 = Tank Spawn Point

Look at the example in data/Maps/Map.txt
```
Name created txt file as Map.txt and move it in data/Maps/ folder

How to build:

* C++: 17
* Additional Include: &emsp;&emsp;`$(ProjectDir)pcheader\;$(ProjectDir)include\;%(AdditionalIncludeDirectories)`
* Additional Dependencies: &emsp;&emsp;&emsp;&emsp;`$(ProjectDir)lib\FrameworkRelease_x64.lib;%(AdditionalDependencies)`
* Additional Library Dependencies:&emsp;`$(ProjectDir)lib;%(AdditionalLibraryDirectories)`
* Use Precompiled Header: &emsp;&emsp;&emsp;&emsp;`"PCHeader.h"`

Post-Build Event:
```
call robocopy "$(SolutionDir)data" "$(TargetDir)data" /MIR
call robocopy "$(SolutionDir)lib" "$(TargetDir)." /XF FrameworkRelease_x64.lib
if %errorlevel% LEQ 3 exit 0
```

You can run game using command lines:

```
Usage: BattleCity.exe
Options:
	-w, -window 800x600	Specify window size
```