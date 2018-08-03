#include <QApplication>

#include "mainwindow.h"

// TODO: Remove me
#include <fstream>
#include "tab.pb.h"

void writeSampleTab() {
    Tab tab;
    std::string *s;
    Measure *m;
    Chord *c;
    Note *n;

    s = tab.add_strings();
    *s = "E";
    s = tab.add_strings();
    *s = "A";
    s = tab.add_strings();
    *s = "D";
    s = tab.add_strings();
    *s = "G";
    s = tab.add_strings();
    *s = "B";
    s = tab.add_strings();
    *s = "e";

    m = tab.add_measures();

    c = m->add_chords();
    n = c->add_notes();
    n->set_string(0);
    n->set_value(3);
    n = c->add_notes();
    n->set_string(1);
    n->set_value(2);
    n = c->add_notes();
    n->set_string(2);
    n->set_value(0);
    n = c->add_notes();
    n->set_string(3);
    n->set_value(0);
    n = c->add_notes();
    n->set_value(3);
    n->set_string(4);
    n = c->add_notes();
    n->set_value(3);
    n->set_string(5);

    c = m->add_chords();
    n = c->add_notes();
    n->set_value(3);
    n->set_string(5);

    c = m->add_chords();
    n = c->add_notes();
    n->set_value(3);
    n->set_string(4);

    c = m->add_chords();
    n = c->add_notes();
    n->set_value(0);
    n->set_string(3);

    c = m->add_chords();
    n = c->add_notes();
    n->set_value(3);
    n->set_string(4);

    m = tab.add_measures();

    c = m->add_chords();
    n = c->add_notes();
    n->set_value(0);
    n->set_string(2);

    c = m->add_chords();
    n = c->add_notes();
    n->set_value(2);
    n->set_string(3);

    c = m->add_chords();
    n = c->add_notes();
    n->set_value(3);
    n->set_string(4);

    c = m->add_chords();
    n = c->add_notes();
    n->set_value(2);
    n->set_string(5);

    c = m->add_chords();
    n = c->add_notes();
    n->set_value(0);
    n->set_string(5);

    c = m->add_chords();
    n = c->add_notes();
    n->set_value(3);
    n->set_string(4);

    c = m->add_chords();
    n = c->add_notes();
    n->set_value(2);
    n->set_string(3);

    c = m->add_chords();
    n = c->add_notes();
    n->set_value(3);
    n->set_string(4);

    m = tab.add_measures();

    c = m->add_chords();
    n = c->add_notes();
    n->set_value(0);
    n->set_string(2);
    n = c->add_notes();
    n->set_value(0);
    n->set_string(3);

    c = m->add_chords();
    n = c->add_notes();
    n->set_string(2);
    n->set_value(2);
    n->set_modifier(NoteModifier::HammerOn);

    std::fstream f("test.tab", std::ios::out | std::ios::trunc | std::ios::binary);
    tab.SerializeToOstream(&f);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    return app.exec();
}
