#pragma once

#include <QMutex>
#include <QString>
#include <QHash>

/**
 * @brief Represents a theater with a fixed number of seats.
 *
 * Seats are identified by row (A-D) and column (1-5), e.g., "A1", "B3".
 */
class Theater
{
public:
    /**
     * @brief Possible states of a seat.
     */
    enum class SeatState
    {
        Available,  ///< Seat is available
        Booked      ///< Seat has already been booked
    };

    /**
     * @brief Status codes for seat booking operations.
     */
    enum class BookingStatus {
        Success,           ///< Booking succeeded
        InvalidSeat,       ///< One or more seat IDs are invalid
        SeatAlreadyBooked, ///< One or more seats are already booked
    };

    /// @brief Number of rows in the theater.
    static constexpr size_t numRows = 4;

    /// @brief Number of columns in the theater.
    static constexpr size_t numColumns = 5;

    /**
     * @brief Generates a SeatId from row and column indices.
     *
     * @param row The row index (0-based).
     * @param column The column index (0-based).
     * @return The corresponding SeatId.
     */
    static QString seatId(size_t row, size_t column);

    /**
     * @brief Constructs a Theater with all seats initially available.
     */
    Theater();

    /**
     * @brief Virtual destructor.
     */
    virtual ~Theater() = default;

    /**
     * @brief Books multiple seats.
     * If all seats can't be booked, no seats are booked.
     *
     * @param ids The seat IDs to book.
     * @return Status indicating success or failure reason.
     */
    BookingStatus bookSeats(const QStringList& ids);

    /**
     * @brief Checks whether a given seat is booked.
     *
     * @param id the seat ID to check.
     * @return true if the seat is booked, false otherwise.
     */
    bool isSeatBooked(QString id) const;

private:
    /// @brief Internal storage for seat states.
    QHash<QString, SeatState> m_seatStates;

    /// @brief Mutex to protect seat booking operations.
    mutable QMutex m_mutex;
};

