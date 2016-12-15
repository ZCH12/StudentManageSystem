@echo off
setlocal enabledelayedexpansion


:start
cls
(
	for /l %%a in (100001,1,200000) do (
		set /p b=160%%a <nul
		set /a aa=!random!%%499
		call :getXing "!aa!"
		set /a ab=!random!%%138
		call :getName "!ab!"
		set /a ad=!random!%%2
		set /p b=!ad! <nul
		set /a ae=!random!%%10
		set /p b=!ae! <nul
		for /l %%b in (1,1,10) do (
			set /a ac=!random!%%101
			set /p b=!ac! <nul
		)
		echo.
	)
) >1.txt
echo.生成成功
pause
exit

:getXing
if not "%~1"=="" (
set /a num=%~1+1
) else (
set /a num=1
)
for /f "skip=%num%" %%c in (姓.txt) do (
	set /p b=%%~c<nul
	goto :eof
)
goto :eof
   
:getName
if not "%~1"=="" (
set /a num=%~1+1
) else (
set /a num=1
)
for /f "skip=%num%" %%c in (名字.txt) do (
	set /p b=%%~c <nul
	goto :eof
)
goto :eof