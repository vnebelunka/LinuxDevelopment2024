# Сборка

```
mkdir build
cd build
make
```

# Локализация

В директории `lang` лежит шаблон `messages.pot` и два примера `ru_RU.po` и `en_US.po`.

Для добавления локализация `*.po` файл необходимо поместить в директорию `lang`, дальше `cmake` сам добавит его в сборку.

# Запуск

Смену локализации можно делать при помощи `LC_MESSAGES=[]` или `LC=[]`.

# Очистка

с помощью команды `make clean`

# Примеры

```shell
$ build/binsearch 
число больше чем 50?
да
число больше чем 75?
?
неизвестная команда. Возможные варианты ответа: да/нет.
число больше чем 75?
нет
число больше чем 62?
нет
число больше чем 56?
нет
число больше чем 53?
нет
число больше чем 51?
нет
число больше чем 50?
нет
ответ это 50!
```

```shell
$ LC_MESSAGES=en_US build/binsearch 
number is greater than 50?
yes
number is greater than 75?
yes
number is greater than 87?
yes
number is greater than 93?
yes
number is greater than 96?
yes
number is greater than 98?
yes
number is greater than 99?
yes
number is greater than 99?
yes
answer is 100!
```
