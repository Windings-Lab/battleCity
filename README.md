# How to Build
Source code of my first game written on C++

NewVersion is currently in development

How to create map

```
1 = Void
2 = Player
5 = Wall
6 = Phoenix
7 = PowerUps spawn positions
```

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
