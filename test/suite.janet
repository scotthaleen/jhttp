(import build/jhttp :as jhttp)

(print (jhttp/get "https://postman-echo.com/get?foo1=bar1&foo2=bar2"))

