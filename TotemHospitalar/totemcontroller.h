#ifndef TOTEMCONTROLLER_H
#define TOTEMCONTROLLER_H

#include <QObject>
#include <QString>

class TotemController : public QObject
{
    Q_OBJECT
public:
    explicit TotemController(QObject *parent = nullptr);

    // Método público chamado pelos botões do QML
    Q_INVOKABLE void printTicket(const QString &ticketType, const QString &cpf);

private:
    // Função para verificar se a impressora existe no Spooler do Windows
    bool checkPrinterExists(const QString &printerName);
};

#endif // TOTEMCONTROLLER_H