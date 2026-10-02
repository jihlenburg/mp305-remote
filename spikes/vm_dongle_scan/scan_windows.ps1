# Listens for Bluetooth LE advertisements for $Seconds seconds with the
# Windows advertisement watcher (active scanning mode) and prints the ones
# that look like an MP305B (name layout or manufacturer data 0xABBA AF FA),
# plus the number of other addresses seen. No connection is made.
#
# Windows PowerShell 5.1 cannot subscribe to Windows Runtime events, so the
# listener is a small C# program built with the compiler that ships with
# the .NET Framework. Nothing is installed; the build output goes to the
# temp folder.
param([int]$Seconds = 15)
$ErrorActionPreference = 'Stop'
$rt = [System.Runtime.InteropServices.RuntimeEnvironment]::GetRuntimeDirectory()
$csc = Join-Path $rt 'csc.exe'
$md = Join-Path $env:windir 'System32\WinMetadata'
$work = Join-Path $env:TEMP 'mp305scan'
New-Item -ItemType Directory -Force -Path $work | Out-Null
$cs = Join-Path $work 'scan.cs'
$exe = Join-Path $work 'scan.exe'
$src = @'
using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using Windows.Devices.Bluetooth.Advertisement;
public static class Mp305Scan {
    public static int Main(string[] args) {
        int seconds = int.Parse(args[0]);
        var lines = new List<string>();
        var others = new HashSet<ulong>();
        var w = new BluetoothLEAdvertisementWatcher();
        w.ScanningMode = BluetoothLEScanningMode.Active;
        w.Received += (s, e) => {
            var adv = e.Advertisement;
            var sb = new StringBuilder();
            bool match = false;
            string name = adv.LocalName ?? "";
            if (name.Length >= 8 && name.Substring(4, 4) == "MP30") match = true;
            sb.Append(e.Timestamp.ToUniversalTime().ToString("HH:mm:ss.fff"));
            sb.Append(" addr ").Append(e.BluetoothAddress.ToString("X12"));
            sb.Append(" rssi ").Append(e.RawSignalStrengthInDBm);
            sb.Append(" type ").Append(e.AdvertisementType);
            sb.Append(" name [").Append(name).Append("]");
            foreach (var m in adv.ManufacturerData) {
                byte[] d = new byte[m.Data.Length];
                Windows.Storage.Streams.DataReader.FromBuffer(m.Data).ReadBytes(d);
                sb.Append(" mfr ").Append(m.CompanyId.ToString("X4")).Append(":").Append(BitConverter.ToString(d));
                if (m.CompanyId == 0xABBA && d.Length >= 2 && d[0] == 0xAF && d[1] == 0xFA) match = true;
            }
            foreach (var u in adv.ServiceUuids) sb.Append(" uuid ").Append(u);
            lock (lines) {
                if (match) lines.Add(sb.ToString()); else others.Add(e.BluetoothAddress);
            }
        };
        Console.WriteLine("start " + DateTime.UtcNow.ToString("yyyy-MM-ddTHH:mm:ssZ") + " for " + seconds + " s");
        w.Start();
        Thread.Sleep(seconds * 1000);
        Console.WriteLine("watcher status " + w.Status);
        w.Stop();
        lock (lines) {
            foreach (var line in lines) Console.WriteLine(line);
            Console.WriteLine("matching advertisements: " + lines.Count);
            Console.WriteLine("other addresses seen: " + others.Count);
        }
        return 0;
    }
}
'@
Set-Content -Path $cs -Value $src -Encoding UTF8
# The facade assemblies sit in the runtime directory or in its Facades
# subdirectory, depending on the Windows build.
function Find-Reference([string]$name) {
    foreach ($dir in @($rt, (Join-Path $rt 'Facades'))) {
        $path = Join-Path $dir $name
        if (Test-Path $path) { return $path }
    }
    throw "reference $name not found under $rt"
}
$refs = @(
    (Join-Path $md 'Windows.Devices.winmd'),
    (Join-Path $md 'Windows.Foundation.winmd'),
    (Join-Path $md 'Windows.Storage.winmd'),
    (Find-Reference 'System.Runtime.dll'),
    (Find-Reference 'System.Runtime.InteropServices.WindowsRuntime.dll')
)
$cscArgs = @('/nologo', '/target:exe', "/out:$exe") + ($refs | ForEach-Object { "/r:$_" }) + @($cs)
& $csc @cscArgs
if ($LASTEXITCODE -ne 0) { throw "csc failed with $LASTEXITCODE" }
& $exe $Seconds
