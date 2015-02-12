/********************************************************************************
** Form generated from reading UI file 'main_form.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_FORM_H
#define UI_MAIN_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainForm
{
public:
    QAction *actionExit;
    QAction *actionImport;
    QAction *actionNew_database;
    QAction *actionImport_2;
    QAction *actionExit_2;
    QAction *actionNewDatabase;
    QAction *actionImportDatabase;
    QAction *actionQuit;
    QWidget *centralwidget;
    QPlainTextEdit *spechText;
    QGroupBox *mngSpeechBox;
    QPushButton *toogleSRBtn;
    QPushButton *trainBtn;
    QProgressBar *powerBar;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *sampleGLayout;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *debugGLayout;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuTools;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainForm)
    {
        if (MainForm->objectName().isEmpty())
            MainForm->setObjectName(QStringLiteral("MainForm"));
        MainForm->resize(778, 366);
        MainForm->setMinimumSize(QSize(778, 366));
        MainForm->setMaximumSize(QSize(778, 366));
        MainForm->setWindowOpacity(1);
        actionExit = new QAction(MainForm);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionImport = new QAction(MainForm);
        actionImport->setObjectName(QStringLiteral("actionImport"));
        actionNew_database = new QAction(MainForm);
        actionNew_database->setObjectName(QStringLiteral("actionNew_database"));
        actionImport_2 = new QAction(MainForm);
        actionImport_2->setObjectName(QStringLiteral("actionImport_2"));
        actionExit_2 = new QAction(MainForm);
        actionExit_2->setObjectName(QStringLiteral("actionExit_2"));
        actionNewDatabase = new QAction(MainForm);
        actionNewDatabase->setObjectName(QStringLiteral("actionNewDatabase"));
        actionImportDatabase = new QAction(MainForm);
        actionImportDatabase->setObjectName(QStringLiteral("actionImportDatabase"));
        actionQuit = new QAction(MainForm);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        centralwidget = new QWidget(MainForm);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        spechText = new QPlainTextEdit(centralwidget);
        spechText->setObjectName(QStringLiteral("spechText"));
        spechText->setGeometry(QRect(3, 0, 381, 321));
        spechText->setReadOnly(true);
        mngSpeechBox = new QGroupBox(centralwidget);
        mngSpeechBox->setObjectName(QStringLiteral("mngSpeechBox"));
        mngSpeechBox->setGeometry(QRect(390, 0, 381, 321));
        toogleSRBtn = new QPushButton(mngSpeechBox);
        toogleSRBtn->setObjectName(QStringLiteral("toogleSRBtn"));
        toogleSRBtn->setGeometry(QRect(10, 20, 81, 23));
        trainBtn = new QPushButton(mngSpeechBox);
        trainBtn->setObjectName(QStringLiteral("trainBtn"));
        trainBtn->setGeometry(QRect(100, 20, 75, 23));
        powerBar = new QProgressBar(mngSpeechBox);
        powerBar->setObjectName(QStringLiteral("powerBar"));
        powerBar->setGeometry(QRect(10, 50, 361, 16));
        powerBar->setValue(0);
        powerBar->setOrientation(Qt::Horizontal);
        verticalLayoutWidget = new QWidget(mngSpeechBox);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 70, 361, 121));
        sampleGLayout = new QVBoxLayout(verticalLayoutWidget);
        sampleGLayout->setObjectName(QStringLiteral("sampleGLayout"));
        sampleGLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayoutWidget_2 = new QWidget(mngSpeechBox);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(10, 190, 361, 121));
        debugGLayout = new QVBoxLayout(verticalLayoutWidget_2);
        debugGLayout->setObjectName(QStringLiteral("debugGLayout"));
        debugGLayout->setContentsMargins(0, 0, 0, 0);
        MainForm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainForm);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 778, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuTools = new QMenu(menubar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        MainForm->setMenuBar(menubar);
        statusbar = new QStatusBar(MainForm);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainForm->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuTools->menuAction());
        menuFile->addAction(actionQuit);
        menuTools->addAction(actionNewDatabase);

        retranslateUi(MainForm);

        QMetaObject::connectSlotsByName(MainForm);
    } // setupUi

    void retranslateUi(QMainWindow *MainForm)
    {
        MainForm->setWindowTitle(QApplication::translate("MainForm", "SRSystem", 0));
        actionExit->setText(QApplication::translate("MainForm", "Exit", 0));
        actionImport->setText(QApplication::translate("MainForm", "Import...", 0));
        actionNew_database->setText(QApplication::translate("MainForm", "New database", 0));
        actionImport_2->setText(QApplication::translate("MainForm", "Import", 0));
        actionExit_2->setText(QApplication::translate("MainForm", "Exit", 0));
        actionNewDatabase->setText(QApplication::translate("MainForm", "Manage database", 0));
        actionImportDatabase->setText(QApplication::translate("MainForm", "Import database", 0));
        actionQuit->setText(QApplication::translate("MainForm", "Quit", 0));
        mngSpeechBox->setTitle(QApplication::translate("MainForm", "Manage speech", 0));
        toogleSRBtn->setText(QApplication::translate("MainForm", "Start Listening", 0));
        trainBtn->setText(QApplication::translate("MainForm", "Train", 0));
        menuFile->setTitle(QApplication::translate("MainForm", "File", 0));
        menuTools->setTitle(QApplication::translate("MainForm", "Tools", 0));
    } // retranslateUi

};

namespace Ui {
    class MainForm: public Ui_MainForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_FORM_H
