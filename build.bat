@echo off

mkdir build
cd build
cmake .. -G "Visual Studio 15 2017 Win64" -DSFML_ROOT="C:/Program Files/SFML"
msbuild R-TYPE.sln /p:Configuration=Release
cd ..
Xcopy /E /I assets Release\assets
