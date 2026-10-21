struct Device { virtual ~Device() = default; int id = 0; };

struct Scanner : virtual Device { int dpi = 600; };
struct Printer : virtual Device { int ppm = 20; };

struct Copier : Scanner, Printer { int copies = 0; };   // ромб: Device один

static_assert(sizeof(Copier) == 48);
Copier copier;
