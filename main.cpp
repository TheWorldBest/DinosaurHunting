/*
阿里笔试题：树桩围恐龙
已知每个树桩的坐标和恐龙的坐标，判断通过树桩是否可将恐龙围住。
输入：
输入数字包含1行，共2N个浮点数据，前面2（N-1）为树桩坐标，最后2个为恐龙出现的坐标，N=[2, 101]；
输出：
如果通过树桩能围住恐龙，则返回true，否则返回false；

思路：
先寻找N个点（包括恐龙坐标）的最小外接凸多边形，然后判断恐龙坐标是否为这个凸多边形的一个顶点坐标，如果是，则不能围住，返回false，否则返回true

Xinwei Qiu
2017/3/13
*/

#include <iostream>
#include <vector>
#include <numeric>
#include <limits>

using namespace std;

// 定义2pi角度数值
#define  CIRCLE_RADIANS  6.283185307179586476925286766559  
 
/*
求向量（x,y）与x轴的夹角[0,2pi)

@param x, y：待计算角度的向量(x,y)
return: 向量夹角，弧度制，[0,2pi)
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
根据已知的一系列点，寻找最小外接凸多边形

@param x, y：输入的点集的坐标
@param numPoints：输入的点集的个数
@param polyX, polyY：找到的凸多边形的顶点坐标
@param numCorners：找到的凸多边形的顶点个数
return：如果最后一个点的坐标参与为该凸多边形的一个顶点，则返回false，否则true
*/
bool findSmallestPolygon(double *x, double *y, long numPoints, double *polyX, double *polyY, long &numCorners) 
{
	double  newX = x[0], newY = y[0], xDif, yDif, oldAngle = .0*CIRCLE_RADIANS, newAngle, angleDif, minAngleDif;
	long    i;

	//  Find a starting point.  取左上角点：（1）取y轴上最大的点；（2）如多个点在最上方，取x最小的点
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
				// 如果角度相等，取最远的点
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
		// 判断是否用到了恐龙坐标构建最小外接凸多边形，恐龙为最后一个坐标点
		if (newX == x[numPoints - 1] && newY == y[numPoints - 1])
		{
			return false;
		}
		(numCorners)++; 
		oldAngle -= minAngleDif;
	}
	return true;
}

/*请完成下面这个函数，实现题目要求的功能*/
/*当然，你也可以不按照下面这个模板来作答，完全按照自己的想法来 ^-^ */
/******************************开始写代码******************************/
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
/******************************结束写代码******************************/


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
