#include "TheaterTests.h"
#include "BookingServiceTests.h"

int main(int argc, char** argv)
{
    int status = 0;
    status |= QTest::qExec(new TheaterTests, argc, argv);
    status |= QTest::qExec(new BookingServiceTests, argc, argv);

    return status;
}
