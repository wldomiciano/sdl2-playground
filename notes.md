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

# Testar com Clang
