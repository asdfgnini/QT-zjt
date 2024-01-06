#include "opengl_widget.h"

opengl_widget::opengl_widget(QWidget *parent)
    : QOpenGLWidget(parent)
    ,VBO(QOpenGLBuffer::VertexBuffer)
    ,texture(QOpenGLTexture::Target2D)
    ,texture01(QOpenGLTexture::Target2D)
{


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

        cubePositions = {
          { 0.0f,  0.0f,  0.0f  },
          { 2.0f,  5.0f, -15.0f },
          {-1.5f, -2.2f, -2.5f  },
          {-3.8f, -2.0f, -12.3f },
          { 2.4f, -0.4f, -3.5f  },
          {-1.7f,  3.0f, -7.5f  },
          { 1.3f, -2.0f, -2.5f  },
          { 1.5f,  2.0f, -2.5f  },
          { 1.5f,  0.2f, -1.5f  },
          {-1.3f,  1.0f, -1.5f  },
        };
        timer.setInterval(18);
        connect(&timer,&QTimer::timeout,this,static_cast<void (QOpenGLWidget::*)()>(&QOpenGLWidget::update));
        timer.start();

}

opengl_widget::~opengl_widget()
{


}

void opengl_widget::initializeGL()
{
    this->initializeOpenGLFunctions();

    if(!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/Vertex.vert"))
    {     //添加并编译顶点着色器
        qDebug()<<"ERROR:"<<shaderProgram.log();    //如果编译出错,打印报错信息
    }
    if(!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/Fragment.frag"))
    {   //添加并编译片段着色器
        qDebug()<<"ERROR:"<<shaderProgram.log();    //如果编译出错,打印报错信息
    }
    if(!shaderProgram.link())
    {                      //链接着色器
        qDebug()<<"ERROR:"<<shaderProgram.log();    //如果链接出错,打印报错信息
    }

    VAO.create();
    VAO.bind();

    VBO.create();
    VBO.bind();

    VBO.allocate(vertices.data(),(int)sizeof(float)*vertices.size());

    texture.create();
    texture.setData(QImage(":/opengl.jpg").mirrored());
    texture.setMinMagFilters(QOpenGLTexture::LinearMipMapLinear,QOpenGLTexture::Linear);
    texture.setWrapMode(QOpenGLTexture::DirectionS,QOpenGLTexture::Repeat);
    texture.setWrapMode(QOpenGLTexture::DirectionT,QOpenGLTexture::Repeat);

    texture01.create();
    texture01.setData(QImage(":/opengl2.jpg").mirrored());
    texture01.setMinMagFilters(QOpenGLTexture::LinearMipMapLinear,QOpenGLTexture::Linear);
    texture01.setWrapMode(QOpenGLTexture::DirectionS,QOpenGLTexture::Repeat);
    texture01.setWrapMode(QOpenGLTexture::DirectionT,QOpenGLTexture::Repeat);

    //设置顶点解析格式，并启用顶点
    shaderProgram.setAttributeBuffer("aPos", GL_FLOAT, 0, 3, sizeof(GLfloat) * 5);
    shaderProgram.enableAttributeArray("aPos");
//    shaderProgram.setAttributeBuffer("aColor", GL_FLOAT,sizeof(GLfloat) * 3, 3, sizeof(GLfloat) * 8);
//    shaderProgram.enableAttributeArray("aColor");
    shaderProgram.setAttributeBuffer("aTexCoord", GL_FLOAT,sizeof(GLfloat) * 3, 2, sizeof(GLfloat) * 5);
    shaderProgram.enableAttributeArray("aTexCoord");

    VAO.release();
    this->glEnable(GL_DEPTH_TEST);
}

void opengl_widget::resizeGL(int w, int h)
{
    this->glViewport(0,0,w,h);
}

void opengl_widget::paintGL()
{
    //设置清屏颜色
    this->glClearColor(0.1f,0.5f,0.7f,1.0f);
    //清除颜色缓存
    this->glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    shaderProgram.bind();
    VAO.bind();

//    float time=QTime::currentTime().msecsSinceStartOfDay()/1000.0;
//    QMatrix4x4 model;
//    model.rotate(180*time,QVector3D(1.0f,0.5f,0.3f));
//    shaderProgram.setUniformValue("model",model);

    QMatrix4x4 view;
    view.translate(0.0f,0.0f,-3.0f);
    shaderProgram.setUniformValue("view",view);

    QMatrix4x4 projection;
    projection.perspective(45.0f,width()/(float)height(),0.1f,100.0f);
    shaderProgram.setUniformValue("projection",projection);


    texture.bind(0);
    shaderProgram.setUniformValue("texture01",0);

    texture01.bind(1);
    shaderProgram.setUniformValue("texture02",1);


    float time=QTime::currentTime().msecsSinceStartOfDay()/1000.0;
    for(unsigned int i = 0; i < 10; i++){
        QMatrix4x4 model;
        model.translate(cubePositions[i]);
        model.rotate(180*time+i*20.0f,QVector3D(1.0f,0.5f,0.3f));
        shaderProgram.setUniformValue("model",model);
        this->glDrawArrays(GL_TRIANGLES, 0, 36);
    }}


