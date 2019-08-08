#include "TestCode.h"


int main(void) {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(XO_Test1),
            cmocka_unit_test(XO_Test2),
            cmocka_unit_test(XO_Test3),
            cmocka_unit_test(XO_Test4),
            cmocka_unit_test(XO_Test5),
            cmocka_unit_test(XO_Test6),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}