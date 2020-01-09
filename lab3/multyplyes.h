#include <iostream>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

void eiler_rotation_matrix(glm::mat4& rotation_matrix, GLfloat prec_a, GLfloat nut_a, GLfloat himrot_a);
void vector_multyply(glm::vec3& ab, const glm::vec3& a, const glm::vec3& b);
void scalar_multyply3(GLfloat& res, const glm::vec3& a, const glm::vec3& b);
void scalar_multyply4(GLfloat& res, const glm::vec4& a, const glm::vec4& b);
void quaternion_multyply(glm::vec4& q, const glm::vec4& q1, const glm::vec4& q2);
void s_quaternion(glm::vec4& s_q, const glm::vec4& q);
void vector_rotate_xyz(glm::vec3& res, GLfloat x_a, GLfloat y_a, GLfloat z_a, const glm::vec3& u);
void rotation_func(glm::vec3& res, const glm::vec4& q, const glm::vec3& u);
void xyz_rotation_to_quaternion(glm::vec4& quaternion, GLfloat x_a, GLfloat y_a, GLfloat z_a);
void x_rotation_to_quaternion(glm::vec4& quaternion, const GLfloat x_a);
void y_rotation_to_quaternion(glm::vec4& quaternion, const GLfloat y_a);
void z_rotation_to_quaternion(glm::vec4& quaternion, const GLfloat z_a);
void quaternion_to_matrix(glm::mat4& rotation_matrix, const glm::vec4& quaternion);
void normal_quaternion(glm::vec4& normal_quaternion, const glm::vec4& input);



void eiler_rotation_matrix(glm::mat4& rotation_matrix, GLfloat prec_a, GLfloat nut_a, GLfloat himrot_a){
    /*
        Eiler matrix:
       | cos(a)cos(c)-cos(b)sin(a)sin(c)   -cos(c)sin(a)-cos(a)cos(b)sin(c)    sin(b)sin(c) | a - precession angle
       | cos(b)cos(c)sin(a)+cos(a)sin(c)    cos(a)cos(b)cos(c)-sin(a)sin(c)   -cos(c)sin(b) | b - nutation angle
       |             sin(a)sin(b)                       cos(a)sin(b)               cos(b)   | c - himself rotation angle
    */
    rotation_matrix[0][0] = cos(prec_a)*cos(himrot_a) - cos(nut_a)*sin(prec_a)*sin(himrot_a);
    rotation_matrix[0][1] = -cos(himrot_a)*sin(prec_a) - cos(prec_a)*cos(nut_a)*sin(himrot_a);
    rotation_matrix[0][2] = sin(nut_a)* sin(himrot_a);
    rotation_matrix[0][3] = 0.0f;
    rotation_matrix[1][0] = cos(nut_a)*cos(himrot_a)*sin(prec_a) + cos(prec_a)*sin(himrot_a);
    rotation_matrix[1][1] = cos(prec_a)*cos(nut_a)*cos(himrot_a) - sin(prec_a)*sin(himrot_a);
    rotation_matrix[1][2] = -cos(himrot_a)*sin(nut_a);
    rotation_matrix[1][3] = 0.0f;
    rotation_matrix[2][0] = sin(prec_a)*sin(nut_a);
    rotation_matrix[2][1] = cos(prec_a)*sin(nut_a);
    rotation_matrix[2][2] = cos(nut_a);
    rotation_matrix[2][3] = 0.0f;
    rotation_matrix[3][0] = 0.0f;
    rotation_matrix[3][1] = 0.0f;
    rotation_matrix[3][2] = 0.0f;
    rotation_matrix[3][3] = 1.0f;
}

void vector_multyply(glm::vec3& ab, const glm::vec3& a, const glm::vec3& b){
    ab.x = a.y*b.z - a.z*b.y;
    ab.y = a.z*b.x - b.z*a.x;
    ab.z = a.x*b.y - b.x*a.y;
}

void scalar_multyply3(GLfloat& res, const glm::vec3& a, const glm::vec3& b){
    res = a.x*b.x + a.y*b.y + a.z*b.z;
}

void scalar_multyply4(GLfloat& res, const glm::vec4& a, const glm::vec4& b){
    res = a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
}

void quaternion_multyply(glm::vec4& q, const glm::vec4& q1, const glm::vec4& q2){
    GLfloat a_b = 0;
    glm::vec3 axb;
    const glm::vec3 a = glm::vec3(q1);
    const glm::vec3 b = glm::vec3(q2);
    scalar_multyply3(a_b, a, b);
    vector_multyply(axb, a, b);

    q.w = q1.w*q2.w - a_b;
    q.x = q1.w*q2.x + q2.w*q1.x + axb.x;
    q.y = q1.w*q2.y + q2.w*q1.y + axb.y;
    q.z = q1.w*q2.z + q2.w*q1.z + axb.z;
}

void s_quaternion(glm::vec4& s_q, const glm::vec4& q){
    s_q.w = q.w;
    s_q.x = -q.x;
    s_q.y = -q.y;
    s_q.z = -q.z;
}

void vector_rotate_xyz(glm::vec3& res, GLfloat x_a, GLfloat y_a, GLfloat z_a, const glm::vec3& u){
    glm::vec4 quaternion;
    xyz_rotation_to_quaternion(quaternion, x_a, y_a, z_a);
    rotation_func(res, quaternion, u);
}

void rotation_func(glm::vec3& res, const glm::vec4& q, const glm::vec3& u){
    glm::vec4 q_1, uq, result, vec = glm::vec4(u, 0.0f);
    s_quaternion(q_1, q);
    quaternion_multyply(uq, q, vec);
    quaternion_multyply(result, uq, q_1);
    res.x = result.x;
    res.y = result.y;
    res.z = result.z;
}

void xyz_rotation_to_quaternion(glm::vec4& quaternion, GLfloat x_a, GLfloat y_a, GLfloat z_a){
    glm::vec4 x_rot_q, y_rot_q, z_rot_q, res;
    glm::vec4 yz;
    x_rotation_to_quaternion(x_rot_q, x_a);
    y_rotation_to_quaternion(y_rot_q, y_a);
    z_rotation_to_quaternion(z_rot_q, z_a);
    //std::cout << "x: " << x_rot_q.w << ' ' << x_rot_q.x << ' ' << x_rot_q.y << ' ' << x_rot_q.z << std::endl;
    //std::cout << "y: " << y_rot_q.w << ' ' << y_rot_q.x << ' ' << y_rot_q.y << ' ' << y_rot_q.z << std::endl;
    //std::cout << "z: " << z_rot_q.w << ' ' << z_rot_q.x << ' ' << z_rot_q.y << ' ' << z_rot_q.z << std::endl;


    quaternion_multyply(yz, y_rot_q, z_rot_q);
    //std::cout << yz.w << ' ' << yz.x << ' ' << yz.y << ' ' << yz.z << std::endl;    
    quaternion_multyply(quaternion, x_rot_q, yz);
    //std::cout << quaternion.w << ' ' << quaternion.x << ' ' << quaternion.y << ' ' << quaternion.z << std::endl;
}

void x_rotation_to_quaternion(glm::vec4& quaternion, const GLfloat x_a){
    quaternion.w = cos(x_a / 2.0f);
    quaternion.x = sin(x_a / 2.0f);
    quaternion.y = quaternion.z = 0.0f;
}

void y_rotation_to_quaternion(glm::vec4& quaternion, const GLfloat y_a){
    quaternion.w = cos(y_a / 2.0f);
    quaternion.y = sin(y_a / 2.0f);
    quaternion.x = quaternion.z = 0.0f;
}

void z_rotation_to_quaternion(glm::vec4& quaternion, const GLfloat z_a){
    quaternion.w = cos(z_a / 2.0f);
    quaternion.z = sin(z_a / 2.0f);
    quaternion.x = quaternion.y = 0.0f;
}


void quaternion_to_matrix(glm::mat4& rotation_matrix, const glm::vec4& quaternion){

    /*  
        Translation Quaternion q = (w, xi + yj + zk) to rotation matrix:
        | 1-2yy-2zz   2xy-2wz    2xz+2wy   |  
        |  2xy+2wz   1-2xx-2zz   2yz-2wx   |  
        |  2xz-2wy    2yz+2wx   1-2xx-2yy  |  
    */


  GLfloat wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;
  x2 = quaternion.x + quaternion.x;
  y2 = quaternion.y + quaternion.y;
  z2 = quaternion.z + quaternion.z;
  xx = quaternion.x * x2;   xy = quaternion.x * y2;   xz = quaternion.x * z2;
  yy = quaternion.y * y2;   yz = quaternion.y * z2;   zz = quaternion.z * z2;
  wx = quaternion.w * x2;   wy = quaternion.w * y2;   wz = quaternion.w * z2;

  rotation_matrix[0][0]=1.0f-(yy+zz); 
  rotation_matrix[0][1]=xy-wz;        
  rotation_matrix[0][2]=xz+wy;
  rotation_matrix[1][0]=xy+wz;        
  rotation_matrix[1][1]=1.0f-(xx+zz); 
  rotation_matrix[1][2]=yz-wx;
  rotation_matrix[2][0]=xz-wy;        
  rotation_matrix[2][1]=yz+wx;       
  rotation_matrix[2][2]=1.0f-(xx+yy);

  rotation_matrix[0][3] = rotation_matrix[1][3] = rotation_matrix[2][3] = 0.0f;
  rotation_matrix[3][0] = rotation_matrix[3][1] = rotation_matrix[3][2] = 0.0f;
  rotation_matrix[3][3] = 1.0f;
}

void normal_quaternion(glm::vec4& normal_quaternion, const glm::vec4& input){
    GLfloat magnitude = sqrt(input.x*input.x + 
                        input.y*input.y + 
                        input.z*input.z + 
                        input.w*input.w);
    if(!magnitude){
        magnitude = 1.0f;
    }
    normal_quaternion.x = input.x / magnitude;
    normal_quaternion.y = input.y / magnitude;
    normal_quaternion.z = input.z / magnitude;
    normal_quaternion.w = input.w / magnitude;
}