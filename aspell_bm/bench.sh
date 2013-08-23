while read line $a
do
    lw=( $line )
    
    echo -n "${lw[0]}"
    echo -n " "
    echo ${lw[0]}|aspell pipe --encoding utf-8|sed 's/,/\n/g'|grep ':'|cut -f2 -d':'|sed 's/^ //'

done < "kc.txt"
