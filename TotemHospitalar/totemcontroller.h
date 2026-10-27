#ifndef TOTEMCONTROLLER_H
#define TOTEMCONTROLLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class TotemController : public QObject
{
    Q_OBJECT
public:
    explicit TotemController(QObject *parent = nullptr);


    Q_INVOKABLE void printTicket(const QString &tipoSenha);

    Q_INVOKABLE void solicitarSenha(const QString &tipoSenha);

private:
    // Função para verificar se a impressora existe no Spooler do Windows
    bool checkPrinterExists(const QString &printerName);

private:
    QNetworkAccessManager *networkManager; // requisição http

private slots:
    void onRespostaApiRecebida(QNetworkReply *reply);
};

#endif // TOTEMCONTROLLER_H