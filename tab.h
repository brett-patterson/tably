#ifndef TAB_H
#define TAB_H

#include <QList>

#define EMPTY_NOTE_VALUE -1

enum NoteModifier {
    None,
};

class Note
{
public:
    explicit Note(int value);
    explicit Note(int value, NoteModifier modifier);

    static Note* empty() {
        static Note emptyNote(EMPTY_NOTE_VALUE);
        return &emptyNote;
    }

    bool isEmpty() {
        return value == EMPTY_NOTE_VALUE;
    }

    int value;
    NoteModifier modifier;
};

class Chord
{
public:
    explicit Chord(QList<Note*> notes);
    QList<Note*> notes;
};

class Measure
{
public:
    explicit Measure(QList<Chord*> chords);
    QList<Chord*> chords;
};

class Tab
{
public:
    explicit Tab(QList<Measure*> measures);
    QList<Measure*> measures;
};

#endif // TAB_H
