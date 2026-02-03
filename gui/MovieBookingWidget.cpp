#include "BookingService.h" 
#include "MovieBookingWidget.h" 
#include "SeatsModel.h" 
#include "ui_MovieBookingWidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>
#include <QLabel>


MovieBookingWidget::MovieBookingWidget(BookingService* service, QWidget* parent)
    : QMainWindow(parent)
    , m_service(service)
    , m_ui(new Ui::MovieBookingWidget)
{
    m_ui->setupUi(this);

    connect(m_ui->movieCombo, &QComboBox::currentTextChanged, this, &MovieBookingWidget::updateTheaters);
    connect(m_ui->theaterCombo, &QComboBox::currentTextChanged, this, &MovieBookingWidget::updateItemModel);
    connect(m_ui->bookButton, &QPushButton::clicked, this, &MovieBookingWidget::onBookClicked);

    loadMovies();
}

MovieBookingWidget::~MovieBookingWidget()
{
    delete m_ui;
}

void MovieBookingWidget::loadMovies()
{
    QStringList movies = m_service->movies();
    m_ui->movieCombo->clear();
    m_ui->movieCombo->addItems(movies);
}

void MovieBookingWidget::updateTheaters(QString selectedMovie)
{
    QStringList theaters = m_service->theatersForMovie(selectedMovie);
    m_ui->theaterCombo->clear();
    m_ui->theaterCombo->addItems(theaters);
}

void MovieBookingWidget::updateItemModel()
{
    auto theater = m_service->getTheater(m_ui->movieCombo->currentText(), m_ui->theaterCombo->currentText());

    if (theater)
    {
        SeatsModel* model = new SeatsModel(theater, this);
        m_ui->tableView->setModel(model);
    }
    else
    {
        m_ui->tableView->setModel(nullptr);
    }
}

void MovieBookingWidget::onBookClicked()
{
    auto* selectionModel = m_ui->tableView->selectionModel();

    auto selectedItems = selectionModel->selectedIndexes();

    QStringList seatsToBook;

    for (const QModelIndex& index : selectedItems)
        seatsToBook << Theater::seatId(index.row(), index.column());

    if (seatsToBook.isEmpty())
    {
        QMessageBox::warning(this, "No Seats Selected", "Please select at least one seat to book.");
        return;
    }

    Theater::BookingStatus status = m_service->getTheater(m_ui->movieCombo->currentText(), m_ui->theaterCombo->currentText())->bookSeats(seatsToBook);

    if (status == Theater::BookingStatus::Success)
    {
        QMessageBox::information(this, "Success", "Seats booked successfully!");
        m_ui->tableView->update();
    }
    else
    {
        QString msg;
        switch (status)
        {
        case Theater::BookingStatus::InvalidSeat:
            msg = "Invalid seat";
            break;
        case Theater::BookingStatus::SeatAlreadyBooked:
            msg = "Seat already booked";
            break;
        default:
            msg = "Unknown error";
            break;
        }

        QMessageBox::critical(this, "Error", msg);
    }
}
