#include "TestCode.h"




void XO_Test1(void **state) {
    assert_int_equal(xo("xo"), true);
}

void XO_Test2(void **state) {
    assert_int_equal(xo("Xo"), true);
}

void XO_Test3(void **state) {
    assert_int_equal(xo("xxOo"), true);
}

void XO_Test4(void **state) {
    assert_int_equal(xo("xxxm"), false);
}

void XO_Test5(void **state) {
    assert_int_equal(xo("Oo"), false);
}

void XO_Test6(void **state) {
    assert_int_equal(xo("ooom"), false);
}