#pragma once

#include <QMainWindow>

class SeatsModel;
class BookingService;

namespace Ui {
    class MovieBookingWidget;  // Forward declare the generated Ui class
}

/**
 * @brief Main widget for booking movie seats.
 *
 * MovieBookingWidget provides a GUI for users to select movies,
 * theaters, view seat availability, and book seats.
 */
class MovieBookingWidget : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the MovieBookingWidget.
     * @param service Pointer to the BookingService instance.
     * @param parent Optional parent QWidget.
     */
    explicit MovieBookingWidget(BookingService* service, QWidget* parent = nullptr);

    /**
     * @brief Destructor.
     */
    virtual ~MovieBookingWidget();

private:
    /// @brief Pointer to the BookingService instance.
    BookingService* m_service;
    /// @brief Pointer to the generated UI class.
    Ui::MovieBookingWidget* m_ui;
    /// @brief Pointer to the SeatsModel instance.
    SeatsModel* m_seatsModel;

    /// @brief Loads the list of movies into the movie combo box.
    void loadMovies();

private slots:
    /// @brief Updates the theater combo box based on the selected movie.
    void updateTheaters(QString selectedMovie);
    /// @brief Updates the seat model based on the selected movie and theater.
    void updateItemModel();
    /// @brief Handles the booking of selected seats when the book button is clicked.
    void onBookClicked();
};
