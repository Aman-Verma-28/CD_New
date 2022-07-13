# CD_New

    cd CD_Local
    cmake . && cmake --build .
    cd customCompiler
    clang++ checkPostIncrement.cpp -o check
    ./check ../testfiles/primitive.cpp
    ./check ../testfiles/nonprimitive.cpp
