cat > README.md << 'EOF'
# Курсовой проект (C++ и Java)

**Автор:** Semyon Polyakov  
**Группа:** 53  
**Год:** 2026

## О проекте

Краткое описание курсового проекта.

## Структура

- `cpp/` — исходники C++
- `java/` — исходники Java
- `docs/` — документация
- `tests/` — тесты

## Сборка и запуск

### C++

```bash
cd cpp
g++ -static -finput-charset=UTF-8 -fexec-charset=UTF-8 src/main.cpp -Iinclude -o app.exe
./app.exe