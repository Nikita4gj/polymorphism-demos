#include <cstdio>

struct Plain { int i; char c; };   // POD
struct PlainChild : Plain { char d; };

struct WithCtor {                  // уже не POD
    int i; char c;
    WithCtor() : i(0), c(0) {}
};
struct WithCtorChild : WithCtor { char d; };

int main() {
    std::printf("PlainChild:    %zu\n", sizeof(PlainChild));      // 12
    std::printf("WithCtorChild: %zu\n", sizeof(WithCtorChild));   // 8
}
