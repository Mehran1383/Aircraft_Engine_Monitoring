#ifndef SENSORERRORTABLE_H
#define SENSORERRORTABLE_H

#include <QWidget>

namespace Ui {
class SensorErrorTable;
}

class SensorErrorTable : public QWidget
{
    Q_OBJECT

public:
    explicit SensorErrorTable(QWidget *parent = nullptr);
    ~SensorErrorTable();

private:
    Ui::SensorErrorTable *ui;
};

#endif // SENSORERRORTABLE_H
