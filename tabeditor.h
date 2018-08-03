#ifndef TABEDITOR_H
#define TABEDITOR_H

#include <QWidget>
#include "tab.pb.h"

using namespace tably;

class TabEditor : public QWidget
{
    Q_OBJECT
public:
    explicit TabEditor(QWidget *parent = nullptr);
    void setTab(Tab *tab);
    ~TabEditor();

protected:
    void paintEvent(QPaintEvent *);

signals:

public slots:

private:
    Tab *tab;

    void drawMeasures(QPainter &p);
    void drawStaff(QPainter &p, int index);
    void drawChord(QPainter &p, const Chord& chord, int x, int line);
    void drawNote(QPainter &p, const Note& note, int x, int line);

    int staffHeight();
};

#endif // TABEDITOR_H
