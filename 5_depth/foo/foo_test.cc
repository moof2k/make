#include "foo.h"
#include <assert.h>
#include <stdio.h>

int main() {
    Foo foo;
    printf("Running foo_test\n");
    assert(foo.GetFoo() == 7);
    return 0;
}
