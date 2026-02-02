#include "TheaterTests.h"

#include <QtConcurrent>
#include <QFuture>

void TheaterTests::constructor_initializesAllSeatsAvailable()
{
    // Given a Theater
    Theater theater;

    // Then all seats are available
    for (size_t i = 0; i < Theater::numRows; ++i)
    {
        for (size_t j = 0; j < Theater::numColumns; ++j)
        {
            QVERIFY(!theater.isSeatBooked(Theater::seatId(i, j)));
        }
    }
}

void TheaterTests::bookSingleSeat()
{
    // Given a Theater
    Theater theater;

    // When booking a single seat
    auto status = theater.bookSeats({ "A2" });
    QCOMPARE(status, Theater::BookingStatus::Success);


    // Then the seat is marked as booked
    QVERIFY(theater.isSeatBooked("A2"));
}

void TheaterTests::bookMultipleSeats()
{
    // Given a Theater
    Theater theater;

    // When booking multiple seats
    auto status = theater.bookSeats({ "A2", "B1", "C3" });
    QCOMPARE(status, Theater::BookingStatus::Success);

    // Then the seats are marked as booked
    QVERIFY(theater.isSeatBooked("A2"));
    QVERIFY(theater.isSeatBooked("B1"));
    QVERIFY(theater.isSeatBooked("C3"));
}

void TheaterTests::bookingShouldFailIfSeatIsAlreadyBooked()
{
    // Given a Theater with a booked seat
    Theater theater;
    theater.bookSeats({ "A3" });

    // When booking the same seat again
    auto status = theater.bookSeats({ "A3" });

    // Then the booking fails with SeatAlreadyBooked status
    QVERIFY(status == Theater::BookingStatus::SeatAlreadyBooked);
}

void TheaterTests::bookingShouldFailOnInvalidSeatId()
{
    // Given a Theater
    Theater theater;

    // When booking an invalid seat ID
    auto status = theater.bookSeats({ "Z9" });

    // Then the booking fails with InvalidSeat status
    QVERIFY(status == Theater::BookingStatus::InvalidSeat);
}

void TheaterTests::isSeatBookedShouldHandleInvalidId()
{
    // Given a Theater
    Theater theater;

    // When checking an invalid seat ID
    // Then isSeatBooked returns false
    QVERIFY(!theater.isSeatBooked("K7"));
}

void TheaterTests::bookingMultipleShouldFailAtomicallyIfAnySeatBooked()
{
    // Given a Theater with two booked seats
    Theater theater;
    QCOMPARE(theater.bookSeats({ "A1", "A2" }), Theater::BookingStatus::Success);  // Initial booking

    // When booking multiple seats including an already booked one
    auto status = theater.bookSeats({ "A2", "A3" });  // A2 already booked
    QCOMPARE(status, Theater::BookingStatus::SeatAlreadyBooked);

    // Then none of the seats in the booking request are booked
    QVERIFY(!theater.isSeatBooked("A3"));
}

void TheaterTests::concurrentBookingsDoNotOverbook()
{
    // Given a Theater
    Theater theater;
    const QString seat = "A1";

    // Define the booking function
    auto bookFunc = [&theater, seat]() -> Theater::BookingStatus {
        return theater.bookSeats({ seat });
        };

    // When launching 5 concurrent booking attempts on the same seat
    QVector<QFuture<Theater::BookingStatus>> futures;
    for (int i = 0; i < 5; ++i) {
        futures.push_back(QtConcurrent::run(bookFunc));
    }

    // Then 1 booking should succeed and 4 should fail
    int successCount = 0;
    int failureCount = 0;
    for (auto& future : futures) {
        Theater::BookingStatus status = future.result();
        if (status == Theater::BookingStatus::Success) {
            ++successCount;
        }
        else if (status == Theater::BookingStatus::SeatAlreadyBooked) {
            ++failureCount;
        }
        else {
            QFAIL("Unexpected status returned");
        }
    }

    QCOMPARE(successCount, 1);  // Only one thread books it
    QCOMPARE(failureCount, 4);  // The rest fail as expected

    // And the seat is indeed booked
    QVERIFY(theater.isSeatBooked(seat));
}