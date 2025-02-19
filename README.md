FileMergeSort - реализация сортировки файлов слиянием.

Является реализацией учебного ТЗ:

"Написать программу сортировки слиянием нескольких файлов.

Входные файлы содержат данные одного из двух видов: целые числа или строки. Данные записаны в
столбик (каждая строка файла – новый элемент). Строки могут содержать любые не пробельные символы.

Файлы должны быть предварительно отсортированы.

Результатом работы программы должен являться новый файл с объединенным содержимым входных
файлов, отсортированным по возрастанию или убыванию путем сортировки слиянием.

Если содержимое исходных файлов не позволяет произвести сортировку слиянием (например, нарушен
порядок сортировки), производится частичная сортировка (насколько возможно для этого алгоритма).

Выходной файл должен содержать отсортированные данные даже в случае ошибок, однако возможна
потеря ошибочных данных.

Необходимо самостоятельно реализовать алгоритм сортировки методом слияния и использовать его для
сортировки содержимого файлов. Не использовать библиотечные функции сортировки. Алгоритм должен
быть устойчив к большим файлам, не помещающимся целиком в оперативную память.

Все возможные виды ошибок должны быть обработаны. Программа не должна «падать». Если после
ошибки продолжить выполнение невозможно, программа должна сообщить об этом пользователю с
указанием причины неудачи. Частичная обработка при наличии ошибок более предпочтительна чем
останов программы.

Для реализации можно использовать любой язык программирования из списка:
Java, C, C++, C#, Python, Ruby, Scala, Pascal, PHP, Basic (можно предложить свой вариант).

Решение принимается в виде исходного кода проекта.

Параметры программы задаются при запуске через аргументы командной строки:
1. режим сортировки (-a или -d), необязательный, по умолчанию сортируем по возрастанию;
2. тип данных (-s или -i), обязательный;
3. имя выходного файла, обязательное;
4. остальные параметры – имена входных файлов, не менее одного."

==============Инструкция по запуску====================
1. Перейти в ветку "Release" и склонировать репозиторий
2. Находясь в корневой директории проекта, перейдите в папку "/Build"
3. Откройте консольное окно команд в текущей директории
4. Пропишите название исполняемого файла "FileMergeSort.exe" и параметры запуска, запустите


2 способа записи параметров запуска:
  1) Сгенерировать параметры в FMSParamGen
  2) В ручную, опираясь на правила

Для первого способа достаточно запустить “FMSParametrsGenerator.exe”, который находится в папке “/Build”. После запуска окна достаточно выбрать режим и тип сортировки, а также вписать названия входных файлов (каждое название с новой строчки), а также название выходного. Если есть необходимость, то можно изменить размер буфера по умолчанию (примерное кол-во ОЗУ которое будет задействовано во время выполнения программы). После чего достаточно просто скопировать сгенерированную команду запуска и вставить ее в консоль.

Для ручного ввода параметров необходимо знать правила и обозначения:
	 Обозначения: 
		“-a” - Сортировка по возрастанию
		“-d” - Сортировка по убыванию
		“-i” - Сортировка в числовом порядке
		“-s” - Сортировка в лексикографическом порядке
		
   “-b [size]“ - Задания размера буфера (в МБ), где “[size]” - число от 1 до 1000
    “*.txt” - Название файла
    
    Правила:
    1. Параметр типа сортировки (“-i”/”-s”), название входного, а также названия(-е) входных файлов - обязательные параметры, без них начало программы невозможно (по ТЗ)
    2. Если среди параметров обнаружен “-d”, то сортировка будет в режиме убывания, иначе в порядке возрастания
    3. Если было указано несколько типов сортировки, то лексикографическому порядку будет дано предпочтение.
    4. За название выходного файла берется первый параметр, у которого обнаружено расширение “txt”, все последующие файлы с тем же расширением будут рассмотрены как названия входных файлов
    5. Размер буфера необходимо указывать через пробел после параметра “-b”, между объявлением и инициализацией не должно быть других параметров, иначе  параметр будет проигнорирован. При многократном указании размера буфера, размер буфера будет равен последней успешной инициализации.

P.S. Большинство параметров может идти вразнобой, помимо тех, порядок которых указан в правилах.

Примеры:
 “FileMergeSort.exe -i out.txt in1.txt in2.txt”
 
 Сортировка по числовому возрастанию. 
 “out.txt” - выходной файл.
 “in1.txt”, “in2.txt” - выходные файлы.
 Буфер - 50МБ.

“FileMergeSort.exe -d -s -b 152 out.txt in1.txt in2.txt”

Сортировка по лексикографическому убыванию.
“out.txt” - выходной файл.
“in1.txt”, “in2.txt” - выходные файлы.
Буфер - 152МБ.

“FileMergeSort.exe out.txt  -b 512 -i in1.txt -s -i  in2.txt”

Сортировка по лексикографическому возрастанию.
“out.txt” - выходной файл.
“in1.txt”, “in2.txt” - выходные файлы.
Буфер - 512МБ.
