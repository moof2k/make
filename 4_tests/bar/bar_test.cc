#include <stdio.h>
#include <assert.h>

#include "bar.h"
#include "foo/foo.h"

int main() {
    Bar bar;
    Foo foo;
    assert(bar.GetBar() == 6);
    assert(foo.GetFoo() == 7);
    return 0;
}