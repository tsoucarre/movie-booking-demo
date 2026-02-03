#include "SeatsModel.h"
#include "Theater.h"

#include <QColor>

SeatsModel::SeatsModel(QSharedPointer<Theater> theater, QObject* parent)
    : QAbstractTableModel(parent)
    , m_theater(theater)
{
}

int SeatsModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;

    return static_cast<int>(Theater::numRows);
}

int SeatsModel::columnCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;

    return static_cast<int>(Theater::numColumns);
}

QVariant SeatsModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    QString id = Theater::seatId(index.row(), index.column());

    switch (role)
    {
    case Qt::DisplayRole:
    case Qt::ToolTipRole:
        return id;
    case Qt::BackgroundRole:
        return m_theater->isSeatBooked(id) ? QColor("red") : QColor("green");
    default:
        return QVariant();
    }
}

Qt::ItemFlags SeatsModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    QString id = Theater::seatId(index.row(), index.column());

    Qt::ItemFlags flags = Qt::ItemNeverHasChildren;

    if (!m_theater->isSeatBooked(id))
        flags |= Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    return flags;
}

