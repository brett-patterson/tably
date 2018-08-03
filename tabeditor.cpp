#include <QPainter>

#include "tabeditor.h"

using namespace std;
using namespace tably;

#define PADDING 10
#define STRING_SPACING 10
#define LINE_SPACING 20
#define STAFF_HEIGHT(n) (((n) - 1) * STRING_SPACING)
#define NOTE_SPACING 15
#define FONT_SIZE 10

TabEditor::TabEditor(QWidget *parent) : QWidget(parent)
{
    this->tab = NULL;
}

void TabEditor::setTab(Tab *tab) {
    this->tab = tab;
    repaint();
}

void TabEditor::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QSize s = size();

    p.fillRect(0, 0, s.width(), s.height(), QBrush(QColor(Qt::white)));

    if (this->tab != NULL) {
        drawMeasures(p);
    }
}

void TabEditor::drawMeasures(QPainter &p) {
    QBrush whiteBrush = QBrush(QColor(Qt::white));
    QSize s = size();

    p.setPen(QColor(Qt::black));

    QFont font = p.font();
    font.setPixelSize(FONT_SIZE);
    p.setFont(font);

    int line = 0;
    int left = PADDING + 2 * NOTE_SPACING;
    int x = left;

    int staffHeight = STAFF_HEIGHT(tab->strings_size());

    drawStaff(p, line);

    for (int i = 0; i < tab->measures_size(); i++) {
        const Measure& measure = tab->measures(i);
        for (int j = 0; j < measure.chords_size(); j++) {
            const Chord& chord = measure.chords(j);
            drawChord(p, chord, x, line);

            x += NOTE_SPACING;

            if (x >= s.width() - PADDING - NOTE_SPACING) {
                drawStaff(p, ++line);
                x = left;
            }
        }

        p.drawLine(x, PADDING + line * (staffHeight + LINE_SPACING), x, PADDING + line * (staffHeight + LINE_SPACING) + staffHeight);
        x += NOTE_SPACING;
    }
}

void TabEditor::drawStaff(QPainter &p, int index) {
    QRect textRect;
    QSize s = size();

    int left = PADDING + NOTE_SPACING;

    // Draw horizontal staff lines with names
    for (int j = 0; j < tab->strings_size(); j++) {
        int y = PADDING + index * (staffHeight() + LINE_SPACING) + j * STRING_SPACING;
        textRect = QRect(PADDING, y - FONT_SIZE / 2, FONT_SIZE, FONT_SIZE);
        p.drawText(textRect, Qt::AlignCenter, QString::fromStdString(tab->strings(tab->strings_size() - j - 1)));

        p.drawLine(left, y, s.width() - PADDING, y);
    }

    // Draw vertical beginning and ending lines
    int y1 = PADDING + index * (staffHeight() + LINE_SPACING);
    int y2 = y1 + staffHeight();
    p.drawLine(left, y1, left, y2);
    p.drawLine(s.width() - PADDING, y1, s.width() - PADDING, y2);
}

void TabEditor::drawChord(QPainter &p, const Chord &chord, int x, int line) {
    for (int i = 0; i < chord.notes_size(); i++) {
        const Note& note = chord.notes(i);
        drawNote(p, note, x, line);
    }
}

void TabEditor::drawNote(QPainter &p, const Note &note, int x, int line) {
    QBrush whiteBrush = QBrush(QColor(Qt::white));

    if (note.value() >= 0) {
        int y = PADDING + line * (staffHeight() + LINE_SPACING) + (tab->strings_size() - note.string() - 1) * STRING_SPACING;
        QRect textRect = QRect(x - FONT_SIZE / 2, y - FONT_SIZE / 2, FONT_SIZE, FONT_SIZE);
        p.fillRect(textRect, whiteBrush);
        p.drawText(textRect, Qt::AlignCenter, QString::number(note.value()));

        QRect hRect;
        switch (note.modifier()) {
        case NoteModifier::HammerOn:
            hRect = QRect(x - NOTE_SPACING + FONT_SIZE / 2, y - FONT_SIZE / 2, FONT_SIZE / 2, FONT_SIZE);
            p.fillRect(hRect, whiteBrush);
            p.drawText(hRect, Qt::AlignCenter, QString("h"));
            break;
        case NoteModifier::None:
            break;
        }
    }
}

int TabEditor::staffHeight() {
    return STAFF_HEIGHT(tab->strings_size());
}

TabEditor::~TabEditor()
{
}
