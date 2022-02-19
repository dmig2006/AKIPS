#include "comport.h"
#include "ui_comport.h"

ComPort::ComPort(QWidget *parent) :
    QDialog(parent), MDObject(106,"ComGui"),
    ui(new Ui::ComPort)
{
    ui -> setupUi(this);
#ifdef DISPLAY
    initialVarableCom();
#endif

    flagIndex = false;
    numberIndex = 0;

    textComLabel = new QLabel(this);
    enterComButton = new QPushButton(this);
    cancelComButton = new QPushButton(this);

    numberCOM = new QComboBox(this);

    connect(numberCOM, SIGNAL(activated(int)), this, SLOT(index(int)));
    connect(enterComButton, SIGNAL(clicked()), this, SLOT(emitIndex()));
    connect(cancelComButton, SIGNAL(clicked()), this, SLOT(close()));

    initialCom();

    char c;
    c = ADDEvent("ComOpenId");

#ifdef _TRANSLATE
    retranslateUi();
#endif
}

ComPort::~ComPort()
{
    delete numberCOM;
    delete cancelComButton;
    delete enterComButton;
    delete textComLabel;
    delete ui;
}

void ComPort::comKol(QList<QSerialPortInfo> *pList_info)
{
    int i = 0;
#ifdef DISPLAY
    numberCOM -> setGeometry(75*mashtabX,100*mashtabY,100*mashtabX,40*mashtabY);
#endif
    int size_list=pList_info->size();
    i=0;
    numberCOM->clear();
    while(i<size_list)
    {

        numberCOM->addItem(pList_info->at(i).portName(),i);
        i++;
    }

    numberCOM -> show();
}

void ComPort::testCom(int p)
{
    int i = 0;
#ifdef DISPLAY
    numberCOM -> setGeometry(75*mashtabX,100*mashtabY,100*mashtabX,40*mashtabY);
#endif
    while(i<p)
    {
        numberCOM->addItem(QString::number(i));
        i++;
    }
}

#ifdef _TRANSLATE
void ComPort::retranslateUi()
{
    textComLabel -> setText(tr("Выберите СОМ порт"));
    enterComButton -> setText(tr("ОК"));
    cancelComButton -> setText(tr("Отмена"));
}
#endif
void ComPort::displayComButton(QPushButton *pButton, int pFont, int pX, int pY, int pX1, int pY1, QString pString)
{
    QFont font;
    font.setPointSize(pFont);
    pButton -> setGeometry(pX, pY, pX1, pY1);
    pButton -> setFont(font);
    pButton -> setText(pString);
}

void ComPort::displayComLabel(QLabel *pLabel, int pFont, int pX, int pY, int pX1, int pY1, QString pString)
{
    QFont font;
    font.setPointSize(pFont);
    pLabel -> setGeometry(pX, pY, pX1, pY1);
    pLabel -> setFont(font);
    pLabel -> setText(pString);
}

void ComPort::initialCom()
{
#ifdef DISPLAY
    mashtabX = float(WIDTH / 1024.0f);
    mashtabY = float(HEIGHT / 768.0f);

    displayComLabel(textComLabel, 14, 10*mashtabX, 10*mashtabY, 200*mashtabX, 40*mashtabY, "Выберите СОМ порт");
    displayComButton(enterComButton, 14, 10*mashtabX, 200*mashtabY, 100*mashtabX, 50*mashtabY, "ОК");
    displayComButton(cancelComButton, 14, 130*mashtabX, 200*mashtabY, 100*mashtabX, 50*mashtabY, "Отмена" );
#else
    displayComLabel(textComLabel, 14, 10, 10, 200, 40, "Выберите СОМ порт");
    displayComButton(enterComButton, 14, 10, 200, 100, 50, "ОК");
    displayComButton(cancelComButton, 14, 130, 200, 100, 50, "Отмена" );
#endif
}
#ifdef DISPLAY
void ComPort::initialVarableCom()
{
    mashtabX = 0.0f;
    mashtabY = 0.0f;
}
#endif
void ComPort::index(int p)
{
    numberIndex = p;
    flagIndex = true;
}

void ComPort::emitIndex()
{
    if (flagIndex)
    {
        flagIndex = false;
        comOpen(numberIndex);
        numberCOM -> clear();
        this -> hide();
        Event_BUS::getInstance() -> SendEvent("StartThread", 100, ReadID());

    }
#ifdef LOG
    else
        qDebug() << "Выберите COM";
#endif

}

void ComPort::comOpen(int pInt)
{
    Event_BUS::getInstance() -> SendEvent("OpenCOMX", 0, ReadID(), pInt);
}
