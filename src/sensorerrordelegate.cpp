#include "sensorerrordelegate.h"


SensorErrorDelegate::SensorErrorDelegate(QObject *parent)
    : QStyledItemDelegate(parent),
      iconSafe(":/img/img/off-icon.jpg"),  // Replace with your icon paths
      iconDanger(":/img/img/on-icon.jpg")  // Replace with your icon paths
{
}

void SensorErrorDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid()) {
        return;
    }

    // Get the value of the sensor to determine which icon to use
    int value = index.model()->data(index.sibling(index.row(), 1), Qt::DisplayRole).toInt();  // Assuming value is in column 1

    QIcon icon = (value == 1) ? iconDanger : iconSafe;

    // Paint the icon in the designated area
    QRect iconRect = option.rect;
    iconRect.setWidth(iconRect.height());  // Make the icon square
    icon.paint(painter, iconRect);

    // If you want to also paint the text, call the base class paint method
    QStyledItemDelegate::paint(painter, option, index);
}
