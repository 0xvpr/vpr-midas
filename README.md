<h1 align="center">vpr midas</h1>
<p align="center">
  <img src="https://img.shields.io/badge/Windows--x86__64-supported-44CC11?style=flat-square"/>
  <img src="https://img.shields.io/badge/Windows--x86-supported-44CC11?style=flat-square"/>
  <a href="https://mit-license.org/" target="_blank">
    <img src="https://img.shields.io/badge/License-MIT-44CC11"/>
  </a>
  <!--<img src="https://img.shields.io/github/actions/workflow/status/0xvpr/lazy-payload-poc/docker_build.yml?label=Build&style=flat-square"/>
  <img src="https://img.shields.io/github/actions/workflow/status/0xvpr/lazy-payload-poc/windows_runtime_test.yml?label=Tests"/>-->
</p>
<br>

This project aims to provide a tool for the modification of the  
date-time information of a file.

## Build instructions (Windows with CMake)
```powershell
git clone https://github.com/0xvpr/vpr-midas && cd vpr-midas
cmake.exe -B build
cmake.exe --build build
# cmake.exe --target install # if you want it available globally (only recommended for WSL/MSYS environments)
```

## Example Usage
```bash
vpr-midas path/to/file1 path/to/file2 -c "19900101000000" --silent
```

## Testing (Needs improvement)
```bash
chmod +x ./run-test.sh && ./run-test.sh
```
