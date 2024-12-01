# Где что лежит

При сборке

```shell
mkdir build
cd build
cmake ..
make
```

по пути `build/docs/man/man1` находится мануал к данной программе.

# Пример использования

## help

```shell
Использование: binsearch [-r]
Простая игра "угадай число" на интервале [1, 100] с использованием бинарного поиска.
Допустимые ответы: да/нет на каждый ответ.

-h, --help                 Вывести эту подсказку об использовании
-r                         Использовать в игре Римские цифры
```

```shell
Usage: binsearch [-r]
Simple "guess number" game in interval [1, 100] with binary search.
Possible answers: yes/no for each question.

-h, --help                 Give this help list
-r                         Use romanian numbers in game
```

## examples

```shell
./binsearch
число больше чем 50?
да
число больше чем 75?
да
число больше чем 87?
нет
число больше чем 81?
нет
число больше чем 78?
да
число больше чем 79?
нет
число больше чем 78?
да
ответ это 79!
```

```shell
./binsearch -r 
число больше чем L?
нет
число больше чем XXV?
нет
число больше чем XIII?
нет
число больше чем VII?
нет
число больше чем IV?
да
число больше чем V?
да
число больше чем VI?
да
число больше чем VI?
да
ответ это VII!
```
