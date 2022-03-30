while (true)
echo Leaks in Push_Swap:;
do leaks -q push_swap | grep "ROOT LEAK" | wc -l;
sleep 2;
clear;
done;
