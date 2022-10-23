#include "./SVGdraw.h"
#include <iostream>
#include <cmath>
using namespace std;
void length_func(double homex, double homey, double postax, double postay, long double &length)
{
  length = sqrt(pow(homex - postax, 2) + pow(homey - postay, 2));
}
int main(void)
{
  double dist;
  const int MAXP = 10;
  const char *farby[MAXP] = {"red", "green", "blue", "white", "black", "gray",
                             "yellow", "brown", "orange", "purple"};
  int homes, postes;
  cin >> homes >> postes;
  double homes_arr[homes * 2];
  double postes_arr[postes * 2];
  for (int i = 0; i < homes * 2; i++)
  {
    double dot;
    cin >> dot;
    homes_arr[i] = dot;
  }
  for (int i = 0; i < postes * 2; i++)
  {
    double dot;
    cin >> dot;
    postes_arr[i] = dot;
  }

  int vX, vY;
  cin >> vX >> vY;
  cin >> dist;
  SVGdraw drawing(vX, vY, "posty.svg");
  long double length;
  int domov = 0;
  int MAXN = 10000;
  int array[MAXN];
  for (int i = 0; i < homes * 2; i += 2)
  {
    double data = 10000000000;
    int posta;
    for (int j = 0; j < postes * 2; j += 2)
    {
      length_func(homes_arr[i], homes_arr[i + 1], postes_arr[j], postes_arr[j + 1], length);
      if (data > length)
      {
        data = length;
        posta = j;
      }
    }
    drawing.setFillColor(farby[posta / 2]);
    array[i / 2] = posta / 2;
    drawing.drawLine(homes_arr[i], homes_arr[i + 1], postes_arr[posta], postes_arr[posta + 1]);
    drawing.drawRectangle(postes_arr[posta] - dist / 2, postes_arr[posta + 1] - dist / 2, dist, dist);
    drawing.drawEllipse(homes_arr[i], homes_arr[i + 1], dist / 2, dist / 2);
    cout << "dom " << domov << " posta " << posta / 2 << endl;
    domov++;
  }
  drawing.finish();
  for (int j = 0; j < postes; j++)
  {
    int res = 0;
    for (int i = 0; i < homes; i++)
    {
      if (j == array[i])
        res++;
    }
    cout << "posta " << j << " pocet domov " << res << endl;
  }
}