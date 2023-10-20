(declare-project
  :name "ripemd160"
  :description ```The hash function RIPEMD-160.```
  )

(declare-native
  :name "ripemd160"
  :source @["module.c" "rmd160.c"]
  )
