<#
.SYNOPSIS
    cfrost - Retrieve version, license, help, or library documentation.

.DESCRIPTION
    This script accepts a command and an optional path.
    --author          : Display the name of author.
    -- brief          : Display a brief text about the project.
    --version         : Display the script version.
    --license         : Display the content of the license file.
    --help            : Display general usage help.
    --help <path>     : Display documentation for a specific library.

.PARAMETER Command
    The command: --version, --license, or --help

.PARAMETER Path
    Optional library path for --help command

.EXAMPLE
    .\cfrost.ps1 --author
    .\cfrost.ps1 --brief
    .\cfrost.ps1 --version
    .\cfrost.ps1 --license
    .\cfrost.ps1 --help
    .\cfrost.ps1 --help cfrost/structure.h
    .\cfrost.ps1 --help cfrost.h
#>

param(
    [Parameter(Mandatory = $true, Position = 0)]
    [ValidateSet('--version', '--license', '--author', '--brief', '--help')]
    [string]$Command,
    
    [Parameter(Position = 1)]
    [string]$Path = $null
)

# ===================== Global Settings =====================
$script:Version = "beta 0.1.1"
$script:LicenseFile = Join-Path -Path $PSScriptRoot -ChildPath "documentation/lic.txt"
$script:HelpRoot = "help"
$script:briefFile = "help/brief.txt"

# ===================== Helper Functions =====================

function Show-Version {
    Write-Host "cfrost version $script:Version" -ForegroundColor Green
}

function Show-License {
    if (Test-Path $script:LicenseFile) {
        Write-Host "`n=== LICENSE ===`n" -ForegroundColor Yellow
        Get-Content $script:LicenseFile | ForEach-Object { Write-Host $_ }
    }
    else {
        Write-Error "License file not found: $script:LicenseFile"
        Write-Host "Please create a lic.txt file in the 'documentation' folder." -ForegroundColor Red
    }
}

function Show-Brief {
    if (Test-Path $script:briefFile) {
        Write-Host "`n=============== BRIEF ===============`n" -ForegroundColor Yellow
        Get-Content $script:briefFile | ForEach-Object { Write-Host $_ }
    }
    else {
        Write-Error "Brief file not found: $script:briefFile"
        Write-Host "Please create a brief.txt file in the 'documentation' folder." -ForegroundColor Red
    }
}

function Show-Help {
    $helpText = @"
===========================================
        cfrost - Information System
===========================================

Usage:
    .\cfrost.ps1 --author
    .\cfrost.ps1 --brief
    .\cfrost.ps1 --version
    .\cfrost.ps1 --license
    .\cfrost.ps1 --help
    .\cfrost.ps1 --help <path>

Options:
    --author                : Show the name of the author.
    --brief                 : Show a brief text.
    --version               : Show script version.
    --license               : Show license content (from documentation/lic.txt).
    --help                  : Show this help message.
    --help <path>           : Show documentation for a specific library.
                              <path> is the library file path (e.g., cfrost/structure.h).
                              The script looks for documentation at:
                              help/<path_without_extension>.txt

Examples:
    .\cfrost.ps1 --help cfrost/structure.h
    .\cfrost.ps1 --help cfrost.h

Note:
    - The documentation root folder is 'documentation/text' relative to the script location.
    - Path separators can be '/' or '\' and are handled correctly.
    - Any file extension is removed and replaced with .txt.
"@
    Write-Host $helpText -ForegroundColor White
}

function Search-Help {
    param([string]$LibraryPath)

    # Normalize path separators to Windows backslash
    $normalizedPath = $LibraryPath -replace '/', '\'
    
    # Remove extension (everything after the last dot)
    $withoutExt = $normalizedPath -replace '\.[^.]*$', ''
    
    # Build the documentation file path inside help
    $docFileRelative = Join-Path -Path $script:HelpRoot -ChildPath "$withoutExt.txt"
    
    # Get absolute path (based on script location)
    $docFullPath = Join-Path -Path $PSScriptRoot -ChildPath $docFileRelative

    Write-Host "Looking for documentation of: $LibraryPath" -ForegroundColor Cyan
    Write-Host "Expected documentation file: $docFileRelative" -ForegroundColor DarkGray

    if (Test-Path $docFullPath) {
        Write-Host "`n=== Documentation for: $LibraryPath ===`n" -ForegroundColor Yellow
        Get-Content $docFullPath | ForEach-Object { Write-Host $_ }
    }
    else {
        Write-Error "Documentation file not found: $docFileRelative"
        Write-Host "Please ensure the file exists at: $docFullPath" -ForegroundColor Red
        exit 1
    }
}

# ===================== Main Logic =====================

if ($Command -eq "--author") {
    Write-Host "author: Ali Lafi (acting under the pseudonym `Ken Roth`)"
}
elseif ($Command -eq "--version") {
    Show-Version
}
elseif ($Command -eq "--license") {
    Show-License
}
elseif ($Command -eq "--brief") {
    Show-Brief
}
elseif ($Command -eq "--help") {
    if ($Path) {
        Search-Help -LibraryPath $Path
    }
    else {
        Show-Help
    }
}