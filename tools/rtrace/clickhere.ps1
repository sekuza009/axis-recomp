# a left click (or right with -right) where the pointer is, without moving it
param([switch]$right)
Add-Type -Namespace U -Name M -MemberDefinition @'
[DllImport("user32.dll")] public static extern void mouse_event(uint f, int dx, int dy, uint d, System.UIntPtr e);
'@
if ($right) { [U.M]::mouse_event(0x08, 0, 0, 0, [UIntPtr]::Zero); Start-Sleep -Milliseconds 60; [U.M]::mouse_event(0x10, 0, 0, 0, [UIntPtr]::Zero) }
else { [U.M]::mouse_event(0x02, 0, 0, 0, [UIntPtr]::Zero); Start-Sleep -Milliseconds 60; [U.M]::mouse_event(0x04, 0, 0, 0, [UIntPtr]::Zero) }
'ok'
