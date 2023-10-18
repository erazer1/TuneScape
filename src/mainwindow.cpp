#include "include/mainwindow.h"
#include "../ui_mainwindow.h"

#include <QIcon>
#include <QDebug>
#include <QMessageBox>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    infoDialogApp();

    //******************************************************************
    ui->setupUi(this);
    ui->previous->hide();
    ui->next->hide();
    set_icon_btn();
    start();
    connect(ui->infoApp, &QPushButton::clicked, this, &MainWindow::info);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (radioExplorer) {
        delete radioExplorer;
        qDebug() << "radioExplorer";
    }
}

void MainWindow::set_icon_btn()
{
    ui->stop->setIcon(QIcon(":/images/img/stop30.png"));
    ui->previous->setIcon(QIcon(":/images/img/prev30.png"));
    ui->playPause->setIcon(QIcon(":/images/img/play30.png"));
    ui->next->setIcon(QIcon(":/images/img/next30.png"));
    ui->volume->setIcon(QIcon(":/images/img/audioplay.png"));
    ui->favorite->setIcon(QIcon(":/images/img/bookmark-empty.png"));
}

void MainWindow::start()
{
    radioExplorer = new RadioExplorer(ui);
    radioList     = new RadioList(ui);
    radioExplorer->createMenu();
    radioList->loadAllData();

    // version beta
    ui->tabWidget->removeTab(1);
    ui->tabRadioListWidget->removeTab(1);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    if (height() < 140 && ui->splitter->isVisible()) {
        ui->splitter->hide();
        ui->serachInput->hide();

    } else if (height() >= 140 && !ui->splitter->isVisible()) {
        ui->splitter->show();
        ui->serachInput->show();
    }
    qDebug() << ui->centralwidget->geometry().height();
}

void MainWindow::info()
{
    QFile file(":/src/files/license.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString licenseText = in.readAll();
        licenseLabel->setText(licenseText);
        file.close();
    }

    licenseDialog->show();
}

void MainWindow::infoDialogApp()
{
    licenseDialog = new QDialog(this);
    licenseDialog->setWindowTitle("About");

    scrollArea = new QScrollArea(licenseDialog);
    scrollArea->setWidgetResizable(true);

    QWidget *scrollAreaWidget = new QWidget;
    scrollArea->setWidget(scrollAreaWidget);

    licenseLabel = new QLabel;
    licenseLabel->setWordWrap(true);

    aboutAudioLink = new QLabel;
    aboutAudioLink->setText("<p style=\"font-size: 18pt; line-height: 1.5;\">AudioLink 0.0.1</p>"
                            "This is a free and Open Source online radio player based on "
                            "<a href=\"https://www.radio-browser.info\">radio-browser service.</a> "
                            "This is the beta version. If you want help to develop this app, look at "
                            "<a href=\"https://github.com/grzesiekkedzior/AudioLink\"><u>AudioLink</u></a>");
    aboutAudioLink->setOpenExternalLinks(true);
    aboutAudioLink->setWordWrap(true);

    QVBoxLayout *scrollAreaLayout = new QVBoxLayout(scrollAreaWidget);
    scrollAreaLayout->addWidget(aboutAudioLink);
    scrollAreaLayout->addWidget(licenseLabel);

    QVBoxLayout *dialogLayout = new QVBoxLayout(licenseDialog);
    dialogLayout->addWidget(scrollArea);
}
