#ifndef OPENGL_WIDGET_H
#define OPENGL_WIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QMouseEvent>



class OpenGL_Widget : public QOpenGLWidget,QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit OpenGL_Widget(QWidget *parent = nullptr);
    ~OpenGL_Widget();
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;


    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;


private:

    QOpenGLShaderProgram shaderprogram;

    QOpenGLBuffer VBO;
    QOpenGLVertexArrayObject VAO;
    QVector<float> vertices;

    QOpenGLTexture texture;

    float x_rotate;
    float z_rotate;
    float x_trans;
    float y_trans;
    float zoom;

    bool first_mouse;
    bool leftMousePress;
    bool MidMousePress;




};

#endif // OPENGL_WIDGET_H
