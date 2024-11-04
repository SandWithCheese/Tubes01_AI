# Tugas Besar 1 IF3170 Inteligensi Artifisial

## Deskripsi

Tugas Besar I pada kuliah IF3070 Dasar Inteligensi Buatan dan IF3170 Inteligensi Buatan bertujuan agar peserta kuliah mendapatkan wawasan tentang bagaimana cara mengimplementasikan algoritma local search untuk mencari solusi suatu permasalahan. Pada tugas ini, peserta kuliah akan ditugaskan untuk mengimplementasikan algoritma local search untuk mencari solusi Diagonal Magic Cube.

## Cara Menjalankan Program

### Kompilasi di Windows

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

### Kompilasi di WSL

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
    ./run.sh
    ```

Kompilasi Manual

1. Install Dependencies

    - C++
    - CMake
    - OpenGL
    - Python 3.10
    - Matplotlib
    - Numpy
    - X Server (WSL)

2. Pindah ke Folder `build`

    ```bash
    cd build
    ```

3. Jalankan CMake

    ```bash
    cmake ..
    ```

4. Build Binary

    ```bash
    make
    ```

5. Jalankan Program

    ```bash
    ./main
    ```

## Anggota dan Pembagian Tugas

| Nama                       | NIM      | Pembagian Tugas                                 |
|----------------------------|----------|-------------------------------------------------|
| Ahmad Naufal Ramadan       | 13522005 | Laporan, Stochastic, Genetic Algorithm, Plot, Cube (MagicFive) |
| Erdianti Wiga Putri Andini | 13522053 | Laporan, Steepest Ascent, Sideways Move        |
| Bagas Sambega Rosyada      | 13522071 | Laporan, Simulated Annealing, Cube (MagicFive) |
| Ahmad Mudabbir Arif        | 13522072 | Laporan, Random Restart, Visualisasi           |

