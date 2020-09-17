
@"%SystemRoot%\System32\WindowsPowerShell\v1.0\powershell.exe" -NoProfile -InputFormat None -ExecutionPolicy Bypass -Command "[System.Net.ServicePointManager]::SecurityProtocol = 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))" && SET "PATH=%PATH%;%ALLUSERSPROFILE%\chocolatey\bin"
choco install -y msys2
choco install -y cmake --installargs 'ADD_CMAKE_TO_PATH=System'
SET "PATH=C:\tools\msys64;C:\tools\msys64\mingw64\bin;C:\tools\msys64\usr\bin;%PATH%"
pacman -Syu
pacman -S --noconfirm --needed mingw-w64-x86_64-toolchain mingw-w64-x86_64-glfw cmake git python mingw-w64-x86_64-git-lfs

cd \
git clone --recursive https://github.com/InfiniBrains/mobagen
