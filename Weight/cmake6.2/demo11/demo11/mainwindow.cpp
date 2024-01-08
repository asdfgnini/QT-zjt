#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "opengl_widget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton,&QPushButton::clicked,ui->openGLWidget,&OpenGL_Widget::draw);
    connect(ui->pushButton_2,&QPushButton::clicked,ui->openGLWidget,&OpenGL_Widget::clear);
    connect(ui->checkBox,SIGNAL(clicked(bool)),ui->openGLWidget,SLOT(wireframe(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

