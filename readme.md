# OpenGL viewer
### Description
----
Simple viewer based on OpenGL. <br>
**Features**: mesh view

#### Build
----
> conan install . --output-folder=build --build=missing <br>
> cmake .. -G "Visual Studio 15 2017" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake <br>
> cmake --build . --config Release <br>

**You can vary Debug or other profiles instead Release, depending of your aims*
