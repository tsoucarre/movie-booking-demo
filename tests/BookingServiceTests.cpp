#include "BookingServiceTests.h"

void BookingServiceTests::shouldRetrieveMoviesList()
{
	// Given a BookingService with multiple screenings
    BookingService service;

    service.addMovieScreening("Matrix", "Paris");
    service.addMovieScreening("Matrix", "Lyon");
    service.addMovieScreening("Inception", "Paris");

	// When retrieving the movies list
    auto moviesList = service.movies();

	// Then the list contains unique movie titles
    QStringList expected = { "Inception", "Matrix" };
    QCOMPARE(moviesList, expected);
}

void BookingServiceTests::shouldRetrieveTheaterList()
{
    // Given a BookingService with multiple screenings
    BookingService service;
    service.addMovieScreening("Matrix", "Paris");
    service.addMovieScreening("Matrix", "Lyon");
    service.addMovieScreening("Inception", "London");
    // When retrieving the theaters for "Matrix"
    auto theatersForMatrix = service.theatersForMovie("Matrix");
    // Then the list contains the correct theaters
    QStringList expectedMatrix = { "Lyon", "Paris" };
    QCOMPARE(theatersForMatrix, expectedMatrix);
}

void BookingServiceTests::shouldGetTheaterInstance()
{
    // Given a BookingService with a screening
    BookingService service;
    service.addMovieScreening("Inception", "Berlin");
    // When retrieving the Theater instance
    auto theater = service.getTheater("Inception", "Berlin");
    // Then the Theater instance is valid
    QVERIFY(theater != nullptr);
}

void BookingServiceTests::shouldReturnNullIfScreeningDoesNotExist()
{
    // Given a BookingService
    BookingService service;
    service.addMovieScreening("Inception", "Berlin");
    // When retrieving a Theater for a non-existent screening
    // Then the result is nullptr
    QCOMPARE(service.getTheater("Star Wars", "Berlin"), nullptr);
    QCOMPARE(service.getTheater("Inception", "Munich"), nullptr);
}

void BookingServiceTests::shouldNotOverwriteTheater()
{
    // Given a BookingService with an existing screening
    BookingService service;
    service.addMovieScreening("Inception", "Berlin");
    auto originalTheater = service.getTheater("Inception", "Berlin");
    // When adding the same screening again
    service.addMovieScreening("Inception", "Berlin");
    auto retrievedTheater = service.getTheater("Inception", "Berlin");
    // Then the Theater instance remains the same (not overwritten)
    QCOMPARE(originalTheater, retrievedTheater);
}
