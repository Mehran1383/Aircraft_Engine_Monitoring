#include <QStyledItemDelegate>
#include <QPainter>
#include <QStyleOptionViewItem>



class SensorErrorDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit SensorErrorDelegate(QObject *parent = nullptr);

    // Override the paint method to draw the icon
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    QIcon iconSafe;
    QIcon iconDanger;
};
