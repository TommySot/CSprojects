$sessionOptions = New-PSSessionOption -IncludePortInSPN
# Redacted OU's and domain name
$OU = "OU=xxx,OU=xxx,OU=xxx,DC=xxx,DC=xxx,DC=xxx"
$domainSuffix = "xxxxxxx.com"

# Script block to run on each remote server
$sb = {
    if (Test-Path "C:\Windows\WinSxS") {
        $size = ((Get-ChildItem -Path "C:\Windows\WinSxS" -Recurse -File | Measure-Object -Property Length -Sum).Sum / 1GB)
        $size = [Math]::Round($size, 2)
        Write-Output $size
    }
    else {
        Write-Output "WinSxS folder not found!"
    }
}

# Get list of servers in that OU
$Servers = Get-ADComputer -Filter * -SearchBase $OU -Property Name

foreach ($Computer in $Servers) {
    $ComputerName = $Computer.Name
    $FQDN = "$ComputerName$domainSuffix"
    Write-Output "Checking $FQDN 'C:\Windows\WinSxS' folder size..."

    try {
        # Create a temporary session, run command, and remove it
        $session = New-PSSession -ComputerName $FQDN -SessionOption $sessionOptions -ErrorAction Stop
        $result = Invoke-Command -Session $session -ScriptBlock $sb

        if ($result -is [double] -and $result -gt 15) {
            Write-Output "[$ComputerName] WinSxS folder size is $result GB --> Above 15 GB"
        }
        else {
            Write-Output "[$ComputerName] WinSxS folder size is $result GB"
        }

        Remove-PSSession $session
    }
    catch {
        Write-Warning "Failed to connect to $FQDN. $_"
    }
}
