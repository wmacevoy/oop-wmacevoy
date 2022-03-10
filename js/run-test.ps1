function ExitWithCode($exitcode) {
  $host.SetShouldExit($exitcode)
  exit
}

$buildProc = Start-Process docker.exe  -windowstyle Hidden -ArgumentList "build -t js ." -PassThru
$buildProc.WaitForExit();
if ($buildProc.ExitCode -ne 0) {
    Write-Warning "$_ exited with status code $($buildProc.ExitCode)"
    ExitWithCode($buildProc.ExitCode)
}

$pwd = Get-Location
$runProc = Start-Process docker.exe  -windowstyle Hidden -ArgumentList "run --rm -v `"${pwd}:/app`" -p 8080:8080 js" -PassThru
$runProc.WaitForExit();

if ($runProc.ExitCode -ne 0) {
    Write-Warning "$_ exited with status code $($runProc.ExitCode)"
    ExitWithCode($runProc.ExitCode)
}
