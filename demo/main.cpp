#include "BookingService.h"
#include "MovieBookingWidget.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    BookingService service;
    // Add sample data for testing
    service.addMovieScreening("The Lord of the Rings", "Abu Dhabi");
    service.addMovieScreening("The Lord of the Rings", "Paris");
    service.addMovieScreening("The Lord of the Rings", "New York");
    service.addMovieScreening("Star Wars", "London");
    service.addMovieScreening("Star Wars", "Rome");
    service.addMovieScreening("Back to the Future", "Abu Dhabi");
    service.addMovieScreening("Back to the Future", "London");
    service.addMovieScreening("Matrix", "New York");
    service.addMovieScreening("Matrix", "Rome");
    service.addMovieScreening("Matrix", "Madrid");

    MovieBookingWidget widget(&service);
    widget.show();

    return app.exec();
}
