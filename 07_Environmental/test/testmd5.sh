rhasher_path=$1
echo "aboba" > in.txt
res1=$(echo "Md5 \"in.txt\"" | ${rhasher_path} 2>/dev/null | tail -n 1)
res2=$(echo "aboba" | md5sum | sed "s/\(.*\) -/\1/")
echo $res1
echo $res2
rm in.txt
[[ "$(echo $res1)" == "$(echo $res2)" ]]