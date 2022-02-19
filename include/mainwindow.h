
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#define ADMINON

#define BUTTONFULL
#define DISABLEDEDIT
#define NORESULTSAVE
#define FIRSTWRITE
#define ERRORTEXT

#define STR_FLAG "Результат проверки: БРАК"
#define STR_FLAG1 "Result test: BRAK"
#define FLAG1 "БРАК"
#define FLAG2 "BRAK"

#define TESTBUTTON

#include <QMainWindow>
#include <QWidget>
#include <QLineEdit>
#include <QSystemTrayIcon>

#include <QKeyEvent>
#include <QCloseEvent>

#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QDesktopServices>
#include <QDateTime>
#include <QTime>
#include <QTimer>
#include <QListWidget>

#include <QDebug>
#include <QFile>
#include <sql_window.h>

#ifdef _TRANSLATE
    #include <QTranslator>
#endif

#include "error.h"
#include "ava_terminal.h"
#include "kpa_com.h"
#include "messagesave.h"
#include "comport.h"
#include "kpa_rocket.h"
#include "datamanager.h"
#include "ava_cxpoh.h"
#include "ava_sqlite.h"

namespace Ui {
class MainWindow;
}

struct Block1
{
    QString date;
    QString time;
    QString product;
    QString serialProduct;
    QString numberProduct;
    QString ResultControl;
    QString numberCheck;
    QString measureDate;
    QString permissionDate;
    QString defice;
};

struct Block2
{
    QString date;
    QString time;
    QString product;
    QString serialProduct;
    QString numberProduct;
    QString ResultControl;
    QString numberCheck;
    QString measureDate;
    QString permissionDate;
    QString defice;
};

struct Block3
{
    QString date;
    QString time;
    QString product;
    QString serialProduct;
    QString numberProduct;
    QString ResultControl;
    QString numberCheck;
    QString measureDate;
    QString permissionDate;
    QString defice;
};

struct FlagLog
{
    bool flagString1;
    bool flagString2;
    bool flagString3;
};

struct SaveStr
{
    bool flagComSave;//подключен ли СОМ
    bool flagDir;   //Определяет SaveAs или save при нажатии save
    bool flagWriteSave;//Dir faila
    bool flagError; //?
#ifdef NORESULTSAVE
    bool flagResult; //проверка на брак или исправно
    bool flagNumber; //Проверка ввода Номера
    bool flagSerial; //Проверка ввода серии
#endif
};

struct FlagHide
{
    bool flagComHide;
    bool flagSaveHide;
    bool flagSaveAsHide;
    bool flagHelpHide;
    bool flagMessageHide;
};

struct FlagTranslate
{
    bool flagTranslate;
};

class MainWindow : public QMainWindow, public MDObject
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent=0);

//    MainWindow();
    ~MainWindow();
    AVA_Terminal ava_t;
    KPA_COM *kpa_com = new KPA_COM(100,"KPA_COM");// = KPA_COM(100,"KPA_COM");
    KPA_Rocket *kpa_rocket = new KPA_Rocket(101,"KPA_ROCKET");
    DataManager *datamanager = new DataManager(110, "DataManager");
    ava_cxpoH my_CXPOH;
    AVA_SQLite *ava_sqlite = new AVA_SQLite(111,"AVA_SQLite");
    sql_window mysql_win;

    void writeText(bool pFlag);
    void saveDate(QString pStr, QString pStrFile, int pNumber);

// Cлоты
    void dateRocket(QVector<QString> pVector);
    void appendLog(QString pStr);
    static void appendLog(const char * data);
    void errorCom(int pError);
    void testIndexCom(int id);
    void choose_Port(QList<QSerialPortInfo> *list_info);
    void comOpen();
    void saveDataCom(QByteArray *pByte);
    void exitMessageSustem(bool pFlag);

private:
    void initial();
    void displayLabel(QLabel *pLabel, int pFont,
                      int pX, int pY, int pX1, int pY1,
                      QString pString); //Отображение меток
    void displayButton(QPushButton *pButton, int pFont,
                      int pX, int pY, int pX1, int pY1,
                      QString pString); //Отображение Кнопок
    void displayLineEdit(QLineEdit *pText, int pFont,
                         int pX, int pY, int pX1, int pY1,
                         QString pString); //Отображение Текста
    void vibor();
    void hiding();
    void showing();
    void initialStruct(int i, QString pStr, int pNumber);

    void writeHistory();
    void writeLog1();
    void writeLog2();
    void writeLog3();

    void exitSystem();
    void hideWindow();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void errorRocket(int pError);
    void portCom_closed();

#ifdef FILEDELETE
    void saveDataAs(QString pStr, QString pStrFile, int pNumber);
    bool flagAs = false;
#endif


    Ui::MainWindow *ui;

    static QListWidget *static_log;

    MessageSave *mMessageSave;
    ComPort *mComPort;

    QPushButton *connectComButton, *saveButton, *saveAsButton,
                *updateButton, *helpButton, *exitButton, *hideButton,
                *englishButton, *russionButton, *tableButton;

    QLabel      *serialProductLabel, *numberProductLabel, *resulControlLabel,
                *numberCheckLabel, *measureDateLabel, *permisionDateLabel,
                *titleLabel, *titlePictureLabel;

    QLineEdit   *serialProductText, *serial_number_1, *serial_number_2,
                *serial_number_3, *serial_number_4, *serial_number_5,
                *numberProductText, *resulControlText, *productText,
                *numberCheckText, *measureDateText, *permisionDateText;

    bool    flagHide, flagWrite, flagCom;
    int     numberStruct;
    QTimer m_timer;
    QValidator *validator, *validator1;
    QVector<QString> strVector, vectorEdit;
#ifdef FIRSTWRITE
    QString strDateWrite;
#endif
    QString strDate, date;
    QString strFile,strFileAs;
    FlagLog flagString;
    SaveStr saveFlag;
    FlagHide flagHideWindow;

#ifdef ERRORTEXT
    bool errorText;
#endif

    Block1 blockString1;
    Block2 blockString2;
    Block3 blockString3;
    Block4 dateString;

#ifdef _TRANSLATE
    QTranslator *appTranslator;
    QTranslator *qtTranslator;
    void retranslateUi();
    void writeLogFile_RU(QString pStr);
    void writeLogFile_EN(QString pStr);
#else
    void writeLogFile_RU(QString pStr);
#endif

#ifdef DISABLEDEDIT
    void disEdit();
#endif

#ifdef DISPLAY
    float mashtabX;
    float mashtabY;
    void initialVarable();
#endif

protected:
    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);
    void changeEvent(QEvent *event);

//Сигналы
    void updateDateSignal();
    void comOpenSignal();
    void comOpenIdSignal(int id);
    void comCloseSignal();
    void cxronWriteSignal(Block4 pDate);
    void readDataSignal();
    void kpa_testSignal(QByteArray *pByte);
    void writeData(QByteArray *pByte);

private slots:
    void portCom();
    void saveFile();
    void saveAsFile();
    void help();
    void updateDate();

#ifdef TESTBUTTON
    void englishClicked();
    void russionClicked();
    void tableClicked();
#endif

    void sizeEdit1(QString pStr);
    void sizeEdit2(QString pStr);
    void sizeEdit3(QString pStr);

    void on_pushButton_t_clicked();
    void on_pushButton_b_clicked();
    void on_pushButton_g_clicked();
    void on_pushButton_z_clicked();

public slots:
    void handleTimeout();//Avatara ADD
};

#endif // MAINWINDOW_H
