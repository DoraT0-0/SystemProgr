import os
import ctypes
import mmap
import time

# Функция для записи текста и графики из буфера обмена в файл
def write_to_file(filename):
    # Получение текста из буфера обмена
    text = ctypes.windll.user32.GetClipboardData(1)
    if text:
        with open(filename, 'w') as file:
            file.write(text)
        print("Текст успешно записан в файл.")
    else:
        print("Ошибка при получении текста из буфера обмена.")

# Функция для чтения данных из файла и их передачи в буфер обмена
def read_from_file(filename):
    # Чтение данных из файла
    with open(filename, 'r') as file:
        data = file.read()
    # Передача данных в буфер обмена
    ctypes.windll.user32.SetClipboardData(1, data)
    print("Данные успешно переданы в буфер обмена.")

# Функция для передачи данных через именованный канал
def transfer_data(filename):
    # Создание именованного канала
    pipe_name = r'\\.\pipe\example_pipe'
    pipe = os.open(pipe_name, os.O_RDWR)
    # Чтение данных из файла
    with open(filename, 'r') as file:
        data = file.read()
    # Передача данных через именованный канал
    os.write(pipe, data.encode())
    print("Данные успешно переданы через именованный канал.")

# Пример использования функций
if __name__ == "__main__":
    filename = "example.txt"
    write_to_file(filename)
    time.sleep(1)  # Пауза для ожидания записи в файл
    read_from_file(filename)
    time.sleep(1)  # Пауза для ожидания передачи в буфер обмена
    transfer_data(filename)