import ctypes
from ctypes import wintypes
import psutil  # Pour trouver le PID du processus

# Constantes pour accéder au processus
PROCESS_ALL_ACCESS = 0x1F0FFF

# Configuration des pointeurs
process_name = "ac_client.exe"
pointer_offsets = [0x00109B74, 0x0010F4F4, 0x0011E20C]  # Offsets des pointeurs

def get_process_id(process_name):
    """ Trouve le PID du processus """
    for proc in psutil.process_iter(['name', 'pid']):
        if proc.info['name'] == process_name:
            return proc.info['pid']
    raise Exception(f"Processus '{process_name}' introuvable.")

def get_module_base_address(pid, module_name):
    """ Récupère l'adresse de base d'un module dans un processus """
    TH32CS_SNAPMODULE = 0x00000008
    snapshot = ctypes.windll.kernel32.CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid)
    module_entry = ctypes.create_string_buffer(556)  # Taille du MODULEENTRY32
    ctypes.memset(module_entry, 0, ctypes.sizeof(module_entry))
    ctypes.cast(module_entry, ctypes.POINTER(ctypes.c_ulong))[0] = ctypes.sizeof(module_entry)

    if ctypes.windll.kernel32.Module32First(snapshot, module_entry):
        while True:
            module_name_bytes = module_entry[36:36+260].split(b'\x00', 1)[0]
            if module_name_bytes.decode("utf-8") == module_name:
                base_address = int.from_bytes(module_entry[8:12], byteorder='little')  # Adresse de base
                ctypes.windll.kernel32.CloseHandle(snapshot)
                return base_address
            if not ctypes.windll.kernel32.Module32Next(snapshot, module_entry):
                break
    ctypes.windll.kernel32.CloseHandle(snapshot)
    raise Exception(f"Module '{module_name}' introuvable.")

def read_pointer(handle, address):
    """ Lit la valeur pointée par l'adresse spécifiée """
    buffer = ctypes.create_string_buffer(4)  # 4 bytes pour un entier
    bytes_read = ctypes.c_size_t()
    if not ctypes.windll.kernel32.ReadProcessMemory(handle, ctypes.c_void_p(address), buffer, 4, ctypes.byref(bytes_read)):
        return None  # Échec de la lecture
    return int.from_bytes(buffer.raw, byteorder='little')

def read_nested_pointer(handle, address, depth=3):
    """ Lit un pointeur imbriqué jusqu'à la profondeur spécifiée """
    value = address
    for i in range(depth):
        if value is None:
            return None
        value = read_pointer(handle, value)
        print(f"Niveau {i+1} - Pointeur vers : {hex(value)}")
    return value

def main():
    try:
        # Trouver le PID du processus
        pid = get_process_id(process_name)

        # Récupérer l'adresse de base du module
        base_address = get_module_base_address(pid, process_name)
        print(f"Adresse de base de '{process_name}': {hex(base_address)}")

        # Ouvrir le processus
        process_handle = ctypes.windll.kernel32.OpenProcess(PROCESS_ALL_ACCESS, False, pid)
        print(f"Processus ouvert : {process_name}")

        # Lire les pointeurs imbriqués
        for i, offset in enumerate(pointer_offsets, start=1):
            address = base_address + offset
            print(f"\n--- Lecture du pointeur {i} ({hex(address)}) ---")
            final_value = read_nested_pointer(process_handle, address, depth=3)  # Profondeur de 3 pointeurs imbriqués
            if final_value is not None:
                print(f"Valeur finale de pointeur {i}: {final_value}")
            else:
                print(f"Pointeur {i}: Lecture impossible")

    finally:
        # Fermer le handle du processus
        ctypes.windll.kernel32.CloseHandle(process_handle)
        print("Processus fermé.")

if __name__ == "__main__":
    main()
