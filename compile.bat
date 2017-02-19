@echo off
echo Compiling %1.cpp
g++ -std=c++14 -o %1.exe %1.cpp
IF %ERRORLEVEL% == 0 (GOTO OK) ELSE (GOTO FAIL)
exit

:OK
echo Compilation succeded
start run.bat %1
exit

:FAIL
echo Compilation failed
exit
