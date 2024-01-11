#include "opengl_widget.h"

OpenGL_Widget::OpenGL_Widget(QWidget *parent)
    : QOpenGLWidget(parent)
    , VBO(QOpenGLBuffer::VertexBuffer)
    , IBO(QOpenGLBuffer::IndexBuffer)
{
    time.start(1000);
    connect(&time,&QTimer::timeout,this,&OpenGL_Widget::on_timeslots);

    QSurfaceFormat surface;
    surface.setAlphaBufferSize(24);
    surface.setVersion(3,3);
    surface.setSamples(10);
    this->setFormat(surface);

    vertexs = {
        -0.5f,0.5f,0.0f,
        0.5f,0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        -0.5f,-0.5f,0.0f
    };

    vertex_inx = {
        0,1,2,
        3,0,2
    };

}

OpenGL_Widget::~OpenGL_Widget()
{
    if(!isValid())// 判断对象是否创建了
    {

    }
}



void OpenGL_Widget::initializeGL()
{
    this->initializeOpenGLFunctions();

    shaderprogram.addCacheableShaderFromSourceFile(QOpenGLShader::Vertex,":/Vertex.vert");
    shaderprogram.addCacheableShaderFromSourceFile(QOpenGLShader::Fragment,":/Fragment.frag");
    shaderprogram.link();

    VAO.create();
    VAO.bind();

    VBO.create();
    VBO.bind();

    VBO.allocate(vertexs.data(),(int)sizeof(float)*vertexs.size());

    IBO.create();
    IBO.bind();
    IBO.allocate(vertex_inx.data(),(int)sizeof(unsigned int)*vertex_inx.size());

    shaderprogram.setAttributeArray("aPos",GL_FLOAT,0,3,sizeof(float)*3);
    shaderprogram.enableAttributeArray("aPos");

    VBO.release();
    VAO.release();
}

void OpenGL_Widget::resizeGL(int w, int h)
{
    this->glViewport(0,0,w,h);
}

void OpenGL_Widget::paintGL()
{
    glClearColor(0.1f,0.5f,0.7f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderprogram.bind();
    VAO.bind();
    this->glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
    shaderprogram.release();

}

void OpenGL_Widget::on_timeslots()
{
    makeCurrent();
    qDebug() << "123";
    int timevalue = QTime::currentTime().second();
    float greenvalue = (sin(timevalue) / 2.0f) + 0.5f;
    shaderprogram.setUniformValue("ourcolor",0.0f,1.0f,0.0f,1.0f);

    doneCurrent();
    update();
}

