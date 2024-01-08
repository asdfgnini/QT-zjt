#include "opengl_widget.h"

OpenGL_Widget::OpenGL_Widget(QWidget *parent)
    : QOpenGLWidget(parent)
    , VBO01(QOpenGLBuffer::VertexBuffer)
    , VBO02(QOpenGLBuffer::VertexBuffer)
{

    QSurfaceFormat surface;
    surface.setAlphaBufferSize(24);
    surface.setVersion(3,3);
    surface.setSamples(10);

    this->setFormat(surface);

    vertex[0] = {
        -0.9f,0.0f,0.0f,
        0.0f,0.0f,0.0f,
        -0.45f,0.5f,0.0f,
    };

    vertex[1] = {
        0.9f,0.0f,0.0f,
        0.0f,0.0f,0.0f,
        0.45f,0.5f,0.0f
    };

}

void OpenGL_Widget::drawshape(type_info shape)
{
    m_show = shape;
    update();
}

void OpenGL_Widget::setwireframe(bool state)
{
    makeCurrent();
    qDebug("%d",state);
    if(state)
    {
       this->glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    }
    else
    {
       this->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    }
    update();
    doneCurrent();

}

void OpenGL_Widget::initializeGL()
{
    this->initializeOpenGLFunctions();

    shaderprogram[0].addCacheableShaderFromSourceFile(QOpenGLShader::Vertex,":/Vertex.vert");
    shaderprogram[0].addCacheableShaderFromSourceFile(QOpenGLShader::Fragment,":/Fragment.frag");
    shaderprogram[0].link();

    shaderprogram[1].addCacheableShaderFromSourceFile(QOpenGLShader::Vertex,":/Vertex.vert");
    shaderprogram[1].addCacheableShaderFromSourceFile(QOpenGLShader::Fragment,":/Fragment01.frag");
    shaderprogram[1].link();

    VAO[0].create();
    VAO[0].bind();

    VBO01.create();
    VBO01.bind();

    VBO01.allocate(vertex[0].data(),(int)sizeof(float)*vertex[0].size());

    shaderprogram[0].setAttributeArray("aPos",GL_FLOAT,0,3,sizeof(float)*3);
    shaderprogram[0].enableAttributeArray("aPos");

    VBO01.release();
    VAO[0].release();

    VAO[1].create();
    VAO[1].bind();

    VBO02.create();
    VBO02.bind();

    VBO02.allocate(vertex[1].data(),(int)sizeof(float)*vertex[1].size());

    shaderprogram[1].setAttributeArray("aPos",GL_FLOAT,0,3,sizeof(float)*3);
    shaderprogram[1].enableAttributeArray("aPos");

    VBO02.release();
    VAO[1].release();


}

void OpenGL_Widget::resizeGL(int w, int h)
{
    this->glViewport(0,0,w,h);
}

void OpenGL_Widget::paintGL()
{
    glClearColor(0.2f,0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);




    switch (m_show) {
    case TRIANGE:
        shaderprogram[0].bind();
        VAO[0].bind();
        this->glDrawArrays(GL_TRIANGLES,0,3);
        // glDrawElements //绘制带索引的数组
        shaderprogram[0].release();

        shaderprogram[1].bind();
        VAO[1].bind();
        this->glDrawArrays(GL_TRIANGLES,0,3);
        shaderprogram[1].release();
        break;
    default:
        break;
    }

}

void OpenGL_Widget::draw()
{
    drawshape(TRIANGE);
}

void OpenGL_Widget::clear()
{
    drawshape(NONE);
}

void OpenGL_Widget::wireframe(bool state)
{
    setwireframe(state);
}
