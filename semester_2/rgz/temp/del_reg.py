import os

def rename_files_to_lower():
    # Получаем путь к папке, где находится скрипт
    current_dir = os.path.dirname(os.path.abspath(__file__))
    
    # Перебираем все файлы в текущей папке
    for filename in os.listdir(current_dir):
        # Полный путь к файлу
        old_path = os.path.join(current_dir, filename)
        
        # Пропускаем папки (если нужно переименовывать только файлы)
        if os.path.isfile(old_path):
            # Пропускаем сам скрипт, чтобы он не переименовал сам себя
            if filename == os.path.basename(__file__):
                continue
            
            # Переводим имя файла в нижний регистр
            new_filename = filename.lower()
            new_path = os.path.join(current_dir, new_filename)
            
            # Переименовываем только если имя изменилось
            if old_path != new_path:
                os.rename(old_path, new_path)
                print(f"Переименован: {filename} -> {new_filename}")

if __name__ == "__main__":
    rename_files_to_lower()
    print("Готово!")