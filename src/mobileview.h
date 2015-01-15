#ifndef MOBILEVIEW_H
#define MOBILEVIEW_H

#include <QGraphicsView>

/*
 * Sole purpose of this class is to hide the cursor in
 * the QGraphicsView which would look odd in a mobile interface.
 * Maemo: Draws a hand cursor by default.
 */

class MobileView : public QGraphicsView
{
public:
    MobileView(QWidget* parent);
    ~MobileView();

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void enterEvent(QEvent* event);
};

#endif // MOBILEVIEW_H
