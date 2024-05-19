@echo off
rem Do not edit! This batch file is created by CASIO fx-9860G SDK.

if exist debug\*.obj  del debug\*.obj
if exist SHENAN.G1A  del SHENAN.G1A

cd debug
if exist FXADDINror.bin  del FXADDINror.bin
"D:\programing\projects\casio\env\fx9860g_sdk\OS\SH\Bin\Hmake.exe" Addin.mak
cd ..
if not exist debug\FXADDINror.bin  goto error

"D:\programing\projects\casio\env\fx9860g_sdk\Tools\MakeAddinHeader363.exe" "D:\programing\projects\casio\SN"
if not exist SHENAN.G1A  goto error
echo Build has completed.
goto end

:error
echo Build was not successful.

:end

