#ifndef FLIGHTFORM_H
#define FLIGHTFORM_H

#include <QWidget>

namespace Ui {
class flightform;
}

class flightform : public QWidget
{
    Q_OBJECT

public:
    explicit flightform(QWidget *parent = nullptr);
    ~flightform();

private slots:
    void on_home_btn_clicked();

private:
    Ui::flightform *ui;

signals:
    void HomeClicked();
};

#endif // FLIGHTFORM_H
