#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QFileDialog * dialog = new QFileDialog();
    QString filename = dialog->getOpenFileName(this, "Select File");
    QFile file(filename);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Can not open the file!";
    }
    QTextStream in(&file);
    QString code = in.readAll();
    qDebug() << code;
    parser *pr = parser::get_inst();
    pr->program(code);

    Form * treeWindow = new Form();
    treeWindow->show();
}

