#include "messagesave.h"
#include "ui_messagesave.h"

MessageSave::MessageSave(QWidget *parent) : QDialog(parent), MDObject(105,"MessageSave"),ui(new Ui::MessageSave)
{
    ui -> setupUi(this);

    setParent(parent);
#ifdef DISPLAY
    initialVarableMessage();
#endif
    exitMessageButton = new QPushButton(this);
    cancelMessageButton = new QPushButton(this);
    messageLabel = new QLabel(this);
    errorLabel1 = new QLabel(this);
    errorLabel2 = new QLabel(this);

    connect(exitMessageButton, SIGNAL(clicked()), this, SLOT(exitMessage()));
    connect(cancelMessageButton, SIGNAL(clicked()), this, SLOT(cancelMessage()));

    initialMessage();

    char ch;
    ch = ADDEvent("New_Exit");

    Event_BUS::getInstance() -> AddMDObject(this);

#ifdef _TRANSLATE
    retranslateUi();
#endif
}

MessageSave::~MessageSave()
{
    delete errorLabel2;
    delete errorLabel1;
    delete messageLabel;
    delete cancelMessageButton;
    delete exitMessageButton;

    delete ui;
}

void MessageSave::hiddingButton(int errorInt)
{
    messageLabel -> hide();
    cancelMessageButton -> hide();
    exitMessageButton -> hide();



    if(KPA_Rocket::flag)
    {
        switch (errorInt)
        {
#ifdef TESTERROR
            case COM_PORT_ERROR_NO_COM_PORT:
                errorLabel2 -> setText("No com port");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;

            case COM_PORT_ERROR_SET_BAUD:
                errorLabel2 -> setText("No connect COM");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;

            case COM_PORT_ERROR_SET_DATABIT:
                errorLabel2 -> setText("No connect COM");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;

            case COM_PORT_ERROR_SET_PARITY:
                errorLabel2 -> setText("No connect COM");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;

            case COM_PORT_ERROR_OPEN_COM:
                errorLabel2 -> setText("No connect COM");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;

            case COM_PORT_ERROR_BAD_PATH_TO_COM:
                errorLabel2 -> setText("No connect COM");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;

            case COM_PORT_ERROR_WRITE_DATA:
                errorLabel2 -> setText("Error write com");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;

            case COM_PORT_ERROR_DISCONECTED:
                errorLabel2 -> setText("COM port disconnected");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;

            case COM_PORT_ERROR_CRC8:
                errorLabel2 -> setText("error CRC");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;

            case ERROR_WRITE_SERIAL:
                errorLabel2 -> setText("write serial number");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;

            case ERROR_NO_CHANGE_FILE:
                errorLabel2 -> setText("Change file");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;

            case ERROR_PORT_OPEN:
                errorLabel2 -> setText("Port yge otkrit");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;

            case ERROR_WRITE_NUMBER:
                errorLabel2 -> setText("write number product");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;

            case SQL_WINDOW_ERROR_OPENDB:
                errorLabel2 -> setText("Error open db");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;

            case SQL_WINDOW_ERROR_OPENTABLE:
                errorLabel2 -> setText("Error open table");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;

            case SQL_WINDOW_ERROR_TIMEOUT_DATA:
                errorLabel2 -> setText("Error time read data");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;

            case ERROR_ROCKET:
                errorLabel2 -> setText("Error Rocket");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;

            case ERROR_RESULT:
                errorLabel2 -> setText("Not Result cControl");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;
#ifdef ERROR_READ_FILE
            case ERROR_READ_FILE:
                errorLabel2 -> setText("FILE NOT WRITE");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;
#endif

#ifdef FILEDELETE
            case ERROR_DELETE_FILE:
                errorLabel2 -> setText("FILE DELETE");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;
#endif

#else
            case 0:
                errorLabel2 -> setText("error COM");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;

            case 1:
                errorLabel2 -> setText("error CRC");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;

            case 2:
                errorLabel2 -> setText("error ????????????");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;

            case 3:
                errorLabel2 -> setText("not connect COM");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;

            case 4:
                errorLabel2 -> setText("write serial number");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;

            case 5:
                errorLabel2 -> setText("Change file");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;

            case 6:
                errorLabel2 -> setText("Port yge otkrit");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;

            case 10:
                errorLabel2 -> setText("COM port disconnected");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;
#endif

        }
    }
    else
    {
        switch (errorInt)
        {
#ifdef TESTERROR
        case COM_PORT_ERROR_NO_COM_PORT:
            errorLabel2 -> setText("?????? COM ??????????");
            errorLabel2 -> setAlignment(Qt::AlignCenter);
        break;

        case COM_PORT_ERROR_SET_BAUD:
            errorLabel2 -> setText("?????? ???????????????????? ?? COM");
            errorLabel2 -> setAlignment(Qt::AlignCenter);
        break;

        case COM_PORT_ERROR_SET_DATABIT:
            errorLabel2 -> setText("?????? ???????????????????? ?? COM");
            errorLabel2 -> setAlignment(Qt::AlignCenter);
        break;

        case COM_PORT_ERROR_SET_PARITY:
            errorLabel2 -> setText("?????? ???????????????????? ?? COM");
            errorLabel2 -> setAlignment(Qt::AlignCenter);
        break;

        case COM_PORT_ERROR_OPEN_COM:
            errorLabel2 -> setText("?????? ???????????????????? ?? COM");
            errorLabel2 -> setAlignment(Qt::AlignCenter);
        break;

        case COM_PORT_ERROR_BAD_PATH_TO_COM:
            errorLabel2 -> setText("?????? ???????????????????? ?? COM");
            errorLabel2 -> setAlignment(Qt::AlignCenter);
        break;

        case COM_PORT_ERROR_WRITE_DATA:
            errorLabel2 -> setText("???????????? ???????????? ?? COM");
            errorLabel2 -> setAlignment(Qt::AlignCenter);
        break;

        case COM_PORT_ERROR_DISCONECTED:
            errorLabel2 -> setText("COM ???????? ????????????????");
            errorLabel2 -> setAlignment(Qt::AlignCenter);
        break;

        case COM_PORT_ERROR_CRC8:
            errorLabel2 -> setText("???????????? CRC");
            errorLabel2 -> setAlignment(Qt::AlignCenter);
        break;

        case ERROR_WRITE_SERIAL:
            errorLabel2 -> setText("?????????????? ???????????????? ??????????");
            errorLabel2 -> setAlignment(Qt::AlignCenter);
        break;

        case ERROR_NO_CHANGE_FILE:
            errorLabel2 -> setText("???????????????? ????????");
            errorLabel2 -> setAlignment(Qt::AlignCenter);
        break;

        case ERROR_PORT_OPEN:
            errorLabel2 -> setText("???????? ?????? ????????????");
            errorLabel2 -> setAlignment(Qt::AlignCenter);
        break;

        case ERROR_WRITE_NUMBER:
            errorLabel2 -> setText("?????????????? ?????????? ??????????????");
            errorLabel2 -> setAlignment(Qt::AlignCenter);
        break;

        case SQL_WINDOW_ERROR_OPENDB:
            errorLabel2 -> setText("???????????????? ???????? ????????????");
            errorLabel2 -> setAlignment(Qt::AlignCenter);
        break;

        case SQL_WINDOW_ERROR_OPENTABLE:
            errorLabel2 -> setText("???????????????? ??????????????");
            errorLabel2 -> setAlignment(Qt::AlignCenter);
        break;

        case SQL_WINDOW_ERROR_TIMEOUT_DATA:
            errorLabel2 -> setText("?????????? ???????????????? ???????????? ????????????");
            errorLabel2 -> setAlignment(Qt::AlignCenter);
        break;

        case ERROR_ROCKET:
            errorLabel2 -> setText("???????????? ????????????");
            errorLabel2 -> setAlignment(Qt::AlignCenter);
        break;

        case ERROR_RESULT:
            errorLabel2 -> setText("?????? ???????????????????? ????????????????");
            errorLabel2 -> setAlignment(Qt::AlignCenter);
        break;
#ifdef ERROR_READ_FILE
        case ERROR_READ_FILE:
            errorLabel2 -> setText("???????? ???? ?????? ????????????");
            errorLabel2 -> setAlignment(Qt::AlignCenter);
        break;
#endif

#ifdef FILEDELETE
        case ERROR_DELETE_FILE:
            errorLabel2 -> setText("???????? ????????????");
            errorLabel2 -> setAlignment(Qt::AlignCenter);
        break;
#endif
#else
            case 0:
                errorLabel2 -> setText("???????????? COM");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;

            case 1:
                errorLabel2 -> setText("???????????? CRC");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;

            case 2:
                errorLabel2 -> setText("???????????? ????????????");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;

            case 3:
                errorLabel2 -> setText("?????? ???????????????????? COM");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;

            case 4:
                errorLabel2 -> setText("?????????????? ?????????????????? ??????????");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;

            case 5:
                errorLabel2 -> setText("???????????????? ????????");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;

            case 6:
                errorLabel2 -> setText("???????? ?????? ????????????");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;

            case 10:
                errorLabel2 -> setText("COM ???????? ????????????????");
                errorLabel2 -> setAlignment(Qt::AlignCenter);
            break;
#endif
        }
    }

    errorLabel1 -> setAlignment(Qt::AlignCenter);
    errorLabel1 -> setStyleSheet("color:#DC1727");
    errorLabel2 -> setStyleSheet("color:#DC1727");
    errorLabel1 -> show();

    errorLabel2 -> show();
}

void MessageSave::showingButton()
{
    messageLabel -> show();
    cancelMessageButton -> show();
    exitMessageButton -> show();
    errorLabel1 -> hide();
    errorLabel2 -> hide();
}

void MessageSave::displayMessageButton(QPushButton *pButton, int pFont, int pX, int pY, int pX1, int pY1, QString pString)
{
    QFont font;
    font.setPointSize(pFont);
    pButton -> setGeometry(pX, pY, pX1, pY1);
    pButton -> setFont(font);
    pButton -> setText(pString);
}

void MessageSave::displayMessageLabel(QLabel *pLabel, int pFont, int pX, int pY, int pX1, int pY1, QString pString)
{
    QFont font;
    font.setPointSize(pFont);
    pLabel -> setGeometry(pX, pY, pX1, pY1);
    pLabel -> setFont(font);
    pLabel -> setText(pString);
}

void MessageSave::initialMessage()
{
#ifdef DISPLAY
    mashtabX = float(WIDTH / 1024.0f);
    mashtabY = float(HEIGHT / 768.0f);

    displayMessageButton(exitMessageButton, 14, 10*mashtabX, 300*mashtabY, 150*mashtabX, 40*mashtabY, "????");
    displayMessageButton(cancelMessageButton, 14, 200*mashtabX, 300*mashtabY, 150*mashtabX, 40*mashtabY, "????????????");
    displayMessageLabel(messageLabel, 18, 0*mashtabX, 10*mashtabY, 400*mashtabX, 250*mashtabY, "???? ?????????????? ?????? ???????????? ??????????");
    displayMessageLabel(errorLabel1, 20, 0*mashtabX, 100*mashtabY, 400*mashtabX, 40*mashtabY, "????????????");
    displayMessageLabel(errorLabel2, 20, 0*mashtabX, 140*mashtabY, 400*mashtabX, 40*mashtabY, "???????????? com");
#else
    displayMessageButton(exitMessageButton, 14, 10, 300, 150, 40, "????");
    displayMessageButton(cancelMessageButton, 14, 200, 300, 150, 40, "????????????");
    displayMessageLabel(messageLabel, 18, 0, 10, 400, 250, "???? ?????????????? ?????? ???????????? ??????????");
    displayMessageLabel(errorLabel1, 20, 0, 100, 400, 40, "????????????");
    displayMessageLabel(errorLabel2, 20, 0, 140, 400, 40, "???????????? com");
#endif
    errorLabel1 -> hide();
    errorLabel2 -> hide();
}

#ifdef DISPLAY
void MessageSave::initialVarableMessage()
{
    mashtabX = 0.0f;
    mashtabY = 0.0f;
}
#endif

void MessageSave::exitMessage()
{
    newExitSignal(true);
}

void MessageSave::cancelMessage()
{
    newExitSignal(false);
}

void MessageSave::retranslateUi()
{
   exitMessageButton -> setText(tr("????"));
   cancelMessageButton -> setText(tr("????????????"));
   messageLabel -> setText(tr("???? ?????????????? ?????? ???????????? ??????????"));
   errorLabel1 -> setText(tr("????????????"));

   messageLabel ->setAlignment(Qt::AlignCenter);
}

void MessageSave::newExitSignal(bool pFlag)
{
    Event_BUS::getInstance() -> SendEvent("New_Exit", 0, ReadID(), pFlag);
}

void MessageSave::closeEvent(QCloseEvent *event)
{
    emit updateDateMainWindow();
    event->accept();
}
