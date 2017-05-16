
#include "board.h"
#include "board/board.pb.h"
#include "base/foo.h"

int main() {
    Board board;
    Test test;
    Foo foo;
    printf("foo = %d\n", foo.GetFoo());
    return 0;
}