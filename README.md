Hello world example based on fbthrift.

# Generate code from IDL with fbthrift 
```
../fbthrift/bin/thrift1 --gen mstch_cpp2 -v -debug -o ./ ./hello.thrift
```

# Build

```
mkdir build
cd build
cmake ..
// ccmake ..
make .
// make VERBOSE=1
```

# Other resources
https://github.com/lefticus/cpp_starter_project/blob/master/CMakeLists.txt