set Program=%~1

%Program% tests\empty.txt "%TEMP%\empty.txt" B A
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\empty.txt" tests\empty.txt >nul
if ERRORLEVEL 1 goto err

%Program% tests\song.txt "%TEMP%\song-replace.txt" line square
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\song-replace.txt" tests\song-replace-line-square.txt >nul
if ERRORLEVEL 1 goto err

%Program% tests\text-replace-zero.txt "%TEMP%\zero-replace.txt" around ""
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\zero-replace.txt" tests\text-replace-zero.txt >nul
if ERRORLEVEL 1 goto err

%Program% tests\mother.txt "%TEMP%\mother-replace.txt" ma mama
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\mother-replace.txt" tests\mother-ma-mama.txt >nul
if ERRORLEVEL 1 goto err

echo Program testing succesed
exit 0

:err
echo Program testing failed
exit 1