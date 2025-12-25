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
    QString file_name = QFileDialog::getOpenFileName(this, tr("Open a file"), QDir::homePath(), tr("Image Files (*.png *.jpg *.bmp *.jpeg)"));
    if (QString::compare(file_name, QString()) != 0) {
        QImage image;
        bool valid = image.load(file_name);
        if (valid) {
            QImage scaledImage = image.scaled(ui -> labelImage -> size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            QImage scaledOutput = (image.width() > image.height()) ? image.scaledToWidth(100, Qt::SmoothTransformation) : image.scaledToHeight(100, Qt::SmoothTransformation);
            ui -> labelImage -> setPixmap(QPixmap::fromImage(scaledImage));
            QString fullRes = QString(getAsciiStringofImage(image).c_str());
            QString lowRes = QString(getAsciiStringofImage(scaledOutput).c_str());
            ui -> textBrowser -> setText(fullRes);
            ui -> textBrowser_2 -> setText(lowRes);
        }
    }


}

