#!/bin/bash
it=0
homecomp="/home"
while IFS=':' read login pass uid gid user home shell;
do
    if [ $home != "" ];
    then
        # echo -e "dirname $home"
        # echo -e "$home"
        dirna=$(dirname $home)
        # echo -e "$dirna"
        if [ "$dirna" = "$homecomp" ];
        then
            echo -e "[Entry #$it]"
            echo -e "\tlogin=$login"
            echo -e "\tenc_pass=$pass"
            echo -e "\tuid=$uid"
            echo -e "\tgid=$guid"
            echo -e "\tuser_name=$user"
            echo -e "\thome=$home"
            echo -e "\tshell=$shell"
            ((it++))
        fi
    fi
    
done < /etc/passwd

# OPCIONAL: cut -d \: -f 6 /etc/passwd | grep /home
