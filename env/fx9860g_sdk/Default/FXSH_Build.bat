@echo off
rem Do not edit! This batch file is created by CASIO fx-9860G SDK.


if exist   del 

cd debug
if exist   del 
"C:\Program Files\CASIO\fx-9860G SDK\OS\SH\Bin\Hmake.exe" Addin.mak
cd ..
if not exist debug\  goto error

"C:\Program Files\CASIO\fx-9860G SDK\Tools\MakeAddinHeader363.exe" "C:\Program Files\CASIO\fx-9860G SDK\Default"
if not exist   goto error
echo Build has completed.
goto end

:error
echo Build was not successful.

:end

