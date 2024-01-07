#ifndef OPENGL_WIDGET_H
#define OPENGL_WIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QOpenGLShader>
#include <QOpenGLVertexArrayObject>
#include <QVector>

#include <worker.h>

class OpenGL_Widget : public QOpenGLWidget, QOpenGLFunctions
{
    Q_OBJECT
public:
    OpenGL_Widget(QWidget *parent=nullptr);
    ~OpenGL_Widget();
    void play(QString filepath);
private:
    Media* media;
    Controller* control;
    unsigned char* ptr;
    int idY,idU,idV;
    int width,height;
    //原版
    QOpenGLShaderProgram m_program;
    QOpenGLBuffer vbo;
    /******************************/
    QVector<float> vertices;
    QOpenGLShaderProgram shaderprogram;
    QOpenGLBuffer VBO;
    QOpenGLVertexArrayObject VAO;
protected:
    void initializeGL() override;
    void resizeGL(int w,int h) override;
    void paintGL() override;

public slots:
    void slot_send_img(unsigned char* p,int w,int h);
    void slot_new_frame();
};

#endif // OPENGL_WIDGET_H


