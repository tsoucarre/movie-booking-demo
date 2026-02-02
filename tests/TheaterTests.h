#pragma once

#include "Theater.h"

#include <QtTest/QtTest>


class TheaterTests : public QObject
{
    Q_OBJECT

private slots:
    void constructor_initializesAllSeatsAvailable();
    void bookSingleSeat();
    void bookMultipleSeats();
    void bookingShouldFailIfSeatIsAlreadyBooked();
    void bookingShouldFailOnInvalidSeatId();
    void isSeatBookedShouldHandleInvalidId();
    void bookingMultipleShouldFailAtomicallyIfAnySeatBooked();
    void concurrentBookingsDoNotOverbook();
};

