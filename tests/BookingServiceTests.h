#pragma once

#include "BookingService.h"
#include <QtTest/QtTest>

class BookingServiceTests : public QObject
{
    Q_OBJECT

private slots:
    void shouldRetrieveMoviesList();
    void shouldRetrieveTheaterList();
    void shouldGetTheaterInstance();
    void shouldReturnNullIfScreeningDoesNotExist();
    void shouldNotOverwriteTheater();
};

