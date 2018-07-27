#include "tab.h"

Note::Note(int v) :
    value(v),
    modifier(NoteModifier::None)
{
}

Note::Note(int v, NoteModifier m) :
    value(v),
    modifier(m)
{
}

Chord::Chord(QList<Note*> n) :
    notes(n)
{
}

Measure::Measure(QList<Chord*> c) :
    chords(c)
{
}

Tab::Tab(QList<Measure*> m) :
    measures(m)
{

}
