#include <QDebug>
#include "mobileview.h"

MobileView::MobileView(QWidget* parent):
    QGraphicsView(parent)
{
}

MobileView::~MobileView()
{
}

void MobileView::mousePressEvent(QMouseEvent* event)
{
    qDebug() << "MobileView: mousePressEvent called";
    QGraphicsView::mousePressEvent(event);
    viewport()->setCursor(Qt::ArrowCursor);
}

void MobileView::mouseReleaseEvent(QMouseEvent* event)
{
    QGraphicsView::mouseReleaseEvent(event);
    viewport()->setCursor(Qt::ArrowCursor);
}

void MobileView::enterEvent(QEvent* event)
{
    QGraphicsView::enterEvent(event);
    viewport()->setCursor(Qt::ArrowCursor);
}
