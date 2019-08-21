IF NOT EXIST cache ( md cache )

IF NOT EXIST cache\boost_1_60_0-msvc-14.0-32.exe (
    curl -fsSL -o cache/boost_1_60_0-msvc-14.0-32.exe https://sourceforge.net/projects/boost/files/boost-binaries/1.60.0/boost_1_60_0-msvc-14.0-32.exe/download
)
IF NOT EXIST lib\boost_1_60_0 ( cache\boost_1_60_0-msvc-14.0-32.exe /DIR=lib/boost_1_60_0 /VERYSILENT )