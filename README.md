
# jhttp 
[![Actions Status](https://github.com/scotthaleen/jhttp/workflows/janet%20ci/badge.svg)](https://github.com/scotthaleen/jhttp/actions)


Sample [Janet](https://janet-lang.org) module that provides
a simple [libcurl](https://curl.haxx.se/libcurl/c/example.html) wrapper


See [jurl](https://github.com/sepisoad/jurl) for a full featured wrapper of libcurl


## Build

```
jpm clean
jpm build
```

## Test
```
jpm test
```

## Example

```
cat sample.janet | janet -q -e

janet -e '(import build/jhttp :as jhttp)' -e '(print (jhttp/get "https://postman-echo.com/get?foo1=bar1&foo2=bar2"))'
```

```
janet
Janet 1.3.1-944347e  Copyright (C) 2017-2019 Calvin Rose

janet:1:> (import build/jhttp :as http)
nil
janet:2:> (http/get "https://postman-echo.com/get?foo1=bar1&foo2=bar2")
201 bytes retrieved
"{\"args\":{\"foo1\":\"bar1\",\"foo2\":\"bar2\"},\"headers\":{\"x-forwarded-proto\":\"https\",\"host\":\"postman-echo.com\",\"accept\":\"*/*\",\"x-forwarded-port\":\"443\"},\"url\":\"https://postman-echo.com/get?foo1=bar1&foo2=bar2\"}"a
```

## Capabilites
[x] GET <br/>
[ ] POST <br/>
[ ] DELETE <br/>
