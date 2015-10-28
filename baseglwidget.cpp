#include "baseglwidget.h"

BaseGLWidget::BaseGLWidget(QWidget *parent):QOpenGLWidget(parent){

}

void BaseGLWidget::initializeGL(){

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);


    //shaders link
    QOpenGLShader vShader(QOpenGLShader::Vertex);
    vShader.compileSourceFile(":/files/Shaders/vShader.glsl");


    QOpenGLShader fShader(QOpenGLShader::Fragment);
    fShader.compileSourceFile(":/files/Shaders/fShader.glsl");

    glClearDepth(1.0f);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);

    shader_program.addShader(&vShader);
    shader_program.addShader(&fShader);

    if(!shader_program.link()){
        qWarning("Can't link the shader program");
    }

    vertexAttr = shader_program.attributeLocation("vertexAttr");
    colorAttr = shader_program.attributeLocation("colorAttr");
    matrixUniform = shader_program.uniformLocation("projection");
    modelViewMatrix = shader_program.uniformLocation("modelView");

    pen = new Draw(&shader_program, vertexAttr, colorAttr, modelViewMatrix);


}

void BaseGLWidget::paintGL(){


    if(!shader_program.bind())
        return;
    //lights
   /* QVector4D diffuse0 = QVector4D(1.0, 0.0, 0.0, 1.0);
    QVector4D ambient0 = QVector4D(1.0, 0.0, 0.0, 1.0);
    QVector4D specular0 = QVector4D(1.0, 0.0, 0.0, 1.0);
    QVector4D light0_pos = QVector4D(1.0, 2.0, 3.0, 1.0);
    QVector4D lightPosition = QVector4D(1.0, 1.0, 1.0, 0.0 );
    QVector4D lightAmbient = QVector4D(0.2, 0.2, 0.2, 1.0 );
    QVector4D lightDiffuse = QVector4D( 1.0, 1.0, 1.0, 1.0 );
    QVector4D lightSpecular = QVector4D( 1.0, 1.0, 1.0, 1.0 );

    QVector4D materialAmbient = QVector4D( 1.0, 0.0, 1.0, 1.0 );
    QVector4D materialDiffuse = QVector4D( 1.0, 0.8, 0.0, 1.0);
    QVector4D materialSpecular = QVector4D( 1.0, 0.8, 0.0, 1.0 );
    int materialShininess = 100.0;

    QVector4D ambientProduct = QVector3D::crossProduct(lightAmbient.toVector3D(), materialAmbient.toVector3D());
    QVector4D diffuseProduct = QVector3D::crossProduct(lightDiffuse.toVector3D(), materialDiffuse.toVector3D());
    QVector4D specularProduct = QVector3D::crossProduct(lightSpecular.toVector3D(), materialSpecular.toVector3D());

    shader_program.setUniformValue(shader_program.uniformLocation("ambientProduct"), ambientProduct);
    shader_program.setUniformValue(shader_program.uniformLocation("specularProduct"), specularProduct);
    shader_program.setUniformValue(shader_program.uniformLocation("lightPosition"), lightPosition);
    shader_program.setUniformValue(shader_program.uniformLocation("shininess"), materialShininess);

    QVector2D a,b,c,d;
         QVector2D t1 = a - b;
         QVector2D t2 = c - b;
         QVector3D normal = QVector3D::crossProduct(t1.toVector3D(), t2.toVector3D());
         normal = normal.normalize();

         pointsArray.push(vertices[a]);
         normalsArray.push(normal);
}

*/

    /*var ambient0 = vec4(1.0, 0.0, 0.0, 1.0);
    var specular0 = vec4(1.0, 0.0, 0.0, 1.0);
    var light0_pos = vec4(1.0, 2.0, 3,0, 1.0);*/
    //translate the camera away
    QMatrix4x4 matrix;
    matrix.ortho( -ORTHO_DIST, ORTHO_DIST, -ORTHO_DIST, ORTHO_DIST, ORTHO_DIST, -ORTHO_DIST);
    shader_program.setUniformValue(matrixUniform, matrix);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    pen->Paint();
    //release the  binded shader program
    shader_program.release();

}

void BaseGLWidget::resizeGL(int width, int height){
    glViewport(0, 0, width, height);
    //translate the camera away
    QMatrix4x4 matrix;
    matrix.ortho( -ORTHO_DIST, ORTHO_DIST, -ORTHO_DIST, ORTHO_DIST, ORTHO_DIST, -ORTHO_DIST);

    shader_program.setUniformValue(matrixUniform, matrix);
    pen->setHeight(height);
    pen->setWidth(width);

}

