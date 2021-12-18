$data = Get-Content ./realinput.txt


for ([int] $i = 0; $i -lt $data.Length - 2; $i += 1)
{
    for ([int]  $j = $i + 1; $j -lt $data.Length - 1; $j += 1)
    {
        if ($i -ne $j)
        {
            "$($data[$i])`n$($data[$j])" > ./input.txt
            #exit 1 
            & "C:\Repos\aoc-2021\x64\Debug\AocSolutions.exe"

            "$($data[$j])`n$($data[$i])" > ./input.txt
            #exit 1 
            & "C:\Repos\aoc-2021\x64\Debug\AocSolutions.exe"
        }
    }
}

[int] $max = -1;
$values = Get-Content ./out.txt
foreach ($v in $values)
{
    if ([int] $v -gt $max)
    {
        $max = $v
        write-output $max 
    }
}

write-output $max