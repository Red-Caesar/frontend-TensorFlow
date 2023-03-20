cmake_minimum_required(VERSION 3.24)
project(FrontendTensorFlow)

set(CMAKE_CXX_STANDARD 17)

add_executable(FrontendTensorFlow main.cpp bits.h fft.cpp fft.h filterbank.h filterbank.c
        frontend.c frontend.h kiss_fft_common.h kiss_fft_int16.h log_lut.c log_lut.h
        log_scale.c log_scale.h noise_reduction.c noise_reduction.h pcan_gain_control.c pcan_gain_control.h
        window.c window.h
        third_party/kissfft/kiss_fft.c third_party/kissfft/kiss_fft.h
        third_party/kissfft/_kiss_fft_guts.h third_party/kissfft/kiss_fft_log.h
        third_party/kissfft/tools/kiss_fftr.c third_party/kissfft/tools/kiss_fftr.h
        frontend_util.h frontend_util.c
        filterbank_util.h filterbank_util.c
        fft_util.h fft_util.cpp
        log_scale_util.h log_scale_util.c
        noise_reduction_util.h noise_reduction_util.c
        pcan_gain_control_util.h pcan_gain_control_util.c
        window_util.h window_util.c help_fun.h help_fun.cpp)
