#include "gridCreationClass.h"
#include <time.h>

gridCreationClass::gridCreationClass(float biome, float steepness,float height, float width)
{
	srand(time(NULL));
	PerlinNoise pn;
	double r = rand();
	_width = width;
	_height = height;

	for (int a = 0; a < width; a++)
	{
		for (int b = 0; b < height; b++)
		{	
			double n = pn.noise(((a/width)+r *width)*2, 10 *2, ((b/height) +r *height)*2);
			vertices.push_back(VertexType(XMFLOAT3(origin.x + a, n*biome, origin.z + b), XMFLOAT2(0, 0)));				
			vertices.back().setTex(XMFLOAT2(0, 1 - setValues(vertices.back().position.y /4)));
			heightPoint.push_back(n*biome);
			costDifference.push_back(0);
		}
	}
		for (int w = 0; w < width - 1; w++)
		{
			for (int x = 0; x < height - 1; x++)
			{
				indicies.push_back(int(w * height) + x);
				indicies.push_back(int(w * height) + x + 1);
				indicies.push_back(int(w * height) + x + height);

				indicies.push_back(int(w * height) + x + 1);
				indicies.push_back(int(w * height) + x + height + 1);
				indicies.push_back(int(w * height) + x + height);
			}
		}
}

gridCreationClass::~gridCreationClass()
{


}

float gridCreationClass::setValues(float input)
{

	if (input > 1)
	{
		return 1;
	}
	return input;
}