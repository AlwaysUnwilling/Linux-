#!/bin/bash 

#echo  "hello world"

#echo "please input your name:"
#read name
#echo "your name : "$name

#read -p "input your username and passwd: " user passwd 
#echo "your username is : $user ,your passwd is : $passwd"

#read -p "input two operate nums:" x y
#echo "$((x)) + $((y)) = $((x+y))"

#echo "please input filename:"
#read filename 
#test -e $filename && echo "$filename exists" || echo "$filename not exists"

#read -p "inputs two string:" str1 str2
#test $str1 == $str2 && echo "$str1 equals $str2" || echo "$str1 not equals $str2" 
#[ "$str1" == "$str2" ] && echo "$str1 equals $str2" || echo "$str1 not equals $str2" 

#echo "shellcmd : " $0 $# $@

  

#help()
#{
#  echo "this is help cmd!"
#}
#function close()
#{
#  echo "this is close cmd"
#}

#case $1 in                    #接受shell的第一个参数
#  "a")
#    echo "a"
#    help 
#    ;;
#  "b")
#    echo "b"
#    close
#    ;;
#  "c")
#    echo "c"
#    ;;
#  *)
#    echo "other char"
#    ;;
#esac

#print()
#{
#  echo "param 1:$1"
#  echo "param 2:$2"
#}
#print a b

#read value
#if [ "$value"=="Y" ] || [ "$value"=="y" ]; then
#  echo "your input is $value"
#  exit 0
#else 
#  echo "your input is $value"
#fi

while [ "$value" != "close" ]
do 
  read -p "input cmd :" value 
done

for name in p1 p2 p3    # 表示循环3词p1 p2 p3 
do 
  echo "your name is : $name"
done 

read -p "input count:" cnt
total=0
for((i=0;i<=cnt;++i))
do 
  total=$(($total+$i))
done 
  echo "1+2+3... = " $total 

