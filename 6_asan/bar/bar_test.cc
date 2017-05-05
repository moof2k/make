#include <stdio.h>
#include <assert.h>

#include "bar.h"
#include "foo/foo.h"
#include "foo/hat/hat.h"

int main() {
    Bar bar;
    Foo foo;
    FooHat foohat;
    assert(bar.GetBar() == 6);
    assert(foo.GetFoo() == 7);
    assert(foohat.GetFooHat() == 5);
    return 0;
}