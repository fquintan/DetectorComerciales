 #!/bin/bash

time ./detector gray_32_3_3/videos/comerciales gray_32_3_3/videos/mega-2014_04_20T21_59_53.mp4.des results/gray_32_3_3.txt 100000

echo gray_32_3_3
echo ___________________________________________


time ./detector gray_32_4_4/videos/comerciales gray_32_4_4/videos/mega-2014_04_20T21_59_53.mp4.des results/gray_32_4_4.txt 100000

echo gray_32_4_4
echo ___________________________________________


time ./detector gray_64_3_3/videos/comerciales gray_64_3_3/videos/mega-2014_04_20T21_59_53.mp4.des results/gray_64_3_3.txt 100000

echo gray_64_3_3
echo ___________________________________________


time ./detector gray_64_4_4/videos/comerciales gray_64_4_4/videos/mega-2014_04_20T21_59_53.mp4.des results/gray_64_4_4.txt 100000

echo gray_64_4_4
echo ___________________________________________


time ./detector gray_128_3_3/videos/comerciales gray_128_3_3/videos/mega-2014_04_20T21_59_53.mp4.des results/gray_128_3_3.txt 100000

echo gray_128_3_3
echo ___________________________________________


time ./detector gray_128_4_4/videos/comerciales gray_128_4_4/videos/mega-2014_04_20T21_59_53.mp4.des results/gray_128_4_4.txt 100000

echo gray_128_4_4
echo ___________________________________________
