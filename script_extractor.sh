 #!/bin/bash

mkdir gray_32_3_3
mkdir gray_32_3_3/videos
mkdir gray_32_3_3/videos/comerciales

time ./extractor gray_32_3_3/videos/comerciales GRAY_32_3_3 gray_32_3_3/videos/comerciales
time ./extractor gray_32_3_3/videos GRAY_32_3_3 gray_32_3_3/videos

echo gray_32_3_3
echo ___________________________________________



mkdir gray_32_4_4
mkdir gray_32_4_4/videos
mkdir gray_32_4_4/videos/comerciales

time ./extractor gray_32_4_4/videos/comerciales GRAY_32_4_4 gray_32_4_4/videos/comerciales
time ./extractor gray_32_4_4/videos GRAY_32_4_4 gray_32_4_4/videos

echo gray_32_4_4
echo ___________________________________________


mkdir gray_64_3_3
mkdir gray_64_3_3/videos
mkdir gray_64_3_3/videos/comerciales

time ./extractor gray_64_3_3/videos/comerciales GRAY_64_3_3 gray_64_3_3/videos/comerciales
time ./extractor gray_64_3_3/videos GRAY_64_3_3 gray_64_3_3/videos

echo gray_64_3_3
echo ___________________________________________


mkdir gray_64_4_4
mkdir gray_64_4_4/videos
mkdir gray_64_4_4/videos/comerciales

time ./extractor gray_64_4_4/videos/comerciales GRAY_32_4_4 gray_64_4_4/videos/comerciales
time ./extractor gray_64_4_4/videos GRAY_64_4_4 gray_64_4_4/videos

echo gray_64_4_4
echo ___________________________________________


mkdir gray_128_3_3
mkdir gray_128_3_3/videos
mkdir gray_128_3_3/videos/comerciales

time ./extractor gray_128_3_3/videos/comerciales GRAY_128_3_3 gray_128_3_3/videos/comerciales
time ./extractor gray_128_3_3/videos GRAY_128_3_3 gray_128_3_3/videos

echo gray_128_3_3
echo ___________________________________________


mkdir gray_128_4_4
mkdir gray_128_4_4/videos
mkdir gray_128_4_4/videos/comerciales

time ./extractor gray_128_4_4/videos/comerciales GRAY_128_4_4 gray_128_4_4/videos/comerciales
time ./extractor gray_128_4_4/videos GRAY_128_4_4 gray_128_4_4/videos

echo gray_128_4_4
echo ___________________________________________

