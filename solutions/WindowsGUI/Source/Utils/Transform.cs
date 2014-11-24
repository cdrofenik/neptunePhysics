using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Windows.Media;

namespace WindowsGUI.Source.Utils
{
    struct Vector3f
	{
		public float x, y, z;
	}

    struct Matrix3f
	{
        public double[,] localMatrix;
	}

    class Transform
    {
        Transform() { }

        //Matrix3f rotate(double degrees, Vector3f vector) {
        //    double radian = degrees * ( Math.PI / 180);
        //    Matrix3f result;
        //    //result.localMatrix[0,0] = Math.Cos(radian) + (1.0 - Math.Cos(radian)) * (vector.x * vector.x) + Math.Sin(radian) * 0.0;
        //    //result.localMatrix[0,1] = (1.0 - Math.Cos(radian)) * (vector.x * vector.x) + Math.Sin(radian) * 0.0;
        //    //result.localMatrix[0,2] =  (1.0 - Math.Cos(radian)) * (vector.x * vector.x) + Math.Sin(radian) * 0.0;
        //    //result.localMatrix[1,0] = (1.0 - Math.Cos(radian)) * (vector.x * vector.x) + Math.Sin(radian) * 0.0;
        //    //result.localMatrix[1,1] = Math.Cos(radian) + (1.0 - Math.Cos(radian)) * (vector.y * vector.y) + Math.Sin(radian) * 0.0;
        //    //result.localMatrix[1,2] = (1.0 - Math.Cos(radian)) * (vector.x * vector.x) + Math.Sin(radian) * 0.0;
        //    //result.localMatrix[2,0] = (1.0 - Math.Cos(radian)) * (vector.x * vector.x) + Math.Sin(radian) * 0.0;
        //    //result.localMatrix[2,1] = (1.0 - Math.Cos(radian)) * (vector.x * vector.x) + Math.Sin(radian) * 0.0;
        //    //result.localMatrix[2,2] = Math.Cos(radian) + (1.0 - Math.Cos(radian)) * (vector.z * vector.z) + Math.Sin(radian) * 0.0;
        //    return result;
        //}
    }
}
