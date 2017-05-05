#include "foo.h"
#include <assert.h>
#include <stdio.h>

int main() {
    Foo foo;
    printf("Running foo_test\n");
    assert(foo.GetFoo() == 7);

    int *bogus = (int *) malloc(sizeof(int));
    free(bogus);
    printf("Bogus: %d\n", *bogus);
    return 0;
}
