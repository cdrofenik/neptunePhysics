using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using SharpGL;
using SharpGL.SceneGraph;
using SharpGL.SceneGraph.Primitives;

namespace WindowsGUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void DrawGrid(OpenGL gl)
        {
            gl.Begin(OpenGL.GL_LINES);
            for (int i = 0; i <= 10; i++)
            {
                gl.Color(.25, .25, .25);
                gl.Vertex(i, 0, 0);
                gl.Vertex(i, 0, 10);
                gl.Color(.25, .25, .25);
                gl.Vertex(0, 0, i);
                gl.Vertex(10, 0, i);
            };
            gl.End();
        }

        private void OpenGLControl_OpenGLDraw(object sender, OpenGLEventArgs args)
        {
            //  Get the OpenGL instance that's been passed to us.
            OpenGL gl = args.OpenGL;

            //  Clear the color and depth buffers.
            gl.Clear(OpenGL.GL_COLOR_BUFFER_BIT | OpenGL.GL_DEPTH_BUFFER_BIT);

            //  Reset the modelview matrix.
            gl.LoadIdentity();

            //  Move the geometry into a fairly central position.
            gl.Translate(-5.5f, -2.0f, -16.0f);

            //  Draw a pyramid. First, rotate the modelview matrix.
            //gl.Rotate(rotatePyramid, 1.0f, 0.0f, 0.0f);

            DrawGrid(gl);

            //  Flush OpenGL.
            gl.Flush();

            //  Rotate the geometry a bit.
            rotatePyramid += 3.0f;
            rquad -= 3.0f;
        }

        float rotatePyramid = 0;
        float rquad = 0;

        private void OpenGLControl_OpenGLInitialized(object sender, OpenGLEventArgs args)
        {
            //  Enable the OpenGL depth testing functionality.
            args.OpenGL.Enable(OpenGL.GL_DEPTH_TEST);
        }

        private void OpenGLControl_Resized(object sender, OpenGLEventArgs args)
        {
            //  Get the OpenGL instance.
            OpenGL gl = args.OpenGL;

            //  Load and clear the projection matrix.
            gl.MatrixMode(OpenGL.GL_PROJECTION);
            gl.LoadIdentity();

            // Calculate The Aspect Ratio Of The Window
            gl.Perspective(45.0f, (float)gl.RenderContextProvider.Width / (float)gl.RenderContextProvider.Height,
                0.1f, 100.0f);

            //  Load the modelview.
            gl.MatrixMode(OpenGL.GL_MODELVIEW);
        }

        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
    }
}
