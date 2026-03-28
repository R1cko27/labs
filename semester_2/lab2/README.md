# Lab 2 (semester_2/lab2)

Этот репозиторий содержит реализацию лабораторной работы №2 для курса по структурам данных (C). Проект включает:

- двоичное дерево поиска с удалением по ключу и экспортом в JSON
- работу с учебными группами (структура `StudyGroup`)
- стек (`push`, `pop`)
- множество на упорядоченном списке (insert / remove / union / intersection)
- кольцевую двусвязную очередь (enqueue / dequeue)
- сериализацию/десериализацию бинарных деревьев (`tree.bin`, `full_tree.bin`)

## Файлы

- `main.c` - бинарное дерево `int`:
  - вставка, удаление (без дубликатов), печать текстового графического дерева
  - экспорт структуры в JSON (`export1.json`, `export2.json`)

- `main2.c` - расширенное дерево `StudyGroup`:
  - чтение групп из `groups.txt` или ввод с клавиатуры
  - сравнение/удаление/печать
  - экспорт в JSON (`export3.json` .. `export6.json`)
  - запись/чтение (неупорядоченное: `tree.bin`) и структуру с сохранением порядка (префиксное) `full_tree.bin`

- `study_group.h`, `study_group.c`:
  - структура `StudyGroup`
  - проверки корректности (`validate_study_group`)
  - инициализация (`init_study_group`)
  - сравнение и сортировка (`are_study_groups_equal`, `is_study_group_less`)
  - вывод на экран

- `list_structures.h`, `list_structures.c`:
  - стек (`Node`, `push`, `pop`, `print_list`, `delete_list`)
  - упорядоченное множество `StudyGroup` (`SetNode`): вставка, удаление, `union`, `intersection`, `contains`, печать
  - кольцевая очередь (`QueueNode`): `enqueue`, `dequeue`, `print_queue`, `delete_queue`

- `groups.txt` - данные для `main2.c` (формат `group_name;direction;year;level`)

- `блок_схема.json` - блок-схема алгоритмов (для отчетов)

- `.bin` и `.json` файлы - результаты выполнения, промежуточное хранилище
- `export/` — рекомендуемая папка для `export1.json`..`export6.json` (можно визуализировать на https://artem.email/tree)

## Формат `groups.txt`

Каждая строка:
`<group_name>;<direction>;<year>;<level>`

Где:
- `group_name` (до 10 символов, например `AP-526`)
- `direction`: `IS`, `PI`, `AI`, `PR`, `VT`
- `year`: год набора (int)
- `level`: `B` (бакалавр) или `M` (магистр)

Пример:
```
AP-526;IS;2023;B
CS-620;PI;2022;B
```

## Сборка и запуск

На Windows (компилятор `gcc`, `cl` и т.п.):

```bash
gcc -o main.exe main.c
gcc -o main2.exe main2.c study_group.c list_structures.c
```

Запуск:

```bash
./main.exe
./main2.exe
```

Если используете `main2.exe`, сначала выберите режим ввода:
1) из файла `groups.txt` (рекомендуется)
2) вручную (не более 100 групп)

Далее программа запишет JSON-файлы и бинарные деревья:
- `export3.json`..`export6.json`
- `tree.bin`, `full_tree.bin`

## Что протестировано

- вставка/удаление/печать бинарного дерева на `main.c` и `main2.c`
- сохранение/загрузка из `tree.bin`, `full_tree.bin`
- работа со стеком, множеством и очередью в `list_structures.c`
- валидация структуры `StudyGroup` (имя, направление, год, уровень)

## Рекомендации

- перед вводом данных убедитесь, что год набора актуален, иначе он корректируется в коде на текущий год
- чтобы избежать дубликатов в множестве, используйте уникальное `group_name` и валидные поля `direction`/`level`

---