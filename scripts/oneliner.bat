:: Check privileges 
net file 1>NUL 2>NUL
if not '%errorlevel%' == '0' (
    powershell Start-Process -FilePath "%0" -ArgumentList "%cd%" -verb runas >NUL 2>&1
    exit /b
)

:: Change directory with passed argument. Processes started with
:: "runas" start with forced C:\Windows\System32 workdir
cd /d %1


powershell Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))

choco install -y visualstudio2019community vscode git

choco install -y visualstudio2019buildtools

choco install -y cmake --installargs 'ADD_CMAKE_TO_PATH=System'

choco install -y visualstudio2019-workload-vctools --package-parameters "--includeOptional"

choco install -y msys2

choco install -y cmake --installargs 'ADD_CMAKE_TO_PATH=System'

SET "PATH=C:\tools\msys64;C:\tools\msys64\mingw64\bin;C:\tools\msys64\usr\bin;%PATH%"

pacman -Syu

pacman -S --noconfirm --needed mingw-w64-x86_64-toolchain mingw-w64-x86_64-glfw python mingw-w64-x86_64-git-lfs mingw64/mingw-w64-x86_64-cmake

pacman -S --noconfirm mingw64/mingw-w64-x86_64-qt5 mingw64/mingw-w64-x86_64-qt-creator