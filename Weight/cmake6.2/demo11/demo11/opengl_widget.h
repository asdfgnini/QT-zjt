#ifndef OPENGL_WIDGET_H
#define OPENGL_WIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions_3_3_Core>
#include <QVector>

class OpenGL_Widget : public QOpenGLWidget,QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    enum type_info{
        NONE,
        TRIANGE,
        JU,
    };
    explicit OpenGL_Widget(QWidget *parent = nullptr);

    void drawshape(type_info shape);
    void setwireframe(bool state);
protected:
    void initializeGL()override;
    void resizeGL(int w , int h)override;
    void paintGL()override;

private:

    QOpenGLShaderProgram shaderprogram[2];
    QOpenGLBuffer VBO01;
    QOpenGLBuffer VBO02;


    QOpenGLVertexArrayObject VAO[2];

    QVector<float> vertex[2];

    type_info m_show;

public slots:
    void draw();
    void clear();
    void wireframe(bool state);
};

#endif // OPENGL_WIDGET_H
