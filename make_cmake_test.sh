
# echo "Hello World !"

# printf "%-10s %-8s %-4s\n" 姓名 性别 体重kg  
# printf "%-10s %-8s %-4.2f\n" 郭靖 男 66.1234 
# printf "%-10s %-8s %-4.2f\n" 杨过 男 48.6543 
# printf "%-10s %-8s %-4.2f\n" 郭芙 女 47.9876 

 if [  -d "./bin" ]; then
    #mkdir ./build
    rm -rf build
    echo “删除”
 fi

 if [ ! -d "./bin" ]; then
    mkdir ./build
 fi

#删除命令
#

cd ./bin
cmake ..
make 
#  cd bin
#  ./main