#include <cstdio>

extern "C" void set_radius(double r) {
    std::printf("set_radius получила %f\n", r);
}
