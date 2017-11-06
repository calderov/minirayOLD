make
./miniray
cd renders
for file in *.bmp; do convert $file -rotate 180 $file; done
cd ..
ffmpeg -f image2 -framerate 25 -pattern_type sequence -start_number 0 -r 25 -i renders/frame%d.bmp render.mp4
