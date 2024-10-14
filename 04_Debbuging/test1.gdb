set verbose off
set debuginfod enabled on

break main
commands
  silent
end

run 1 12 > /dev/null
break 12

commands
  silent
end
c

watch i if i % 5 == 0
while(i < N - i)
  printf " @@@ N=%d, M=%d, S=%d, i=%d", N, M, S, i
  c
end
