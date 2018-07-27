#ifndef TABEDITOR_H
#define TABEDITOR_H

#include <QWidget>
#include "tab.h"

class TabEditor : public QWidget
{
    Q_OBJECT
public:
    explicit TabEditor(QWidget *parent = nullptr);
    ~TabEditor();

protected:
    void paintEvent(QPaintEvent *);

signals:

public slots:

private:
    Tab *tab;

    void drawStaff(QPainter *p, int index);
};

#endif // TABEDITOR_H
