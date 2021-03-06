# Quack
Виртуальная машина, на которой исполняется программа на языке Quack, имеет
внутри себя очередь, содержащую целые числа по модулю 65536 (то есть, числа от 0
до 65535, соответствующие беззнаковому 16-битному целому типу). Слово get в
описании операций означает извлечение из очереди, put — добавление в очередь.
Кроме того, у виртуальной машины есть 26 регистров, которые обозначаются буквами
от 'a' до 'z'. Изначально все регистры хранят нулевое значение. В языке Quack
существуют следующие команды (далее под A и B подразумеваются некие
абстрактные временные переменные):
*   [&plus;]   Сложение: get A, get B, put (A + B) mod 65536<br />
*   [&minus;]   Вычитание: get A, get B, put (A - B) mod 65536<br />
*   [*]   Умножение: get A, get B, put (A * B) mod 65536<br />
*   [/] Целочисленное деление: get A, get B, put A div B (будем считать, A что div 0 = 0)<br />
*   [>[register]]   Положить в регистр: get A, установить значение [register] в A<br />
*   [<[register]]   Взять из регистра: put значение [register]<br />
*   [P]   Напечатать: get A, вывести A в стандартный поток вывода и перевести строку<br />
*   [P[register]]  Вывести значение регистра [register] в стандартный поток вывода и перевести строку<br />
*   [C]   Вывести как символ: get A, вывести символ с ASCII-кодом A mod 256 в стандартный поток вывода<br />
*   [C[register]]   Вывести регистр как символ: вывести символ с ASCII-кодом mod 256 (где A — значение регистра [register]) в стандартный поток вывода<br />
*   [:[label]]   Метка: эта строка программы имеет метку [label]<br />
*   [J[label]]   Переход на строку с меткой [label]<br />
*   [Z[register][label]]   Переход если 0: если значение регистра [register] равно нулю, выполнение программы продолжается с метки [label]<br />
*   [E[register1][register2][label]]   Переход если равны: если значения регистров [register1] и [register2] равны, исполнение программы продолжается с метки [label]<br />
*   [G[register1][register2][label]]   Переход если больше: если значение регистра [register1] больше, чем значение регистра [register2], исполнение программы продолжается с метки [label]<br />
*   [Q]   Завершить работу программы. Работа также завершается, если выполнение доходит до конца программы<br />
*   [[number]]   Просто число во входном файле — put это число<br />


Формат входного файла <br />
Входной файл содержит синтаксически корректную программу на языке Quack.
Известно, что программа завершает работу не более чем за 10<sup>5</sup> шагов. Программа
содержит не менее одной и не более 10<sup>5</sup> инструкций. Метки имеют длину от 1 до 10
и состоят из цифр и латинских букв.

Формат выходного файла <br />
Формат выходного файла
Выведите содержимое стандартного потока вывода виртуальной машины в выходной
файл.
