@echo off
SET SCRIPT_PATH=%~dp0
SET PROJECT_PATH=%SCRIPT_PATH%

REM Get IP address
for /f "tokens=2 delims=:" %%a in ('ipconfig ^| findstr /R /C:"IPv4 Address.*172\."') do set IP=%%a
set IP=%IP:~1%

REM Run the container
docker run -it --rm ^
    -e DISPLAY=%IP%:0.0 ^
    -v %PROJECT_PATH%:/app ^
    cpp-opengl-app