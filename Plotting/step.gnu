
t = t + 1

set terminal jpeg
outfile = sprintf('animation/step%03.0f.png',t)
set output outfile
set dgrid3d 30,30
dataFile=sprintf('data/dataset_%d.txt',t)

set table dataFile.'.grid'
splot dataFile u 1:2:3
unset table

set table dataFile.'.color'
splot dataFile u 1:2:4
unset table

set view 60,45
set hidden3d
set palette defined (0 "blue", 0.5 "white", 1 "pink")
set autoscale cbfix
set pm3d
unset dgrid3d
set ticslevel 0

set title "4D data (3D Heat Map)"
set title  offset character 0, 1, 0 font "" norotate
#set xlabel "x"
#set ylabel "y"
#set zlabel "z"
set colorbox user
set colorbox vertical origin screen 0.9, 0.2 size screen 0.03, 0.6 front  noinvert noborder

splot sprintf('< paste %s.grid %s.color', dataFile, dataFile) u 1:2:3:7 with pm3d notitle

if(t<end_time) reread;
