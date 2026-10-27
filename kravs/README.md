# Kravs Roblox Executor (`~/kravs`)

> **[+]Meezo Tsardom[-]**

Modular Roblox Executor implementation adhering to the 8-phase architecture pipeline:
1. **Yükleme (Loader & Verification)**
2. **Enjeksiyon (Injection)**
3. **Kancalama (Hooking & Anti-Detection)**
4. **Çalışma Ortamı (Isolated Sandbox Environment)**
5. **API Köprüsü (API Bridge & Wrapper)**
6. **Zamanlayıcı (Script Scheduler & Queue)**
7. **Yürütme (Execution Engine)**
8. **Arayüz ve Çıktı (UI & Output Management)**

## Build & Run

```bash
mkdir build && cd build
cmake ..
make
./kravs_executor
```
