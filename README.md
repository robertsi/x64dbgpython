# x64dbg python

x64dbg python is a x64dbg plugin allow you to run python script to interactive with x64dbg in python3. x64dbg python provide script api similar to `_scriptapi_*.h` header in plugin SDK. You can look at folder "example script" for example

## Installation

- Install both python3 32 bit and 64 bit. Don't forget to add to path environment.
- Copy plugin to x32dbg and x64dbg plugin folder  

**New version of  x64dbg block load dependencies from PATH. Please use `snapshot_2023-03-03_01-29` or using [PATH](https://github.com/ElvisBlue/PATH) plugin to load this plugin**

## Wrapper

x64dbg python made some wrapper for easy to use in python language. If you're going to using one of those function below, look at [wrapper](/WRAPPER.md) definition instead.

## Credits

- [pybind11](https://github.com/pybind/pybind11)
- [VC-LTL](https://github.com/Chuyu-Team/VC-LTL)
- [x64dbg](https://github.com/x64dbg/x64dbg)

 
## Donation

Please consider donating to [x64dbg](https://github.com/x64dbg/x64dbg)

## _x64dbgpython companion plugin

This is just a necessary helper plugin that reads PythonHome from x32dbg.ini and x64dbg.ini and puts the python folder on the x64dbg bin path. It runs before x64dbgpython plugin so that python.dll/folder is available. No need to use PATH plugin anymore and pollute System/User path environemnt variable anymore.

Example enetry in x32dbg.ini

```ini
[x64dbgpython]
PythonHome=C:\Users\robert\AppData\Local\Python\pythoncore-3.14-32
```

### Build

```powershell
# get cmkr
iwr "https://raw.githubusercontent.com/build-cpp/cmkr/main/cmake/cmkr.cmake" -OutFile "cmake/cmkr.cmake"
# Generate CMakeLists.txt from cmake.toml
cmake -P cmake/cmkr.cmake 
cmake -B Release/x86 -A Win32
cmake --build Release/x86 --config Release

cmake -B Release/x64 -A x64
cmake --build Release/x64 --config Release
```
