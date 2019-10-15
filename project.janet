(declare-project
 :name "jhttp"
 :url "https://github.com/scotthaleen/jhttp"
 :repo "https://github.com/scotthaleen/jhttp")

(declare-native
 :name "jhttp"
 :lflags ["-lcurl"]
 :source @["jhttp.c"])

