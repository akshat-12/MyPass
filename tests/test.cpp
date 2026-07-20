#include <cstdlib>

int add(int a, int b) {
    return a + b;
}

int maxValue(int x, int y) {
    if (x > y) {
        return x;
    } else {
        return y;
    }
}

int accumulate(int n) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += i;
    }
    return sum;
}

void swapValues(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int compute(int x, int y, int z) {
    int result = add(x, y);
    if (result > z) {
        result += z;
    } else {
        result -= z;
    }
    return result;
}
