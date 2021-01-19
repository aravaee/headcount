/**
 * @file MainWindow.cpp
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief creates the main window and allow user to select a video
 * @version 0.1
 * @date 2020-12-02
 *
 * @copyright Copyright (c) 2020
 *
 */
#include <QAction>
#include <QFileDialog>
#include <QBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include <Qt>
#include <QPushButton>
#include <QFileInfo>
#include <QDebug>
#include <QSettings>

#include "MainWindow.h"
#include "MaxCapacitySelector.h"
#include "VideoDisplay.h"
#include "DBConnection.h"
#include "AnalyticWindow.h"
#include "SettingsWindow.h"

#include <QSqlTableModel>
/**
 * @brief Construct a new Main Window:: Main Window object
 * @param capture
 * @param objectDetector
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    videoSource = new VideoSource(this);
    objectTracker = new ObjectTracker(this);


    /*Buttons to draw flags and create the object tracker so we can track the people in the video frame*/
    QSettings settings;
    const auto drawFlags = settings.value("tracker/drawFlags").value<ObjectTracker::DrawFlags>();
    const auto enterDirection = settings.value("tracker/enterDirection").toUInt();
    objectTracker->setDrawFlags(drawFlags);
    objectTracker->setEnterDirection(static_cast<ObjectTracker::EnterDirection>(enterDirection));

    // connects us to the video source being capatured
    connect(videoSource, &VideoSource::frameCaptured, objectTracker, &ObjectTracker::processFrame);

    // Connects to a store object so we can store the data
    store = new Store(this);
    connect(objectTracker, &ObjectTracker::personEntered, store, &Store::personEntered);
    connect(objectTracker, &ObjectTracker::personExited, store, &Store::personExited);


    // connects the video display to display the video
    auto video = new VideoDisplay(this);
    connect(objectTracker, &ObjectTracker::frameProcessed, video, &VideoDisplay::updateImage);


    video->setMinimumSize(320, 200); // sets the minmum size of the GUI
    QPalette pal = palette();
    /* Sets the background colour of the GUI to black*/
    pal.setColor(QPalette::Background, Qt::black);
    video->setAutoFillBackground(true);
    video->setPalette(pal);

    MaxCapacitySelector *capacitySelector = new MaxCapacitySelector(this);

    // Open files with a button
    QPushButton *openButton = new QPushButton("Open", this);
    connect(openButton, &QPushButton::clicked, this, &MainWindow::openFile);

    // Opens a quit button
    QPushButton *quitButton = new QPushButton("Quit", this);
    connect(quitButton, &QPushButton::clicked, qApp, &QApplication::quit);

    // Opens a add contact button
    QPushButton *addContactButton = new QPushButton("Add Contact", this);
    connect(addContactButton, &QPushButton::clicked, this, &MainWindow::openAddNewContact);

    // Opens a contacts button
    QPushButton *contactsButton = new QPushButton("Contacts", this);
    connect(contactsButton, &QPushButton::clicked, this, &MainWindow::openContacts);

    // opens a composeButton
    QPushButton *composeButton = new QPushButton("Compose", this);
    connect(composeButton, &QPushButton::clicked, this, &MainWindow::openCompose);

    // Opens a analytic button
    QPushButton *analyticButton = new QPushButton("Analytics", this);
    connect(analyticButton, &QPushButton::clicked, this, &MainWindow::openAnalyticWindow);

    //opens a settings button
    QPushButton *settingsButton = new QPushButton("Settings", this);
    connect(settingsButton, &QPushButton::clicked, this, &MainWindow::openSettingsWindow);

    //opens a play button
    QPushButton *playButton = new QPushButton("Play", this);
    connect(playButton, &QPushButton::clicked, videoSource, &VideoSource::play);

    //opens a pause button
    QPushButton *pauseButton = new QPushButton("Pause", this);
    connect(pauseButton, &QPushButton::clicked, videoSource, &VideoSource::stop);

    /*SETS THE LAYOUT AND BUTTONS OF THE GUI*/
    QVBoxLayout *layoutSide = new QVBoxLayout;
    layoutSide->addWidget(capacitySelector);
    layoutSide->addWidget(addContactButton);
    layoutSide->addWidget(contactsButton);
    layoutSide->addWidget(composeButton);
    layoutSide->addWidget(analyticButton);
    layoutSide->addWidget(settingsButton);
    layoutSide->addStretch(1);

    /*The file label name of the video if no video is active*/
    fileNameLabel = new QLabel(this);
    fileNameLabel->setText("No video active.");
    fileNameLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // sets the current capacity of the label 0 and aligns to the left side of the GUI
    currentCapacityLabel = new QLabel(this);
    currentCapacityLabel->setText("Current Capacity: 0");
    currentCapacityLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    connect(store, &Store::capacityChanged, this, &MainWindow::updateCapacityLabel);

    /* Sets a box layout*/
    QVBoxLayout *layoutVideoV = new QVBoxLayout;
    layoutVideoV->addWidget(video, 2);
    layoutVideoV->addWidget(fileNameLabel);
    layoutVideoV->addWidget(currentCapacityLabel);

    /* Sets the box layout*/
    QHBoxLayout *layoutVideoH = new QHBoxLayout;
    layoutVideoH->addLayout(layoutVideoV, 2);
    layoutVideoH->addLayout(layoutSide);

    // Set layout (horizontal)
    QHBoxLayout *layoutH = new QHBoxLayout;
    layoutH->addWidget(openButton, 1);
    layoutH->addWidget(pauseButton);
    layoutH->addWidget(playButton);
    layoutH->addStretch(2);
    layoutH->addWidget(quitButton, 2);

    // Set layout (vertical)
    QVBoxLayout *layoutV = new QVBoxLayout;
    layoutV->addLayout(layoutVideoH);
    layoutV->addLayout(layoutH);

    // Set layout in QWidget
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layoutV);

    // Set QWidget as the central layout of the main window
    setCentralWidget(centralWidget);

    // Add file menu to menu bar
    QMenu *fileMenu = menuBar()->addMenu("&File");
    menuBar()->setNativeMenuBar(false); // For macOS users, would not use the native menu bar

    // Add open action
    const auto openIcon = QIcon(":/resources/open.png");

    QAction *openAction = new QAction(openIcon, "&Open", this);
    fileMenu->addAction(openAction);
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);

    // Adds a camera action
    QAction *cameraAction = new QAction("Open Camera", this);
    fileMenu->addAction(cameraAction);
    connect(cameraAction, &QAction::triggered, this, &MainWindow::openCamera);

    // Add settings window action
    QAction *settingsAction = new QAction("Settings", this);
    fileMenu->addAction(settingsAction);
    connect(settingsAction, &QAction::triggered, this, &MainWindow::openSettingsWindow);

    // Add quit action
    QAction *quitAction = new QAction("&Quit", this);
    fileMenu->addAction(quitAction);
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
}

/**
 * @brief destrcutor for the MainWIndowclass
 *
 */
MainWindow::~MainWindow() {

}

/**
 * @brief opens a video through the selected path
 *
 */
void MainWindow::openFile()
{
    // opening the file path selected
    QString filepath = QFileDialog::getOpenFileName(this, "Open Video File", QDir::currentPath(), "Video Files (*.mp4 *.avi)");

    /*Checks if the file path has been selected and notifies the user*/
    if (!filepath.isNull())
    {
        if (videoSource->openFile(filepath)) {
            fileNameLabel->setText(QString("File Path: %1").arg(filepath));
        } else {
            fileNameLabel->setText("No video active.");
        }
    }
}


/**
 * @brief opens the camera to display the video
 *
 */
void MainWindow::openCamera() {
    // Use default system default camera
    if (videoSource->openCamera(0)) {
        fileNameLabel->setText("Capturing from default system camera.");
    } else {
        fileNameLabel->setText("No video active.");
    }
}

/**
 * @brief open a new window for the user to enter their contact info
 *
 */
void MainWindow::openAddNewContact()
{
    qDebug() << "openAddNewContact";
    contactWindow = new ContactWindow(this);
    contactWindow->show();
}
/**
 * @brief displays the contacts that exist in the database
 *
 */
void MainWindow::openContacts()
{
    /*Connects the database and then prints a contactlist and adds the data*/
    DBConnection DB("ContactList.db");
    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable("Contact");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("FirstName"));
    model->setHeaderData(2, Qt::Horizontal, tr("LastName"));
    model->setHeaderData(3, Qt::Horizontal, tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, tr("PhoneNumber"));
    model->setHeaderData(5, Qt::Horizontal, tr("Role"));
    model->setHeaderData(6, Qt::Horizontal, tr("PreferEmail"));
    model->setHeaderData(7, Qt::Horizontal, tr("PreferPhoneNumber"));

    /*Also us to show the database in a table view to see what contacts have been added*/
    QTableView *view = new QTableView;
    view->setMinimumSize(650, 100);
    view->resize(700, 200);
    view->setModel(model);
    view->resizeColumnsToContents();
    view->setWindowTitle("Contacts");
    view->show();
}

/**
 * @brief opens a composed window
 *
 */
void MainWindow::openCompose()
{
    qDebug() << "openCompose";
    composeWindow = new ComposeWindow(this);
    composeWindow->show();
}


/**
 * @brief opens a Analytic Window
 *
 */
void MainWindow::openAnalyticWindow()
{
    qDebug() << "openAnalyticWindow";
    analyticWindow = new AnalyticWindow(store, this);
    analyticWindow->show();
}

/**
 * @brief opens a settings Window
 *
 */
void MainWindow::openSettingsWindow() {
    SettingsWindow *settingsWindow = new SettingsWindow(objectTracker, this);
    settingsWindow->setWindowFlag(Qt::Window, true);
    settingsWindow->show();
}

/**
 * @brief Updates the capactiy everytime it has been changed
 *
 */
void MainWindow::updateCapacityLabel(unsigned int capacity) {
    currentCapacityLabel->setText(QString("Current Capacity: %1").arg(capacity));
}
