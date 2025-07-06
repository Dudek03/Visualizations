
@echo off
echo Kompiluję GameOfLife.dll...

g++ -std=c++17 -shared -o GameOfLife.dll GameOfLife.cpp -static-libgcc -static-libstdc++

if %ERRORLEVEL% neq 0 (
    echo  Kompilacja nie powiodła się.
    exit /b %ERRORLEVEL%
)

echo  Kompilacja zakończona sukcesem.
