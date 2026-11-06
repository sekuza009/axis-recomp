# suspend a process for some seconds, then resume it (packet-loss test)
param([string]$name, [int]$seconds)
Add-Type -Namespace U -Name N -MemberDefinition @'
[DllImport("ntdll.dll")] public static extern int NtSuspendProcess(System.IntPtr h);
[DllImport("ntdll.dll")] public static extern int NtResumeProcess(System.IntPtr h);
'@
$p = Get-Process $name -ErrorAction Stop | Select-Object -First 1
[U.N]::NtSuspendProcess($p.Handle) | Out-Null; Start-Sleep -Seconds $seconds; [U.N]::NtResumeProcess($p.Handle) | Out-Null
"suspended $name for $seconds s"
