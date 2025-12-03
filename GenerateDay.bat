@echo off
set /p num=Which day is it (number only)?   

if %num% LSS 10 (
    set num=0%num%
)

mkdir %num%

copy base\main.cpp %num%\main.cpp
copy base\01 %num%\01
copy base\02 %num%\02

echo Day generated: %num%
pause
