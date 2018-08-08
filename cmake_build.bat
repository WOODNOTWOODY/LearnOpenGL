@echo off

echo Specify the generator for this project
echo 1.Visual Studio 2013
echo 2.Visual Studio 2013 Win64
echo 3.Visual Studio 2017
echo 4.Visual Studio 2017 Win64

set /p a=select:
if %a%==1 goto vs12
if %a%==2 goto vs12_64
if %a%==3 goto vs15
if %a%==4 goto vs15_64

:vs12
mkdir Build.win32.vs12
cmake -E chdir Build.win32.vs12 cmake -G "Visual Studio 12 2013" ^
	-DMSVC=1 ^
	..
goto end

:vs12_64
mkdir Build.win64.vs12
cmake -E chdir Build.win64.vs12 cmake -G "Visual Studio 12 2013 Win64" ^
	-DMSVC=1 ^
	-DCPUX64=1 ^
	..
goto end

:vs15
mkdir Build.win32.vs15
cmake -E chdir Build.win32.vs15 cmake -G "Visual Studio 15 2017" ^
	-DMSVC=1 ^
	..
goto end

:vs15_64
mkdir Build.win64.vs15
cmake -E chdir Build.win64.vs15 cmake -G "Visual Studio 15 2017 Win64" ^
	-DMSVC=1 ^
	-DCPUX64=1 ^
	..
goto end

:end
pause
