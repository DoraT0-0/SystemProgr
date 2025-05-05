import psutil
import platform

def get_virtual_memory_info():
    """Получает информацию о виртуальной памяти."""
    mem = psutil.virtual_memory()
    print(f"Общий объем виртуальной памяти: {mem.total / (1024 ** 3):.2f} ГБ")
    print(f"Используемая виртуальная память: {mem.used / (1024 ** 3):.2f} ГБ")
    print(f"Свободная виртуальная память: {mem.free / (1024 ** 3):.2f} ГБ")
    print(f"Процент использования: {mem.percent}%")

def get_processor_info():
    """Получает информацию о процессоре."""
    print(f"Архитектура процессора: {platform.machine()}")
    print(f"Количество ядер процессора: {psutil.cpu_count(logical=False)}")
    print(f"Количество логических процессоров: {psutil.cpu_count(logical=True)}")

def get_system_info():
    """Получает общую информацию о системе."""
    print(f"Операционная система: {platform.system()}")
    print(f"Имя узла: {platform.node()}")
    print(f"Версия ОС: {platform.version()}")
    print(f"Процессор: {platform.processor()}")

def main():
    print("Информация о виртуальной памяти:")
    get_virtual_memory_info()
    print("\nИнформация о процессоре:")
    get_processor_info()
    print("\nОбщая информация о системе:")
    get_system_info()

if __name__ == "__main__":
    main()