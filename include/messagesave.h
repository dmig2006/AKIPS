#ifndef MESSAGESAVE_H
#define MESSAGESAVE_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QCloseEvent>

#include "kpa_rocket.h"
#include "ava_terminal.h"

#include "error.h"

#define TESTERROR

namespace Ui {
class MessageSave;
}

class MessageSave : public QDialog, public MDObject
{
    Q_OBJECT

public:
    explicit MessageSave(QWidget *parent = 0);
    ~MessageSave();
    void hiddingButton(int errorInt);
    void showingButton();

#ifdef _TRANSLATE
    void retranslateUi();
#endif

private:
    void displayMessageButton(QPushButton *pButton, int pFont,
                              int pX, int pY, int pX1, int pY1,
                              QString pString); //Отображение Кнопок

    void displayMessageLabel(QLabel *pLabel, int pFont,
                      int pX, int pY, int pX1, int pY1,
                      QString pString); //Отображение меток

    void initialMessage();//Инициализация окна сообщений

#ifdef DISPLAY
    void initialVarableMessage();
    float mashtabX;
    float mashtabY;
#endif


    Ui::MessageSave *ui;

    QPushButton *exitMessageButton, *cancelMessageButton;
    QLabel *messageLabel, *errorLabel1, *errorLabel2;

private slots:
    void exitMessage();
    void cancelMessage();



protected:
    void newExitSignal(bool pFlag);
    void closeEvent(QCloseEvent *event);

signals:
    void updateDateMainWindow();
};

#endif // MESSAGESAVE_H
