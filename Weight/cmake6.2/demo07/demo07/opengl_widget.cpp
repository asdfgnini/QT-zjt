#include "opengl_widget.h"

OpenGL_Widget::OpenGL_Widget(QWidget *parent)
    : QOpenGLWidget(parent)
    , VBO(QOpenGLBuffer::VertexBuffer)
    , texture(QOpenGLTexture::Target2D)
{

    x_rotate = -30.0;
    z_rotate = 100.0;
    x_trans = 0.0;
    y_trans = 0.0;
    zoom = 45.0;
    first_mouse = true;
    leftMousePress = false;
    MidMousePress = false;


    QSurfaceFormat format;
    format.setAlphaBufferSize(24);  //设置alpha缓冲大小
    format.setVersion(3,3);         //设置版本号
    format.setSamples(10);          //设置重采样次数，用于反走样
    //...
    this->setFormat(format);

    vertices = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };


}

OpenGL_Widget::~OpenGL_Widget()
{

}

void OpenGL_Widget::initializeGL()
{
    this->initializeOpenGLFunctions();

    if(!shaderprogram.addCacheableShaderFromSourceFile(QOpenGLShader::Vertex,":/Vertex.vert"))
    {
        qDebug() <<"ERROR" << shaderprogram.log();
    }
    if(!shaderprogram.addCacheableShaderFromSourceFile(QOpenGLShader::Fragment,":/Fragment.frag"))
    {
        qDebug() <<"ERROR" << shaderprogram.log();
    }
    if(!shaderprogram.link())
    {
        qDebug() <<"ERROR" << shaderprogram.log();
    }

    VAO.create();
    VAO.bind();

    VBO.create();
    VBO.bind();

    VBO.allocate(vertices.data(),(int)sizeof(float)*vertices.size());

    texture.create();
    texture.setData(QImage(":/face.png").mirrored());
    texture.setMinMagFilters(QOpenGLTexture::LinearMipMapLinear,QOpenGLTexture::Linear);
    texture.setWrapMode(QOpenGLTexture::DirectionS,QOpenGLTexture::Repeat);
    texture.setWrapMode(QOpenGLTexture::DirectionT,QOpenGLTexture::Repeat);


    //设置顶点解析格式，并启用顶点
    shaderprogram.setAttributeBuffer("aPos", GL_FLOAT, 0, 3, sizeof(GLfloat) * 5);
    shaderprogram.enableAttributeArray("aPos");
    shaderprogram.setAttributeBuffer("aTexCoord", GL_FLOAT,sizeof(GLfloat) * 3, 2, sizeof(GLfloat) * 5);
    shaderprogram.enableAttributeArray("aTexCoord");


    VAO.release();
    this->glEnable(GL_DEPTH_TEST);

}
void OpenGL_Widget::resizeGL(int w, int h)
{
    this->glViewport(0,0,w,h);

}

void OpenGL_Widget::paintGL()
{
    // this->glClearColor(0.1f,0.5f,0.7f,1.0f);
    this->glClearColor(0.2f, 0.3f, 0.2f, 1.0f);
    this->glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

    shaderprogram.bind();
    VAO.bind();

    QMatrix4x4 model;
    model.translate(x_trans, y_trans, 0.0);
    model.rotate(x_rotate, 1.0, 0.0, 0.0);
    model.rotate(z_rotate, 0.0, 0.0, 1.0);
    shaderprogram.setUniformValue("model",model);

    QMatrix4x4 view;
    view.lookAt(QVector3D(0.0, 0.0, 3.0), QVector3D(0.0, 0.0, 1.0), QVector3D(0.0, 1.0, 0.0));
    shaderprogram.setUniformValue("view",view);

    QMatrix4x4 projection;
    projection.perspective(zoom, (float)width() / (float)height(), 1.0f, 100.0f);
    shaderprogram.setUniformValue("projection",projection);

    texture.bind(0);
    shaderprogram.setUniformValue("texture01",0);


    this->glDrawArrays(GL_TRIANGLES,0,36);

}

void OpenGL_Widget::mouseMoveEvent(QMouseEvent* event)
{
    static QPoint lastPos;
    auto currentPos = event->pos();
    QPoint deltaPos;

    if (leftMousePress == true)
    {
        if (first_mouse == true)
        {
            lastPos = currentPos;
            first_mouse = false;
        }

        deltaPos = currentPos - lastPos;
        lastPos = currentPos;

        x_rotate = x_rotate + 0.3 * deltaPos.y();
        z_rotate = z_rotate + 0.3 * deltaPos.x();

        if (x_rotate > 30.0f)
            x_rotate = 30.0f;
        if (x_rotate < -120.0f)
            x_rotate = -120.0f;
    }
    else if (MidMousePress == true)
    {
        if (first_mouse == true)
        {
            lastPos = currentPos;
            first_mouse = false;
        }

        deltaPos = currentPos - lastPos;
        lastPos = currentPos;

        x_trans = x_trans + 0.01 * deltaPos.x();
        y_trans = y_trans - 0.01 * deltaPos.y();
    }
    update();
}

void OpenGL_Widget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        first_mouse = true;
        leftMousePress = true;
    }

    else if (event->button() == Qt::MiddleButton)
    {
        first_mouse = true;
        MidMousePress = true;
    }
}

void OpenGL_Widget::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        leftMousePress = false;
    }
    else if (event->button() == Qt::MiddleButton)
    {
        MidMousePress = false;
    }
}

void OpenGL_Widget::wheelEvent(QWheelEvent* event)
{
    auto scroll_offest = event->angleDelta().y() / 120;
    zoom = zoom - (float)scroll_offest;

    if (zoom < 10.0f)
    {
        zoom = 10.0f;
    }

    if (zoom > 80.0f)
    {
        zoom = 80.0f;
    }

    update();
}

