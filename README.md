<p align="center"><img src="https://camo.githubusercontent.com/a0059d19965c15e435f818c72e4fbf19a21a8bdda5deccef11fab4e36d45dd4c/68747470733a2f2f63646e2e646973636f72646170702e636f6d2f6174746163686d656e74732f3231313637393735383834373730353039382f3934353133373936333737303230383333362f6b736d2d6c6f676f2e706e67" alt="logo" width="300" /></p>

## About
The engine behind the upcoming KRECKA game series

## Building

### Dependencies
This project relies on the <a href="https://www.autodesk.com/developer-network/platform-technologies/fbx-sdk-2020-2">FBXSDK</a> provided by Autodesk

### Cloning
```
git clone --recursive https://github.com/afxw/ksm-dare.git
```

### Compiling
Windows (Visual Studio)
```
premake5 vs2019
MSBuild.exe Kreckanism.sln
```

Linux
```
premake5 gmake2
make
```
