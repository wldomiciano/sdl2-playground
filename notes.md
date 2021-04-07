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
