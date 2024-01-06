#include "opengl_widget.h"

opengl_widget::opengl_widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    x_rotate = -30.0;
    z_rotate = 100.0;
    x_trans = 0.0;
    y_trans = 0.0;
    zoom = 45.0;
    first_mouse = true;
    leftMousePress = false;
    MidMousePress = false;
    testTexture = nullptr;
}

opengl_widget::~opengl_widget()
{
    makeCurrent();
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    shaderProgram.release();
    doneCurrent();
}

void opengl_widget::initializeGL()
{
    initializeOpenGLFunctions();

    // enable depth_test
    glEnable(GL_DEPTH_TEST);

    // link shaders
    //这里改为自己的着色器文件路径
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Vertex.vert");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Fragment.frag");
    shaderProgram.link();

    float vertices[] = {
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

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    //这里改为自己的纹理文件路径
    testTexture = new QOpenGLTexture(QImage(":/face.png").mirrored(false, true));
}

void opengl_widget::paintGL()
{
    glClearColor(0.2f, 0.3f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 projection, view, model;
    projection.perspective(zoom, (float)width() / (float)height(), 1.0f, 100.0f);

    view.lookAt(QVector3D(0.0, 0.0, 3.0), QVector3D(0.0, 0.0, 1.0), QVector3D(0.0, 1.0, 0.0));

    model.translate(x_trans, y_trans, 0.0);
    model.rotate(x_rotate, 1.0, 0.0, 0.0);
    model.rotate(z_rotate, 0.0, 0.0, 1.0);

    shaderProgram.bind();
    shaderProgram.setUniformValue("projection", projection);
    shaderProgram.setUniformValue("view", view);
    shaderProgram.setUniformValue("model", model);

    shaderProgram.setUniformValue("texture1", 0);

    shaderProgram.bind();
    glBindVertexArray(VAO);
    testTexture->bind(0);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void opengl_widget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

void opengl_widget::mouseMoveEvent(QMouseEvent* event)
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

void opengl_widget::mousePressEvent(QMouseEvent* event)
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

void opengl_widget::mouseReleaseEvent(QMouseEvent* event)
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

void opengl_widget::wheelEvent(QWheelEvent* event)
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
