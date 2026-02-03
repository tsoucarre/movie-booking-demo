#pragma once

#include <QAbstractTableModel>
#include <QSharedPointer>

class Theater;

/**
 * @brief Model representing the seating arrangement in a theater.
 *
 * Each cell in the model corresponds to a seat in the theater,
 * represented by its row and column.
 * Cell background color indicates seat availability:
 * Green for available seats, Red for booked seats.
 */
class SeatsModel : public QAbstractTableModel {
    Q_OBJECT

public:
    /**
     * @brief Constructs a SeatsModel for the given theater.
     * @param theater Shared pointer to the Theater instance.
     * @param parent Optional parent QObject.
     */
    explicit SeatsModel(QSharedPointer<Theater> theater, QObject* parent = nullptr);

    // Overridden methods from QAbstractTableModel
    /**
     * @brief Returns the number of rows in the table.
     * @param parent The parent index.
     * @return Number of rows (seating rows) in the theater.
     */
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    /**
     * @brief Returns the number of columns in the table.
     * @param parent The parent index.
     * @return Number of columns (seating columns) in the theater.
     */
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    /**
     * @brief Returns the data for a given index and role.
     * @param index The model index identifying the cell.
     * @param role The data role.
     * @return QVariant representing the requested data.
     *
     * - Qt::DisplayRole: Seat id (A1, A2, ..., D4, D5).
     * - Qt::BackgroundRole: Indicates seat availability (green for available, red for booked).
     *
     * Returns an invalid QVariant for indexes out of range or unsupported roles.
     */
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    /**
     * @brief Returns the item flags for a given index.
     * @param index The model index.
     * @return Qt::ItemFlags indicating the properties of the item.
     *
     * Seats that are booked are not enabled or selectable.
     */
    Qt::ItemFlags flags(const QModelIndex& index) const override;


private:
    /// @brief Shared pointer to the Theater instance.
    QSharedPointer<Theater> m_theater;
};
