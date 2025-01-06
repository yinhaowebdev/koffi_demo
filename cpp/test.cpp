// #include <iostream>

extern "C" {
    double add(double a, double b) {
        return a + b;
    }

    const char* greet() {
        return "Hello from C++!";
    }
}
