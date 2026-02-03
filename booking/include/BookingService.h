#pragma once

#include "Theater.h"

#include <QMap>
#include <QSharedPointer>

/**
 * @brief Service for managing movie screenings and seat bookings.
 *
 * BookingService keeps track of theaters showing each movie.
 * Movies are identified by their title (QString).
 * Theaters are identified by the city they are located in (QString).
 */
class BookingService
{
public:
    /**
     * @brief Adds a new screening of a movie in a given city.
     *
     * This will create a new Theater instance owned by BookingService.
     * If a screening for the same movie in the same city already exists,
     * no action is taken, no overwrite occurs.
     *
     * @param movie Title of the movie.
     * @param city The city where the screening takes place.
     */
    void addMovieScreening(const QString& movie, const QString& city);

    /**
     * @brief Retrieves a list of all movies with screenings.
     *
     * @return A list of movie titles.
     */
    QStringList movies() const;

    /**
     * @brief Retrieves a list of theaters showing a given movie.
     *
     * @param movie Title of the movie.
     * @return A list of theater names.
     */
    QStringList theatersForMovie(const QString& movie) const;

    /**
     * @brief Retrieves the Theater instance for a given movie in a specified city.
     *
     * @param movie Title of the movie.
     * @param city The city where the screening takes place.
     * @return A shared pointer to the Theater instance, or nullptr if not found.
     */
    QSharedPointer<Theater> getTheater(const QString& movie, const QString& city) const;

private:
    /// @brief Mapping from movie titles to their associated theaters.
    QMap<QString, QMap<QString, QSharedPointer<Theater>>> m_movieTheaters;
};
