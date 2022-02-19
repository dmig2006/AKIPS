#include "mainwindow.h"
#include "ui_mainwindow.h"

QListWidget *MainWindow::static_log=0;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),MDObject(104,"MainWindow"),ui(new Ui::MainWindow)
{
    ui -> setupUi(this);

#ifdef DISPLAY
    this -> setFixedSize(WIDTH,HEIGHT);
#endif

#ifdef _TRANSLATE
    setParent(parent);
    qtTranslator = new QTranslator(this);
    appTranslator = new QTranslator(this);
    qApp -> installTranslator(appTranslator);
    qApp -> installTranslator(qtTranslator);
#endif
    static_log = ui -> logWidget;

    QString style;

    QFile fStyle(":/new/prefix1/File/my.css");
    if (fStyle.open(QIODevice::ReadOnly))
    {
        style = fStyle.readAll();
        fStyle.close();
    }
#ifdef LOG
    else
        qDebug() << "не открыт";
#endif
    qApp -> setStyleSheet(style);
#ifdef BUTTONFULL
    this -> setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint | Qt::CustomizeWindowHint | Qt::WindowSystemMenuHint);
#else
    this -> setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint |
                          Qt::WindowCloseButtonHint | Qt::CustomizeWindowHint);
#endif
    flagHide = true;
    flagCom = false;
    flagWrite = true;

    flagString.flagString1 = true;
    flagString.flagString2 = false;
    flagString.flagString3 = false;

    numberStruct = 1;

    titlePictureLabel = new QLabel(this);
    titleLabel = new QLabel(this);

    connectComButton = new QPushButton(this);
    saveButton = new QPushButton(this);
    saveAsButton = new QPushButton(this);
    updateButton = new QPushButton(this);
    helpButton = new QPushButton(this);

#ifdef TESTBUTTON
    russionButton = new QPushButton(this);
    englishButton = new QPushButton(this);
    tableButton = new QPushButton(this);
#endif
    serialProductLabel = new QLabel(this);
    numberProductLabel = new QLabel(this);
    resulControlLabel = new QLabel(this);

    productText = new QLineEdit(this);
    serialProductText = new QLineEdit(this);
    serial_number_1 = new QLineEdit(this);
    serial_number_2 = new QLineEdit(this);
    serial_number_3 = new QLineEdit(this);
    serial_number_4 = new QLineEdit(this);
    serial_number_5 = new QLineEdit(this);
    numberProductText = new QLineEdit(this);
    resulControlText = new QLineEdit(this);

    numberCheckLabel = new QLabel(this);
    measureDateLabel = new QLabel(this);
    permisionDateLabel = new QLabel(this);

    numberCheckText = new QLineEdit(this);
    measureDateText = new QLineEdit(this);
    permisionDateText = new QLineEdit(this);

    mMessageSave = new MessageSave();
    mComPort = new ComPort();

#ifdef DISPLAY
    initialVarable();
#endif

    initial();

    connect(connectComButton, SIGNAL(clicked()), this, SLOT(portCom()));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveFile()));
    connect(saveAsButton, SIGNAL(clicked()), this, SLOT(saveAsFile()));
    connect(updateButton, SIGNAL(clicked()), this, SLOT(updateDate()));
    connect(helpButton, SIGNAL(clicked()), this, SLOT(help()));

    connect(mMessageSave, SIGNAL(updateDateMainWindow()), this, SLOT(updateDate()));

#ifdef TESTBUTTON
    connect(englishButton, SIGNAL(clicked()), this, SLOT(englishClicked()));
    connect(russionButton, SIGNAL(clicked()), this, SLOT(russionClicked()));
    connect(tableButton, SIGNAL(clicked()), this, SLOT(tableClicked()));
#endif

    connect(serial_number_1, SIGNAL(textChanged(QString)), this, SLOT(sizeEdit1(QString)));
    connect(serial_number_3, SIGNAL(textChanged(QString)), this, SLOT(sizeEdit2(QString)));
    connect(serial_number_5, SIGNAL(textChanged(QString)), this, SLOT(sizeEdit3(QString)));

    vibor();

    updateDate();
    hiding();


    QRegExp rx("^[0-9]*[0-9]*$");
    validator = new QRegExpValidator(rx,this);
    serial_number_1 -> setValidator(validator);
    serial_number_1 -> setMaxLength(2);
    serial_number_2 -> setValidator(validator);
    serial_number_2 -> setMaxLength(2);
    serial_number_3 -> setValidator(validator);
    serial_number_3 -> setMaxLength(2);
    serial_number_4 -> setValidator(validator);
    serial_number_4 -> setMaxLength(2);
    serial_number_5 -> setValidator(validator);
    serial_number_5 -> setMaxLength(2);

    serial_number_1 -> setFocus();

    numberProductText -> setValidator(validator);
    numberProductText -> setMaxLength(4);

    char ch;
    ch = ADDEvent("TestOk", new Delegate(this, &MainWindow::dateRocket));
    ch = ADDEvent("ComOpenId", new Delegate(this, &MainWindow::testIndexCom));
    ch = ADDEvent("ChoosePort", new Delegate(this, &MainWindow::choose_Port));
    ch = ADDEvent("Port_Error", new Delegate(this, &MainWindow::errorCom));
    ch = ADDEvent("Port_open", new Delegate(this, &MainWindow::comOpen));
    ch = ADDEvent("Port_close", new Delegate(this,&MainWindow::portCom_closed));
    ch = ADDEvent("Data_Come", new Delegate(this, &MainWindow::saveDataCom));
    ch = ADDEvent("New_Log", new Delegate(this, &MainWindow::appendLog));
    ch = ADDEvent("New_Exit", new Delegate(this, &MainWindow::exitMessageSustem));
#ifdef ERRROR_SQLITE
    ch = ADDEvent("SQL_Window_ERROR", new Delegate(this, &MainWindow::errorCom));
#endif

    ch = ADDEvent("TestERR", new Delegate(this, &MainWindow::errorCom));

#ifdef DISABLEDEDIT
    ch = ADDEvent("disabled_edit", new Delegate(this, &MainWindow::disEdit));
#endif

    ch = ADDEvent("Update");
    ch = ADDEvent("OpenCOM");
    ch = ADDEvent("OpenCOMX");
    ch = ADDEvent("ClosePort");
    ch = ADDEvent("Cxron_Write");
    ch = ADDEvent("Read_Data");
    ch = ADDEvent("Kpa_Test");
    ch = ADDEvent("WriteCOM");
    ch = ADDEvent("SaveData");

    Event_BUS::getInstance() -> AddMDObject(this);

#ifdef _TRANSLATE
    retranslateUi();
#endif
}

MainWindow::~MainWindow()
{
    delete kpa_com;
    delete kpa_rocket;
    delete ava_sqlite;
    delete datamanager;

    delete validator;
    delete mComPort;
    delete mMessageSave;

    delete permisionDateText;
    delete measureDateText;
    delete numberCheckText;

    delete permisionDateLabel;
    delete measureDateLabel;
    delete numberCheckLabel;

    delete resulControlText;
    delete numberProductText;
    delete serial_number_5;
    delete serial_number_4;
    delete serial_number_3;
    delete serial_number_2;
    delete serial_number_1;
    delete serialProductText;
    delete productText;

    delete resulControlLabel;
    delete numberProductLabel;
    delete serialProductLabel;

#ifdef TESTBUTTON
    delete tableButton;
    delete englishButton;
    delete russionButton;
#endif

    delete helpButton;
    delete updateButton;
    delete saveAsButton;
    delete saveButton;
    delete connectComButton;

    delete titleLabel;
    delete titlePictureLabel;
    delete ui;

#ifdef _TRANSLATE
    delete qtTranslator;
    delete appTranslator;
#endif

}

void MainWindow::displayLabel(QLabel *pLabel, int pFont, int pX, int pY, int pX1, int pY1, QString pString)
{
    QFont font;
    font.setPointSize(pFont);
    pLabel -> setGeometry(pX, pY, pX1, pY1);
    pLabel -> setFont(font);
    pLabel -> setText(pString);
}

void MainWindow::displayButton(QPushButton *pButton, int pFont, int pX, int pY, int pX1, int pY1, QString pString)
{
    QFont font;
    font.setPointSize(pFont);
    pButton -> setGeometry(pX, pY, pX1, pY1);
    pButton -> setIcon(QIcon(pString));
    pButton -> setIconSize(QSize(pX1-10,pY1-10));
}

void MainWindow::displayLineEdit(QLineEdit *pText, int pFont, int pX, int pY, int pX1, int pY1, QString pString)
{
    QFont font;
    font.setPointSize(pFont);
    pText -> setGeometry(pX, pY, pX1, pY1);
    pText -> setFont(font);
    pText -> setText(pString);
}

void MainWindow::initial()
{
#ifdef DISPLAY
    mashtabX = float(WIDTH / 1024.0f);
    mashtabY = float(HEIGHT / 768.0f);

    mMessageSave -> setGeometry(10*mashtabX, 10*mashtabY, 400*mashtabX, 400*mashtabY);
    mMessageSave -> setFixedSize(400*mashtabX,400*mashtabY);
    mComPort -> setGeometry(10*mashtabX, 10*mashtabY, 250*mashtabX, 300*mashtabY);
    mComPort -> setFixedSize(250*mashtabX, 300*mashtabY);

    displayLabel(titlePictureLabel, 12, 10*mashtabX, 10*mashtabY, 200*mashtabX, 50*mashtabY, "picture");
    displayLabel(titleLabel, 14, 100*mashtabX, 10*mashtabY, 600*mashtabX, 50*mashtabY, "Проверка изделия 9М311-1М");

    displayButton(connectComButton, 8, 10*mashtabX,  80*mashtabY, 80*mashtabX, 50*mashtabY, ":/new/prefix1/images/COM_DISCONNECT.png");
    displayButton(saveButton,       8, 100*mashtabX, 80*mashtabY, 80*mashtabX, 50*mashtabY, ":/new/prefix1/images/SAVE.png");
    displayButton(saveAsButton,     8, 190*mashtabX, 80*mashtabY, 80*mashtabX, 50*mashtabY, ":/new/prefix1/images/SAVE_AS.png");
    displayButton(updateButton,     8, 280*mashtabX, 80*mashtabY, 80*mashtabX, 50*mashtabY, ":/new/prefix1/images/UPDATE.png");
    displayButton(helpButton,       8, 370*mashtabX, 80*mashtabY, 80*mashtabX, 50*mashtabY, ":/new/prefix1/images/HELP.png");

#ifdef TESTBUTTON
    displayButton(russionButton,    8, 460*mashtabX, 80*mashtabY, 80*mashtabX, 50*mashtabY, ":/new/prefix1/images/RUSSION.png");
    displayButton(englishButton,    8, 550*mashtabX, 80*mashtabY, 80*mashtabX, 50*mashtabY, ":/new/prefix1/images/ENGLISH.png");
    displayButton(tableButton,      8, 640*mashtabX, 80*mashtabY, 80*mashtabX, 50*mashtabY, ":/new/prefix1/images/TABLE.png");
#endif

    displayLabel(serialProductLabel,14, 75*mashtabX, 240*mashtabY, 250*mashtabX, 50*mashtabY, "Серия изделия");
    displayLabel(numberProductLabel,14, 75*mashtabX, 300*mashtabY, 250*mashtabX, 50*mashtabY, "Номер изделия");
    displayLabel(resulControlLabel, 14, 75*mashtabX, 420*mashtabY, 250*mashtabX, 50*mashtabY, "Результат проверки");
    displayLabel(numberCheckLabel,  14, 75*mashtabX, 490*mashtabY, 250*mashtabX, 50*mashtabY, "№ проверки");
    displayLabel(measureDateLabel,  14, 75*mashtabX, 560*mashtabY, 250*mashtabX, 50*mashtabY, "Измерение значение");
    displayLabel(permisionDateLabel,14, 75*mashtabX, 630*mashtabY, 250*mashtabX, 50*mashtabY, "Допустимое значение");

    displayLineEdit(serialProductText,14, 340*mashtabX, 240*mashtabY, 140*mashtabX, 40*mashtabY, "Серия изделия");
    displayLineEdit(serial_number_1,  14, 340*mashtabX, 240*mashtabY, 37*mashtabX, 40*mashtabY, "");
    displayLineEdit(serial_number_2,  14, 381*mashtabX, 240*mashtabY, 10*mashtabX, 40*mashtabY, "-");
    displayLineEdit(serial_number_3,  14, 394*mashtabX, 240*mashtabY, 37*mashtabX, 40*mashtabY, "");
    displayLineEdit(serial_number_4,  14, 428*mashtabX, 240*mashtabY, 10*mashtabX, 40*mashtabY, "-");
    displayLineEdit(serial_number_5,  14, 442*mashtabX, 240*mashtabY, 37*mashtabX, 40*mashtabY, "");
    displayLineEdit(numberProductText,14, 340*mashtabX, 300*mashtabY, 140*mashtabX, 40*mashtabY, "Номер изделия");
    displayLineEdit(resulControlText, 14, 340*mashtabX, 420*mashtabY, 140*mashtabX, 40*mashtabY, "Результат проверки");


    displayLineEdit(numberCheckText,  14, 340*mashtabX, 490*mashtabY, 140*mashtabX, 40*mashtabY, "№ проверки");
    displayLineEdit(measureDateText,  14, 340*mashtabX, 560*mashtabY, 140*mashtabX, 40*mashtabY, "Измерение значение");
    displayLineEdit(permisionDateText,14, 340*mashtabX, 630*mashtabY, 140*mashtabX, 40*mashtabY, "Допустимое значение");

    displayButton(ui -> pushButton_b, 14, 743*mashtabX, 640*mashtabY, 121*mashtabX, 23*mashtabY, "Отправить b");
    displayButton(ui -> pushButton_z, 14, 873*mashtabX, 640*mashtabY, 121*mashtabX, 23*mashtabY, "Отправить z");
    displayButton(ui -> pushButton_t, 14, 743*mashtabX, 670*mashtabY, 121*mashtabX, 23*mashtabY, "Отправить t");
    displayButton(ui -> pushButton_g, 14, 873*mashtabX, 670*mashtabY, 121*mashtabX, 23*mashtabY, "Отправить g");

#else
    mMessageSave -> setGeometry(10, 10, 400, 400);
    mMessageSave -> setFixedSize(400,400);
    mComPort -> setGeometry(10, 10, 250, 300);
    mComPort -> setFixedSize(250, 300);

    displayLabel(titlePictureLabel, 12, 10, 10, 200, 50, "picture");
    displayLabel(titleLabel, 14, 220, 10, 700, 50, "Проверка изделия 9М311-1М");

    displayButton(connectComButton, 8, 10,  80, 80, 50, ":/new/prefix1/images/COM_DISCONNECT.png");
    displayButton(saveButton,       8, 100, 80, 80, 50, ":/new/prefix1/images/SAVE.png");
    displayButton(saveAsButton,     8, 190, 80, 80, 50, ":/new/prefix1/images/SAVE_AS.png");
    displayButton(updateButton,     8, 280, 80, 80, 50, ":/new/prefix1/images/UPDATE.png");
    displayButton(helpButton,       8, 370, 80, 80, 50, ":/new/prefix1/images/HELP.png");

#ifdef TESTBUTTON
    displayButton(russionButton,    8, 460, 80, 80, 50, ":/new/prefix1/images/RUSSION.png");
    displayButton(englishButton,    8, 550, 80, 80, 50, ":/new/prefix1/images/ENGLISH.png");
    displayButton(tableButton,      8, 640, 80, 80, 50, ":/new/prefix1/images/TABLE.png");
#endif

    displayLabel(serialProductLabel,14, 75, 240, 250, 50, "Серия изделия");
    displayLabel(numberProductLabel,14, 75, 300, 250, 50, "Номер изделия");
    displayLabel(resulControlLabel, 14, 75, 420, 250, 50, "Результат проверки");
    displayLabel(numberCheckLabel,  14, 75, 490, 250, 50, "№ проверки");
    displayLabel(measureDateLabel,  14, 75, 560, 250, 50, "Измерение значение");
    displayLabel(permisionDateLabel,14, 75, 630, 250, 50, "Допустимое значение");

    displayLineEdit(serialProductText,14, 340, 240, 140, 40, "Серия изделия");
    displayLineEdit(serial_number_1,  14, 340, 240, 37, 40, "");
    displayLineEdit(serial_number_2,  14, 381, 240, 10, 40, "-");
    displayLineEdit(serial_number_3,  14, 394, 240, 37, 40, "");
    displayLineEdit(serial_number_4,  14, 428, 240, 10, 40, "-");
    displayLineEdit(serial_number_5,  14, 442, 240, 37, 40, "");
    displayLineEdit(numberProductText,14, 340, 300, 140, 40, "Номер изделия");
    displayLineEdit(resulControlText, 14, 340, 420, 140, 40, "Результат проверки");


    displayLineEdit(numberCheckText,  14, 340, 490, 140, 40, "№ проверки");
    displayLineEdit(measureDateText,  14, 340, 560, 140, 40, "Измерение значение");
    displayLineEdit(permisionDateText,14, 340, 630, 140, 40, "Допустимое значение");

    displayButton(ui -> pushButton_b, 14, 743, 690, 121, 23, "Отправить b");
    displayButton(ui -> pushButton_z, 14, 873, 690, 121, 23, "Отправить z");
    displayButton(ui -> pushButton_t, 14, 743, 720, 121, 23, "Отправить t");
    displayButton(ui -> pushButton_g, 14, 873, 720, 121, 23, "Отправить g");
#endif
    saveFlag.flagDir = false;
    saveFlag.flagWriteSave = true;
    saveFlag.flagError = false;
#ifdef NORESULTSAVE
    saveFlag.flagComSave = false;
    saveFlag.flagResult = false;
    saveFlag.flagNumber = false;
    saveFlag.flagSerial = false;
#endif

#ifdef ERRORTEXT
    errorText = true;
#endif

    QVector<QString> lVector (5);
    lVector[0] = "";
    lVector[1] = "";
    lVector[2] = "";
    lVector[3] = "";
    lVector[4] = "";
    dateRocket(lVector);

    vectorEdit.resize(3);
    vectorEdit[0] = "";
    vectorEdit[1] = "";
    vectorEdit[2] = "";

    serialProductText -> setEnabled(false);
    serial_number_1 -> setAlignment(Qt::AlignCenter);
    serial_number_2 -> setAlignment(Qt::AlignCenter);
    serial_number_3 -> setAlignment(Qt::AlignCenter);
    serial_number_4 -> setAlignment(Qt::AlignCenter);
    serial_number_5 -> setAlignment(Qt::AlignCenter);

    serial_number_2 -> setEnabled(false);
    serial_number_4 -> setEnabled(false);
    resulControlText -> setEnabled(false);
    numberProductText -> setEnabled(false);
    numberCheckText -> setEnabled(false);
    measureDateText -> setEnabled(false);
    permisionDateText -> setEnabled(false);

    titlePictureLabel -> setPixmap(QPixmap::fromImage(QImage(":/new/prefix1/images/LOGO.png")));
    titleLabel  -> setAlignment(Qt::AlignCenter);

}

void MainWindow::saveDate(QString pStr, QString pStrFile, int pNumber)
{
#ifdef FILEDELETE
    if (pStrFile == NULL )
    {
        showing();
    }
    else
    {
        QFile file(pStrFile);

        if (file.exists())
        {
            if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
            {
                saveFlag.flagError = true;
                QTextStream out(&file);
                out << pStr +"\n";
                initialStruct(numberStruct, pStr, pNumber);
            }
            else
                if (file.open(QIODevice::ReadOnly))
                    errorCom(ERROR_READ_FILE);
        file.close();
        }
        else
        {
            errorCom(ERROR_DELETE_FILE);
        }
    }
#else
    if (pStrFile == NULL )
    {
        showing();
    }
    else
    {
        QFile file(pStrFile);
        if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        {
            saveFlag.flagError = true;
            QTextStream out(&file);
            out << pStr +"\n";
            initialStruct(numberStruct, pStr, pNumber);
        }
        else
            if (file.open(QIODevice::ReadOnly))
                errorCom(ERROR_READ_FILE);
#ifdef LOG
            qDebug()<<"bad";
#endif
        file.close();
    }
#endif

}

void MainWindow::showing()
{

    permisionDateText -> show();
    measureDateText -> show();
    numberCheckText -> show();

    permisionDateLabel -> show();
    measureDateLabel -> show();
    numberCheckLabel -> show();

    resulControlText -> show();
    numberProductText -> show();
    serialProductText -> show();

    resulControlLabel -> show();
    numberProductLabel -> show();
    serialProductLabel -> show();

    hideButton -> show();
    exitButton -> show();

    helpButton -> show();
    updateButton -> show();
    saveAsButton -> show();
    saveButton -> show();
    connectComButton -> show();

    titleLabel -> show();
    titlePictureLabel -> show();
}

void MainWindow::vibor()
{
#ifdef DISPLAY
#ifndef ADMINON
    {
        ui -> logWidget -> setGeometry(740*mashtabX, 31*mashtabY, 256*mashtabX, 600*mashtabY);
        ui -> pushButton_b -> hide();
        ui -> pushButton_g -> hide();
        ui -> pushButton_t -> hide();
        ui -> pushButton_z -> hide();
        tableButton -> hide();
    }
#else
    {
        ui -> logWidget -> setGeometry(740*mashtabX, 31*mashtabY, 256*mashtabX, 600*mashtabY);
        ui -> pushButton_b -> show();
        ui -> pushButton_g -> show();
        ui -> pushButton_t -> show();
        ui -> pushButton_z -> show();
        tableButton -> show();
    }
#endif
#else
#ifndef ADMINON
    {
        ui -> logWidget -> setGeometry(740, 81, 256, 600);
        ui -> pushButton_b -> hide();
        ui -> pushButton_g -> hide();
        ui -> pushButton_t -> hide();
        ui -> pushButton_z -> hide();
        tableButton -> hide();
    }
#else
    {
        ui -> logWidget -> setGeometry(740, 81, 256, 600);
        ui -> pushButton_b -> show();
        ui -> pushButton_g -> show();
        ui -> pushButton_t -> show();
        ui -> pushButton_z -> show();
        tableButton -> show();
    }
#endif
#endif
}

void MainWindow::initialStruct(int i, QString pStr, int pNumber)
{
    switch (i)
    {
        case 1:

            flagString.flagString1 = true;
            flagString.flagString2 = false;
            flagString.flagString3 = false;

            switch (pNumber)
            {
                case 1:
                    blockString1.date = pStr;
                break;

                case 2:
                    blockString1.time = pStr;
                break;

                case 3:
                    blockString1.product = pStr;
                break;

                case 4:
                    blockString1.serialProduct = pStr;
                break;

                case 5:
                    blockString1.numberProduct = pStr;
                break;

                case 6:
                    blockString1.ResultControl = pStr;
                break;

                case 7:
                    if ((blockString1.ResultControl == STR_FLAG) or (blockString1.ResultControl == STR_FLAG1))
                        blockString1.numberCheck = pStr;
                    else
                        blockString1.numberCheck = " ";
                break;

                case 8:
                    if ((blockString1.ResultControl == STR_FLAG) or (blockString1.ResultControl == STR_FLAG1))
                        blockString1.measureDate = pStr;
                    else
                        blockString1.measureDate = " ";
                break;

                case 9:
                    if ((blockString1.ResultControl == STR_FLAG) or (blockString1.ResultControl == STR_FLAG1))
                        blockString1.permissionDate = pStr;
                    else
                        blockString1.permissionDate = " ";
                break;

                case 0:
                    blockString1.defice = pStr;
                    numberStruct = 2;
                break;
            }
        break;

        case 2:

            flagString.flagString1 = false;
            flagString.flagString2 = true;
            flagString.flagString3 = false;

            switch (pNumber)
            {
                case 1:
                    blockString2.date = pStr;
                break;

                case 2:
                    blockString2.time = pStr;
                break;

                case 3:
                    blockString2.product = pStr;
                break;

                case 4:
                    blockString2.serialProduct = pStr;
                break;

                case 5:
                    blockString2.numberProduct = pStr;
                break;

                case 6:
                    blockString2.ResultControl = pStr;
                break;

                case 7:
                    if ((blockString2.ResultControl == STR_FLAG) or (blockString2.ResultControl == STR_FLAG1))
                        blockString2.numberCheck = pStr;
                    else
                        blockString2.numberCheck = " ";
                break;

                case 8:
                    if ((blockString2.ResultControl == STR_FLAG) or (blockString2.ResultControl == STR_FLAG1))
                        blockString2.measureDate = pStr;
                    else
                        blockString2.measureDate = " ";
                break;

                case 9:
                    if ((blockString2.ResultControl == STR_FLAG) or (blockString2.ResultControl == STR_FLAG1))
                        blockString2.permissionDate = pStr;
                    else
                        blockString2.permissionDate = " ";
                break;

                case 0:
                    blockString2.defice = pStr;
                    numberStruct = 3;
                break;
            }
            break;

        case 3:

            flagString.flagString1 = false;
            flagString.flagString2 = false;
            flagString.flagString3 = true;

            flagWrite = false;

            switch (pNumber)
            {
                case 1:
                    blockString3.date = pStr;
                break;

                case 2:
                    blockString3.time = pStr;
                break;

                case 3:
                    blockString3.product = pStr;
                break;

                case 4:
                    blockString3.serialProduct = pStr;
                break;

                case 5:
                    blockString3.numberProduct = pStr;
                break;

                case 6:
                    blockString3.ResultControl = pStr;
                break;

                case 7:
                    if ((blockString3.ResultControl == STR_FLAG) or (blockString3.ResultControl == STR_FLAG1))
                        blockString3.numberCheck = pStr;
                    else
                        blockString3.numberCheck = " ";
                break;

                case 8:
                    if ((blockString3.ResultControl == STR_FLAG) or (blockString3.ResultControl == STR_FLAG1))
                        blockString3.measureDate = pStr;
                    else
                        blockString3.measureDate = " ";
                break;

                case 9:
                    if ((blockString3.ResultControl == STR_FLAG) or (blockString3.ResultControl == STR_FLAG1))
                        blockString3.permissionDate = pStr;
                    else
                        blockString3.permissionDate = " ";
                break;

                case 0:
                    blockString3.defice = pStr;
                    numberStruct = 1;
                break;
            }
        break;

        case 0:
            strFileAs = QFileDialog::getOpenFileName(this, "save", QDir::currentPath(), "*.txt");
            if (strFileAs == NULL )
            {
#ifdef DISPLAY
                mMessageSave -> move(300*mashtabX,200*mashtabY);
#else
                mMessageSave -> move(300, 200);
#endif
                mMessageSave -> show();

                flagHideWindow.flagMessageHide = true;

                mMessageSave -> hiddingButton(ERROR_NO_CHANGE_FILE);
                initialStruct(0,"",1);

            }
            else
            {
                mMessageSave -> hide();

                flagHideWindow.flagMessageHide = false;

                QFile file(strFileAs);
                if (file.open(QIODevice::ReadOnly))
                {
                    QTextStream stream(&file);
                    QString tempString;
                    QChar pChar;

                    int i = 1;
                    int number = 1;

                    while (!stream.atEnd())
                    {
                        tempString = stream.readLine();
                        pChar = tempString[1];

                        switch (number)
                        {
                            case 1:
                                if (pChar == '-')
                                    number = 2;
                                switch (i)
                                {
                                    case 1:
                                        blockString1.date = tempString;
                                        i = 2;
                                    break;

                                    case 2:
                                        blockString1.time = tempString;
                                        i = 3;
                                    break;

                                    case 3:
                                        blockString1.product = tempString;
                                        i = 4;
                                    break;

                                    case 4:
                                        blockString1.serialProduct = tempString;
                                        i = 5;
                                    break;

                                    case 5:
                                        blockString1.numberProduct = tempString;
                                        i = 6;
                                    break;

                                    case 6:
                                        blockString1.ResultControl = tempString;
                                        i = 7;
                                    break;

                                    case 7:
                                        if ((blockString1.ResultControl == STR_FLAG) or (blockString1.ResultControl == STR_FLAG1))
                                            blockString1.numberCheck = pStr;
                                        else
                                            blockString1.numberCheck = " ";
                                        i = 8;
                                    break;

                                    case 8:
                                        if ((blockString1.ResultControl == STR_FLAG) or (blockString1.ResultControl == STR_FLAG1))
                                            blockString1.measureDate = pStr;
                                        else
                                            blockString1.measureDate = " ";
                                        i = 9;
                                    break;

                                    case 9:
                                        if ((blockString1.ResultControl == STR_FLAG) or (blockString1.ResultControl == STR_FLAG1))
                                            blockString1.permissionDate = pStr;
                                        else
                                            blockString1.permissionDate = " ";
                                        i = 0;
                                    break;

                                    case 0:
                                        blockString1.defice = tempString;
                                        i = 1;
                                    break;
                                }
                            break;

                            case 2:
                                if (pChar == '-') number = 3;
                                switch (i)
                                {
                                    case 1:
                                        blockString2.date = tempString;
                                        i = 2;
                                    break;

                                    case 2:
                                        blockString2.time = tempString;
                                        i = 3;
                                    break;

                                    case 3:
                                        blockString2.product = tempString;
                                        i = 4;
                                    break;

                                    case 4:
                                        blockString2.serialProduct = tempString;
                                        i = 5;
                                    break;

                                    case 5:
                                        blockString2.numberProduct = tempString;
                                        i = 6;
                                    break;

                                    case 6:
                                        blockString2.ResultControl = tempString;
                                        i = 7;
                                    break;

                                    case 7:
                                        if ((blockString2.ResultControl == STR_FLAG) or (blockString2.ResultControl == STR_FLAG1))
                                            blockString2.numberCheck = pStr;
                                        else
                                            blockString2.numberCheck = " ";
                                        i = 8;
                                    break;

                                    case 8:
                                        if ((blockString2.ResultControl == STR_FLAG) or (blockString2.ResultControl == STR_FLAG1))
                                            blockString2.measureDate = pStr;
                                        else
                                            blockString2.measureDate = " ";
                                        i = 9;
                                    break;

                                    case 9:
                                        if ((blockString2.ResultControl == STR_FLAG) or (blockString2.ResultControl == STR_FLAG1))
                                            blockString2.permissionDate = pStr;
                                        else
                                            blockString2.permissionDate = " ";
                                        i = 0;
                                    break;

                                    case 0:
                                        blockString2.defice = tempString;
                                        i = 1;
                                    break;
                                }
                            break;

                            case 3:
                                if (pChar == '-') number = 1;
                                switch (i)
                                {
                                    case 1:
                                        blockString3.date = tempString;
                                        i = 2;
                                    break;

                                    case 2:
                                        blockString3.time = tempString;
                                        i = 3;
                                    break;

                                    case 3:
                                        blockString3.product = tempString;
                                        i = 4;
                                    break;

                                    case 4:
                                        blockString3.serialProduct = tempString;
                                        i = 5;
                                    break;

                                    case 5:
                                        blockString3.numberProduct = tempString;
                                        i = 6;
                                    break;

                                    case 6:
                                        blockString3.ResultControl = tempString;
                                        i = 7;
                                    break;

                                    case 7:
                                        if ((blockString3.ResultControl == STR_FLAG) or (blockString3.ResultControl == STR_FLAG1))
                                            blockString3.numberCheck = pStr;
                                        else
                                            blockString3.numberCheck = " ";
                                        i = 8;
                                    break;

                                    case 8:
                                        if ((blockString3.ResultControl == STR_FLAG) or (blockString3.ResultControl == STR_FLAG1))
                                            blockString3.measureDate = pStr;
                                        else
                                            blockString3.measureDate = " ";
                                        i = 9;
                                    break;

                                    case 9:
                                        if ((blockString3.ResultControl == STR_FLAG) or (blockString3.ResultControl == STR_FLAG1))
                                            blockString3.permissionDate = pStr;
                                        else
                                            blockString3.permissionDate = " ";
                                        i = 0;
                                    break;

                                    case 0:
                                        blockString3.defice = tempString;
                                        i =1;
                                    break;
                                }
                            break;
                        }

                    }
                    if (stream.status()!= QTextStream::Ok)
                    {
#ifdef LOG
                        qDebug() << "Ошибка чтений файла";
#endif
                    }
                    file.close();
                }

            }

            numberStruct = 1;
        break;
    }

}

void MainWindow::writeHistory()
{
    if (flagWrite and flagString.flagString1)
        writeLog1();
    else
        if (flagWrite and flagString.flagString2)
        {
            writeLog1();
            writeLog2();
        }
        else
            if (flagString.flagString3)
            {
                writeLog1();
                writeLog2();
                writeLog3();
            }
                else
                    if (flagString.flagString1)\
                    {
                        writeLog2();
                        writeLog3();
                        writeLog1();
                    }
                    else
                        if(flagString.flagString2)
                        {
                            writeLog3();
                            writeLog1();
                            writeLog2();
                        }
}

void MainWindow::writeLog1()
{
    appendLog(blockString1.date);
    appendLog(blockString1.time);
    appendLog(blockString1.product);
    appendLog(blockString1.serialProduct);
    appendLog(blockString1.numberProduct);
    appendLog(blockString1.ResultControl);

    if ((blockString1.ResultControl == STR_FLAG) or (blockString1.ResultControl == STR_FLAG1))
    {
        appendLog(blockString1.numberCheck);
        appendLog(blockString1.measureDate);
        appendLog(blockString1.permissionDate);
    }
    appendLog(blockString1.defice);
}

void MainWindow::writeLog2()
{
    appendLog(blockString2.date);
    appendLog(blockString2.time);
    appendLog(blockString2.product);
    appendLog(blockString2.serialProduct);
    appendLog(blockString2.numberProduct);
    appendLog(blockString2.ResultControl);

    if ((blockString2.ResultControl == STR_FLAG) or (blockString2.ResultControl == STR_FLAG1))
    {
        appendLog(blockString2.numberCheck);
        appendLog(blockString2.measureDate);
        appendLog(blockString2.permissionDate);
    }
    appendLog(blockString2.defice);
}

void MainWindow::writeLog3()
{
    appendLog(blockString3.date);
    appendLog(blockString3.time);
    appendLog(blockString3.product);
    appendLog(blockString3.serialProduct);
    appendLog(blockString3.numberProduct);
    appendLog(blockString3.ResultControl);

    if ((blockString3.ResultControl == STR_FLAG) or (blockString3.ResultControl == STR_FLAG1))
    {
        appendLog(blockString3.numberCheck);
        appendLog(blockString3.measureDate);
        appendLog(blockString3.permissionDate);
    }
    appendLog(blockString3.defice);
}

void MainWindow::writeLogFile_RU(QString pStr)
{
    QLocale russion(QLocale::Russian);
    vector<string> mix;
    while(1)
    {
        mix.push_back(russion.toString(dateString.data,"dd.MM.yy").toStdString());  //Добавлено 17.01.17
        strDate = "Дата: " + russion.toString(dateString.data,"dd.MMMM.yyyy");
#ifdef FILEDELETE
        if (flagAs)
            saveDataAs(strDate, strFileAs, 1);
        else
            saveDate(strDate, strFileAs, 1);
#else
        saveDate(strDate, strFileAs, 1);
#endif
        strDate = "Время: " + dateString.data.toString("HH:mm:ss");
        mix.push_back(strDate.right(strDate.size() - 7).left(5).toStdString());  //Добавлено 17.01.17

#ifdef FILEDELETE
        if (flagAs)
            saveDataAs(strDate, strFileAs, 2);
        else
            saveDate(strDate, strFileAs, 2);
#else
        saveDate(strDate, strFileAs, 2);
#endif

        strDate = "Изделие: ";
        strDate = strDate + strVector[0];
        //mix.push_back(strVector[0].toStdString());  //Добавлено 17.01.17
#ifdef FILEDELETE
        if (flagAs)
            saveDataAs(strDate, strFileAs, 3);
        else
            saveDate(strDate, strFileAs, 3);
#else
        saveDate(strDate, strFileAs, 3);
#endif

        strDate = "Серия: ";
        strDate = strDate +  pStr;
        mix.push_back(pStr.toStdString());  //Добавлено 17.01.17

#ifdef FILEDELETE
        if (flagAs)
            saveDataAs(strDate, strFileAs, 4);
        else
            saveDate(strDate, strFileAs, 4);
#else
        saveDate(strDate, strFileAs, 4);
#endif

        strDate = "Номер: ";
        strDate = strDate +  numberProductText -> text();
        mix.push_back(numberProductText -> text().toStdString());  //Добавлено 17.01.17
#ifdef FILEDELETE
        if (flagAs)
            saveDataAs(strDate, strFileAs, 5);
        else
            saveDate(strDate, strFileAs, 5);
#else
        saveDate(strDate, strFileAs, 5);
#endif

        strDate = "Результат проверки: ";
        strDate = strDate + strVector[1];
        mix.push_back(strVector[1].left(2).toStdString());  //Добавлено 17.01.17
#ifdef FILEDELETE
        if (flagAs)
            saveDataAs(strDate, strFileAs, 6);
        else
            saveDate(strDate, strFileAs, 6);
#else
        saveDate(strDate, strFileAs, 6);
#endif
        if(strVector[1] != FLAG1)
        {
            strDate = mixik::GetInstance() -> DoMixik(mix);
#ifdef FILEDELETE
        if (flagAs)
            saveDataAs(strDate, strFileAs, 7);
        else
            saveDate(strDate, strFileAs, 7);
#else
        saveDate(strDate, strFileAs, 7);
#endif
            //Добавлено 17.01.17
            break;
        }

        strDate = "№ проверки: ";
        strDate = strDate + strVector[2];
        //mix.push_back(strVector[2].toStdString());  //Добавлено 17.01.17
#ifdef FILEDELETE
        if (flagAs)
            saveDataAs(strDate, strFileAs, 7);
        else
            saveDate(strDate, strFileAs, 7);
#else
        saveDate(strDate, strFileAs, 7);
#endif

        strDate = "Измерение значение: ";
        strDate = strDate + strVector[3];
        //mix.push_back(strVector[3].toStdString());  //Добавлено 17.01.17
#ifdef FILEDELETE
        if (flagAs)
            saveDataAs(strDate, strFileAs, 8);
        else
            saveDate(strDate, strFileAs, 8);
#else
        saveDate(strDate, strFileAs, 8);
#endif

        strDate = "Допустимое значение: ";
        strDate = strDate + strVector[4];
#ifdef FILEDELETE
        if (flagAs)
            saveDataAs(strDate, strFileAs, 9);
        else
            saveDate(strDate, strFileAs, 9);
#else
        saveDate(strDate, strFileAs, 9);
#endif

        strDate = mixik::GetInstance() -> DoMixik(mix);
#ifdef FILEDELETE
        if (flagAs)
            saveDataAs(strDate, strFileAs,10);
        else
            saveDate(strDate, strFileAs,10);
#else
        saveDate(strDate, strFileAs,10);
#endif  //Добавлено 17.01.17
        break;
    }

    strDate.clear();
    for (int i = 0; i < 50; i++)
        strDate = strDate + "-";
#ifdef FILEDELETE
        if (flagAs)
            saveDataAs(strDate, strFileAs, 0);
        else
            saveDate(strDate, strFileAs, 0);
#else
        saveDate(strDate, strFileAs, 0);
#endif
    if (saveFlag.flagError)
    {
        ui -> logWidget-> clear();
        writeHistory();
    }
    else
    {
        //ui -> logWidget ->clear();
    }
}

void MainWindow::writeLogFile_EN(QString pStr)
{
    QLocale english(QLocale::English);
    vector<string> mix;
    while (1)
    {
        mix.push_back(english.toString(dateString.data,"dd.MM.yy").toStdString());  //Добавлено 17.01.17
        strDate = "Date: " + english.toString(dateString.data,"dd.MMMM.yyyy");
#ifdef FILEDELETE
        if (flagAs)
            saveDataAs(strDate, strFileAs, 1);
        else
            saveDate(strDate, strFileAs, 1);
#else
        saveDate(strDate, strFileAs, 1);
#endif

        strDate = "Time: " + dateString.data.toString("HH:mm:ss");
        mix.push_back(strDate.right(strDate.size() - 6).left(5).toStdString());  //Добавлено 17.01.17
#ifdef FILEDELETE
        if (flagAs)
            saveDataAs(strDate, strFileAs, 2);
        else
            saveDate(strDate, strFileAs, 2);
#else
        saveDate(strDate, strFileAs, 2);
#endif

        strDate = "Product: ";
        //mix.push_back(strVector[0].toStdString());  //Добавлено 17.01.17
        strDate = strDate + strVector[0];
#ifdef FILEDELETE
        if (flagAs)
            saveDataAs(strDate, strFileAs, 3);
        else
            saveDate(strDate, strFileAs, 3);
#else
        saveDate(strDate, strFileAs, 3);
#endif

        strDate = "Seria: ";
        strDate = strDate +  pStr;
        mix.push_back(pStr.toStdString());  //Добавлено 17.01.17
#ifdef FILEDELETE
        if (flagAs)
            saveDataAs(strDate, strFileAs, 4);
        else
            saveDate(strDate, strFileAs, 4);
#else
        saveDate(strDate, strFileAs, 4);
#endif

        strDate = "Number: ";
        strDate = strDate +  numberProductText -> text();
        mix.push_back(numberProductText -> text().toStdString());  //Добавлено 17.01.17
#ifdef FILEDELETE
        if (flagAs)
            saveDataAs(strDate, strFileAs, 5);
        else
            saveDate(strDate, strFileAs, 5);
#else
        saveDate(strDate, strFileAs, 5);
#endif

        strDate = "Result test: ";
        strDate = strDate + strVector[1];
#ifdef linux
        mix.push_back(strVector[1].left(4).toStdString());  //Добавлено 17.01.17
#endif
#ifdef win32
        mix.push_back(strVector[1].left(2).toStdString());  //Добавлено 17.01.17
#endif
#ifdef FILEDELETE
        if (flagAs)
            saveDataAs(strDate, strFileAs, 6);
        else
            saveDate(strDate, strFileAs, 6);
#else
        saveDate(strDate, strFileAs, 6);
#endif;
        if (strVector[1] != FLAG2){
            strDate = mixik::GetInstance() -> DoMixik(mix);
#ifdef FILEDELETE
        if (flagAs)
            saveDataAs(strDate, strFileAs, 7);
        else
            saveDate(strDate, strFileAs, 7);
#else
        saveDate(strDate, strFileAs, 7);
#endif  //Добавлено 17.01.17
            break;
        }

        strDate = "№ Test: ";
        strDate = strDate + strVector[2];
        //mix.push_back(strVector[2].toStdString());  //Добавлено 17.01.17
#ifdef FILEDELETE
        if (flagAs)
            saveDataAs(strDate, strFileAs, 7);
        else
            saveDate(strDate, strFileAs, 7);
#else
        saveDate(strDate, strFileAs, 7);
#endif
        strDate = "Measure value: ";
        strDate = strDate + strVector[3];
        //mix.push_back(strVector[3].toStdString());  //Добавлено 17.01.17
#ifdef FILEDELETE
        if (flagAs)
            saveDataAs(strDate, strFileAs, 8);
        else
            saveDate(strDate, strFileAs, 8);
#else
        saveDate(strDate, strFileAs, 8);
#endif

        strDate = "Permission value: ";
        strDate = strDate + strVector[4];
#ifdef FILEDELETE
        if (flagAs)
            saveDataAs(strDate, strFileAs, 9);
        else
            saveDate(strDate, strFileAs, 9);
#else
        saveDate(strDate, strFileAs, 9);
#endif

        strDate = mixik::GetInstance() -> DoMixik(mix);
#ifdef FILEDELETE
        if (flagAs)
            saveDataAs(strDate, strFileAs,10);
        else
            saveDate(strDate, strFileAs,10);
#else
        saveDate(strDate, strFileAs,10);
#endif  //Добавлено 17.01.17
        break;
    }

    strDate.clear();
    for (int i = 0; i < 50; i++)
        strDate = strDate + "-";
#ifdef FILEDELETE
        if (flagAs)
            saveDataAs(strDate, strFileAs, 0);
        else
            saveDate(strDate, strFileAs, 0);
#else
        saveDate(strDate, strFileAs, 0);
#endif

    ui -> logWidget-> clear();
    writeHistory();
}
#ifdef DISABLEDEDIT
void MainWindow::disEdit()
{
    serial_number_1 ->setEnabled(false);
    serial_number_2 -> setEnabled(false);
    serial_number_3 -> setEnabled(false);
    serial_number_4 -> setEnabled(false);
    serial_number_5 -> setEnabled(false);
    numberProductText -> setEnabled(false);
    numberCheckText -> setEnabled(false);
    measureDateText -> setEnabled(false);
    permisionDateText -> setEnabled(false);
#ifdef NORESULTSAVE
    saveFlag.flagResult = true;
#endif
}
#endif

#ifdef DISPLAY
void MainWindow::initialVarable()
{
    mashtabX = 0.0f;
    mashtabY = 0.0f;
}
#endif

void MainWindow::hiding()
{
    //productText -> displayButton(connectComButton, 8, 10,  80, 80, 50, ":/new/prefix1/images/COM_CONNECT.png");
    productText -> hide();
    numberCheckLabel -> hide();
    measureDateLabel -> hide();
    permisionDateLabel -> hide();
    numberCheckText -> hide();
    measureDateText -> hide();
    permisionDateText -> hide();
}

void MainWindow::exitSystem()
{
#ifdef DISPLAY
    mMessageSave -> move(300*mashtabX, 200*mashtabY);
#else
    mMessageSave -> move(300,200);
#endif
    flagHideWindow.flagMessageHide = true;

    mMessageSave -> showingButton();
    mMessageSave -> show();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event -> key())
    {
        case Qt::Key_Escape:
            exitSystem();
        break;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    exitSystem();
}

void MainWindow::changeEvent(QEvent *event)
{
    QMainWindow::changeEvent(event);
    if(event ->type() == QEvent::WindowStateChange)
    {
        if(isMinimized())
        {
            if (flagHideWindow.flagMessageHide == true)
            {
                mMessageSave -> hide();
                updateDate();
            }
        }
    }

#ifdef _TRANSLATE
    if (event -> type() == QEvent::LanguageChange)
    {
        retranslateUi();
    }
    else QWidget::changeEvent(event);
#endif
}

void MainWindow::appendLog(QString pStr)
{
    QListWidgetItem *newItem = new QListWidgetItem;
    newItem -> setText(pStr);
    ui -> logWidget -> insertItem(100, newItem);
}

void MainWindow::appendLog(const char *data)
{
    QListWidgetItem *newItem = new QListWidgetItem;
    newItem -> setText(data);
    static_log -> insertItem(100, newItem);
}

void MainWindow::portCom()
{
#ifdef LOG
    qDebug() << "Сигнал на открытие ком порта";
#endif
    if (!flagCom)
    {
        comOpenSignal();
    }
    else
    {
       comCloseSignal();
    }
}

void MainWindow::saveFile()
{
#ifdef FILEDELETE
    flagAs = false;
#endif

#ifndef NORESULTSAVE
    if (saveFlag.flagComSave)
    {
        if (saveFlag.flagWriteSave)
        {
            if (!saveFlag.flagDir and !saveFlag.flagError)
            {
                if (!saveFlag.flagDir)
                {
                    saveAsFile();
                }
                else
                {
                    QString pStrEdit,pStrEdit1;
                    pStrEdit1 = numberProductText -> text();
                    pStrEdit = vectorEdit[0] + serial_number_2 -> text() + vectorEdit[1] + serial_number_4 -> text() + vectorEdit[2];

                    if (pStrEdit1.length() == 0)
                    {
                        errorCom(ERROR_WRITE_NUMBER);
                    }
                    else
                    {
#ifdef NORESULTSAVE
                        if(saveFlag.flagResult)
                        {
                            errorCom(ERROR_RESULT);
                            saveFlag.flagResult = true;
                        }
                        else
                        {
#endif
                            pStrEdit1.clear();
                            if (pStrEdit.length() == 8)
                            {
                                QDateTime dat;
                                dat = QDateTime::currentDateTime();

                                dateString.data = dat;
                                dateString.serial = pStrEdit;
                                dateString.number = numberProductText -> text();

                                my_CXPOH.CXPOH_Write(dateString);

                                //отправляем dat  mClas -> function(dat);
                                //отправляем vectorEdit[0], vectorEdit[1], vectorEdit[2] QString
                                //отпарвляем numberProductText -> text() QString
                               datamanager -> AddDataHead(numberProductText -> text().toStdString(), pStrEdit.toStdString());
                               Event_BUS::getInstance() -> SendEvent("SaveData", 110, ReadID());
    #ifdef _TRANSLATE
                               if(KPA_Rocket::flag)
                                   writeLogFile_EN(pStrEdit);
                               else
                                   writeLogFile_RU(pStrEdit);

    #else
                                writeLogFile_RU(pStrEdit);
    #endif
                            }
                            else
                            {
                                errorCom(ERROR_WRITE_SERIAL);
                            }
#ifdef NORESULTSAVE
                        }
#endif
                    }

                }
            }
            else
            {
                if (!saveFlag.flagError)
                {
                    QString pStrEdit;
                    pStrEdit = vectorEdit[0] + serial_number_2 -> text() + vectorEdit[1] + serial_number_4 -> text() + vectorEdit[2];
                    if (pStrEdit.length() == 8)
                    {
                        QDateTime dat;
                        dat = QDateTime::currentDateTime();

                        dateString.data = dat;
                        dateString.serial = pStrEdit;
                        dateString.number = numberProductText -> text();

                        my_CXPOH.CXPOH_Write(dateString);


                        //отправляем dat  mClas -> function(dat);
                        //отправляем vectorEdit[0], vectorEdit[1], vectorEdit[2] QString
                        //отпарвляем numberProductText -> text() QString
                        datamanager -> AddDataHead(numberProductText -> text().toStdString(), pStrEdit.toStdString());
                        Event_BUS::getInstance() -> SendEvent("SaveData", 110, ReadID());

#ifdef _TRANSLATE
                       if(KPA_Rocket::flag)
                           writeLogFile_EN(pStrEdit);
                       else
                           writeLogFile_RU(pStrEdit);

#else
                        writeLogFile_RU(pStrEdit);
#endif
                    }
                    else
                    {
                        errorCom(ERROR_WRITE_SERIAL);
                    }
                }
                else
                {
                    saveAsFile();
                }
            }
        }
        else
        {
            if (!saveFlag.flagError)
            {
                QString pStrEdit,pStrEdit1;
                pStrEdit = vectorEdit[0] + serial_number_2 -> text() + vectorEdit[1] + serial_number_4 -> text() + vectorEdit[2];
                pStrEdit1 = numberProductText -> text();
                if (pStrEdit.length() == 8)
                {
                    if (pStrEdit1.length() == 0)
                    {
                        errorCom(ERROR_WRITE_NUMBER);
                    }
                    else
                    {
                        QDateTime dat;
                        dat = QDateTime::currentDateTime();

                        dateString.data = dat;
                        dateString.serial = pStrEdit;
                        dateString.number = numberProductText -> text();
                        //cxronWriteSignal(dateString);
                        my_CXPOH.CXPOH_Write(dateString);

                        //отправляем dat  mClas -> function(dat);
                        //отправляем vectorEdit[0], vectorEdit[1], vectorEdit[2] QString
                        //отпарвляем numberProductText -> text() QString

                        datamanager -> AddDataHead(numberProductText -> text().toStdString(), pStrEdit.toStdString());
                        Event_BUS::getInstance() -> SendEvent("SaveData", 110, ReadID());
    #ifdef _TRANSLATE
                           if(KPA_Rocket::flag)
                               writeLogFile_EN(pStrEdit);
                           else
                               writeLogFile_RU(pStrEdit);

    #else
                            writeLogFile_RU(pStrEdit);
    #endif
                    }
                }
                else
                {
                    errorCom(ERROR_WRITE_SERIAL);
                }
            }
            else
            {
                QString pStrEdit;
                pStrEdit = vectorEdit[0] + serial_number_2 -> text() + vectorEdit[1] + serial_number_4 -> text() + vectorEdit[2];
                if (pStrEdit.length() == 8)
                {
                    QDateTime dat;
                    dat = QDateTime::currentDateTime();

                    dateString.data = dat;
                    dateString.serial = pStrEdit;
                    dateString.number = numberProductText -> text();
                    //cxronWriteSignal(dateString);
                    my_CXPOH.CXPOH_Write(dateString);

                    //отправляем dat  mClas -> function(dat);
                    //отправляем vectorEdit[0], vectorEdit[1], vectorEdit[2] QString
                    //отпарвляем numberProductText -> text() QString
                    datamanager -> AddDataHead(numberProductText -> text().toStdString(), pStrEdit.toStdString());
                    Event_BUS::getInstance() -> SendEvent("SaveData", 110, ReadID());

#ifdef _TRANSLATE
                       if(KPA_Rocket::flag)
                           writeLogFile_EN(pStrEdit);
                       else
                           writeLogFile_RU(pStrEdit);

#else
                        writeLogFile_RU(pStrEdit);
#endif
                }
                else
                {
                    errorCom(ERROR_WRITE_SERIAL);
                }
            }
        }
    }
    else
    {
        errorCom(COM_PORT_ERROR_OPEN_COM);
    }
#else
    QString pStrEdit, pStrEdit1;
    pStrEdit = vectorEdit[0] + serial_number_2 -> text() + vectorEdit[1] + serial_number_4 -> text() + vectorEdit[2];
    pStrEdit1 = numberProductText -> text();

    QDateTime dat;
    dat = QDateTime::currentDateTime();

    if (pStrEdit.length() == 8) saveFlag.flagSerial = true;
    else saveFlag.flagSerial = false;

    if (pStrEdit1.length() != 0) saveFlag.flagNumber = true;
    else saveFlag.flagNumber = false;

    if ((saveFlag.flagComSave) and (saveFlag.flagResult)
         and (saveFlag.flagNumber) and (saveFlag.flagSerial))
    {
        if (saveFlag.flagDir)
        {
            dateString.data = dat;
            dateString.serial = pStrEdit;
            dateString.number = numberProductText -> text();
            my_CXPOH.CXPOH_Write(dateString);
#ifdef _TRANSLATE
            if(KPA_Rocket::flag) writeLogFile_EN(pStrEdit);
            else writeLogFile_RU(pStrEdit);
#else
            writeLogFile_RU(pStrEdit);
#endif
            datamanager -> AddDataHead(numberProductText -> text().toStdString(), pStrEdit.toStdString());
            Event_BUS::getInstance() -> SendEvent("SaveData", 110, ReadID());
        }
        else
        {
            saveAsFile();
        }
    }
    else
    {
        if (!saveFlag.flagComSave) errorCom(COM_PORT_ERROR_OPEN_COM);
        else if (!saveFlag.flagSerial) errorCom(ERROR_WRITE_SERIAL);
        else if (!saveFlag.flagNumber) errorCom(ERROR_WRITE_NUMBER);
        else if (!saveFlag.flagResult)
        {
            errorCom(ERROR_RESULT);
            saveFlag.flagResult = false;
        }
    }
#endif
}

void MainWindow::saveAsFile()
{
#ifdef FILEDELETE
    flagAs = true;
#endif

#ifndef NORESULTSAVE
    if (saveFlag.flagComSave)
    {

        QString pStrEdit, pStrEdit1;
        pStrEdit1 = numberProductText->text();
        pStrEdit = vectorEdit[0] + serial_number_2 -> text() + vectorEdit[1] + serial_number_4 -> text() + vectorEdit[2];
        if (pStrEdit.length() == 8)
        {
            if (pStrEdit1.length() == 0)
            {
                errorCom(ERROR_WRITE_NUMBER);
            }
            else
            {
#ifdef NORESULTSAVE
                if(saveFlag.flagResult)
                {
                    errorCom(ERROR_RESULT);
                    saveFlag.flagResult = true;
                }
                else
                {
#endif
                    pStrEdit1.clear();
                    strFile = strFileAs;
                    strFileAs = QFileDialog::getSaveFileName(this, "save", QDir::currentPath(), "*.txt");

                    QDateTime dat;
                    dat = QDateTime::currentDateTime();

                    dateString.data = dat;
                    dateString.serial = pStrEdit;
                    dateString.number = numberProductText -> text();
                    my_CXPOH.CXPOH_Write(dateString);

                    if (strFileAs.size() > 0)
                    {

    #ifdef _TRANSLATE
                        if(KPA_Rocket::flag)
                            writeLogFile_EN(pStrEdit);
                        else
                            writeLogFile_RU(pStrEdit);
    #else
                        writeLogFile_RU(pStrEdit);
    #endif
                        datamanager -> AddDataHead(numberProductText -> text().toStdString(), pStrEdit.toStdString());
                        Event_BUS::getInstance() -> SendEvent("SaveData", 110, ReadID());


                        saveFlag.flagDir = true;
                        saveFlag.flagError = false;
                        saveFlag.flagWriteSave = false;
                    }
                    else
                    {
                        if (!saveFlag.flagWriteSave)
                        {
                            strFileAs = strFile;
                        }
                        saveFlag.flagError = true;
                    }
#ifdef NORESULTSAVE
                }
#endif
            }
        }
        else
        {
            errorCom(ERROR_WRITE_SERIAL);
        }
    }
    else
    {
        errorCom(COM_PORT_ERROR_OPEN_COM);
    }

#else
    QString pStrEdit, pStrEdit1;
    pStrEdit = vectorEdit[0] + serial_number_2 -> text() + vectorEdit[1] + serial_number_4 -> text() + vectorEdit[2];
    pStrEdit1 = numberProductText -> text();

    if (pStrEdit.length() == 8) saveFlag.flagSerial = true;
    else saveFlag.flagSerial = false;

    if (pStrEdit1.length() != 0) saveFlag.flagNumber = true;
    else saveFlag.flagNumber = false;


    if ((saveFlag.flagComSave) and (saveFlag.flagResult)
         and (saveFlag.flagNumber) and (saveFlag.flagSerial))
    {
        pStrEdit1.clear();
        strFile = strFileAs;

        QDateTime dat;
        dat = QDateTime::currentDateTime();
        strFileAs = QFileDialog::getSaveFileName(this, "save", QDir::currentPath(), "*.txt");
        dateString.data = dat;
        dateString.serial = pStrEdit;
        dateString.number = numberProductText -> text();
        my_CXPOH.CXPOH_Write(dateString);

        if (strFileAs.size() > 0)
        {            
            if(!strFileAs.endsWith(QString(".txt")))
                strFileAs += ".txt";

#ifdef _TRANSLATE
            if(KPA_Rocket::flag) writeLogFile_EN(pStrEdit);
            else writeLogFile_RU(pStrEdit);
#else
            writeLogFile_RU(pStrEdit);
#endif
            datamanager -> AddDataHead(numberProductText -> text().toStdString(), pStrEdit.toStdString());
            Event_BUS::getInstance() -> SendEvent("SaveData", 110, ReadID());

            saveFlag.flagDir = true;
        }
        else
        {
            errorCom(ERROR_NO_CHANGE_FILE);
            saveFlag.flagDir = false;
        }
    }
    else
    {
        if (!saveFlag.flagComSave) errorCom(COM_PORT_ERROR_OPEN_COM);
        else if (!saveFlag.flagSerial) errorCom(ERROR_WRITE_SERIAL);
        else if (!saveFlag.flagNumber) errorCom(ERROR_WRITE_NUMBER);
        else if (!saveFlag.flagResult)
        {
            errorCom(ERROR_RESULT);
            saveFlag.flagResult = false;
        }
    }
#endif
}

void MainWindow::updateDate()
{
   // ui -> logWidget ->clear();
#ifdef DISABLEDEDIT
    ui -> pushButton_b -> setEnabled(true);
    ui -> pushButton_g -> setEnabled(true);
    ui -> pushButton_t -> setEnabled(true);
    ui -> pushButton_z -> setEnabled(true);
    connectComButton -> setEnabled(true);
    saveButton -> setEnabled(true);
    saveAsButton -> setEnabled(true);
    updateButton -> setEnabled(true);
    helpButton -> setEnabled(true);
    russionButton -> setEnabled(true);
    englishButton -> setEnabled(true);
    tableButton -> setEnabled(true);

    ui ->centralWidget->setEnabled(true);


    numberProductText -> setEnabled(true);
    serial_number_1 -> setEnabled(true);
    serial_number_3 -> setEnabled(true);
    serial_number_5 -> setEnabled(true);
#endif

#ifdef NORESULTSAVE
    saveFlag.flagNumber = false;
    saveFlag.flagSerial = false;
    saveFlag.flagResult = false;
    saveFlag.flagError = false;
#endif

#ifdef ERRORTEXT
    errorText = true;
#endif

    productText -> setText("");
    serialProductText -> setText("");

    serial_number_1 -> setText("");
    serial_number_2 -> setText("-");
    serial_number_3 -> setText("");
    serial_number_4 -> setText("-");
    serial_number_5 -> setText("");

    numberProductText -> setText("");
    resulControlText -> setText("");
    numberCheckText -> setText("");
    measureDateText -> setText("");
    permisionDateText -> setText("");

    updateDateSignal();

    QVector<QString> pStrVector;
    pStrVector.resize(5);
    pStrVector[0] = "";
    pStrVector[1] = "";
    pStrVector[2] = "";
    pStrVector[3] = "";
    pStrVector[4] = "";
    dateRocket(pStrVector);

    serialProductText -> setFocus();
    Event_BUS::getInstance() -> SendEvent("ClearData", 110, ReadID());
    Event_BUS::getInstance() -> SendEvent((char *) "ClearFlags", 100, ReadID());
}

void MainWindow::help()
{
#ifdef LOG
    qDebug() << (tr("help"));
#endif

    QDesktopServices::openUrl(QUrl("help.docx"));
    //mysql_win.show();
}

void MainWindow::hideWindow()
{
#ifdef LOG
   qDebug()<<"hide window";
#endif
   flagHide = true;
   hide();
}

void MainWindow::exitMessageSustem(bool pFlag)
{
    if (pFlag)
        QApplication::exit(149);
    else
    {
        mMessageSave -> hide();

        flagHideWindow.flagMessageHide = false;

        this->show();
        updateDate();
    }
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
        case QSystemTrayIcon::Trigger:
            if(flagHide)
            {
                if(!this->isVisible())
                {
                    this->show();
                    flagHide = false;
                }
                else
                {
                    this->hide();
                }
            }
        break;

        default:
        break;
    }
}

void MainWindow::dateRocket(QVector<QString> pVector)
{
        strVector.resize(5);
        strVector[0] = pVector.at(0);
        strVector[1] = pVector.at(1);
        strVector[2] = pVector.at(2);
        strVector[3] = pVector.at(3);
        strVector[4] = pVector.at(4);

#ifdef ERRORTEXT
        if (errorText)
        {
            if ((strVector[1] == FLAG1) or (strVector[1] == FLAG2))
            {
                numberCheckLabel -> show();
                measureDateLabel -> show();
                permisionDateLabel -> show();
                numberCheckText -> show();
                measureDateText -> show();
                permisionDateText -> show();
            }
            else
            {
                numberCheckLabel -> hide();
                measureDateLabel -> hide();
                permisionDateLabel -> hide();
                numberCheckText -> hide();
                measureDateText -> hide();
                permisionDateText -> hide();
            }

            productText -> setText(strVector[0]);
            resulControlText -> setText(strVector[1]);
            numberCheckText -> setText(strVector[2]);
            measureDateText -> setText(strVector[3]);
            permisionDateText -> setText(strVector[4]);
        }
        else
        {
            saveFlag.flagResult = false;
        }
#else
        if ((strVector[1] == FLAG1) or (strVector[1] == FLAG2))
        {


            numberCheckLabel -> show();
            measureDateLabel -> show();
            permisionDateLabel -> show();
            numberCheckText -> show();
            measureDateText -> show();
            permisionDateText -> show();
        }
        else
        {
            numberCheckLabel -> hide();
            measureDateLabel -> hide();
            permisionDateLabel -> hide();
            numberCheckText -> hide();
            measureDateText -> hide();
            permisionDateText -> hide();
        }

        productText -> setText(strVector[0]);
        resulControlText -> setText(strVector[1]);
        numberCheckText -> setText(strVector[2]);
        measureDateText -> setText(strVector[3]);
        permisionDateText -> setText(strVector[4]);
#endif
}

void MainWindow::comOpen()
{
    flagCom = true;
#ifdef DISPLAY
    displayButton(connectComButton, 8, 10*mashtabX, 80*mashtabY, 80*mashtabX, 50*mashtabY, ":/new/prefix1/images/COM_CONNECT.png");
#else
    displayButton(connectComButton, 8, 10,  80, 80, 50, ":/new/prefix1/images/COM_CONNECT.png");
#endif
    saveFlag.flagComSave = true;
#ifdef LOG
    qDebug() << "Com open";
#endif
}

void MainWindow::handleTimeout()
{
    readDataSignal();
}

void MainWindow::choose_Port(QList<QSerialPortInfo> *list_info)
{
    mComPort -> comKol(list_info);
#ifdef DISPLAY
    mComPort -> move(300*mashtabX, 300*mashtabY);
#else
    mComPort -> move(300,300);
#endif
    mComPort -> show();
}

void MainWindow::errorCom(int pError)
{
#ifdef FILEDELETE
    ui -> pushButton_b -> setEnabled(false);
    ui -> pushButton_g -> setEnabled(false);
    ui -> pushButton_t -> setEnabled(false);
    ui -> pushButton_z -> setEnabled(false);
    connectComButton -> setEnabled(false);
    saveButton -> setEnabled(false);
    saveAsButton -> setEnabled(false);
    updateButton -> setEnabled(false);
    helpButton -> setEnabled(false);
    russionButton -> setEnabled(false);
    englishButton -> setEnabled(false);
    tableButton -> setEnabled(false);

    serial_number_1 -> setEnabled(false);
    serial_number_3 -> setEnabled(false);
    serial_number_5 -> setEnabled(false);
    numberProductText -> setEnabled(false);
    ui ->centralWidget->setEnabled(false);

#endif

#ifdef DISPLAY
    mMessageSave -> move (300*mashtabX, 200*mashtabY);
#else
    mMessageSave -> move(300, 200);
#endif
#ifdef ERRORTEXT
    errorText = false;
#endif

    switch (pError)
    {
        case COM_PORT_ERROR_NO_COM_PORT:
            mMessageSave -> hiddingButton(pError);
        break;

        case COM_PORT_ERROR_SET_BAUD:
            mMessageSave -> hiddingButton(pError);
        break;

        case COM_PORT_ERROR_SET_DATABIT:
            mMessageSave -> hiddingButton(pError);
        break;

        case COM_PORT_ERROR_SET_PARITY:
            mMessageSave -> hiddingButton(pError);
        break;

        case COM_PORT_ERROR_OPEN_COM:
            mMessageSave -> hiddingButton(pError);
        break;

        case COM_PORT_ERROR_BAD_PATH_TO_COM:
            mMessageSave -> hiddingButton(pError);
        break;

        case COM_PORT_ERROR_WRITE_DATA:
            mMessageSave -> hiddingButton(pError);
        break;

        case COM_PORT_ERROR_DISCONECTED:
            mMessageSave -> hiddingButton(pError);
            Event_BUS::getInstance() -> SendEvent((char *) "ClearData", 110, ReadID());
            //portCom_closed();
        break;

        case COM_PORT_ERROR_CRC8:
            mMessageSave -> hiddingButton(pError);
            //portCom_closed();
            comCloseSignal();
            Event_BUS::getInstance() -> SendEvent((char *) "ClearData", 110, ReadID());
        break;

        case ERROR_WRITE_SERIAL:
            mMessageSave -> hiddingButton(pError);
        break;

        case ERROR_NO_CHANGE_FILE:
            mMessageSave -> hiddingButton(pError);
        break;

        case ERROR_PORT_OPEN:
            mMessageSave -> hiddingButton(pError);
            portCom_closed();
        break;

        case ERROR_WRITE_NUMBER:
            mMessageSave -> hiddingButton(pError);
        break;

        case SQL_WINDOW_ERROR_OPENDB:
            mMessageSave -> hiddingButton(pError);
        break;

        case SQL_WINDOW_ERROR_OPENTABLE:
            mMessageSave -> hiddingButton(pError);
        break;

        case SQL_WINDOW_ERROR_TIMEOUT_DATA:
            mMessageSave -> hiddingButton(pError);
        break;

        case ERROR_ROCKET:
            mMessageSave ->hiddingButton(pError);
            comCloseSignal();
            Event_BUS::getInstance() -> SendEvent((char *) "ClearData", 110, ReadID());
        break;

        case ERROR_RESULT:
            mMessageSave -> hiddingButton(pError);
        break;
#ifdef ERROR_READ_FILE
        case ERROR_READ_FILE:
            mMessageSave -> hiddingButton(pError);
        break;
#endif

#ifdef FILEDELETE
        case ERROR_DELETE_FILE:
            mMessageSave -> hiddingButton(pError);
        break;
#endif
    }

    mMessageSave -> show();

    flagHideWindow.flagMessageHide = true;
}

void MainWindow::testIndexCom(int id)
{
    comOpenIdSignal(id);
    mComPort -> close();
}

void MainWindow::errorRocket(int pError)
{
#ifdef DISPLAY
    mMessageSave -> move (300*mashtabX, 200*mashtabY);
#else
    mMessageSave -> move(300, 200);
#endif
    switch(pError)
    {
        case 0:
            mMessageSave -> hiddingButton(2);
        break;

        default:
            mMessageSave -> hiddingButton(3);
        break;

    }
}

void MainWindow::portCom_closed()
{
    flagCom=false;
#ifdef DISPLAY
    displayButton(connectComButton, 8, 10*mashtabX, 80*mashtabY, 80*mashtabX, 50*mashtabY, ":/new/prefix1/images/COM_DISCONNECT.png");
#else
    displayButton(connectComButton, 8, 10,  80, 80, 50, ":/new/prefix1/images/COM_DISCONNECT.png");
#endif
    saveFlag.flagComSave = false;
    hiding();
}
#ifdef FILEDELETE
void MainWindow::saveDataAs(QString pStr, QString pStrFile, int pNumber)
{
    if (pStrFile == NULL )
    {
        showing();
    }
    else
    {
        QFile file(pStrFile);

            if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
            {
                saveFlag.flagError = true;
                QTextStream out(&file);
                out << pStr +"\n";
                initialStruct(numberStruct, pStr, pNumber);
            }
            else
                if (file.open(QIODevice::ReadOnly))
                    errorCom(ERROR_READ_FILE);
        file.close();
    }
}
#endif

#ifdef TESTBUTTON
#ifdef _TRANSLATE
void MainWindow::englishClicked()
{
    KPA_Rocket::flag = true;

    appTranslator->load("QtLanguage_en");
    qApp->installTranslator(appTranslator);

    if (resulControlText -> text() == "БРАК")
            resulControlText ->setText("BRAK");
    else if (resulControlText -> text() == "ИСПРАВНО")
        resulControlText -> setText("GOOD");

    retranslateUi();
#ifdef LOG
    qDebug() << "English";
#endif
}

void MainWindow::russionClicked()
{
  KPA_Rocket::flag = false;

  appTranslator -> load("QtLanguage_ru");
  qApp -> installTranslator(appTranslator);

  if (resulControlText -> text() == "BRAK")
          resulControlText -> setText("БРАК");
  else if (resulControlText -> text() == "GOOD")
      resulControlText -> setText("ИСПРАВНО");

  retranslateUi();
#ifdef LOG
  qDebug() << "Russion";
#endif
}
#endif

void MainWindow::tableClicked()
{
    mysql_win.show();
}
#endif

void MainWindow::saveDataCom(QByteArray *pByte)
{
    kpa_testSignal(pByte);
    dateString.byte = *pByte;
    dateString.byte = *pByte;
    saveFlag.flagComSave = true;
}

void MainWindow::sizeEdit1(QString pStr)
{
    vectorEdit[0] = pStr;
    if (pStr.size() == 2)
        serial_number_3 -> setFocus();
}

void MainWindow::sizeEdit2(QString pStr)
{
    vectorEdit[1] = pStr;
    if (pStr.size() == 2)
        serial_number_5 -> setFocus();
}

void MainWindow::sizeEdit3(QString pStr)
{
    vectorEdit[2] = pStr;
    if (pStr.size() == 2)
        serial_number_1 -> setFocus();
}


void MainWindow::on_pushButton_t_clicked()
{
    QByteArray qb;
    flagWrite = true;
    ui -> logWidget -> clear();
    qb.resize(1);
    qb[0]='t';
    writeData(&qb);
}

void MainWindow::on_pushButton_b_clicked()
{

    QByteArray qb;
    qb.resize(1);
    qb[0]='b';
    writeData(&qb);
}

void MainWindow::on_pushButton_g_clicked()
{

    QByteArray qb;
    qb.resize(1);
    qb[0]='g';
    writeData(&qb);
}

void MainWindow::on_pushButton_z_clicked()
{
    QByteArray qb;
    qb.resize(1);
    qb[0]='z';
    writeData(&qb);
}

#ifdef _TRANSLATE
void MainWindow::retranslateUi()
{
    titleLabel -> setText(tr("Проверка изделия 9М311-1М"));
    serialProductLabel -> setText(tr("Серия изделия"));
    numberProductLabel -> setText(tr("Номер изделия"));
    resulControlLabel -> setText(tr("Результат проверки"));
    numberCheckLabel -> setText(tr("№ проверки"));
    measureDateLabel -> setText(tr("Измеренное значение"));
    permisionDateLabel -> setText(tr("Допустимое значение"));
    ui -> pushButton_t -> setText(tr("send_t"));
    ui -> pushButton_b -> setText(tr("send_b"));
    ui -> pushButton_g -> setText(tr("send_g"));
    ui -> pushButton_z -> setText(tr("send_z"));
    this -> setWindowTitle(tr("Проверка изделия 9М311-1М"));

    mMessageSave -> setWindowTitle(tr("Окно сообщений"));
    mMessageSave -> retranslateUi();

    mComPort -> setWindowTitle(tr("Меню COM"));
    mComPort -> retranslateUi();

    mysql_win.retranslateUi();

}
#endif

void MainWindow::updateDateSignal()
{
    Event_BUS::getInstance()-> SendEvent("Update", 0, ReadID());
}

void MainWindow::comOpenSignal()
{
    Event_BUS::getInstance() -> SendEvent("OpenCOM", 0, ReadID());
}

void MainWindow::comOpenIdSignal(int id)
{
    Event_BUS::getInstance() -> SendEvent("OpenCOMX", 0, ReadID(), id);
}

void MainWindow::comCloseSignal()
{
    Event_BUS::getInstance() -> SendEvent("ClosePort", 0, ReadID());
}

void MainWindow::cxronWriteSignal(Block4 pDate)
{
    Event_BUS::getInstance()-> SendEvent("Cxron_Write", 0, ReadID(),pDate);
}

void MainWindow::readDataSignal()
{
    Event_BUS::getInstance() -> SendEvent("Read_Data", 0, ReadID());
}

void MainWindow::kpa_testSignal(QByteArray *pByte)
{

    Event_BUS::getInstance() -> SendEvent("Kpa_Test", 0, ReadID(), pByte);
}

void MainWindow::writeData(QByteArray *pByte)
{

    Event_BUS::getInstance() -> SendEvent("WriteCOM", 0, ReadID(), (char*)pByte->toStdString().data(),pByte->size());
}
