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

    /**
     * Set the tab displayed in the editor.
     * @param tab The tab to display
     */
    void setTab(Tab *tab);

    ~TabEditor();

protected:
    void paintEvent(QPaintEvent *);

signals:

public slots:

private:
    /**
     * The current tab in the editor.
     */
    Tab *tab;

    /**
     * Draw the staff and measures for the tab.
     * @param p The painter used to draw
     */
    void drawMeasures(QPainter &p);

    /**
     * Draw a staff.
     * @param p The painter used to draw
     * @param index The index of the staff within the tab
     */
    void drawStaff(QPainter &p, int index);

    /**
     * Draw a chord at a given position.
     * @param p The painter used to draw
     * @param chord The chord to draw
     * @param x The x position of the chord
     * @param line The line in the tab for the chord
     */
    void drawChord(QPainter &p, const Chord& chord, int x, int line);

    /**
     * Draw a note at a given position.
     * @param p The painter used to draw
     * @param note The note to draw
     * @param x The x position of the note
     * @param line The line in the tab for the note
     */
    void drawNote(QPainter &p, const Note& note, int x, int line);

    /**
     * Get the height of a staff for the current tab.
     * @return The staff height
     */
    int staffHeight();
};

#endif // TABEDITOR_H
