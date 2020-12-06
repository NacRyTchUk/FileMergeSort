using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
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
using System.Diagnostics;

namespace FMSTestTool
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private const string INPUT_FILE_PREFIX = "inTest", OUTPUT_PREDICT_FILE_NAME = "outTest.txt", OUTPUT_REAL_FILE_NAME = "outReal.txt";
        public MainWindow()
        {
            InitializeComponent();
        }

        private void TestFileGenerator(int inputFilesCount, int maxValue, bool isIntType)
        {
            List<StreamWriter> inputFiles = new List<StreamWriter>();
            for (int i = 0; i < inputFilesCount; i++) 
                inputFiles.Add(new StreamWriter(INPUT_FILE_PREFIX + (i+1) + ".txt"));
            StreamWriter outputFile = new StreamWriter(OUTPUT_PREDICT_FILE_NAME);

            Random rnd = new Random();

            if (isIntType)
            {
                for (int i = 0; i < maxValue; i += rnd.Next(0, 2))
                {
                    inputFiles[rnd.Next(0, inputFilesCount)].WriteLine(i.ToString());
                    outputFile.WriteLine(i.ToString());
                }
            } else
            {
                string 
            }

            foreach (var f in inputFiles) f.Close();
            outputFile.Close();
        }

        public void StartTest()
        {
            bool isIntType = true, isDeacreaseMode = false;
            int inFileCount = 5, maxValue = 1000;

        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
           //                                                TestFileGenerator(5, 1000);
            Process.Start("FileMergeSort.exe", "-i out.txt inTest1.txt inTest2.txt  inTest3.txt inTest4.txt  inTest5.txt").WaitForExit();
            MessageBox.Show("done");
        }
    }
}
