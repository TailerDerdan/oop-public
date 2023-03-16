set Program=%~1

%Program% data_test\empty.txt "%TEMP%\empty.txt" 
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\empty.txt" data_test\empty-filled.txt >nul
if ERRORLEVEL 1 goto err

%Program% data_test\big-square.txt "%TEMP%\big-squre.txt" 
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\big-squre.txt" data_test\big-square-filled.txt >nul
if ERRORLEVEL 1 goto err

%Program% data_test\big-square.txt "%TEMP%\big-squre.txt" 
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\big-squre.txt" data_test\big-square-filled.txt >nul
if ERRORLEVEL 1 goto err

echo Program testing succesed
exit 0

:err
echo Program testing failed
exit 1