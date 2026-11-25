# Usage:
# PS ..\sm0k34P1> .\build.ps1 64 Debug

Set-Location (Get-Item $PSScriptRoot)

. ./KoalaBox/build.ps1 sm0k34P1 @args

Build-Project
