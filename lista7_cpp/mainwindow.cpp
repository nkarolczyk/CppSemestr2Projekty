#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QIcon>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , isPlaying(false)
{
    ui->setupUi(this);
    connect(ui->action_Koniec, SIGNAL(triggered()), this, SLOT(koniec_programu()));

    updateButtonIcon();

    ui->przycisk->setText("");

    connect(ui->przycisk, &QPushButton::clicked, this, &MainWindow::togglePlayPause);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateButtonIcon()
{
    QIcon icon(isPlaying ? ":/img/media-playback-pause.png" : ":/img/media-playback-start.png");
    if (icon.isNull()) {
        qWarning() << "Icon not found!";
    } else {
        ui->przycisk->setIcon(icon);
    }
}

void MainWindow::togglePlayPause()
{
    isPlaying = !isPlaying;
    updateButtonIcon();
}

void MainWindow::koniec_programu()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Zakończenie programu", "Czy na pewno chcesz zakończyć program?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        qApp->quit();
    }
}

void MainWindow::on_action_O_programie_triggered()
{
    QMessageBox::aboutQt(this, "O wspaniałym programie");
}
