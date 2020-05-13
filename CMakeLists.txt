project(simd_test)

set(CMAKE_CXX_STANDARD 11)

add_executable(test
        main.cc
        yuv_420.cc
        rgb_888.cc
        impl_general.cc)

