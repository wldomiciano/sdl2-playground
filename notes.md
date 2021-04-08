# Add Vcpkg as Git submodule

```sh
git submodule add https://github.com/microsoft/vcpkg
```

# Bootstrap vcpkg

```sh
./vcpkg/bootstrap-vcpkg.sh
```

# Install SDL2 and related projects

```sh
./vcpkg/vcpkg install  sdl2 sdl2-image sdl2-ttf
```

# Run with MinGW in MSYS2

```sh
cmake -G "MinGW Makefiles" -S . -B build -DVCPKG_TARGET_TRIPLET=x64-mingw-static -DVCPKG_APPLOCAL_DEPS=OFF
```

# Run with Clang in Ubuntu

```sh
cmake -S . -B build -DCMAKE_CXX_COMPILER=clang -DCMAKE_C_COMPILER=clang
```

# TODO

- Testar no terminal do macOS
- Testar com Clang
- Testar no Visual Studio
- Testar no CLion
- Testar no Code::Blocks
- Testar no Eclipse
- Testar no Netbeans
- Testar no XCode
- Testar no DevC++???
