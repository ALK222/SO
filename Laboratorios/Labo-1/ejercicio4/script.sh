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
            echo -e "    login=$login"
            echo -e "    enc_pass=$pass"
            echo -e "    uid=$uid"
            echo -e "    gid=$guid"
            echo -e "    user_name=$user"
            echo -e "    home=$home"
            echo -e "    shell=$shell"
            ((it++))
        fi
    fi
    
done < /etc/passwd

# OPCIONAL: cat /etc/passwd | cut -d \: -f 6 | grep /home
