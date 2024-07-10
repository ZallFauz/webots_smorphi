# webots smorphi
webots smorphi adalah simulasi platform robot smorphi yang dikembangkan oleh wefaa robotics pada software webots. Simulasi ini sudah dijalankan pada sistem operasi linux ubuntu dan webots versi 2023b 

# cara install
1. install icecream-cpp dari [https://github.com/renatoGarcia/icecream-cpp.git](https://github.com/renatoGarcia/icecream-cpp.git)
2. install msgpack library
   ```bash
   sudo apt install msgpack
   ```
3. clone repository ini
4. change directory ke smor_cpp
5. build program
   ```bash
   export WEBOTS_HOME=/usr/local/webots
   cmake .
   cmake --build .
   ```
6. change directory ke smorphi_slave
7. lakukan cara 5
8. change directory ke smorphi_slave2
9. lakukan cara 5
    
# cara menjalankan simulasi
1. buka software webots
2. file -> open world -> kemudian pilih youbot.wbt pada folder worlds
3. klik tombol panah untuk menggerakkan robot

# catatan
untuk saat ini baru modul master (berwarna cyan) yang dapat menerima perintah move
