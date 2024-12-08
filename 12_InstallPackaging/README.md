# Сборка

```
mkdir build
cd build
cmake ..
cmake --build .
cmake --install . --prefix /path/to/install
```

# Тесты

После сборки в дирректории `build` необходимо запустить

```
ctest
```

Тесты написаны для локалей `ru_RU.utf8` и `en_US`

# Локализация

В директории `lang` лежит шаблон `messages.pot` и два примера `ru_RU.po` и `en_US.po`.

Для добавления локализация `*.po` файл необходимо поместить в директорию `lang`, дальше `cmake` сам добавит его в сборку.

# Запуск

Смену локализации можно делать при помощи `LC_MESSAGES=[]` или `LC=[]`.

# Примеры

## Использование

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

## Установка

```shell
cmake --install . --prefix /tmp/qq
```

```shell
/tmp/qq:
bin  include  lib  share

/tmp/qq/bin:
binsearch

/tmp/qq/include:
binsearch.h

/tmp/qq/lib:
libbinsearchlib.a

/tmp/qq/share:
locale  man

/tmp/qq/share/locale:
en_US  ru_RU

/tmp/qq/share/locale/en_US:
LC_MESSAGES

/tmp/qq/share/locale/en_US/LC_MESSAGES:
messages.mo

/tmp/qq/share/locale/ru_RU:
LC_MESSAGES

/tmp/qq/share/locale/ru_RU/LC_MESSAGES:
messages.mo

/tmp/qq/share/man:
man1

/tmp/qq/share/man/man1:
binsearch.c.1  binsearch.h.1  library.1  md_README.1
```

Теперь при добавлении данной папки в PATH и в MANPATH можно будет смотреть мануал соответсвующими коммандами
