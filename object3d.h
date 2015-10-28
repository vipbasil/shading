#ifndef OBJECT3D_H
#define OBJECT3D_H
#include <vector>
#include <QOpenGLShaderProgram>
#include <string>
#include <QFile>
#include <QString>


class Object3D
{
public:
    Object3D();
    std::vector<float> vertices;
    std::vector<QVector3D> Vert3D;

    std::vector<float> colors;
    std::vector<float> normals;
    std::vector<float> objects;

    std::vector<float> textures;
    std::vector<float> faces;
    std::vector<QString> mtl;
    std::vector<QString> usemtl;

    int textureUV;
    std::vector<float> frame_colors;

    //material properties
    QVector4D material_diffuse_color;
    QVector4D material_specular_color;
    QVector4D material_ambient_color;
    float material_shininess;

    QMatrix4x4 get_transformations();
    void set_color(float R, float G, float B);

    float RotationX, RotationY, RotationZ;
    float ScaleX, ScaleY, ScaleZ;
    float TranslationX, TranslationY, TranslationZ;

    // Obj file loading
    void loadObjFile(QString filename);
    void record(const QString &line);
    void readlVertices(const QString &line);
    void readTexturCord(const QString &line);
    void readNormals(const QString &line);
    void readSpaceVert(const QString &line);
    void readFace(const QString &line);
    void readMtl(const QString &line);
    void readUseMtl(const QString &line);

    QString get_corret_line(const QString &line);
    bool isblank(const QChar &ch);
    int get_normal_index(int index, QString name);

signals:

public slots:
private:
    bool m_texture_coordinates = false; // is vt
    bool m_normal = false;              // is vn
};

#endif // OBJECT3D_H
