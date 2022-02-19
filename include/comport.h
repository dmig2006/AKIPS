#ifndef COMPORT_H
#define COMPORT_H

#include <QDialog>

#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QtSerialPort/QSerialPortInfo>
#include <QList>
#include <QDebug>

#include "ava_terminal.h"
#include "kpa_rocket.h"
#include "error.h"

namespace Ui {
class ComPort;
}

class ComPort : public QDialog, public MDObject
{
    Q_OBJECT

public:
    explicit ComPort(QWidget *parent = 0);
    ~ComPort();
    void comKol(QList<QSerialPortInfo> *pList_info);
    void testCom(int p);
#ifdef _TRANSLATE
    void retranslateUi();
#endif
private:
    void displayComButton(QPushButton *pButton, int pFont,
                              int pX, int pY, int pX1, int pY1,
                              QString pString); //Отображение Кнопок

    void displayComLabel(QLabel *pLabel, int pFont,
                      int pX, int pY, int pX1, int pY1,
                      QString pString); //Отображение меток

    void initialCom();//Инициализация окна сообщений

    Ui::ComPort *ui;

    QPushButton *enterComButton, *cancelComButton, *menuComButton;
    QLabel *textComLabel;
    QComboBox *numberCOM;

#ifdef DISPLAY
    void initialVarableCom();
    float mashtabX;
    float mashtabY;
#endif

    bool flagIndex;
    int numberIndex;

protected:
    void comOpen(int pInt);


private slots:
    void index(int p);
    void emitIndex();

signals:
    void COM_Open(int pId);

};

#endif // COMPORT_H
