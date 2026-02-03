#include "Theater.h"

#include <QMutexLocker>
#include <stdexcept>
#include <string>

Theater::Theater()
{
    m_seatStates.reserve(numRows * numColumns);

    for (size_t row = 0; row < numRows; ++row)
    {
        for (size_t col = 0; col < numColumns; ++col)
        {
            QString id = seatId(row, col);
            m_seatStates.insert(id, SeatState::Available);
        }
    }
}

QString Theater::seatId(size_t row, size_t column)
{
    return QString("%1%2").arg(QChar('A' + static_cast<int>(row))).arg(column + 1);
}

Theater::BookingStatus Theater::bookSeats(const QStringList& ids)
{
    // Lock the mutex to ensure thread safety
    QMutexLocker locker(&m_mutex);

    for (auto id : ids)
    {
        if (!m_seatStates.contains(id))
            return BookingStatus::InvalidSeat;

        if (m_seatStates[id] == SeatState::Booked)
            return BookingStatus::SeatAlreadyBooked;
    }

    for (auto id : ids)
        m_seatStates[id] = SeatState::Booked;

    return BookingStatus::Success;
}

bool Theater::isSeatBooked(QString id) const
{
    // Return false if the seat ID is invalid
    if (!m_seatStates.contains(id))
        return false;

    return m_seatStates[id] == SeatState::Booked;
}
