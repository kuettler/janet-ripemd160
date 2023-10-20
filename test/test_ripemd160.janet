(use ripemd160)

(defn to-hex [msg]
  (string/join (seq [ch :in msg] (string/format "%02x" ch))))

# test cases from https://homes.esat.kuleuven.be/~bosselae/ripemd160.html

(assert (= (to-hex (ripemd160 "")) "9c1185a5c5e9fc54612808977ee8f548b2258d31"))
(assert (= (to-hex (ripemd160 "a")) "0bdc9d2d256b3ee9daae347be6f4dc835a467ffe"))
(assert (= (to-hex (ripemd160 "abc")) "8eb208f7e05d987a9b044a8e98c6b087f15a0bfc"))
(assert (= (to-hex (ripemd160 "message digest")) "5d0689ef49d2fae572b881b123a85ffa21595f36"))
(assert (= (to-hex (ripemd160 "abcdefghijklmnopqrstuvwxyz")) "f71c27109c692c1b56bbdceb5b9d2865b3708dbc"))
