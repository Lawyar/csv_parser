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
