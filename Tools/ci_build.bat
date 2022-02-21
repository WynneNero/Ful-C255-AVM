@echo off
@echo VICP Toolset: build script for CI system invoke in command line.

REM version 1.0 on Sep 08,2016

rd /s/q ..\obj

REM SET GHS_COMPILER=c:\ghs\comp\ccv850.exe
REM MAKE THE CHANGE FOR JENKINS SYSTEM
SET GHS_COMPILER=C:\ghs\comp_201417\ccv850.exe
SET CI_BUILD_CFGFILE=.\tools\CI_BuildConfig\build.opt
SET CI_BUILD_LOGFILE=.\tools\CI_BuildConfig\build.log

REM go to upper directory to ensure file location in build.opt is recorganized by compiler
cd..

if not exist %GHS_COMPILER%     goto ERROR
if not exist %CI_BUILD_CFGFILE% goto ERROR1

%GHS_COMPILER%  @%CI_BUILD_CFGFILE%  > %CI_BUILD_LOGFILE%


@goto END


:ERROR
echo CI Build Script:FATAL ERROR: GHS compiler tool not found! 
goto ABORT
:ERROR1
echo CI Build Script:FATAL ERROR: build instruction file [build.opt] not found!
goto ABORT


:ABORT
@echo CI Build script abort!


:END
cd tools

call GenS19.bat
@echo on