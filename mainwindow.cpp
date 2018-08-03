#include <fstream>

#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "tab.pb.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::openTabDialog() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Tab"), "", tr("Tab Files (*.tab)"));
    if (filename != NULL) {
        loadTab(filename.toStdString());
    }
}

void MainWindow::loadTab(string filename) {
    fstream input(filename, ios::in | ios::binary);
    Tab *tab = new Tab();
    tab->ParseFromIstream(&input);
    ui->tabEditor->setTab(tab);
}

MainWindow::~MainWindow()
{
    delete ui;
}
