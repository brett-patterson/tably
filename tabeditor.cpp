#include <QPainter>

#include "tabeditor.h"

#define PADDING 10
#define N_STRINGS 6
#define STRING_SPACING 10
#define LINE_SPACING 20
#define STAFF_HEIGHT ((N_STRINGS - 1) * STRING_SPACING)
#define NOTE_SPACING 15
#define FONT_SIZE 10

TabEditor::TabEditor(QWidget *parent) : QWidget(parent)
{
    this->tab = new Tab({
        new Measure({
            new Chord({
                new Note(3),
                new Note(2),
                new Note(0),
                new Note(0),
                new Note(3),
                new Note(3)
            }),
            new Chord({
                Note::empty(),
                Note::empty(),
                Note::empty(),
                Note::empty(),
                Note::empty(),
                new Note(3)
            }),
            new Chord({
                Note::empty(),
                Note::empty(),
                Note::empty(),
                Note::empty(),
                new Note(3),
                Note::empty()
            }),
            new Chord({
                Note::empty(),
                Note::empty(),
                Note::empty(),
                new Note(0),
                Note::empty(),
                Note::empty()
            }),
            new Chord({
                Note::empty(),
                Note::empty(),
                Note::empty(),
                Note::empty(),
                new Note(3),
                Note::empty()
            }),
        }),
        new Measure({
            new Chord({
                Note::empty(),
                Note::empty(),
                new Note(0),
                Note::empty(),
                Note::empty(),
                Note::empty()
            }),
            new Chord({
                Note::empty(),
                Note::empty(),
                Note::empty(),
                new Note(2),
                Note::empty(),
                Note::empty()
            }),
            new Chord({
                Note::empty(),
                Note::empty(),
                Note::empty(),
                Note::empty(),
                new Note(3),
                Note::empty()
            }),
            new Chord({
                Note::empty(),
                Note::empty(),
                Note::empty(),
                Note::empty(),
                Note::empty(),
                new Note(2)
            }),
            new Chord({
                Note::empty(),
                Note::empty(),
                Note::empty(),
                Note::empty(),
                Note::empty(),
                new Note(0)
            }),
            new Chord({
                Note::empty(),
                Note::empty(),
                Note::empty(),
                Note::empty(),
                new Note(3),
                Note::empty()
            }),
            new Chord({
                Note::empty(),
                Note::empty(),
                Note::empty(),
                new Note(2),
                Note::empty(),
                Note::empty()
            }),
            new Chord({
                Note::empty(),
                Note::empty(),
                Note::empty(),
                Note::empty(),
                new Note(3),
                Note::empty()
            })
        }),
        new Measure({
            new Chord({
                Note::empty(),
                Note::empty(),
                new Note(0),
                new Note(0),
                Note::empty(),
                Note::empty()
            }),
            new Chord({
                Note::empty(),
                Note::empty(),
                new Note(2, NoteModifier::HammerOn),
                Note::empty(),
                Note::empty(),
                Note::empty(),
            })
        })
    });
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

    int cellsPerLine = (s.width() - 2 * PADDING) / (FONT_SIZE + NOTE_SPACING);

    for (Measure *measure : tab->measures) {
        for (int i = 0; i < measure->chords.size(); i++) {
            Chord *chord = measure->chords.at(i);
            for (int j = 0; j < N_STRINGS; j++) {
                Note *note = chord->notes.at(N_STRINGS - j - 1);
                if (!note->isEmpty()) {
                    int y = PADDING + line * (STAFF_HEIGHT + LINE_SPACING) + j * STRING_SPACING;
                    QRect textRect = QRect(x - FONT_SIZE / 2, y - FONT_SIZE / 2, FONT_SIZE, FONT_SIZE);
                    p.fillRect(textRect, QBrush(QColor(Qt::white)));
                    p.drawText(textRect, Qt::AlignCenter, QString::number(note->value));

                    QRect hRect;
                    switch (note->modifier) {
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
}
