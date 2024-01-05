#include "opengl_widget.h"

OpenGL_Widget::OpenGL_Widget(QWidget *parent)
    : QOpenGLWidget{parent}
{
    QSurfaceFormat format;
    format.setAlphaBufferSize(24);//设置alpha缓冲区的大小
    format.setVersion(3,3);//设置当前opengl版本
    format.setSamples(10);//设置重采样次数，用于反走样
    this->setFormat(format);
}

OpenGL_Widget::~OpenGL_Widget()
{

}

void OpenGL_Widget::initializeGL()
{
    this->initializeOpenGLFunctions();
    //添加顶点着色器和片段着色器
    if(!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/vertex.vert"))
    {
        qDebug() << "ERROR:" << shaderProgram.log();
    }
    if(!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/fragment.frag"))
    {
        qDebug() << "ERROR:" << shaderProgram.log();
    }
    //链接着色器程序
    if(!shaderProgram.link())
    {
        qDebug() << "ERROR:" << shaderProgram.log();
    }

    vertices = {
        -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f, 0.0f, // right
        0.0f,  0.5f, 0.0f  // top
    };

    //创建一个VAO属性登记表
    VAO.create();
    VAO.bind();//绑定后，接下的VBO的都会在VAO中登记


    VBO.create();
    VBO.bind();

    VBO.allocate(vertices.data(),(int)sizeof(float)*vertices.size());

    shaderProgram.setAttributeBuffer("aPos",GL_FLOAT,0,3,sizeof(float)*3);
    shaderProgram.enableAttributeArray("aPos");

    VAO.release();

}

void OpenGL_Widget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void OpenGL_Widget::paintGL()
{
    glClearColor(0.2f, 0.3f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram.bind();
    VAO.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}


