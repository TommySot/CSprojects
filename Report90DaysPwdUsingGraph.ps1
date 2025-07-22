New-UDApp -Title 'Report-90 days since last password reset' -Content{


    Sync-UDElement -Id 'list_users'


    New-UDDynamic -Id 'list_users' -Content{

	    #Redacted cert and ids
            Connect-MgGraph -CertificateThumbprint 'xxxxxxxxxxxxxxxxxxxxxxxxxx' -TenantId 'xxxxxxxxxxxxxxx' -ClientId 'xxxxxxxxxxxxxxxxxx' -NoWelcome 

        $DateThreshold = (Get-Date).AddDays(-90) # Date Threshold can be set, currently 90 days

# Pulls list of users, sorts out non-employee accounts and disabled accounts
$userlist = Get-MgUser -All -Property UserPrincipalName, lastPasswordChangeDateTime, Surname, employeeID, DisplayName -Filter "accountEnabled eq true"|
    Where-Object {
        $_.Surname -and $_.Surname.Trim() -ne '' -and
        $_.employeeID -and $_.employeeID.Trim() -ne ''
    } |
     Select-Object @{
        Name = 'DisplayName'
        Expression = { $_.DisplayName }
     }, @{
        Name = 'UserPrincipalName'
        Expression = { $_.UserPrincipalName }
    }, @{
        Name = 'lastPasswordChangeDateTime'
        Expression = {
            $dt = [datetime]$_.lastPasswordChangeDateTime       # Sorts out placeholder dates on accounts
            if ($dt -eq [datetime]'1601-01-01') {
                'Never Set'
            } elseif ($dt -le $DateThreshold) {
                $dt
            } else {
                $null
            }
        }
    } |
    Where-Object { $_.lastPasswordChangeDateTime } |
    Sort-Object lastPasswordChangeDateTime              # Sorts table by last Password set date w/ Never set at bottom

Disconnect-MgGraph

$Columns = @(
    New-UDTableColumn -Property DisplayName -Title "Name" -ShowFilter
    New-UDTableColumn -Property UserPrincipalName -Title "Account Name" -ShowFilter
    New-UDTableColumn -Property lastPasswordChangeDateTime -Title "Password Last Set Date" -ShowFilter
)

New-UDTable -Columns $Columns -Data $userlist
    }
}
