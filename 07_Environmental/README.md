# Сборка

```
mkdir build
cd build
cmake ..
make
```

# Опциональный флаг

cmake cache переменная `FORCE_GETLINE` явно включает считывание с помощью getline, даже если была найдена соответсвующая библиотека

```
cmake -DFORCE_GETLINE=ON ..
```

# Запуск тестов

через команду

```
make test
```
