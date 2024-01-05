 #ifndef OPENGL_WIDGET_H
#define OPENGL_WIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>

#include <iostream>

class opengl_widget : public QOpenGLWidget,QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    opengl_widget(QWidget*parent);
    ~opengl_widget();
protected:

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    QOpenGLShaderProgram shaderProgram;

    unsigned int VBO;
    unsigned int VAO;

};

#endif // OPENGL_WIDGET_H
