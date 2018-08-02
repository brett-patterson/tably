#include <QPainter>
#include <QDebug>
#include <QDir>

#include <iostream>
#include <fstream>

#include "tabeditor.h"

#define PADDING 10
#define N_STRINGS 6
#define STRING_SPACING 10
#define LINE_SPACING 20
#define STAFF_HEIGHT ((N_STRINGS - 1) * STRING_SPACING)
#define NOTE_SPACING 15
#define FONT_SIZE 10


using namespace std;
using namespace tably;


TabEditor::TabEditor(QWidget *parent) : QWidget(parent)
{
    fstream input("/Users/brett/code/tably/test.tab", ios::in | ios::binary);
    this->tab = new Tab();
    this->tab->ParseFromIstream(&input);

//    fstream f("test.tab", std::ios::out | std::ios::trunc | std::ios::binary);
//    tab->SerializeToOstream(&f);
}

void TabEditor::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QSize s = size();
    QBrush whiteBrush = QBrush(QColor(Qt::white));

    p.fillRect(0, 0, s.width(), s.height(), whiteBrush);

    p.setPen(QColor(Qt::black));

    QFont font = p.font();
    font.setPixelSize(FONT_SIZE);
    p.setFont(font);

    int line = 0;
    int x = PADDING;
    int measureOnLine = 0;
    int chordsOnLine = 0;

    drawStaff(&p, line);

    int cellsPerLine = (s.width() - 2 * PADDING) / (NOTE_SPACING);

    qDebug() << "Cells per line:" << cellsPerLine << "(w:" << s.width() << "p:" << PADDING << "f:" << FONT_SIZE << "n:" << NOTE_SPACING << ")";

    for (int i = 0; i < tab->measures_size(); i++) {
        const Measure& measure = tab->measures(i);
        for (int j = 0; j < measure.chords_size(); j++) {
            const Chord& chord = measure.chords(j);
            for (int k = 0; k < N_STRINGS; k++) {
                const Note& note = chord.notes(N_STRINGS - k - 1);
                if (note.value() >= 0) {
                    int y = PADDING + line * (STAFF_HEIGHT + LINE_SPACING) + k * STRING_SPACING;
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

            x += NOTE_SPACING;

            if (++chordsOnLine + measureOnLine == cellsPerLine) {
                drawStaff(&p, ++line);
                measureOnLine = 0;
                chordsOnLine = 0;
                x = PADDING;
            }
        }

        p.drawLine(x, PADDING + line * (STAFF_HEIGHT + LINE_SPACING), x, PADDING + line * (STAFF_HEIGHT + LINE_SPACING) + STAFF_HEIGHT);
        measureOnLine++;
        x += NOTE_SPACING;
    }

}

void TabEditor::drawStaff(QPainter *p, int index) {
    QSize s = size();

    for (int j = 0; j < N_STRINGS; j++) {
        int y = PADDING + index * (STAFF_HEIGHT + LINE_SPACING) + j * STRING_SPACING;
        p->drawLine(PADDING, y, s.width() - PADDING, y);
    }
}

TabEditor::~TabEditor()
{
    delete tab;
}
