using System;
using System.Windows;
using System.Windows.Controls;

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
                OutputParametersTextBox.Text = string.Empty;
                OutputParametersTextBox.Text += (SortModeComboBox.SelectedIndex == 0) ? "-a " : "-d ";
                OutputParametersTextBox.Text += (SortTypeComboBox.SelectedIndex == 0) ? "-i " : "-s ";
                OutputParametersTextBox.Text += (Math.Round(BufferSizeSlider.Value) != 50) ? "-b " + Math.Round(BufferSizeSlider.Value).ToString() + " " : string.Empty;
                OutputParametersTextBox.Text += OutputTextBox.Text + " ";
                if (AutoPostfixAddCheckBox.IsChecked == false)
                {
                    OutputParametersTextBox.Text += InputTextBox.Text.Replace(" ", string.Empty).Replace("\n", string.Empty).Replace("\r"," ");
                } else
                {
                  var inputNames =  InputTextBox.Text.Replace(" ", "").Replace('\n', ' ').Split('\r');
                    foreach (var line in inputNames)
                    {
                        if (line.Length < 2) continue;
                        OutputParametersTextBox.Text += line;
                        if ((line.Length < 4) || (line.Substring(line.Length - 4) != ".txt"))
                            OutputParametersTextBox.Text += ".txt";
                        OutputParametersTextBox.Text += " ";
                    }
                }
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

      

        private void InputTextChanged(object sender, TextChangedEventArgs e)
        {
            restructParameters();
        }

        private void CheckedChanded(object sender, RoutedEventArgs e)
        {
            restructParameters();
        }
    }
}
