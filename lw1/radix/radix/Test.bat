set Program=%~1

%Program% "16" "10" "1F"
if ERRORLEVEL 1 goto err

echo Program testing succesed
exit 0

:err
echo Program testing failed
exit 1