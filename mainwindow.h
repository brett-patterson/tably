#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tabeditor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    /**
     * Opens the file dialog to load a tab.
     */
    void openTabDialog();

private:
    Ui::MainWindow *ui;

    /**
     * Load a tab from a file.
     * @param filename The path to the file to load
     */
    void loadTab(std::string filename);
};

#endif // MAINWINDOW_H
