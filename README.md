[![linux](https://github.com/ikonopistsev/purestomp/workflows/linux/badge.svg?branch=main)](https://github.com/ikonopistsev/purestomp/actions?query=workflow%3Alinux)
[![windows](https://github.com/ikonopistsev/purestomp/workflows/windows/badge.svg?branch=main)](https://github.com/ikonopistsev/purestomp/actions?query=workflow%3Awindows)
[![macos](https://github.com/ikonopistsev/purestomp/workflows/macos/badge.svg?branch=main)](https://github.com/ikonopistsev/purestomp/actions?query=workflow%3Amacos)

# purestomp

An example of the [stomptalk](https://github.com/ikonopistsev/stomptalk) C API and a speed test.

It parses a buffer of ten frames ten million times: 100 million frames in all. The buffer holds a CONNECTED and nine MESSAGE frames, with LF and CRLF line ends, with and without `content-length`, and one escaped header. The test counts CONNECTED methods, `content-type:application/json` headers and body bytes. The method is recognized with `stomptalk_method_from`, and headers are compared by name in the callbacks.

The `stomptalk` submodule is pinned to stomptalk 2.0.1.

## Building

```
$ git clone --recursive https://github.com/ikonopistsev/purestomp.git
$ cmake -S purestomp -B build
$ cmake --build build
$ ./build/purestomp
stomptalk v2.0.1
connected 10000000, frame 100000000, json 10000000, total 670000000
```

A build without a build type uses `Release`. Do not build with `-O1`: see the stomptalk README.
