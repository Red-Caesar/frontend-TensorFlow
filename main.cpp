#include <iostream>
#include "frontend.h"
#include "frontend_util.h"
// Configure FFT to output 16 bit fixed point.
#define FIXED_POINT 16

namespace {
    FrontendState g_micro_features_state;
    bool g_is_first_time = true;

}  // namespace

constexpr int kFeatureSliceSize = 10;
constexpr int kFeatureSliceStrideMs = 20;
constexpr int kFeatureSliceDurationMs = 30;
constexpr int kAudioSampleFrequency = 16000;

void InitializeMicroFeatures() {
    FrontendConfig config;
    config.window.size_ms = kFeatureSliceDurationMs;
    config.window.step_size_ms = kFeatureSliceStrideMs;
    config.noise_reduction.smoothing_bits = 10;
    config.filterbank.num_channels = kFeatureSliceSize;
//    config.filterbank.lower_band_limit = 125.0;
//    config.filterbank.upper_band_limit = 7500.0;
    config.filterbank.lower_band_limit = 20.0;
    config.filterbank.upper_band_limit = 4000.0;
    config.noise_reduction.smoothing_bits = 10;
    config.noise_reduction.even_smoothing = 0.025;
    config.noise_reduction.odd_smoothing = 0.06;
    config.noise_reduction.min_signal_remaining = 0.05;
    config.pcan_gain_control.enable_pcan = 1;
    config.pcan_gain_control.strength = 0.95;
    config.pcan_gain_control.offset = 80.0;
    config.pcan_gain_control.gain_bits = 21;
    config.log_scale.enable_log = 1;
    config.log_scale.scale_shift = 6;
    FrontendPopulateState(&config, &g_micro_features_state,kAudioSampleFrequency);
    g_is_first_time = true;
}

int main() {
    InitializeMicroFeatures();
    const int16_t frontend_input[] = {-11771, -11768, -11765, -11765, -11772, -11772, -11778, -11778, -11785, -11787, -11800, -11794, -11804, -11791, -11808, -11791, -11824, -11800, -11834, -11791, -11844, -11784, -11864, -11780, -11887, -11763, -11921, -11734, -11981, -11691, -11921, -1671, 1167, 341, 794, 474, 706, 518, 664, 539, 636, 547, 617, 556, 607, 565, 591, 555, 577, 557, 572, 559, 565, 549, 549, 543, 543, 537, 536, 530, 531, 534, 536, 538, 541, 543, 545, 548, 551, 553, 557, 558, 561, 562, 565, 567, 569, 570, 573, 575, 577, 579, 582, 583, 587, 588, 590, 592, 594, 597, 598, 601, 602, 604, 606, 608, 611, 612, 613, 615, 618, 619, 621, 622, 626, 628, 629, 631, 633, 634, 636, 638, 640, 642, 644, 645, 647, 650, 651, 652, 654, 656, 659, 660, 662, 664, 665, 667, 668, 670, 672, 673, 674, 676, 678, 679, 681, 683, 685, 686, 687, 689, 691, 692, 694, 696, 698, 699, 700, 701, 703, 705, 705, 707, 709, 709, 711, 712, 714, 714, 717, 718, 721, 721, 722, 723, 725, 727, 728, 729, 730, 732, 733, 734, 735, 737, 738, 740, 741, 742, 743, 744, 745, 747, 747, 749, 750, 750, 752, 753, 754, 755, 757, 759, 760, 760, 761, 762, 764, 764, 766, 768, 769, 770, 771, 773, 775, 775, 776, 777, 777, 779, 781, 781, 782, 783, 785, 786, 786, 788, 788, 788, 790, 792, 793, 793, 794, 795, 796, 797, 798, 798, 799, 801, 803, 803, 803, 804, 805, 806, 808, 809, 810, 811, 812, 813, 813, 814, 815, 817, 818, 818, 819, 820, 821, 822, 823, 823, 824, 825, 825, 826, 827, 828, 829, 829, 831, 831, 831, 833, 834, 834, 834, 836, 837, 838, 839, 840, 841, 842, 843, 844, 845, 846, 847, 847, 848, 849, 850, 851, 852, 853, 853, 855, 855, 856, 857, 857, 858, 860, 860, 861, 862, 863, 864, 865, 865, 866, 866, 868, 868, 868, 870, 871, 871, 872, 873, 874, 875, 875, 875, 876, 878, 878, 878, 880, 880, 881, 882, 883, 883, 884, 885, 886, 886, 888, 888, 888, 889, 889, 890, 892, 893, 893, 893, 894, 895, 895, 895, 896, 897, 898, 898, 899, 899, 900, 901, 902, 902, 903, 904, 904, 905, 906, 907, 907, 906, 907, 908, 908, 909, 909, 910, 911, 912, 913, 913, 914, 914, 915, 916, 915, 916, 917, 918, 918, 919, 920, 921, 921, 922, 921, 922, 922, 923, 923, 924, 925, 925, 926, 926, 927, 927, 927, 927, 927, 928, 929, 930, 930, 931, 932, 932, 932, 932, 932, 934, 934, 934, 935, 935, 936, 936, 936, 937, 938, 938, 938, 939, 939, 939, 939, 939, 940, 939, 940, 940, 940, 941, 941, 942, 943, 943, 944, 943, 944, 944, 944, 944, 944, 945, 946, 947, 946, 947, 948, 948, 949, 948, 948, 948, 948, 949, 949, 950, 951, 950, 951, 951, 951, 951, 951, 952, 953, 952, 953, 953, 954, 954, 955};
    int input_size = 480;
    size_t num= 320;
    size_t* num_samples_read = &num;
    FrontendOutput frontend_output = FrontendProcessSamples(
            &g_micro_features_state, frontend_input, input_size, num_samples_read);


    for (size_t i = 0; i < frontend_output.size; ++i){
        std::cout << frontend_output.values[i] << ' ';
    }

    std::cout << '\n';
    for (size_t i = 0; i < frontend_output.size; ++i) {
        constexpr int32_t value_scale = 256;
        constexpr int32_t value_div = static_cast<int32_t>((25.6f * 26.0f) + 0.5f);
        int32_t value =
                ((frontend_output.values[i] * value_scale) + (value_div / 2)) /
                value_div;
        value -= 128;
        if (value < -128) {
            value = -128;
        }
        if (value > 127) {
            value = 127;
        }
        std::cout << value << ' ';
    }
    return 0;
}
