# output as png image
set terminal jpeg size 1280,720

# save file to "benchmark.png"
set output "benchmark-15000-n1000-d5.jpeg"

# graph title
set title "ab 15000 -n 1000 -c 5"

#nicer aspect ratio for image size
set size 1,0.7

# y-axis grid
set grid y

#x-axis label
set xlabel "seconds"

#y-axis label
set ylabel "response time (ms)"

# Tell gnuplot to use tabs as the delimiter instead of spaces (default)
set datafile separator '\t'

#plot data from "out.data" using column 9 with smooth sbezier lines
plot "worker.tsv" using 4 with lines title "Using workers", "native.tsv" using 4 with lines title  "Using native", "buffer.tsv" using 4 with lines title  "Using buffer"
exit