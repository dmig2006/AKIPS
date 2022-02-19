/********************************************************************************
** Form generated from reading UI file 'comport.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPORT_H
#define UI_COMPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_ComPort
{
public:

    void setupUi(QDialog *ComPort)
    {
        if (ComPort->objectName().isEmpty())
            ComPort->setObjectName(QStringLiteral("ComPort"));
        ComPort->resize(400, 300);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ComPort->sizePolicy().hasHeightForWidth());
        ComPort->setSizePolicy(sizePolicy);
        ComPort->setMinimumSize(QSize(400, 300));
        ComPort->setMaximumSize(QSize(400, 300));

        retranslateUi(ComPort);

        QMetaObject::connectSlotsByName(ComPort);
    } // setupUi

    void retranslateUi(QDialog *ComPort)
    {
        ComPort->setWindowTitle(QApplication::translate("ComPort", "\320\234\320\265\320\275\321\216 COM", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ComPort: public Ui_ComPort {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMPORT_H
