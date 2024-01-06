#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
    , ui(new Ui::Widget)
    , VBO(QOpenGLBuffer::VertexBuffer)
    , texture(QOpenGLTexture::Target2D)
    , texture1(QOpenGLTexture::Target2D)
{
    ui->setupUi(this);
    QSurfaceFormat format;
    format.setAlphaBufferSize(24);//设置alpha缓冲区的大小
    format.setVersion(3,3);//设置当前opengl版本
    format.setSamples(10);//设置重采样次数，用于反走样
    this->setFormat(format);

    vertices = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
    };
}

Widget::~Widget()
{
    delete ui;
    makeCurrent();
    texture.destroy();
    texture1.destroy();
    doneCurrent();
}

void Widget::initializeGL()
{
    this->initializeOpenGLFunctions();
    //添加顶点着色器和片段着色器
    if(!shaderprogram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/Vertex.vert"))
    {
        qDebug() << "ERROR:" << shaderprogram.log();
    }
    if(!shaderprogram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/Fragment.frag"))
    {
        qDebug() << "ERROR:" << shaderprogram.log();
    }
    //链接着色器程序
    if(!shaderprogram.link())
    {
        qDebug() << "ERROR:" << shaderprogram.log();
    }
    //创建一个VAO属性登记表
    VAO.create();
    VAO.bind();//绑定后，接下的VBO的都会在VAO中登记

    VBO.create();
    VBO.bind();

    VBO.allocate(vertices.data(),(int)sizeof(float)*vertices.size());

    texture.create();
    texture.setData(QImage(":/opengl.jpg").mirrored());
    texture.setMinMagFilters(QOpenGLTexture::LinearMipMapLinear,QOpenGLTexture::Linear);
    texture.setWrapMode(QOpenGLTexture::DirectionS,QOpenGLTexture::Repeat);
    texture.setWrapMode(QOpenGLTexture::DirectionT,QOpenGLTexture::Repeat);

    texture1.create();
    texture1.setData(QImage(":/opengl2.jpg").mirrored());
    texture1.setMinMagFilters(QOpenGLTexture::LinearMipMapLinear,QOpenGLTexture::Linear);
    texture1.setWrapMode(QOpenGLTexture::DirectionS,QOpenGLTexture::Repeat);
    texture1.setWrapMode(QOpenGLTexture::DirectionT,QOpenGLTexture::Repeat);


    shaderprogram.setAttributeBuffer("aPos",GL_FLOAT,0,3,sizeof(float)*8);
    shaderprogram.enableAttributeArray("aPos");

    shaderprogram.setAttributeBuffer("aColor",GL_FLOAT,sizeof(float)*3,3,sizeof(float)*8);
    shaderprogram.enableAttributeArray("aColor");

    shaderprogram.setAttributeBuffer("aTexture",GL_FLOAT,sizeof(float)*6,2,sizeof(float)*8);
    shaderprogram.enableAttributeArray("aTexture");


    VAO.release();
}

void Widget::resizeGL(int w, int h)
{
    this->glViewport(0,0,w,h);
}

void Widget::paintGL()
{
    glClearColor(0.1f,0.5f,0.7f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderprogram.bind();
    VAO.bind();

    texture.bind(0);
    shaderprogram.setUniformValue("ourTexture",0);

    texture1.bind(1);
    shaderprogram.setUniformValue("ourTexture1",1);

    this->glDrawArrays(GL_POLYGON,0,4);

}


