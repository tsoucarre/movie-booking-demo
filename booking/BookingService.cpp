#include "BookingService.h"

void BookingService::addMovieScreening(const QString& movie, const QString& city)
{
    // If the movie does not exist yet, create a new entry
    if (!m_movieTheaters.contains(movie))
        m_movieTheaters.insert(movie, QMap<QString, QSharedPointer<Theater>>());

    // Get the theaters map for the movie
    auto& theaters = m_movieTheaters[movie];

    // If the theater exists already, do nothing
    if (!theaters.contains(city))
        theaters.insert(city, QSharedPointer<Theater>(new Theater()));
}

QStringList BookingService::movies() const
{
    return m_movieTheaters.keys();
}

QStringList BookingService::theatersForMovie(const QString& movie) const
{
    // Check if the movie exists
    auto itMovie = m_movieTheaters.constFind(movie);
    if (itMovie == m_movieTheaters.constEnd())
        return {};

    const auto& theaters = itMovie.value();
    return theaters.keys();
}

QSharedPointer<Theater> BookingService::getTheater(const QString& movie, const QString& city) const
{
    // If the movie does not exist, return nullptr
    auto itMovie = m_movieTheaters.constFind(movie);
    if (itMovie == m_movieTheaters.constEnd())
        return nullptr;

    // If the theater does not exist, return nullptr
    const auto& theaters = itMovie.value();
    auto itTheater = theaters.constFind(city);
    if (itTheater == theaters.constEnd())
        return nullptr;

    return itTheater.value();
}

