set verbose off
set debuginfod enabled on

break main
commands
  silent
end

run -100 100 3 > /dev/null
break 12

commands
  silent
end
c

watch i
set $j=0
while(i < N - i)
  if(28 <= $j && $j <= 35)
    printf " @@@ N=%d, M=%d, S=%d, i=%d", N, M, S, i
  end
  set $j=$j+1
  c
end
