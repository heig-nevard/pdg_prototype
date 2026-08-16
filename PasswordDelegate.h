#ifndef PASSWORDDELEGATE_H
#define PASSWORDDELEGATE_H

#include <QStyledItemDelegate>

class PasswordDelegate : public QStyledItemDelegate
{
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    QString displayText(const QVariant &value,
                        const QLocale &locale) const override
    {
        Q_UNUSED(locale);

        const QString password = value.toString();
        return QString(16, QChar(u'•'));
    }
};

#endif // PASSWORDDELEGATE_H
