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

namespace FMSParametrsGenerator
{
    public partial class MainWindow : Window
    {
        bool isInit = false;
        public MainWindow()
        {
            InitializeComponent();
            isInit = true;
        }


        void restructParameters()
        {
            if (isInit == false)
                return;


            try
            {
                OutputParametersTextBox.Text = "FileMergeSort.exe ";
                OutputParametersTextBox.Text += (SortModeComboBox.SelectedIndex == 0) ? "-a " : "-d ";
                OutputParametersTextBox.Text += (SortTypeComboBox.SelectedIndex == 0) ? "-i " : "-s ";
                OutputParametersTextBox.Text += (Math.Round(BufferSizeSlider.Value) != 50) ? "-b " + Math.Round(BufferSizeSlider.Value).ToString() + " " : "";
                OutputParametersTextBox.Text += OutputTextBox.Text + " ";
                OutputParametersTextBox.Text += InputTextBox.Text.Replace('\n', ' ').Replace('\r',' ');

            }
            catch (Exception)
            {
            }
        }

        private void BufferValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            restructParameters();
        }

        private void SortTypeSelectChanged(object sender, SelectionChangedEventArgs e)
        {
            restructParameters();
        }

        private void SortModeSelectChanged(object sender, SelectionChangedEventArgs e)
        {
            restructParameters();
        }

        private void OuputTextChanged(object sender, RoutedEventArgs e)
        {
            restructParameters();
        }
    }
}
