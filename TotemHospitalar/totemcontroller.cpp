#include "totemcontroller.h"
#include <QPrinter>
#include <QPrinterInfo>
#include <QPainter>
#include <QDateTime>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

TotemController::TotemController(QObject *parent) : QObject(parent) {

    networkManager = new QNetworkAccessManager(this);

    connect(networkManager, &QNetworkAccessManager::finished, this, &TotemController::onRespostaApiRecebida);
}

void TotemController::solicitarSenha(const QString &tipoSenha){
    QUrl url("http://localhost:5000/api/senhas");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["tipo"] = tipoSenha;
    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    qDebug() << "enviar requisição HTTP para API";
    networkManager->post(request, data);
}

void TotemController::onRespostaApiRecebida(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError){
        QByteArray responseData = reply->readAll();
        qDebug() << "Sucesso! Resposta da API:" << responseData;

        QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObject = jsonResponse.object();

        QString codigoGerado = jsonObject["codigo"].toString();

        if(!codigoGerado.isEmpty()){
            printTicket(codigoGerado);
        }else{
            qWarning() << "A API não devolveu um código válido!" << reply->errorString();
        }

    }else{
        qDebug() << "Erro na comunicação com a API:" << reply->errorString();
    }
    reply->deleteLater();
}

bool TotemController::checkPrinterExists(const QString &printerName)
{
    QList<QPrinterInfo> availablePrinters = QPrinterInfo::availablePrinters();
    for (const QPrinterInfo &printer : availablePrinters) {
        if (printer.printerName().contains(printerName, Qt::CaseInsensitive)) {
            return true;
        }
    }
    return false;
}

void TotemController::printTicket(const QString &senha)
{
    // O nome da tua impressora instalada no Windows
    QString targetPrinterName = "POS58DD";

    qDebug() << "--- A processar impressão de senha ---";

    if (!checkPrinterExists(targetPrinterName)) {
        qWarning() << "ERRO: A impressora" << targetPrinterName << "não está instalada no Windows.";
        return;
    }

    // Configurar o papel e a impressora
    QPrinter printer(QPrinter::HighResolution);
    printer.setPrinterName(targetPrinterName);

    // Papel térmico de 58mm
    QPageSize pageSize(QSizeF(48.0, 100.0), QPageSize::Millimeter);
    printer.setPageSize(pageSize);
    printer.setPageMargins(QMarginsF(0, 0, 0, 0), QPageLayout::Millimeter);

    // Iniciar o Pincel
    QPainter painter;
    if (!painter.begin(&printer)) {
        qWarning() << "ERRO: Falha ao desenhar na impressora.";
        return;
    }

    // Desenhar o Talão
    int yPos = 50;
    int margemEsquerda = 10;
    int larguraMax = printer.pageLayout().paintRectPixels(printer.resolution()).width();

    // Cabeçalho
    QFont fontTitulo("Arial", 14, QFont::Bold);
    painter.setFont(fontTitulo);
    painter.drawText(margemEsquerda, yPos, larguraMax, 100, Qt::AlignHCenter, "HOSPITAL CENTRAL");
    yPos += 150;

    QFont fontSub("Arial", 8, QFont::Normal);
    painter.setFont(fontSub);
    painter.drawText(margemEsquerda, yPos, larguraMax, 100, Qt::AlignHCenter, "Sistema de Triagem Inteligente");
    yPos += 150;

    painter.drawText(margemEsquerda, yPos, larguraMax, 100, Qt::AlignHCenter, "--------------------------");
    yPos += 150;

    // Tipo de Senha
    QFont fontSenha("Arial", 20, QFont::Bold);
    painter.setFont(fontSenha);
    painter.drawText(margemEsquerda, yPos, larguraMax, 150, Qt::AlignHCenter, senha);
    yPos += 200;

    painter.setFont(fontSub);
    painter.drawText(margemEsquerda, yPos, larguraMax, 100, Qt::AlignHCenter, "--------------------------");
    yPos += 150;

    // Rodapé
    painter.setFont(fontSub);
    painter.drawText(margemEsquerda, yPos, larguraMax, 100, Qt::AlignHCenter, "Aguarde ser chamado no painel.");

    painter.end();

    qDebug() << "-> senha impressa na POS58DD!";
}