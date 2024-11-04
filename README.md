# Tugas Besar 1 IF3170 Inteligensi Artifisial

## Deskripsi

Tugas Besar I pada kuliah IF3070 Dasar Inteligensi Buatan dan IF3170 Inteligensi Buatan bertujuan agar peserta kuliah mendapatkan wawasan tentang bagaimana cara mengimplementasikan algoritma local search untuk mencari solusi suatu permasalahan. Pada tugas ini, peserta kuliah akan ditugaskan untuk mengimplementasikan algoritma local search untuk mencari solusi Diagonal Magic Cube.

## Cara Menjalankan Program

Kompilasi di Windows

1. Install [X Server](https://sourceforge.net/projects/vcxsrv/)

2. Konfigurasi X Server

3. Build Docker

    ```bash
    docker build -t cpp-opengl-app .

    ```

4. Jalankan Program

    ```bash
    ./run.bat
    ```

Kompilasi di WSL

1. Install X Server

    ```bash
    sudo apt install x11-xserver-utils
    ```

2. Konfigurasi X Server

    ```bash
    xhost +local:docker
    ```

3. Build Docker

    ```bash
    docker build -t cpp-opengl-app .

    ```

4. Jalankan Program

    ```bash
    docker run -it --rm \
    -e DISPLAY=$DISPLAY \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    --network=host \
    cpp-opengl-app
    ```

## Anggota

| Nama                       | NIM      |
|----------------------------|----------|
| Ahmad Naufal Ramadan       | 13522005 |
| Erdianti Wiga Putri Andini | 13522053 |
| Bagas Sambega Rosyada      | 13522071 |
| Ahmad Mudabbir Arif        | 13522072 |
