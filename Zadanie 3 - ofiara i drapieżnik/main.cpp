#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

class dp {
public:
  float p1, p2, w1, w2, e1, e2; //phi, omega, epsilon
  float A, B, C; //A = m1/m2, B = l2/l1, C=g/l1
  float h; //step 
  unsigned long int i; //number of iteration

  dp(float _A, float _B, float _C, float _h) : A(_A), B(_B), C(_C), h(_h), p1(0), p2(1), w1(0), w2(0), e1(0), e2(0), i(0)
  {}

  float next_e1()
  {
    return -(sin(p1-p2)*(B*pow(w2,2)+pow(w1,2)*cos(p1-p2))+C*((A+1)*sin(p1)-sin(p2)*cos(p1-p2)))/(A+pow(sin(p1-p2),2));
  }
  
  float next_e2()
  {
    return ((A+1)*(pow(w1,2)*sin(p1-p2)-C*sin(p2))+cos(p1-p2)*((B*pow(w2,2)*sin(p1-p2))+C*(A+1)*sin(p1)))/(B*(A+pow(sin(p1-p2),2)));
  }

  float n_e1(float p1, float p2, float w1, float w2)
  {
    return -(sin(p1-p2)*(B*pow(w2,2)+pow(w1,2)*cos(p1-p2))+C*((A+1)*sin(p1)-sin(p2)*cos(p1-p2)))/(A+pow(sin(p1-p2),2));
  }
  
  float n_e2(float p1, float p2, float w1, float w2)
  {
    return ((A+1)*(pow(w1,2)*sin(p1-p2)-C*sin(p2))+cos(p1-p2)*((B*pow(w2,2)*sin(p1-p2))+C*(A+1)*sin(p1)))/(B*(A+pow(sin(p1-p2),2)));
  }

  void next_step()
  {
    e1 = next_e1();
    e2 = next_e2();

    float k1_1 = h*n_e1(p1,p2,w1,w2);
    float k1_2 = h*n_e2(p1,p2,w1,w2);
    float k1_3 = h*(w1);
    float k1_4 = h*(w2);

    float k2_1 = h*n_e1(p1+k1_3/2, p2+k1_4/2, w1+k1_1/2, w2+k1_2/2);
    float k2_2 = h*n_e2(p1+k1_3/2, p2+k1_4/2, w1+k1_1/2, w2+k1_2/2);
    float k2_3 = h*(k1_1/2+w1);
    float k2_4 = h*(k1_2/2+w2);

    float k3_1 = h*n_e1(p1+k2_3/2, p2+k2_4/2, w1+k2_1/2, w2+k2_2/2);
    float k3_2 = h*n_e2(p1+k2_3/2, p2+k2_4/2, w1+k2_1/2, w2+k2_2/2);
    float k3_3 = h*(k2_1/2+w1);
    float k3_4 = h*(k2_2/2+w2);

    float k4_1 = h*n_e1(p1+k3_3, p2+k3_4, w1+k3_1, w2+k3_2);
    float k4_2 = h*n_e2(p1+k3_3, p2+k3_4, w1+k3_1, w2+k3_2);
    float k4_3 = h*(k3_1+w1);
    float k4_4 = h*(k3_2+w2);

    w1 += (k1_1+2*k2_1+2*k3_1+k4_1)/6;
    w2 += (k1_2+2*k2_2+2*k3_2+k4_2)/6;
    p1 += (k1_3+2*k2_3+2*k3_3+k4_3)/6;
    p2 += (k1_4+2*k2_4+2*k3_4+k4_4)/6;

    i++;
  }
  void next_step_e()
  //Eurela
  {
    float n_p1, n_p2, n_w1, n_w2;
    e1 = next_e1();
    e2 = next_e2();
    n_w1 = w1+e1*h;
    n_w2 = w2+e2*h;
    w1 = n_w1;
    w2 = n_w2;
    p1 += w1*h;
    p2 += w2*h;
    i++;
  }

  friend ostream & operator<<(ostream & o, dp & _dp)
  {
    o << _dp.i*_dp.h << " " << _dp.p1 << " " << _dp.p2 << " " 
          << _dp.w1 << " " << _dp.w2 <<
        "\n";
    return o;
  }

};

int main(int argc, char** argv)
{
  ofstream f;
  if(argc < 2) f.open("out.dat");
  else f.open(argv[1]);

  dp w(100,1,1,0.001);
  while(w.i < 300000)
  {
    if(!(w.i % 100)) f << w;
    w.next_step();
  }
  f.close();
}
