# Удаление поддеревьев
Дано некоторое двоичное дерево поиска. Также даны запросы на удаление из него
вершин, имеющих заданные ключи, причем вершины удаляются целиком вместе со
своими поддеревьями.
После каждого запроса на удаление выведите число оставшихся вершин в дереве.
В вершинах данного дерева записаны ключи — целые числа, по модулю не
превышающие 10<sup>9</sup>. Гарантируется, что данное дерево является двоичным деревом
поиска, в частности, для каждой вершины дерева V выполняется следующее
условие:
* все ключи вершин из левого поддерева меньше ключа вершины V;<br />
* все ключи вершин из правого поддерева больше ключа вершины V.<br />

Высота дерева не превосходит 25, таким образом, можно считать, что оно
сбалансировано.

Формат входного файла <br />
Входной файл содержит описание двоичного дерева и описание запросов на
удаление.

В первой строке файла находится число N (1 &le; N &le; 2 * 10<sup>5</sup>) — число вершин в
дереве. В последующих N строках файла находятся описания вершин дерева. В (i+1)-ой строке файла (1 &le; i &le; N) находится описание i-ой вершины, состоящее
из трех чисел K<sub>i</sub>, L<sub>i</sub>, R<sub>i</sub> разделенных пробелами — ключа в i-ой вершине (|K<sub>i</sub>| &le; 10<sup>9</sup>), номера левого ребенка i-ой вершины
(i &le; L<sub>i</sub> &le; N или L<sub>i</sub> = 0, если левого ребенка нет) и номера правого ребенка i-ой вершины (i &le; R<sub>i</sub> &le; N или R<sub>i</sub> = 0, если правого ребенка нет)
Все ключи различны. Гарантируется, что данное дерево является деревом поиска.
В следующей строке находится число M(1 &le; M &le; 2 * 10<sup>5</sup>) — число запросов на
удаление. В следующей строке находятся M чисел, разделенных пробелами —
ключи, вершины с которыми (вместе с их поддеревьями) необходимо удалить. Все эти
числа не превосходят 10<sup>9</sup> по абсолютному значению. Вершина с таким ключом не
обязана существовать в дереве — в этом случае дерево изменять не требуется.
Гарантируется, что корень дерева никогда не будет удален


Формат выходного файла <br />
Выведите M строк. На i-ой строке требуется вывести число вершин, оставшихся в
дереве после выполнения i-го запроса на удаление.
