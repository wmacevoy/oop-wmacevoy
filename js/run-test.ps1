Function ExitWithCode($exitcode) {
 $host.SetShouldExit($exitcode)
  exit
}

Function Background() { 
   $buildProc = Start-Process -NoNewWindow docker.exe  -windowstyle Hidden -ArgumentList "build -t js ." -PassThru
   $buildProc.WaitForExit();
   if ($buildProc.ExitCode -ne 0) {
      Write-Warning "$_ exited with status code $($buildProc.ExitCode)"
      ExitWithCode($buildProc.ExitCode) 
   }

   $runProc = Start-Process -NoNewWindow docker.exe  -windowstyle Hidden -ArgumentList "run --rm -v `"$(Get-Location):/app`" -p 8080:8080 js" -PassThru
   $runProc.WaitForExit();

   if ($runProc.ExitCode -ne 0) {
      Write-Warning "$_ exited with status code $($runProc.ExitCode)"
      ExitWithCode($runProc.ExitCode)
   }
}

Start-Process powershell -NoNewWindow {Background}
