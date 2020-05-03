# TotpCommonCrypto
TOTP Sample Implementation Reference with CommonCrypto(iOS/macOS) and Cpp.
This implementation includes reference implementation of base32(RFC4648) 
and TOTP(RFC6258) using CommonCrypto Library on System Framework in Mac OS X
and iOS.

## How to build and use
This sample implementation is for using on mac OS X development environment.
You can build following steps on Terminal.
```
% mkdir build;cd build
% cmake ..
% make
% ./totpCmd I5R<....DOMAIN SECRETKEY....>UVT
onetime pass: 204147
```

This Domain Secret Key is provided always on QRCode URI format
https://github.com/google/google-authenticator/wiki/Key%20Uri%20Format

## How to hack with Xcode

You can build following steps on Terminal to use Xcode
```
% mkdir build;cd build
% cmake -G Xcode ..
% open totpCmd.xcodeproj
```

## Requirement
* CMake (brew install cmake)
* Xcode

## License
This software is released under MIT License.
Please see LICENSE file.


(c) 2020 Tomoo Mizukami <we_love_blog@yahoo.com>
