while (true)
echo Leaks in FDF:;
do leaks -q fdf | grep "ROOT LEAK" | wc -l;
sleep 2;
clear;
done;
