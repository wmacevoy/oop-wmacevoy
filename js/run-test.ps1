$buildProc = Start-Process -NoNewWindow docker  -ArgumentList "build -t js ." -PassThru
   $buildProc.WaitForExit();
   Start-Process powershell -NoNewWindow ".\run-background.ps1"
