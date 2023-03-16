set Program=%~1

%Program% data-test\empty.txt "%TEMP%\empty.txt" crypt 128 
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\empty.txt" data-test\empty.txt >nul
if ERRORLEVEL 1 goto err

%Program% data-test\The-Script-for-My-Requiem.txt "%TEMP%\The-Script-for-My-Requiem-crypt.txt" crypt 23 
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\The-Script-for-My-Requiem-crypt.txt" data-test\The-Script-for-My-Requiem-crypt.txt >nul
if ERRORLEVEL 1 goto err

%Program% "%TEMP%\The-Script-for-My-Requiem-crypt.txt" "%TEMP%\The-Script-for-My-Requiem-decrypt.txt" decrypt 23 
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\The-Script-for-My-Requiem-decrypt.txt" data-test\The-Script-for-My-Requiem-decrypt.txt >nul
if ERRORLEVEL 1 goto err

echo Program testing succesed
exit 0

:err
echo Program testing failed
exit 1