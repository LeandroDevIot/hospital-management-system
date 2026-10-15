#include "totemcontroller.h"
#include <QPrinter>
#include <QPrinterInfo>
#include <QPainter>
#include <QDateTime>
#include <QDebug>

TotemController::TotemController(QObject *parent) : QObject(parent) {}

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

void TotemController::printTicket(const QString &ticketType, const QString &cpf)
{
    // O nome da tua impressora instalada no Windows
    QString targetPrinterName = "POS58DD";

    qDebug() << "--- A processar impressão de senha ---";

    if (!checkPrinterExists(targetPrinterName)) {
        qWarning() << "ERRO: A impressora" << targetPrinterName << "não está instalada no Windows.";
        return;
    }

    // 1. Configurar o papel e a impressora
    QPrinter printer(QPrinter::HighResolution);
    printer.setPrinterName(targetPrinterName);

    // Papel térmico de 58mm
    QPageSize pageSize(QSizeF(48.0, 100.0), QPageSize::Millimeter);
    printer.setPageSize(pageSize);
    printer.setPageMargins(QMarginsF(0, 0, 0, 0), QPageLayout::Millimeter);

    // 2. Iniciar o Pincel
    QPainter painter;
    if (!painter.begin(&printer)) {
        qWarning() << "ERRO: Falha ao desenhar na impressora.";
        return;
    }

    // 3. Desenhar o Talão
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
    painter.drawText(margemEsquerda, yPos, larguraMax, 150, Qt::AlignHCenter, ticketType);
    yPos += 200;

    painter.setFont(fontSub);
    painter.drawText(margemEsquerda, yPos, larguraMax, 100, Qt::AlignHCenter, "--------------------------");
    yPos += 150;

    // Dados do Paciente
    QFont fontDados("Arial", 10, QFont::Normal);
    painter.setFont(fontDados);
    painter.drawText(margemEsquerda, yPos, larguraMax, 100, Qt::AlignLeft, "CPF: " + cpf);
    yPos += 120;
    painter.drawText(margemEsquerda, yPos, larguraMax, 100, Qt::AlignLeft, "Data: " + QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm"));
    yPos += 150;

    // Rodapé
    painter.setFont(fontSub);
    painter.drawText(margemEsquerda, yPos, larguraMax, 100, Qt::AlignHCenter, "Aguarde ser chamado no painel.");

    painter.end();

    qDebug() << "-> SUCESSO: Talão impresso na POS58DD!";
}