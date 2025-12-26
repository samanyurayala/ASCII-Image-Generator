#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

string getAsciiStringofImage(QImage image) {
    constexpr char ASCII_String[] = " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
    string displayString = "";
    for (int h = 0; h < image.height(); h++) {
        for (int w = 0; w < image.width(); w++) {
            QColor colorOfPixel = image.pixelColor(w, h);
            unsigned short length = sizeof(ASCII_String) - 1;
            unsigned short brightness = qRound(0.299 * colorOfPixel.red() + 0.587 * colorOfPixel.green() + 0.114 * colorOfPixel.blue());
            displayString += ASCII_String[qRound(brightness * (length - 1)/255.0)];
        }
        displayString += "\n";
    }
    return displayString;
}

void MainWindow::on_pushButton_clicked() {
    auto fileContentReady = [this](const QString &fileName, const QByteArray &fileContent) {
        if (fileName.isEmpty()) {
            return;
        } else {
            QImage image;
            bool valid = image.loadFromData(fileContent);
            if (valid) {
                QImage scaledImage = image.scaled(ui -> labelImage -> size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                QImage scaledOutput;
                if (image.width() > 100 || image.height() > 100) scaledOutput = (image.width() > image.height()) ? image.scaledToWidth(100, Qt::SmoothTransformation) : image.scaledToHeight(100, Qt::SmoothTransformation);
                else scaledOutput = image;
                ui -> labelImage -> setPixmap(QPixmap::fromImage(scaledImage));
                QString fullRes = QString::fromStdString(getAsciiStringofImage(image));
                QString lowRes = QString::fromStdString(getAsciiStringofImage(scaledOutput));
                ui -> textBrowser -> setText(fullRes);
                ui -> textBrowser_2 -> setText(lowRes);
            }
        }
    };
    QFileDialog::getOpenFileContent("Images (*.png *.jpg *.bmp *.jpeg)", fileContentReady);
}


