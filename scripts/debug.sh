valgrind -s --track-origins=yes --leak-check=full build/main $1
rm vgcore*