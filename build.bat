@echo off
setlocal

rem === Folder resources ===
set C_SRC=src

rem === Format .c file is activated ===
for %%f in (%C_SRC%\*.c) do (
    echo [INFO] Formatting %%f
    clang-format -i "%%f" 
)

rem === Check if the build folder exists ===
if not exist build (
    echo [INFO] Build folder is not found. Create build folder
    mkdir build
)
cd build

rem === CMake configuration ===
cmake -G "MinGW Makefiles" ..

rem === Build project ===
cmake --build .

echo [INFO] Done
endlocal

cd build