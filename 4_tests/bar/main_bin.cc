#include <stdio.h>
#include "main_bin.h"
#include "foo/foo.h"

int main() {
#ifdef DEBUG
    printf("DEBUG: ");
#endif

    Bar bar;
    Foo foo;
    printf("Hello world %d bar=%d foo=%d\n", kVariable, bar.GetBar(), foo.GetFoo());
}
