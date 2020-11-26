[![Build Status](https://travis-ci.com/wazovskii/os.svg?branch=master)](https://travis-ci.com/github/wazovskii/os)

# os
## Лабораторная 3. Работа с процессами в ОС Linux. Создание проекта «LiteSH»


#### Язык программирования: С/С++

#### Автор Nizamova Veronika
#### Реализовано:
##### В проекте обрабатывается аргумент "-h" для вывода справки, в которой отображаются:
- Авторы;
- Все доступные аргументы;
- Краткое описание проекта;
- Примеры запуска.
- Сборка проекта будет осуществлятся с помощью Make
##### В проекте обрабатывается аргумент "-t" для переноса файла в другую директорию, пример:
- -t /Users/wazovski/Desktop/distant/oss/test.txt /Users/wazovski/Desktop/distant/tes
##### В проекте обрабатывается аргумент "-r" для удаления файла, пример:
- -r to delete file example:\n -r /Users/wazovski/Desktop/distant/oss/test.txt
##### В проекте обрабатывается аргумент "-c" для создания копии файла, пример:
- -c /Users/wazovski/Desktop/distant/oss/test.txt /Users/wazovski/Desktop/distant/oss/test1.txt
##### В проекте обрабатывается аргумент "-s" для измерения размера директории или файла, пример:
- -s /Users/wazovski/Desktop/distant/oss/test.txt
##### В проекте обрабатывается аргумент "-ls" для вывода всего содержимого директории, пример:
- -ls /Users/wazovski/Desktop/distant/oss
##### В проекте обрабатывается аргумент "-pr" для вывода запущенных процессов из директории /proc, пример:
- -pr

- Умеет порождать процесс по его имени и возвращается в строку ввода команд после завершения дочернего процесса;
