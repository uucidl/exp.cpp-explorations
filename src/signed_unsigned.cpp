#include <cstdint>

int main()
{
        uint8_t value = 64;
        size_t i = 5;
        if (i < value/8) {
        }
}

/*

On MSVC VC 14.0, the above code triggers a signed/unsigned comparison
warning at line 7, despite the fact that both value and 8 are
positive.

$ cl -Wall src/signed_unsigned.cpp
Microsoft (R) C/C++ Optimizing Compiler Version 19.00.23026 for x86
Copyright (C) Microsoft Corporation.  All rights reserved.

signed_unsigned.cpp
src/signed_unsigned.cpp(7): warning C4018: '<': signed/unsigned mismatch
Microsoft (R) Incremental Linker Version 14.00.23026.0
Copyright (C) Microsoft Corporation.  All rights reserved.

/out:signed_unsigned.exe
signed_unsigned.obj
*/
