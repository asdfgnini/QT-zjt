#include "opengl_widget.h"


#define ATTRIB_VERTEX 0
#define ATTRIB_TEXTURE 1

OpenGL_Widget::OpenGL_Widget(QWidget *parent):QOpenGLWidget(parent),VBO(QOpenGLBuffer::VertexBuffer)
{
    media = new Media();
    control = new Controller();
    connect(control,&Controller::send_IMG,this,&OpenGL_Widget::slot_send_img);
    connect(control,&Controller::newframe,this,&OpenGL_Widget::slot_new_frame);

    vertices = {
        -1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
         1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
         1.0f,-1.0f, 0.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 0.0f, 0.0f, 1.0f
    };
}

OpenGL_Widget::~OpenGL_Widget()
{
    delete media;
    delete control;
}

void OpenGL_Widget::play(QString filepath)
{
    media->Open(filepath);
    control->start(media);
}
#if 0
void OpenGL_Widget::initializeGL()
{
    this->initializeOpenGLFunctions();
    if(!shaderprogram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/Vertex.vert"))
    {
        qDebug() << "ERROR:" << shaderprogram.log();
    }
    if(!shaderprogram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/Fragment.frag"))
    {
        qDebug() << "ERROR:" << shaderprogram.log();
    }
    if(!shaderprogram.link())
    {
        qDebug() << "ERROR:" << shaderprogram.log();
    }

    VAO.create();
    VAO.bind();

    VBO.create();
    VBO.bind();
    VBO.allocate(vertices.data(),(int)sizeof(float)*vertices.size());


    shaderprogram.setAttributeBuffer("aPos",GL_FLOAT,0,3,sizeof(float)*5);
    shaderprogram.enableAttributeArray("aPos");

    shaderprogram.setAttributeBuffer("aTexture",GL_FLOAT,sizeof(float)*3,2,sizeof(float)*5);
    shaderprogram.enableAttributeArray("aTexture");

    GLuint ids[3];
    glGenTextures(3,ids);
    idY = ids[0];
    idU = ids[1];
    idV = ids[2];

    VAO.release();
}

void OpenGL_Widget::resizeGL(int w, int h)
{
    this->glViewport(0,0,w,h);
}

void OpenGL_Widget::paintGL()
{
    glClearColor(1.0f,0.5f,0.2f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderprogram.bind();
    VAO.bind();


    glActiveTexture(GL_TEXTURE0);//激活纹理单元
    glBindTexture(GL_TEXTURE_2D,idY);//绑定纹理目标
    glTexImage2D(GL_TEXTURE_2D,0,GL_RED,width,height,0,GL_RED,GL_UNSIGNED_BYTE,ptr);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,idU);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RED,width >> 1,height >> 1,0,GL_RED,GL_UNSIGNED_BYTE,ptr + width*height);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D,idV);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RED,width >> 1,height >> 1,0,GL_RED,GL_UNSIGNED_BYTE,ptr + width*height*5/4);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    shaderprogram.setUniformValue("textureY",0);
    shaderprogram.setUniformValue("textureU",1);
    shaderprogram.setUniformValue("textureV",2);

    this->glDrawArrays(GL_QUADS,0,4);

}
#endif
#if 1
void OpenGL_Widget::initializeGL()
{
    initializeOpenGLFunctions();
    const char *vsrc =
        "attribute vec4 vertexIn; \
        attribute vec4 textureIn; \
        varying vec4 textureOut;  \
        void main(void)           \
    {                         \
            gl_Position = vertexIn; \
            textureOut = textureIn; \
    }";

        const char *fsrc =
        "varying vec4 textureOut;\n"
        "uniform sampler2D textureY;\n"
        "uniform sampler2D textureU;\n"
        "uniform sampler2D textureV;\n"
        "void main(void)\n"
        "{\n"
        "vec3 yuv; \n"
        "vec3 rgb; \n"
        "yuv.x = texture2D(textureY, textureOut.st).r; \n"
        "yuv.y = texture2D(textureU, textureOut.st).r - 0.5; \n"
        "yuv.z = texture2D(textureV, textureOut.st).r - 0.5; \n"
        "rgb = mat3( 1,       1,         1, \n"
        "0,       -0.39465,  2.03211, \n"
        "1.13983, -0.58060,  0) * yuv; \n"
        "gl_FragColor = vec4(rgb, 1); \n"
        "}\n";

    m_program.addCacheableShaderFromSourceCode(QOpenGLShader::Vertex,vsrc);
    m_program.addCacheableShaderFromSourceCode(QOpenGLShader::Fragment,fsrc);
    m_program.link();

    GLfloat points[]{
        -1.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, -1.0f,
        -1.0f, -1.0f,

        0.0f,0.0f,
        1.0f,0.0f,
        1.0f,1.0f,
        0.0f,1.0f
    };

    vbo.create();
    vbo.bind();
    vbo.allocate(points,sizeof(points));

    GLuint ids[3];
    glGenTextures(3,ids);
    idY = ids[0];
    idU = ids[1];
    idV = ids[2];
}

void OpenGL_Widget::resizeGL(int w, int h)
{
    if(h < 0)
    {
        h = 1;
    }
    glViewport(0,0,w,h);
}

void OpenGL_Widget::paintGL()
{
    if(ptr == NULL)
    {
        return;
    }
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    m_program.bind();
    vbo.bind();

    m_program.enableAttributeArray("vertexIn");
    m_program.enableAttributeArray("textureIn");
    m_program.setAttributeBuffer("vertexIn",GL_FLOAT, 0, 2, 2*sizeof(GLfloat));
    m_program.setAttributeBuffer("textureIn",GL_FLOAT,2 * 4 * sizeof(GLfloat),2,2*sizeof(GLfloat));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,idY);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RED,width,height,0,GL_RED,GL_UNSIGNED_BYTE,ptr);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,idU);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RED,width >> 1,height >> 1,0,GL_RED,GL_UNSIGNED_BYTE,ptr + width*height);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D,idV);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RED,width >> 1,height >> 1,0,GL_RED,GL_UNSIGNED_BYTE,ptr + width*height*5/4);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    m_program.setUniformValue("textureY",0);
    m_program.setUniformValue("textureU",1);
    m_program.setUniformValue("textureV",2);
    glDrawArrays(GL_QUADS,0,4);
    m_program.disableAttributeArray("vertexIn");
    m_program.disableAttributeArray("textureIn");
    m_program.release();
}
#endif




void OpenGL_Widget::slot_send_img(unsigned char *p, int w, int h)
{
    qDebug() << "OK";
    ptr = p;
    width = w;
    height = h;

}

void OpenGL_Widget::slot_new_frame()
{
    update();

}



