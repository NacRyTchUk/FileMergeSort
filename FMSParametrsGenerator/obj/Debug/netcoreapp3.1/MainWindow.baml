   M S B A M L   `   `   `  ����P  LFMSParametrsGenerator, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null=#clr-namespace:FMSParametrsGeneratorFMSParametrsGenerator  5   	   &     FMSParametrsGenerator.MainWindow   5   	   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35e aSystem.Windows.Controls.Ribbon, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35F 9http://schemas.microsoft.com/winfx/2006/xaml/presentation     5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   5local#clr-namespace:FMSParametrsGenerator     5   	     � Title$  FMS Parameters genetator��5	   	    � 
ResizeMode$ NoResize=�6*   $	��510��6@   $	��410��6M   .��5      �  � ColumnDefinitions 5   
   �� 5      $
��367* �6   �� 5      $	��33* �6   .+�5   
   �� $��	Sort mode��6   $
��Left=�6$   $��Center=�6?   $��	52,10,0,0q�6c   $	��Top=�6v   $��84��6�   �� 5   
   $��	Sort type��6   $
��Left=�6$   $��Center=�6?   $��
259,10,0,0q�6c   $	��Top=�6w   $��70��6�   �� 5   
   $
��1 MB��6   $
��Left=�6   $��Center=�6:   $��	33,95,0,0q�6^   $	��Top=�6q   $��39��6�   �� 5   
   $��1000 MB��6   $
��Left=�6"   $��Center=�6=   $��
297,95,0,0q�6a   $	��Top=�6u   $��57��6�   �� 5   
   $��Output file name��6   $
��Left=�6+   $��
34,352,0,0q�6F   $	��Top=�6Z   $	��122��6r   �� 5   
   $��Input file names��6   $
��Left=�6+   $��
33,154,0,0q�6F   $	��Top=�6Z   $	��121��6r   �� 5   
   $��Buffer size��6   $
��Left=�6&   $��
129,68,0,0q�6A   $	��Top=�6U   $��84��6m   �� 5   
   -   5         ��Name$ SortModeComboBox��5      $
��Left=�6-   $��	33,41,0,0q�6H   $	��Top=�6[   $	��120��6s   .@�5      ��  �� 
IsSelected$
 True��6   .��6-   
Increase67   �� 5      .��6   
Decrease6%   5      �� 5   
   -   5        $ SortTypeComboBox��5      $
��Left=�6-   $��
238,41,0,0q�6H   $	��Top=�6\   $	��120��6t   $��2��6�   .@�5      �� $
 True��6   .��6-   	Integer66   �� 5      .��6   String6#   5      �� 5   
   -   5         ��Name$ BufferSizeSlider��5      $
��Left=�6+   $��	72,99,0,0q�6F   $	��Top=�6Y   $	��226��6q    � Minimum$ 1Q�5        � Maximum$
 1000Q�6    � Value$ 50Q�6,   	 � SmallChange$	 1Q�6Y   
 � LargeChange$
 10Q�6i    �� TickFrequency$ 10Q�6z   �� 5!   
   -   5         ��Name$ OutputTextBox��5!      $
��Left=�6)   $��
33,378,0,0q�6D   $��
output.txt��6X    �� TextWrapping$ NoWrap=�6j   $	��Top=�6�   $	��325��6�   $��2��6�   �� 5"   
   -   5        $ InputTextBox��5"       �� AcceptsReturn$
 True��6)   $
��Left=�6>   $��
33,185,0,0q�6Y   $��in1.txt��6m   $ NoWrap=�6|   $	��Top=�6�   $	��325��6�   $	��162��6�   $��2��6�   �� 5#   
   -   5        $ OutputParametersTextBox��5#      $
��Left=�63   $��
33,436,0,0q�6N   $0��*FileMergeSort.exe -a -i output.txt in1.txt��6b   $ NoWrap=�6�    �� 
IsReadOnly$
 True��6�   $	��Top=�6�   $	��325��6�   $��2��6�   �� 5$   
   $��Generated parameters��6   $��Center=�6/   $
��Left=�6S   $��116,410,0,0q�6n   $	��Top=�6�   $	��138��6�   �� 5%   
   -   5         ��Name$ AutoPostfixAddCheckBox��5%      $��Auto add ".txt"��63   $
��Left=�6W   $��256,160,0,0q�6r   $	��Top=�6�   5(      5)      