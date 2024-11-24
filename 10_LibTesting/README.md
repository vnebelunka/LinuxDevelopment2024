# Growable Memory Buffers for C99

Основано на (<https://github.com/skeeto/growable-buf/tree/master>)

# Запуск

```shell
mkdir build
cd build
cmake ..
make
```

# Запуск тестов

```
make test
```

или

```
ctest -T test
```

при желании запустить лишь частов тестов можно использоватьа `ctest -R <PREFIX>`
где `<PREFIX>` - префикс названия тестов. например

```
ctest -R clear
```

запустит

```
clear
clear empty
clear no-op
```

информация о тестах обычно лежит в `build/Testing/Temporary/LastTest.log` / `build/Testing/Temporary/LastTestFailed.log`

# Проверка покрытия

```
ctest -T test
ctest -T coverage
```

Подробная информация по файлам лежит в `build/Testing/CoverageInfo/*<filename>.gcov`
