#pragma once

#include <stdint.h>

namespace Kernel {

class Uart final {

public:
    Uart() { setup(); }

    ~Uart() = default;

    void print(const char*) const;

private:
    void setup() const;

    void wait() const;
};

}
