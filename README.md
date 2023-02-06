### Build the project with CMake  

1. Navigate to a source code folder.
```
mkdir build
cd build
```

2. Build the source code
```
cmake --build . -j12
```

3. Run executables
```
cd bin
./csv_parser_tests
./csv_parser ../../data/csv5.csv
```

Tested on:
1. g++ (Ubuntu 10.3.0-1ubuntu1~20.04) 10.3.0
2. Microsoft (R) C/C++ Optimizing Compiler Version 19.34.31937 for x86
3. Apple clang version 14.0.0 (clang-1400.0.29.102)

No memory leaks detected (tested with valgrind-3.15.0)
