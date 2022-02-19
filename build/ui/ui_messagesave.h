/********************************************************************************
** Form generated from reading UI file 'messagesave.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSAGESAVE_H
#define UI_MESSAGESAVE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_MessageSave
{
public:

    void setupUi(QDialog *MessageSave)
    {
        if (MessageSave->objectName().isEmpty())
            MessageSave->setObjectName(QStringLiteral("MessageSave"));
        MessageSave->resize(395, 300);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MessageSave->sizePolicy().hasHeightForWidth());
        MessageSave->setSizePolicy(sizePolicy);
        MessageSave->setMinimumSize(QSize(0, 0));
        MessageSave->setMaximumSize(QSize(16777215, 16777215));

        retranslateUi(MessageSave);

        QMetaObject::connectSlotsByName(MessageSave);
    } // setupUi

    void retranslateUi(QDialog *MessageSave)
    {
        MessageSave->setWindowTitle(QApplication::translate("MessageSave", "\320\234\320\265\320\275\321\216 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\271", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MessageSave: public Ui_MessageSave {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSAGESAVE_H
