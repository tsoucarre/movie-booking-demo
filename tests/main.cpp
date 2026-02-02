#include "TheaterTests.h"

int main(int argc, char** argv)
{
    int status = 0;
    status |= QTest::qExec(new TheaterTests, argc, argv);

    return status;
}
