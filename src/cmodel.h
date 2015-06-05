#ifndef CMODEL_H
#define CMODEL_H
#include <QtOpenGL>
#include <cmath>

// класс для описания 3D моделей
class Cmodel
{
protected:
    // Сетка - группа треугольников с одним материалом
    struct Mesh
    {
        int m_materialIndex;
        int m_numTriangles;
        int *m_pTriangleIndices;
    };
    int m_numMeshes;
    Mesh *m_pMeshes;
    // данные о материалах
    struct Material
    {
        float m_ambient[4], m_diffuse[4], m_specular[4], m_emissive[4];
        float m_shininess;
        GLuint m_texture;
        char *m_pTextureFilename;
    };
    int m_numMaterials;
    Material *m_pMaterials;
    // данные о треугольниках
    struct Triangle
    {
        float m_vertexNormals[3][3];
        float m_s[3], m_t[3];
        int m_vertexIndices[3];
    };
    int m_numTriangles;
    Triangle *m_pTriangles;
    // данные о вершинах
    struct Vertex
    {
        char m_boneID;
        float m_location[3];
    };
    int m_numVertices;
    Vertex *m_pVertices;

public:
    // конструктор модели
    Cmodel();
    // деструктор модели
    virtual ~Cmodel();
    // загрузка модели
    virtual bool loadModelData(const char *filename) = 0;
    // вывод модели на экран
    void draw();
    // перезагрузка текстур при потере контекста
    void reloadTextures();
};

// класс, создержащий 3D модели в формате MilkShape 3D
class CMilkshapeModel: public Cmodel
{
public:
    // конструктор модели
    CMilkshapeModel();
    // деструктор модели
    virtual ~CMilkshapeModel();
    // загрузка модели
    virtual bool loadModelData(const char *filename);
protected:
    // просчет нормалей
    void normal_gen();
};

// класс пружинка
class CModelSpring: public CMilkshapeModel
{
protected:
    // индексный массив
    int * a_index;
    // параметры циллиндра
    int num_stacks;
    int num_slices;
    // начальное смещение
    float offset_start;
    // конечное смещение
    float offset_end;
    // количество витков
    int num_turns;
    //диаметр витка
    float radius_turn;
    // диаметр проволоки
    float radius_spring;
    // индексация координат модели
    void indexate();
    // размер по умолчанию
    float def_size;
    // пропуск незначительных изменений
    float length_prev;
    float epsilon;
    // константы
    float pi_x2;
    float pi;
    float pi_d2;
public:
    // конструктор модели
    CModelSpring();
    // деструктор модели
    ~CModelSpring();
    // изменение размера модели
    void resize(float length);
    // инициализация
    void init();
};

#endif //CMODEL_H
