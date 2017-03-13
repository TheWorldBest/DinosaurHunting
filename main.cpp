/*
��������⣺��׮Χ����
��֪ÿ����׮������Ϳ��������꣬�ж�ͨ����׮�Ƿ�ɽ�����Χס��
���룺
�������ְ���1�У���2N���������ݣ�ǰ��2��N-1��Ϊ��׮���꣬���2��Ϊ�������ֵ����꣬N=[2, 101]��
�����
���ͨ����׮��Χס�������򷵻�true�����򷵻�false��

˼·��
��Ѱ��N���㣨�����������꣩����С���͹����Σ�Ȼ���жϿ��������Ƿ�Ϊ���͹����ε�һ���������꣬����ǣ�����Χס������false�����򷵻�true

Xinwei Qiu
2017/3/13
*/

#include <iostream>
#include <vector>
#include <numeric>
#include <limits>

using namespace std;

// ����2pi�Ƕ���ֵ
#define  CIRCLE_RADIANS  6.283185307179586476925286766559  
 
/*
��������x,y����x��ļн�[0,2pi)

@param x, y��������Ƕȵ�����(x,y)
return: �����нǣ������ƣ�[0,2pi)
*/
double angleOf(double x, double y) 
{
	double  dist = sqrt(x*x + y*y);

	if (y >= 0.) 
		return acos(x / dist);
	else       
		return acos(-x / dist) + .5*CIRCLE_RADIANS;
}

/* 
������֪��һϵ�е㣬Ѱ����С���͹�����

@param x, y������ĵ㼯������
@param numPoints������ĵ㼯�ĸ���
@param polyX, polyY���ҵ���͹����εĶ�������
@param numCorners���ҵ���͹����εĶ������
return��������һ������������Ϊ��͹����ε�һ�����㣬�򷵻�false������true
*/
bool findSmallestPolygon(double *x, double *y, long numPoints, double *polyX, double *polyY, long &numCorners) 
{
	double  newX = x[0], newY = y[0], xDif, yDif, oldAngle = .0*CIRCLE_RADIANS, newAngle, angleDif, minAngleDif;
	long    i;

	//  Find a starting point.  ȡ���Ͻǵ㣺��1��ȡy�������ĵ㣻��2�������������Ϸ���ȡx��С�ĵ�
	for (i = 0; i<numPoints; i++)
		if (y[i]>newY || y[i] == newY && x[i]<newX) {
			newX = x[i]; 
			newY = y[i];
		}
	numCorners = 0;

	//  Polygon-construction loop.  
	while (!(numCorners) || newX != polyX[0] || newY != polyY[0]) {
		polyX[numCorners] = newX;
		polyY[numCorners] = newY; 
		minAngleDif = CIRCLE_RADIANS;
		for (i = 0; i<numPoints; i++) {
			xDif = x[i] - polyX[numCorners];
			yDif = y[i] - polyY[numCorners];
			if (xDif || yDif) {
				newAngle = angleOf(xDif, yDif);   
				angleDif = oldAngle - newAngle;
				while (angleDif< 0.) 
					angleDif += CIRCLE_RADIANS;
				while (angleDif >= CIRCLE_RADIANS) 
					angleDif -= CIRCLE_RADIANS;
				if (angleDif<minAngleDif) {
					minAngleDif = angleDif; 
					newX = x[i]; 
					newY = y[i];
				}
				// ����Ƕ���ȣ�ȡ��Զ�ĵ�
				else if (angleDif == minAngleDif){
					double newXDif = newX - polyX[numCorners];
					double newYDif = newX - polyY[numCorners];
					if (abs(newXDif) < abs(xDif) || abs(newYDif) < abs(yDif))
					{
						minAngleDif = angleDif;
						newX = x[i];
						newY = y[i];
					}
				}
			}
		}
		// �ж��Ƿ��õ��˿������깹����С���͹����Σ�����Ϊ���һ�������
		if (newX == x[numPoints - 1] && newY == y[numPoints - 1])
		{
			return false;
		}
		(numCorners)++; 
		oldAngle -= minAngleDif;
	}
	return true;
}

/*������������������ʵ����ĿҪ��Ĺ���*/
/*��Ȼ����Ҳ���Բ������������ģ����������ȫ�����Լ����뷨�� ^-^ */
/******************************��ʼд����******************************/
bool dinosaurHunting(const std::vector<double>& positions) 
{
	int posNum = positions.size() / 2;
	double *x = new double[posNum]();
	double *y = new double[posNum]();

	double *polyX = new double[posNum]();
	double *polyY = new double[posNum]();

	long  numCorners = 0;

	for (int i = 0; i < posNum; i++)
	{
		x[i] = positions[i*2];
		*(y + i) = positions[i*2 + 1];
	}

	return findSmallestPolygon(x, y, posNum, polyX, polyY, numCorners);
}
/******************************����д����******************************/


int main() 
{
	bool res;
	double posTemp[] = { -1, 2, 1, 2, 1, -1, -1, -1, -1, 1, 0, 0 };
	vector<double> pos(begin(posTemp), end(posTemp));
	//double data;
	//while (cin >> data){
	//	pos.push_back(data);
	//}

	res = dinosaurHunting(pos);
	cout << res << endl;

	return 0;
}
